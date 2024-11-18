#include "hashblocks.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Static global variable representing the first level of the hierarchical hash structure.
// Each element corresponds to a letter A-Z (indexed by char_to_index).
HashBlocks *first_level[FIRST_LEVEL_SIZE];

// Forward declarations for internal helper functions.
// These functions are defined later in this file and are used internally within the implementation.

/// Creates and initializes a third-level hash block.
HashBlock* create_hash_block();

/// Creates and initializes a second-level hash structure.
HashBlocks* create_hash_blocks();

/// Maps an uppercase character (A-Z) to its zero-based index.
unsigned int char_to_index(char c);

/// Maps a vowel (A, E, I, O, U, Y) to its corresponding index or a default bucket.
unsigned int vowel_to_index(char c);

/// Creates a new linked list node for storing a name.
Node* create_node(const char *name);

/// Searches for a name in the hierarchical hash structure.
Node* find_name(const char *name);

/// Inserts a node into a sorted linked list while maintaining order.
void insert_sorted(Node **head, Node *new_node);

/// Converts a string to uppercase and validates its content.
int convert_to_upper(const char *input_name, char **output_name);

/**
 * Entry point of the program.
 *
 * Demonstrates the functionality of a hierarchical hash structure for storing and 
 * searching names, with support for dynamic input via command-line arguments.
 * The program performs the following steps:
 *
 * 1. Parses command-line arguments to retrieve names for adding and searching.
 * 2. Adds the specified names to the hierarchical hash structure.
 * 3. Searches for the specified names to demonstrate lookup functionality.
 * 4. Displays the hierarchical structure for debugging and visualization.
 * 5. Cleans up all allocated memory to prevent memory leaks.
 *
 * Command-line Arguments:
 * -n name1,name2,... : A comma-separated list of names to add to the hash structure.
 * -o name1,name2,... : A comma-separated list of names to search for in the structure.
 * 
 * Example Usage:
 * ./hashblock3.exe -n Bill,Jane,Lincoln,Tim -o Jane,Tim
 *
 * Memory Management:
 * - Dynamically allocated memory for the hash structure is freed before program termination.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return 0 on successful execution, or 1 if an error occurs.
 */
int main(int argc, char *argv[]) {

    // Check if there are enough command-line arguments
    // If fewer than two arguments are provided, display usage instructions
    if (argc < 2) {
        printf(
            "\033[96m\nUsage:\033[0m \033[38;2;255;160;122m.\\%s\033[0m \033[38;2;255;140;0m-n\033[0m \033[38;2;210;105;30mname1,name2,...\033[0m \033[38;2;255;140;0m-o\033[0m \033[38;2;210;105;30mname1,name2,...\033[0m\n\n"

            "\033[93mCommand-line Arguments:\033[0m\n"
            "  \033[38;2;255;140;0m-n\033[0m \033[38;2;210;105;30mname1,name2,...\033[0m : A comma-separated list of names to add to the hash structure.\n"
            "  \033[38;2;255;140;0m-o\033[0m \033[38;2;210;105;30mname1,name2,...\033[0m : A comma-separated list of names to search for in the structure.\n\n"

            "\033[93mExample Usage:\033[0m \033[38;2;255;160;122m.\\%s\033[0m \033[38;2;255;140;0m-n\033[0m \033[38;2;210;105;30mBill,Jane,Lincoln,Tim\033[0m \033[38;2;255;140;0m-o\033[0m \033[38;2;210;105;30mJane,Tim\033[0m\n\n",
            "hashblock4.exe", "hashblock4.exe"
        );
        return 1; // Exit the program if arguments are insufficient
    }

    char *add_names = NULL;         // Pointer to hold names to be added (-n argument)
    char *find_names_arg = NULL;    // Pointer to hold names to be searched (-o argument)

    // Parse command-line arguments
    // Loop through all provided arguments and match them with valid switches (-n and -o)
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            add_names = argv[++i]; // Store names following the -n flag
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            find_names_arg = argv[++i]; // Store names following the -o flag
        }
    }

    // Add names to the hash structure
    if (add_names) {
        char *context = NULL;               // Context variable for strtok_s
        char *name = strtok_s(add_names, ",", &context); // Tokenize names using commas
        while (name) {
            if (add_name(name) != 0) {      // Call add_name function for each token
                printf("Failed to add name: %s\n", name); // Handle errors if name addition fails
            }
            name = strtok_s(NULL, ",", &context); // Continue tokenizing the remaining names
        }
    }

    // Search for names in the hash structure
    if (find_names_arg) {
        char *context = NULL;               // Context variable for strtok_s
        char *name = strtok_s(find_names_arg, ",", &context); // Tokenize names using commas
        while (name) {
            if (find_names(name) != 0) {    // Call find_names function for each token
                printf("Name not found: %s\n", name); // Notify user if name is not found
            }
            name = strtok_s(NULL, ",", &context); // Continue tokenizing the remaining names
        }
    }

    // Display the hash block structure
    // Prints the hierarchical organization of names for debugging and visualization
    print_hash_blocks();

    // Free all allocated memory to prevent memory leaks
    // Releases resources used by the hierarchical hash structure
    free_hash_blocks();

    return 0; // Exit the program successfully
}

