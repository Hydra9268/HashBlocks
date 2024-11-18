| Using Two-Letter Keys (e.g., `AA`, `AB`, `AC`)          | Three-Letter Keys (e.g., `AAA`, `AAB`, `AAC`)               |
|---------------------------------------------------------|-----------------------------------------------------------|
| A hash table for two-letter keys could use a hash       | A hash table for three-letter keys might extend this idea: |
| function like:                                          |                                                           |
|                                                         |                                                           |
| `hash(key) = 26 × index_of(first_letter) +              | `hash(key) = 26² × index_of(first_letter)`                |
| `index_of(second_letter)`                               | `+ 26 × index_of(second_letter)`                          |
|                                                         | `+ index_of(third_letter)`                                |
|                                                         |                                                           |
| **For `AA`, `AB`, `AC`:**                               | **For `AAA`, `AAB`, `AAC`:**                              |
| - `AA → 26 × 0 + 0 = 0`                                 | - `AAA → 26² × 0 + 26 × 0 + 0 = 0`                        |
| - `AB → 26 × 0 + 1 = 1`                                 | - `AAB → 26² × 0 + 26 × 0 + 1 = 1`                        |
| - `AC → 26 × 0 + 2 = 2`                                 | - `AAC → 26² × 0 + 26 × 0 + 2 = 2`                        |
|                                                         |                                                           |
| This maps each two-letter key to a unique slot in       | This maps each three-letter key to a unique slot in       |
| a table with size `26 × 26 = 676` spaces.               | a table with size `26 × 26 × 26 = 17,576` spaces.         |
