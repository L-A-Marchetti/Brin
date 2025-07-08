/**
 * @file    brin.h
 * @brief   A minimal C string library offering dynamic memory-safe operations like
 *          insert, concat, trim, join and split, designed for low-footprint environments.
 * @author  Lucas Anatole Marchetti
 *
 * MIT License
 *
 * Copyright (c) 2025 L.A. MARCHETTI
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef BRIN_H
#define BRIN_H

#include <stddef.h>

/**
 * @struct Brin
 * @brief Dynamic string structure optionally including a function pointer table.
 *
 * This structure holds a dynamically allocated string and its length.
 * It optionally includes a set of function pointers implementing
 * operations on the string, acting as an explicit interface.
 *
 * Defining BRIN_LITE disables the function pointers to reduce the
 * memory footprint, useful for constrained environments.
 * All operations remain available as standalone functions.
 */
typedef struct Brin
{
    /**
     * @brief Pointer to the null-terminated string buffer.
     */
    char *string;
    /**
     * @brief Length of the string (excluding the null terminator).
     */
    size_t length;

#ifndef BRIN_LITE
    /**
     * @brief Pointer to function to free the Brin.
     */
    void (*destroy) (struct Brin *b);
    /**
     * @brief Pointer to function to append a C-string.
     */
    void (*concat) (struct Brin *b, const char *suffix);
    /**
     * @brief Pointer to function to check substring containment.
     * @return 1 if contained, 0 otherwise.
     */
    int (*contains) (struct Brin *b, const char *string);
    /**
     * @brief Pointer to function to compare strings.
     * @return 1 if equal, 0 otherwise.
     */
    int (*equals) (struct Brin *b, const char *string);
    /**
     * @brief Pointer to function to find substring index.
     * @return index or -1 if not found.
     */
    int (*index_of) (struct Brin *b, const char *string);
    /**
     * @brief Pointer to function to insert a string at an index.
     */
    void (*insert) (struct Brin *b, int index, const char *string);
    /**
     * @brief Pointer to function to check if string is empty.
     * @return 1 if empty, 0 otherwise.
     */
    int (*is_empty) (struct Brin *b);
    /**
     * @brief Pointer to function to check if string is whitespace only.
     * @return 1 if yes, 0 otherwise.
     */
    int (*is_whitespace) (struct Brin *b);
    /**
     * @brief Pointer to function to convert to lowercase.
     */
    void (*to_lower) (struct Brin *b);
    /**
     * @brief Pointer to function to convert to uppercase.
     */
    void (*to_upper) (struct Brin *b);
    /**
     * @brief Pointer to function to trim leading whitespace.
     */
    void (*trim_start) (struct Brin *b);
    /**
     * @brief Pointer to function to trim trailing whitespace.
     */
    void (*trim_end) (struct Brin *b);
    /**
     * @brief Pointer to function to trim leading and trailing whitespace.
     */
    void (*trim) (struct Brin *b);
    /**
     * @brief Pointer to function to split the string using a separator into a NULL-terminated array of strings.
     */
    char **(*split) (struct Brin *b, const char *sep);
#endif

} Brin;

/**
 * @brief Creates a new Brin instance initialized with the given string.
 *
 * Allocates memory for the string, copies the input string into the newly created Brin,
 * initializes the length field, and sets function pointers if BRIN_LITE mode is not active.
 *
 * @param string The C-string to initialize the Brin with. Must not be NULL.
 * @return A Brin instance containing a copy of the input string.
 *
 * @note This function exits the program with an error if the input string is NULL
 *       or if memory allocation fails.
 */
Brin brin_new(const char *string);

/**
 * @brief Frees the memory used by the string in the Brin instance and resets its state.
 *
 * This function releases the allocated memory for the string inside the given Brin object,
 * sets the string pointer to NULL, and resets the length to zero.
 * If the BRIN_LITE mode is not enabled, it also clears all function pointers to avoid dangling references.
 *
 * @param b Pointer to the Brin instance to destroy.
 */
void brin_destroy(Brin *b);

/**
 * @brief Append a C-string suffix to a Brin string, resizing memory as needed.
 *
 * This function concatenates the null-terminated string `suffix`
 * to the end of the string held in `b`. It reallocates the internal
 * buffer to accommodate the new length, updating the stored length accordingly.
 *
 * @param[in,out] b Pointer to the Brin instance to modify.
 * @param[in] suffix Null-terminated string to append.
 *
 * @pre Both `b` and `suffix` must not be NULL, and `b->string` must be valid.
 *
 * @note The function will exit the program if any input is NULL
 *       or if memory allocation fails.
 */
void brin_concat(Brin *b, const char *suffix);

/**
 * @brief Check if the Brin string contains a given substring.
 *
 * This function searches for the first occurrence of the null-terminated
 * string `string` inside the Brin's internal string.
 *
 * @param[in] b Pointer to the Brin instance to check.
 * @param[in] string Null-terminated substring to search for.
 *
 * @return 1 if the substring is found, 0 otherwise.
 *
 * @pre Both `b` and `string` must not be NULL, and `b->string` must be valid.
 *
 * @note The function will exit the program if any input is NULL.
 */
int brin_contains(Brin *b, const char *string);

/**
 * @brief Compare the Brin string with a null-terminated string for equality.
 *
 * This function checks if the Brin's internal string is exactly equal
 * to the provided null-terminated string `string`.
 *
 * @param[in] b Pointer to the Brin instance.
 * @param[in] string Null-terminated string to compare with.
 *
 * @return 1 if both strings are equal, 0 otherwise.
 *
 * @pre Neither `b`, `b->string`, nor `string` can be NULL.
 *
 * @note The function terminates the program if any input pointer is NULL.
 */