/**
 * Initializes a new HashBlock.
 *
 * This function allocates memory for a HashBlock structure, which represents 
 * a third-level hash table in the hierarchical hash structure. All pointers in 
 * the third_level array are initialized to NULL to ensure a clean state for 
 * subsequent operations.
 *
 * Memory Management:
 * - The caller is responsible for freeing the memory allocated for the returned 
 *   HashBlock structure to prevent memory leaks.
 *
 * Implementation Detail:
 * - The memset function is used to set all elements of the third_level array 
 *   to NULL, ensuring efficient initialization.
 *
 * @return A pointer to the newly created HashBlock structure, or NULL if 
 *         memory allocation fails.
 */
HashBlock* create_hash_block() {
    HashBlock *block = (HashBlock *)malloc(sizeof(HashBlock));
    memset(block->third_level, 0, sizeof(block->third_level)); // Set all elements to NULL
    return block;
}

/**
 * Initializes a new HashBlocks structure.
 *
 * This function allocates memory for a HashBlocks structure, which represents 
 * a second-level hash table in the hierarchical hash structure. All pointers 
 * within the second-level array are initialized to NULL, ensuring a clean and 
 * predictable state for further operations.
 *
 * Memory Management:
 * - The caller is responsible for freeing the memory allocated for the returned 
 *   HashBlocks structure to prevent memory leaks.
 *
 * @return A pointer to the newly created HashBlocks structure, or NULL if 
 *         memory allocation fails.
 */
HashBlocks* create_hash_blocks() {
    HashBlocks *blocks = (HashBlocks *)malloc(sizeof(HashBlocks));
    for (int i = 0; i < SECOND_LEVEL_SIZE; i++) {
        blocks->second_level[i] = NULL; // Set all elements to NULL
    }
    return blocks;
}

/**
 * Searches for a name in the hierarchical hash structure and displays the result.
 *
 * This function takes an input name, converts it to uppercase for consistent 
 * lookup, and searches for it in the hierarchical hash structure. If the name 
 * is found, the function prints "Found" along with the name. If the name is not 
 * found, it prints "Not Found" and returns an error code.
 *
 * - The name is converted to uppercase using convert_to_upper for consistency.
 * - The search is performed using the find_name function, which locates the 
 *   node in the hash structure.
 *
 * Memory Management:
 * - A temporary uppercase version of the name is dynamically allocated and 
 *   freed within this function.
 *
 * @param input_name The name to search for in the hash structure.
 * @return 0 if the name is found, or 1 if the name is not found or an error occurs.
 */
int find_names(const char *input_name) {
    char *name = NULL;

    // Convert to uppercase characters
    if (convert_to_upper(input_name, &name) != 0) {
        return 1;
    }

    Node *result = find_name(name);

    if (result == NULL) {
        printf("Not Found: %s\n", input_name);
        free(name);
        return 1;
    }

    printf("Found: %s\n", result->name);
    free(name);
    return 0;
}

/**
 * Maps a character to an index (A-Z).
 *
 * This function converts an uppercase alphabetical character ('A'-'Z') into its 
 * corresponding zero-based index (0-25). The mapping is calculated by subtracting 
 * the ASCII value of 'A' from the ASCII value of the input character.
 *
 * Assumption:
 * - The input character c is expected to be an uppercase letter ('A'-'Z').
 * - No validation is performed to check if the input is within the valid range.
 *
 * Usage:
 * This mapping is commonly used to index arrays or hash tables based on characters.
 *
 * @param c The character to map (assumed to be uppercase).
 * @return The zero-based index corresponding to the character (0-25).
 */
unsigned int char_to_index(char c) {
    return c - 'A';
}

/**
 * Maps a vowel or default character to an index.
 *
 * This function takes a character as input and returns a corresponding index 
 * for vowels ('A', 'E', 'I', 'O', 'U', 'Y') or a default bucket for any other character.
 * The mapping is used for organizing items into a hash structure based on the 
 * second-level categorization by vowels.
 *
 * - Each vowel is assigned a unique index (0-5).
 * - Any character that is not one of the defined vowels is mapped to the default bucket (index 6).
 *
 * @param c The character to map (assumed to be uppercase).
 * @return The index corresponding to the vowel or the default bucket (0-6).
 */
unsigned int vowel_to_index(char c) {
    switch (c) {
        case 'A': return 0;
        case 'E': return 1;
        case 'I': return 2;
        case 'O': return 3;
        case 'U': return 4;
        case 'Y': return 5;
        default: return 6; // Default bucket
    }
}

