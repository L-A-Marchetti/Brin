# 🌿 Brin

**A minimal C string library offering dynamic memory-safe operations like insert, concat, trim, join, and split, designed for low-footprint environments.**

---

## Overview

Brin is a lightweight, efficient, and safe C string library designed to provide common string operations while ensuring memory safety through dynamic allocation management. It is ideal for embedded or resource-constrained systems where performance and memory footprint matter.

---

## Key Features

* Dynamic, memory-safe string manipulation
* String insertion and concatenation with automatic resizing
* Substring search and equality comparison
* Whitespace trimming (start, end, or both)
* Case conversion (to lower and upper)
* Checks for emptiness and whitespace-only content

---

## Usage Modes

* **Standard mode (default):**
  Uses function pointers within the `Brin` struct to allow method-like syntax (`b.concat(&b, suffix)`).
* **BRIN\_LITE mode:**
  Compile with `-DBRIN_LITE` to disable function pointers inside the struct, reducing memory overhead. Functions remain fully usable but must be called directly (`brin_concat(&b, suffix)`).

---

## Basic Usage Example

```c
Brin b = brin_new("Hello");
b.concat(&b, ", world!");
b.insert(&b, 5, " brave");
if (b.contains(&b, "world")) {
    printf("Contains 'world'\n");
}
b.trim(&b);
b.to_upper(&b);
printf("Result: %s\n", b.string);
b.destroy(&b);
```

---

## Why Choose Brin?

* **Minimal and focused:** Small codebase tailored for constrained environments.
* **Memory-safe:** Prevents null pointer and memory allocation errors.
* **Flexible:** Choose between method-like calls or direct function usage via the `BRIN_LITE` flag.
* **Versatile:** Covers essential string operations without heavy dependencies.

---

## License

MIT License