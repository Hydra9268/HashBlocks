#ifndef HASHBLOCKS_H
#define HASHBLOCKS_H

// Constants defining the sizes of different levels in the Hash Block's structure
#define FIRST_LEVEL_SIZE 26  // Represents the first letter of names (A-Z)
#define SECOND_LEVEL_SIZE 7  // Represents vowels (A, E, I, O, U, Y) and a default bucket
#define THIRD_LEVEL_SIZE 26  // Represents the third letter of names (A-Z)

// Structure for a linked list node to store names
typedef struct Node {
    char *name;           // Pointer to the name stored as a string
    struct Node *next;    // Pointer to the next node in the case of collisions
} Node;

// Structure for the Hash Block's third-level
typedef struct HashBlock {
    Node *third_level[THIRD_LEVEL_SIZE];  // Array of linked list heads for third-level hashing
} HashBlock;

// Structure for the Hash Block's second-level 
typedef struct HashBlocks {
    HashBlock *second_level[SECOND_LEVEL_SIZE];  // Array of pointers to HashBlock structures
} HashBlocks;

/**
 * Adds a name to the Hash Block
 * 
 * @param input_name The name to add to the structure.
 * @return 0 if the operation is successful, 1 if an error occurs (e.g., invalid input or memory allocation failure).
 */
int add_name(const char *input_name);

/**
 * Searches for a name in the Hash Block.
 * 
 * @param name The name to search for in the structure.
 * @return 0 if the name is found, 1 if the name is not found.
 */
int find_names(const char *name);

/**
 * Prints the current state of the Hash Block.
 * Displays the names stored at each level for visualization and debugging purposes.
 */
void print_hash_blocks();

/**
 * Frees all memory allocated for the Hash Block.
 * Ensures there are no memory leaks by deallocating all nodes, blocks, and arrays.
 */
void free_hash_blocks();

#endif
