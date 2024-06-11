

# Dictionary and Spell Checker

This project is a C implementation of a dictionary and spell-checking program. It is the first project of CSCI2021 in University of Minnesota, Twin Cities. The program allows users to add words to a dictionary, look up words, and perform spell-checking on text files using the dictionary.

## Features

- Start and quit the program.
- Add single or multiple words to the dictionary.
- Look up words in the dictionary.
- Print the contents of the dictionary.
- Load and save the dictionary to/from a text file.
- Spell check a text file using the dictionary.
- Handle command line arguments to specify dictionary and text files for spell checking.

## Files

- `dictionary.c`: Contains the main implementation of the dictionary functions.
- `dictionary.h`: Header file declaring the dictionary functions and data structures.
- `spell_check.c`: Implements the spell-checking functionality.
- `Makefile`: Contains the build rules for compiling the project.

## Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/yourusername/dictionary-spell-checker.git
    cd dictionary-spell-checker
    ```

2. Build the project:

    ```bash
    make
    ```

## Usage

### Running the Program

You can run the program by executing the compiled binary:

```bash
./dictionary
```

### Commands

The program supports the following commands:

- `add word`: Adds a word to the dictionary.
- `lookup word`: Looks up a word in the dictionary.
- `print`: Prints all words in the dictionary.
- `load filename`: Loads a dictionary from a text file.
- `save filename`: Saves the current dictionary to a text file.
- `spell_check filename`: Spell checks a text file using the current dictionary.
- `exit`: Exits the program.

### Example

Here's an example session with the program:

```bash
./dictionary
add apple
add banana
lookup apple
print
save my_dictionary.txt
load my_dictionary.txt
spell_check my_text.txt
exit
```

### Command Line Arguments

You can also specify a dictionary file and a text file to spell check as command line arguments:

```bash
./dictionary my_dictionary.txt my_text.txt
```

## Tests

The project includes a series of tests to ensure the functionality of the program. The tests cover:

- Starting and quitting the program.
- Handling end-of-file (EOF) conditions.
- Managing an empty dictionary.
- Adding and looking up words.
- Dictionary persistence.
- Spell-checking with different dictionaries and files.

