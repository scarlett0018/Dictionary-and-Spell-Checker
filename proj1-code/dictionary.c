#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

dictionary_t *create_dictionary() {
    dictionary_t *dict = malloc(sizeof(dictionary_t));
    if (dict == NULL) {
        return NULL;
    }
    dict->root = NULL;
    dict->size = 0;
    return dict;
}

int dict_insert(dictionary_t *dict, const char *word) {
    // Create a new node
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node == NULL) {
        // Memory allocation failed
        return -1;
    }
    strncpy(new_node->word, word, MAX_WORD_LEN);
    new_node->left = NULL;
    new_node->right = NULL;

    // If the tree is empty, set the new node as the root
    if (dict->root == NULL) {
        dict->root = new_node;
        dict->size = 1;
        return 0;
    }

    // Otherwise, traverse the tree to find the appropriate position to insert
    node_t *current = dict->root;
    while (current) {
        int cmp = strcmp(word, current->word);
        if (cmp == 0) {
            // Word already exists in the dictionary, no need to insert
            // free(new_node);
            return 0;
        } else if (cmp < 0) {
            // Word should be inserted to the left
            if (current->left == NULL) {
                current->left = new_node;
                dict->size++;
                return 0;
            }
            current = current->left;
        } else {
            // Word should be inserted to the right
            if (current->right == NULL) {
                current->right = new_node;
                dict->size++;
                return 0;
            }
            current = current->right;
        }
    }

    return 0;
}

int dict_find(const dictionary_t *dict, const char *query) {
    if (dict == NULL || dict->root == NULL) {
        return 0; // Dictionary is empty or not initialized
    }

    // Traverse the binary search tree to find the word
    node_t *current = dict->root;
    while (current != NULL) {
        int cmp = strcmp(query, current->word);
        if (cmp == 0) {
            return 1; // Word found in the dictionary
        } else if (cmp < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return 0; // Word not found in the dictionary
}


// Function to print words in ascending order
void print_words_in_order(node_t *node) {
    if (node != NULL) {
        // Traverse the left subtree
        print_words_in_order(node->left);

        // Print the word
        printf("%s\n", node->word);

        // Traverse the right subtree
        print_words_in_order(node->right);
    }
}

// Wrapper function to print words in the dictionary in ascending order
void dict_print(const dictionary_t *dict) {
    if (dict == NULL || dict->root == NULL) {
        // printf(" ");
        return;
    }

    print_words_in_order(dict->root);
}


void freeNode(node_t *node) {
    if (node == NULL) {
        return;
    }
    
    freeNode(node->left);
    freeNode(node->right);
    free(node);
}

void dict_free(dictionary_t *dict) {
    freeNode(dict->root);
    dict->root = NULL;
    dict->size = 0;

    free (dict);
}



dictionary_t *read_dict_from_text_file(const char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        return NULL;
    }

    // Create an empty dictionary
    dictionary_t *dict = create_dictionary();
    if (dict == NULL) {
        fclose(file);
        return NULL;
    }

    char word[MAX_WORD_LEN];
    while (fgets(word, MAX_WORD_LEN, file) != NULL) {
        // Remove trailing newline character if present
        size_t len = strlen(word);
        if (len > 0 && word[len - 1] == '\n') {
            word[len - 1] = '\0';
        }

        // Insert the word into the dictionary
        if (dict_insert(dict, word)) {
            fclose(file);
            return NULL;
        }
    }

    fclose(file);
    // dict_free(dict);
    
    return dict;
}

int write_node_to_file(FILE *file, const node_t *node) {
     if (node == NULL) {
        return 1; // Node is NULL, nothing to write
    }

    // Write the word to the file
    fprintf(file, "%s\n", node->word);

    // Recursively write left and right children
    if (!write_node_to_file(file, node->left) || !write_node_to_file(file, node->right)) {
        return 0; // Failed to write children to the file
    }

    return 1; // Successfully wrote the node to the file
}

int write_dict_to_text_file(const dictionary_t *dict, const char *file_name) {
    if (dict == NULL || file_name == NULL) {
        return -1; // Invalid input
    }
    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        return -1; // Failed to open the file
    }

    // Call the recursive function to write the nodes in in-order
    if (!write_node_to_file(file, dict->root)) {
        fclose(file);
        return -1; // Failed to write nodes to the file
    }

    fclose(file);
    return 0; // Successfully wrote the dictionary to the file
}

