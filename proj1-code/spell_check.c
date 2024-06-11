#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "dictionary.h"

#define MAX_CMD_LEN 128

// A helper function to spell check a specific file
// 'file_name': Name of the file to spell check
// 'dict': A dictionary containing correct words

#include <stdlib.h>

int spell_check_file(const char *file_name, const dictionary_t *dict) {
    // Open the file for reading
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        return 0; 
    }

    char word[MAX_WORD_LEN];
    int ch;
    int word_length = 0;

    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch)) {
            // If it's an alphabetic character, add it to the word
            if (word_length < MAX_WORD_LEN - 1) {
                word[word_length++] = (char)tolower(ch);
            }
        } else {
            // Non-alphabetic character, end of word
            if (word_length > 0) {
                word[word_length] = '\0'; // Null-terminate the word
                // Check if the word is in the dictionary
                if (!dict_find(dict, word)) {
                    printf("%s[X] ", word);
                  
                } else {
                    printf("%s ", word);
                }
                word_length = 0;
               
            }
            // Print non-alphabetic characters as they are
            putchar(ch);
        }
    }
    fclose(file);
    return 1;
}

int main(int argc, char **argv) {
     dictionary_t *dict = create_dictionary() ;
    char cmd[MAX_CMD_LEN];
    int success;
    if (argc == 1) {
        // dictionary_t *dict = ;     
    }
    else if(argc==2){
          // Check if two additional command line arguments are provided.
        char *dictionary_file = argv[1];


        // Create a dictionary and read it from the dictionary file.
        // dictionary_t *dict = create_dictionary();
        dictionary_t *second_dict = read_dict_from_text_file(dictionary_file);

        if (second_dict == NULL) {
            printf("Failed to read dictionary from text file\n");
            dict_free(dict);
            return 0; // Exit with an error code.
        } else {
            printf("Dictionary successfully read from text file\n");
            dict_free(dict);
            dict = second_dict;
        }
        // dict_free(dict);
        // return 1;

    }
        else if (argc == 3) {
        // Check if two additional command line arguments are provided.
        char *dictionary_file = argv[1];
        char *check_file = argv[2];

        // Create a dictionary and read it from the dictionary file.
        // dictionary_t *dict = create_dictionary();
        dictionary_t *second_dict = read_dict_from_text_file(dictionary_file);

        if (second_dict == NULL) {
            printf("Failed to read dictionary from text file\n");
            dict_free(dict);
            return 0; // Exit with an error code.
        } else {
            printf("Dictionary successfully read from text file\n");
            dict_free(dict);
            dict = second_dict;
        }

        // Perform spell check on the specified file.
        int result = spell_check_file(check_file, dict);
        if (result == 0) {
            printf("Spell check failed\n");
        }

        // Free memory and exit the program.
        dict_free(dict);
        return 1;
    }
   
    
    

    printf("CSCI 2021 Spell Check System\n");
    printf("Commands:\n");
    printf("  add <word>:              adds a new word to dictionary\n");
    printf("  lookup <word>:           searches for a word\n");
    printf("  print:                   shows all words currently in the dictionary\n");
    printf("  load <file_name>:        reads in dictionary from a file\n");
    printf("  save <file_name>:        writes dictionary to a file\n");
    printf("  check <file_name>: spell checks the specified file\n");
    printf("  exit:                    exits the program\n");

    while (1) {
        printf("spell_check> ");
        if (scanf("%s", cmd) == EOF) {
            printf("\n");
            break;
        }

        if (strcmp("exit", cmd) == 0) {
            break;
        }
        else if (strcmp("add", cmd) == 0) { // insertion
            scanf("%s", cmd);          // read string to insert

            success = dict_insert(dict, cmd);   // call list function
            if (success!=0) {                      // check for success
                printf("insert failed\n");
            }
        }
        else if (strcmp("lookup", cmd)==0) {     // get command
       
            scanf("%s", cmd);   

            int re = dict_find(dict, cmd); // call list function
            if (re==0) {                  // check for success
                printf("'%s' not found\n", cmd);
            } else if(re){
                printf("'%s' present in dictionary\n", cmd);
            }
        }
         else if (strcmp("print", cmd) == 0) {   // print command
            dict_print(dict);
        }
        else if (strcmp("load", cmd)==0) {     // get command
       
            scanf("%s", cmd);   

            dictionary_t *second_dict = read_dict_from_text_file(cmd); // call list function
            if (second_dict==NULL) {                  // check for success
                printf("Failed to read dictionary from text file\n");
            } else {
                printf("Dictionary successfully read from text file\n");
                dict_free(dict);
                dict = second_dict;
            }
        }
        else if (strcmp("save", cmd)==0) {     // get command
       
            scanf("%s", cmd);   

            int re = write_dict_to_text_file(dict, cmd); // call list function
            if (re) {                  // check for success
                printf("Failed to write dictionary to text file\n");
            } else if(!re){
                printf("Dictionary successfully written to text file\n");
            }
        }
        else if (strcmp("check", cmd)==0) {     // get command
       
            scanf("%s", cmd);   

            int re = spell_check_file(cmd,dict); // call list function
            if (re==0) {                  // check for success
                printf("Spell check failed\n");
            } 
        }
        else {
            printf("Unknown command %s\n", cmd);
        }
      
   
    } dict_free(dict);
    return 1;

}