int brin_equals(Brin *b, const char *string);

/**
 * @brief Finds the first occurrence index of a substring within the Brin string.
 *
 * This function searches for the first occurrence of the null-terminated substring
 * `string` inside the Brin's internal string.
 *
 * @param[in] b Pointer to the Brin instance.
 * @param[in] string Null-terminated substring to search for.
 *
 * @return The zero-based index of the first occurrence of `string` inside `b->string`,
 *         or -1 if the substring is not found.
 *
 * @pre Neither `b`, `b->string`, nor `string` can be NULL.
 *
 * @note The function terminates the program if any input pointer is NULL.
 */
int brin_index_of(Brin *b, const char *string);

/**
 * @brief Inserts a substring into the Brin string at a specified index.
 *
 * This function inserts the null-terminated substring `string` into the Brin's
 * internal string at the zero-based position `index`.
 *
 * @param[in,out] b Pointer to the Brin instance.
 * @param[in] index Position at which to insert the substring (0 ≤ index ≤ b->length).
 * @param[in] string Null-terminated substring to insert.
 *
 * @pre Neither `b`, `b->string`, nor `string` can be NULL.
 * @pre `index` must be within the valid range [0, b->length].
 *
 * @note The function will allocate new memory for the combined string, free the
 *       old string, and update the length accordingly.
 * @note The function terminates the program if inputs are invalid or memory allocation fails.
 */
void brin_insert(Brin *b, int index, const char *string);

/**
 * @brief Checks if the Brin string is empty.
 *
 * Returns 1 if the string length is zero, otherwise returns 0.
 *
 * @param[in] b Pointer to the Brin instance.
 *
 * @return 1 if the string is empty, 0 otherwise.
 *
 * @pre Neither `b` nor `b->string` can be NULL.
 * @note The function terminates the program if inputs are invalid.
 */
int brin_is_empty(Brin *b);

/**
 * @brief Checks if the Brin string consists only of whitespace characters.
 *
 * Returns 1 if all characters in the string are whitespace according to
 * the standard C `isspace` function, otherwise returns 0.
 *
 * @param[in] b Pointer to the Brin instance.
 *
 * @return 1 if the string is non-empty and contains only whitespace characters,
 *         0 otherwise.
 *
 * @pre Neither `b` nor `b->string` can be NULL.
 * @note The function terminates the program if inputs are invalid.
 */
int brin_is_whitespace(Brin *b);

/**
 * @brief Converts all characters in the Brin string to lowercase.
 *
 * Modifies the string in-place, converting each character to its lowercase
 * equivalent using the standard C `tolower` function.
 *
 * @param[in,out] b Pointer to the Brin instance.
 *
 * @pre Neither `b` nor `b->string` can be NULL.
 * @note The function terminates the program if inputs are invalid.
 */
void brin_to_lower(Brin *b);

/**
 * @brief Converts all characters in the Brin string to uppercase.
 *
 * Modifies the string in-place, converting each character to its uppercase
 * equivalent using the standard C `toupper` function.
 *
 * @param[in,out] b Pointer to the Brin instance.
 *
 * @pre Neither `b` nor `b->string` can be NULL.
 * @note The function terminates the program if inputs are invalid.
 */
void brin_to_upper(Brin *b);

/**
 * @brief Removes leading whitespace characters from the Brin string.
 *
 * Moves the start pointer past any whitespace characters and shifts the
 * remaining string to the beginning. Then reallocates memory to shrink
 * the buffer to the new trimmed length.
 *
 * @param[in,out] b Pointer to the Brin instance.
 *
 * @pre Neither `b` nor `b->string` can be NULL.
 * @note The function terminates the program if inputs are invalid or
 *       if memory reallocation fails.
 */
void brin_trim_start(Brin *b);

/**
 * @brief Removes trailing whitespace characters from the Brin string.
 *
 * Scans backward from the end of the string, truncates the string
 * at the last non-whitespace character, and reallocates memory
 * to shrink the buffer to the new trimmed length.
 *
 * @param[in,out] b Pointer to the Brin instance.
 *
 * @pre Neither `b` nor `b->string` can be NULL.
 * @note The function terminates the program if inputs are invalid or
 *       if memory reallocation fails.
 */
void brin_trim_end(Brin *b);

/**
 * @brief Removes leading and trailing whitespace characters from the Brin string.
 *
 * Calls brin_trim_end to remove trailing spaces, then brin_trim_start
 * to remove leading spaces, effectively trimming the string on both ends.
 *
 * @param[in,out] b Pointer to the Brin instance.
 */
void brin_trim(Brin *b);

/**
 * @brief Joins an array of C strings into a single Brin, separated by `sep`.
 *
 * @param array  Array of C strings to join.
 * @param length Number of elements in the array.
 * @param sep    Separator string (can be empty, but not NULL).
 * @return Brin  The joined string.
 */
Brin brin_join(const char **array, size_t length, const char *sep);

/**
 * @brief Splits the string inside a Brin object into a NULL-terminated array of strings.
 *
 * This function takes a Brin pointer and a separator string, then splits the Brin's string
 * by occurrences of the separator. It returns a dynamically allocated NULL-terminated array
 * of strings, each string is separately allocated and must be freed by the caller.
 *
 * @param b Pointer to the Brin object containing the string to split.
 * @param sep The separator string used to split the input string.
 *
 * @return A NULL-terminated array of dynamically allocated strings resulting from the split.
 *
 * @note The caller is responsible for freeing each string in the returned array,
 *       as well as the array pointer itself.
 * @note The function will exit with failure if input pointers are NULL or memory allocation fails.
 */
char **brin_split(Brin *b, const char *sep);

#endif // BRIN_H