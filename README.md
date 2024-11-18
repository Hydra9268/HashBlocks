# Hash Blocks

![](https://kxmode.com/images/hash-block-cover-artwork.png)

Hash Block: A memory-efficient hierarchical data structure that combines static arrays with dynamic pointers for scalable storage and quick lookups. It's particularly well-suited for structured or sparse datasets like names, addresses, or hierarchical keys.

Hash Blocks offer an effective way to handle hierarchical data with predictable patterns while keeping memory usage low. By blending the strengths of hash tables and hierarchical tries, they strike an excellent balance between scalability, speed, and efficiency.

Check out my [Medium article](https://medium.com/@korval_85759/hierarchical-hash-blocks-a-static-and-dynamic-approach-to-data-storage-fe6597078d0f) for a deeper dive into the concept!

### Purpose of the Code

The code in this repository demonstrates the implementation of Hash Blocks in C, showcasing how this hierarchical data structure efficiently stores and retrieves structured or sparse data. It provides a practical example of the theory, with basic functionality for inserting, searching, and managing keys dynamically within the Hash Block framework.

### Why Hash Blocks Are Different

Traditional hash tables, such as perfect hash tables, and data structures like tries are well-established tools for data storage and retrieval. However, **Hash Blocks** introduce a novel approach that combines the best of these structures while addressing their limitations.

## Examples of a Hash Tables

#### Comparison to Perfect Hash Tables

![](https://kxmode.com/images/prefect-hash-tables-smaller.png)

- **Perfect Hash Tables:**
  - **Strengths:** Direct indexing ensures (`O(1)`) lookup time. Ideal for dense datasets where all possible keys (e.g., `AAA` to `ZZZ`) are used.
  - **Limitations:** Memory-intensive for sparse datasets due to preallocation of all possible keys. Inefficient for hierarchical or dynamic datasets.
- **Hash Blocks:**
  - **Strengths:** Memory-efficient for sparse datasets, as static arrays are only used at predefined levels. Keys are dynamically stored only when needed. Retains (`O(1)`) lookup time at each level.

#### Comparison to Tries

![](https://kxmode.com/images/tries-smaller.png)

- **Tries:**
  - **Strengths:** Excellent for hierarchical or prefix-based data, with predictable traversal for each character. Can adapt to variable-length keys.
  - **Limitations:** Dynamic allocation at every level increases memory fragmentation and lookup overhead, especially for sparse datasets.
- **Hash Blocks:**
  - **Strengths:** Predefined static arrays at the top levels eliminate dynamic memory overhead, while dynamic allocation is limited to the final level. Simplifies implementation for hierarchical data with predictable patterns.

#### Key Advantages of Hash Blocks

![](https://kxmode.com/images/hash-blocks-smaller.png)

1. **Predictable Memory Usage:**
   - Static arrays at higher levels ensure consistent memory allocation, avoiding the fragmentation typical of tries.
   - Dynamic pointers only store what is necessary, making Hash Blocks efficient for sparse or hierarchical datasets.
   
2. **Balance of Static and Dynamic:**
   - Unlike perfect hash tables, which require preallocation of all keys, Hash Blocks dynamically grow only where data exists, reducing waste.
   
3. **Scalability for Real-World Data:**
   - Perfect hash tables struggle with long or complex keys. Tries handle these better but with higher overhead. Hash Blocks provide a middle ground, ideal for applications like name lookups or address storage.

Hash Blocks introduce a new category of hash table, combining the **predictability of static arrays** with the **flexibility of dynamic allocation**. Designed to address inefficiencies in traditional hash tables and tries, Hash Blocks excel in managing structured, hierarchical, or sparse datasets where memory efficiency and scalability are critical.

Instead of growing tall (vertically) like traditional tables or arrays, Hash Blocks expand horizontally, similar to stacking and connecting building blocks to create a structured, scalable foundation. Each hierarchical level serves as a predefined "block," enabling data to flow efficiently across layers without excessive vertical growth. This horizontal approach is the inspiration behind the "block" terminology, highlighting scalability and modularity.

## Features
- **Memory Efficiency**: Predefined static arrays reduce unnecessary allocations.
- **Fast Lookups**: Constant-time (`O(1)`) lookups at each level.
- **Scalable**: Adapts well to sparse datasets or hierarchical data.
- **Flexible**: Handles names, addresses, and other structured keys.

## How It Works
Hash Blocks utilize a hierarchical structure with static arrays at the upper levels and dynamic pointers at the final level. For example:

1. **Level 1:** First letter (A-Z).
2. **Level 2:** Second letter (A, E, I, O, U, Y, or MISC).
3. **Level 3:** Third letter (A-Z).
3. **Level 3 Pointer:** Pointer to dynamically stored data.

**Level 1 Using Alice, Abigail, Anderson.**

The first letter in their names is `A`, so `[0]` represents `A`, indicated by `{...}`.

![](https://kxmode.com/images/hash-block-level-1.png)

**Level 2**

Alice, Abigail, and Anderson don't have a vowel as the second letter, so they are stored at `[6]`, which represents the `misc` (or `default`) bucket.

![](https://kxmode.com/images/hash-block-level-2.png)

**Level 3 and Pointers**

At this level, strings are stored in a `struct` containing a `name` character array and a `next` pointer.

For example, `D` is the third letter in `ANDERSON`, so the name is stored at `[3]`, representing `D`. Meanwhile, both `ALICE` and `ABIGAIL` have `I` as their third letter, so they are stored alphabetically at `[8]`, representing `I`. Since they share this space, `ABIGAIL`'s `next` pointer links to `ALICE`.

![](https://kxmode.com/images/hash-block-level-3-pointers.png)

Print Hash Blocks

The function print_hash_blocks displays a visual representation of how the strings are stored.

![](https://i.imgur.com/CjJPPIx.png)

### Example
For the name "James Smith":
- Level 1: `J`
- Level 2: `A`
- Level 3: `M`
- Level 3 Pointer to `JAMES SMITH`

## Six Reasons Why Hash Blocks Are Awesome!

**1. Memory Efficiency**

In a traditional trie, nodes are created dynamically only for the necessary data, but the use of linked pointers can result in extra memory overhead and slower traversal. Array-based tries take a different approach by allocating a full array, such as 26 slots for A to Z, at every level. While this improves lookup speed, it also wastes memory when dealing with sparse datasets. Hash Blocks, on the other hand, offer a middle ground. By limiting the number of slots at certain levels—for example, grouping vowels and miscellaneous characters into six slots—they significantly reduce memory usage while still ensuring predictable storage.

**2. Predictability and Scalability**

Hash Blocks rely on predefined arrays at higher levels to achieve `O(1)` constant-time lookups, eliminating the need to dynamically traverse linked pointers as in traditional tries. Unlike tries, where the overhead grows with depth, Hash Blocks expand horizontally by adding levels as needed. This design makes them scalable and efficient for both dense and sparse datasets. For instance, adding more levels in a Hash Block exponentially increases storage capacity without a corresponding exponential increase in memory usage, offering a clear advantage over perfect hash tables or array-based tries.

**3. Optimized for Hierarchical Patterns**

Hash Blocks optimize memory usage by restricting even-numbered levels to smaller predefined arrays, such as grouping vowels and miscellaneous characters together. This approach leverages natural patterns often found in hierarchical or linguistic data, like names or addresses. For example, the structure alternates between consonants (26 slots) and vowels plus a misc slot (5+1), creating an efficient balance. Odd-numbered levels, meanwhile, retain a full array for A-Z to ensure sufficient space. This thoughtful design minimizes memory waste while remaining practical for real-world datasets.

**4. Collision Reduction Without Overhead**

Traditional hash tables or perfect hash tables can prevent collisions but often require large amounts of preallocated space, such as reserving slots for all possible combinations from AAA to ZZZ. Hash Blocks take a more efficient approach by combining the structure of a trie with flexible collision handling. Instead of preallocating excessive space, they dynamically allocate linked lists to manage collisions without impacting performance. Additionally, their horizontal expansion with added levels reduces the chance of collisions while keeping memory usage manageable and avoiding exponential growth.

**5. Performance vs. Tries and Hash Tables**

Hash Blocks offer several advantages over both tries and hash tables. Unlike tries, Hash Blocks do away with linked pointers and avoid the memory waste associated with preallocating unnecessary nodes or arrays. They also provide faster lookups by using direct indexing at each level, whereas tries rely on slower pointer dereferencing. Compared to hash tables, Hash Blocks are far more memory-efficient than perfect hash tables and adapt dynamically to sparse or structured datasets. This adaptability helps them avoid the inefficiencies of hash table resizing or dealing with a large number of empty slots.

**6. Real-World Versatility**

Hash Blocks are particularly effective for storing structured, hierarchical, or sparse datasets, such as names, addresses, or categorical data. By combining static arrays for predictable indexing with dynamic storage for keys, they adapt naturally to real-world patterns while ensuring efficient memory usage. This flexibility makes them a practical solution for handling diverse data structures.

## Getting Started

### Prerequisites
- A C compiler (e.g., `clang` or `gcc`)

### Build Instructions
Clone the repository:

```bash
git clone https://github.com/Hydra9268/HashBlocks.git
cd HashBlocks
```

Build the project
```
clang -std=c17 -g -o hashblocks.exe hashblocks.c
```

Run the executable. The arguments can be whatever you wish.
```
.\hashblocks.exe -n apple,banana,grape,watermelon,orange,peach,kiwi -o peach,watermelon,pear,pomegranate,kiwi
```

## Learn More
For a detailed explanation of Hash Blocks, their design, and use cases, check out my [Medium article](https://medium.com/@korval_85759/hierarchical-hash-blocks-a-static-and-dynamic-approach-to-data-storage-fe6597078d0f).