/**
 * Creates a new linked list node for storing a name.
 *
 * This function allocates memory for a new Node structure, initializes it with 
 * the provided name, and sets the next pointer to NULL. The name is dynamically 
 * duplicated using _strdup to ensure the new node has its own copy.
 *
 * - If memory allocation for the Node or its name fails, an error message is 
 *   printed, and NULL is returned to indicate failure.
 * - The caller is responsible for freeing the allocated memory for both the Node 
 *   and its name when the node is no longer needed.
 *
 * @param name The name to be stored in the new node.
 * @return A pointer to the newly created Node, or NULL if memory allocation fails.
 */
Node* create_node(const char *name) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) {
        printf("Memory allocation failed for Node\n");
        return NULL;
    }
    new_node->name = _strdup(name);
    if (!new_node->name) {
        printf("Memory allocation failed for name\n");
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

/**
 * Adds a name to the hierarchical hash structure.
 *
 * This function processes an input name, validates it, converts it to uppercase,
 * and determines the appropriate bucket in the three-level hierarchical hash table.
 * The name is then inserted into a sorted linked list at the third level.
 *
 * - The first-level index is determined by the first character of the name.
 * - The second-level index is determined by the first vowel in the name.
 * - The third-level index is determined by the third character of the name.
 *
 * If the necessary levels or blocks in the hierarchy do not exist, they are
 * initialized dynamically before the insertion.
 *
 * @param input_name The name to be added to the hash structure.
 * @return 0 on success, or 1 on failure (e.g., invalid input or memory issues).
 */
int add_name(const char *input_name) {
    char *name = NULL;

    // Convert to uppercase characters
    if (convert_to_upper(input_name, &name) != 0) {
        return 1;
    }

    // Calculate indices for hierarchical hashing
    unsigned int first_index = char_to_index(name[0]);
    unsigned int second_index = vowel_to_index(name[1]);
    unsigned int third_index = char_to_index(name[2]);

    // Initialize levels if necessary
    if (first_level[first_index] == NULL) {
        first_level[first_index] = create_hash_blocks();
    }
    if (first_level[first_index]->second_level[second_index] == NULL) {
        first_level[first_index]->second_level[second_index] = create_hash_block();
    }

    // Insert the name into the third-level linked list
    HashBlock *block = first_level[first_index]->second_level[second_index];
    if (block->third_level[third_index] == NULL) {
        block->third_level[third_index] = create_node(name);
    } else {
        insert_sorted(&block->third_level[third_index], create_node(name));
    }

    free(name); // Free the temporary copy
    return 0;
}

/**
 * Searches for a name in the hierarchical hash structure.
 *
 * This function looks up a name in the three-level hierarchical hash table 
 * using its indices at each level:
 * - First-level index is determined by the first character of the name.
 * - Second-level index is determined by the first vowel in the name.
 * - Third-level index is determined by the third character of the name.
 *
 * It traverses the corresponding linked list in the third-level hash block 
 * to find a node with a matching name. If found, it returns a pointer to the 
 * node. If not found or if any level is missing, the function returns NULL.
 *
 * @param name The name to search for in the hash structure.
 * @return A pointer to the Node containing the name, or NULL if not found.
 */
Node* find_name(const char *name) {
    int first_index = char_to_index(name[0]);
    int second_index = vowel_to_index(name[1]);
    int third_index = char_to_index(name[2]);

    if (first_level[first_index] == NULL) return NULL;
    if (first_level[first_index]->second_level[second_index] == NULL) return NULL;

    HashBlock *block = first_level[first_index]->second_level[second_index];
    Node *current = block->third_level[third_index];
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/**
 * Inserts a node into a sorted linked list while maintaining the sort order.
 *
 * This function takes a pointer to the head of a linked list and a new node to insert.
 * It finds the appropriate position in the list for the new node based on its name 
 * field (alphabetical order) and inserts it in such a way that the list remains sorted.
 *
 * - If the list is empty or the new node's name is smaller than the head's name,
 *   the new node becomes the new head.
 * - Otherwise, the function traverses the list to find the correct position for insertion.
 *
 * @param head A pointer to the head of the linked list.
 * @param new_node The new node to be inserted into the list.
 */
void insert_sorted(Node **head, Node *new_node) {
    if (*head == NULL || strcmp((*head)->name, new_node->name) > 0) {
        new_node->next = *head;
        *head = new_node;
        return;
    }

    Node *current = *head;
    while (current->next != NULL && strcmp(current->next->name, new_node->name) < 0) {
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
}

/**
 * Converts a given string to uppercase while validating its content.
 *
 * This function takes an input string, validates that it meets the required 
 * criteria (non-NULL, at least 3 characters, and only alphabetic characters),
 * and converts all its characters to uppercase. The resulting string is returned 
 * to the caller via an output pointer. If any validation fails, an error message 
 * is printed, and the function returns an error code.
 *
 * @param input_name The input string to be validated and converted.
 * @param output_name A pointer to a string where the converted uppercase string 
 *                    will be stored. Memory is dynamically allocated and must
 *                    be freed by the caller.
 * @return 0 on success, or 1 on failure (e.g., invalid input or memory allocation issues).
 */
int convert_to_upper(const char *input_name, char **output_name) {
    // Validate input to ensure it is non-NULL and has at least 3 characters
    if (input_name == NULL || strlen(input_name) < 3) {
        printf("Name must have at least 3 characters: %s\n", input_name);
        return 1; // Return an error if input is invalid
    }

    // Create a mutable copy of the input string for processing
    char *name = _strdup(input_name);
    if (name == NULL) {
        printf("Memory allocation failed.\n");
        return 1; // Return an error if memory allocation fails
    }

    // Loop through each character of the string to convert it to uppercase
    for (int i = 0; i < strlen(name); i++) {
        // Check if the character is alphabetical
        if (isalpha((unsigned char)name[i])) {
            name[i] = toupper(name[i]); // Convert to uppercase
        } else {
            // If the character is invalid, print an error, free memory, and exit
            printf("Invalid character in name: %s\n", input_name);
            free(name); // Avoid memory leaks
            return 1;
        }
    }

    // Pass the converted uppercase string back to the caller via the output pointer
    *output_name = name;
    return 0; // Return success
}

/**
 * Frees all allocated memory for the hierarchical hash structure.
 *
 * This function traverses the entire hierarchical hash table and deallocates 
 * all dynamically allocated memory at each level:
 * - Third level: Frees all nodes in the linked lists and their associated names.
 * - Second level: Frees all hash blocks.
 * - First level: Frees the memory for the first-level array of hash blocks.
 *
 * This ensures that no memory leaks occur and that all resources used by the 
 * hierarchical hash structure are properly released.
 *
 * Note: This function should be called before the program terminates to clean 
 * up memory allocated for the hash structure.
 */
void free_hash_blocks() {
    for (unsigned int i = 0; i < FIRST_LEVEL_SIZE; i++) {
        if (first_level[i] != NULL) {
            for (unsigned int j = 0; j < SECOND_LEVEL_SIZE; j++) {
                if (first_level[i]->second_level[j] != NULL) {
                    HashBlock *block = first_level[i]->second_level[j];
                    for (unsigned int k = 0; k < THIRD_LEVEL_SIZE; k++) {
                        Node *current = block->third_level[k];
                        while (current != NULL) {
                            Node *tmp = current;
                            current = current->next;
                            free(tmp->name); // Free the name string
                            free(tmp);       // Free the node
                        }
                    }
                    free(block); // Free the second-level hash block
                }
            }
            free(first_level[i]); // Free the first-level hash block
        }
    }
}

/**
 * Prints a visual representation of the hierarchical hash structure.
 *
 * This function traverses the three levels of the hierarchical hash table and 
 * prints the contents of each level, starting from the first level down to the 
 * third level. Each level is labeled for clarity:
 * - The first level uses alphabetical indices (A-Z).
 * - The second level uses vowels (A, E, I, O, U, Y).
 * - The third level uses alphabetical indices (A-Z).
 *
 * For each entry in the hash structure, the function prints the names stored 
 * in the third-level linked lists. If a level is empty, it is skipped.
 *
 * This function is primarily used for debugging or visualization purposes.
 */
void print_hash_blocks() {
    printf("\n");
    for (unsigned int i = 0; i < FIRST_LEVEL_SIZE; i++) {
        if (first_level[i] != NULL) {
            printf("First Level [%c]:\n", 'A' + i);
            for (unsigned int j = 0; j < SECOND_LEVEL_SIZE; j++) {
                if (first_level[i]->second_level[j] != NULL) {
                    // Determine the label for the second level
                    const char *label;
                    switch (j) {
                        case 0: label = "A"; break;
                        case 1: label = "E"; break;
                        case 2: label = "I"; break;
                        case 3: label = "O"; break;
                        case 4: label = "U"; break;
                        case 5: label = "Y"; break;
                        default: label = "Default"; break;
                    }
                    printf("  Second Level [%s]:\n", label);
                    HashBlock *block = first_level[i]->second_level[j];
                    for (unsigned int k = 0; k < THIRD_LEVEL_SIZE; k++) {
                        if (block->third_level[k] != NULL) {
                            printf("    Third Level [%c]:\n", 'A' + k);
                            Node *current = block->third_level[k];
                            while (current != NULL) {
                                printf("      Name: %s\n", current->name);
                                current = current->next;
                            }
                        }
                    }
                }
            }
        }
    }
}
