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