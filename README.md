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
* Split and Join

---

## Usage Modes

* **Standard mode (default):**
  Uses function pointers within the `Brin` struct to allow method-like syntax (`b.concat(&b, suffix)`).
* **BRIN\_LITE mode:**
  Compile with `-DBRIN_LITE` to disable function pointers inside the struct, reducing memory overhead. Functions remain fully usable but must be called directly (`brin_concat(&b, suffix)`).

---

## 🛠 Build & Test

You can use the following `make` commands to build, test, install, and format the library:

| Command            | Description                                                                 |
| ------------------ | --------------------------------------------------------------------------- |
| `make`             | Compiles the static library `libbrin.a` from `brin.o`                       |
| `make test`        | Builds and runs `test.c` linked against `libbrin.a`                         |
| `make BRIN_LITE=1` | Compiles `test.c` in `BRIN_LITE` mode (disables function pointers)          |
| `make install`     | Installs `brin.h` to `${PREFIX}/include` and `libbrin.a` to `${PREFIX}/lib` |
| `make uninstall`   | Removes installed `brin.h` and `libbrin.a`                                  |
| `make format`      | Formats all `.c` and `.h` files using `astyle` with a consistent style      |
| `make clean`       | Cleans all build artifacts: object files, static library, and test binary   |

> Default install prefix is `/usr/local`. You can override it via `make install PREFIX=/your/path`.

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

## ✅ Available Methods/Functions

All examples work in both **standard** and **BRIN_LITE** modes by changing the call syntax.

---

### `brin_new(const char *init)`

Creates a new Brin string initialized with the provided text.

```c
Brin b = brin_new("Hello");
````

---

### `b.insert(&b, index, text)` / `brin_insert(&b, index, text)`

Inserts a string at a given index.

```c
b.insert(&b, 5, " world"); // Hello world
```

---

### `b.concat(&b, suffix)` / `brin_concat(&b, suffix)`

Concatenates a string to the end.

```c
b.concat(&b, "!");
```

---

### `b.contains(&b, substring)` / `brin_contains(&b, substring)`

Checks if the string contains a given substring.

```c
if (b.contains(&b, "world")) {
    printf("Found\n");
}
```

---

### `b.index_of(&b, substring)` / `brin_index_of(&b, substring)`

Returns the index of the first occurrence of the substring.

```c
int index = b.index_of(&b, "world"); // returns e.g. 6
```

---

### `b.equals(&b, other)` / `brin_equals(&b, other)`

Checks if the string equals another string.

```c
if (b.equals(&b, "Hello world!")) {
    printf("Match\n");
}
```

---

### `b.is_empty(&b)` / `brin_is_empty(&b)`

Checks if the string is empty.

```c
if (b.is_empty(&b)) { ... }
```

---

### `b.is_whitespace(&b)` / `brin_is_whitespace(&b)`

Checks if the string only contains whitespace.

```c
if (b.is_whitespace(&b)) { ... }
```

---

### `b.to_upper(&b)` / `brin_to_upper(&b)`

Converts the string to uppercase.

```c
b.to_upper(&b);
```

---

### `b.to_lower(&b)` / `brin_to_lower(&b)`

Converts the string to lowercase.

```c
b.to_lower(&b);
```

---

### `b.trim_start(&b)` / `brin_trim_start(&b)`

Trims leading whitespace.

```c
b.trim_start(&b);
```

---

### `b.trim_end(&b)` / `brin_trim_end(&b)`

Trims trailing whitespace.

```c
b.trim_end(&b);
```

---

### `b.trim(&b)` / `brin_trim(&b)`

Trims both leading and trailing whitespace.

```c
b.trim(&b);
```

---

### `brin_join(const char **array, size_t len, const char *sep)`

Joins an array of strings with a separator.

```c
const char *arr[] = {"This", "is", "joined"};
Brin joined = brin_join(arr, 3, " ");
printf("%s\n", joined.string); // This is joined
```

---

### `b.split(&b, sep)` / `brin_split(&b, sep)`

Splits the string into an array of strings using a delimiter.

```c
char **parts = b.split(&b, " ");
for (size_t i = 0; parts[i]; i++) {
    printf("%s\n", parts[i]);
    free(parts[i]);
}
free(parts);
```

---

### `b.destroy(&b)` / `brin_destroy(&b)`

Frees the memory used by the Brin string.

```c
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