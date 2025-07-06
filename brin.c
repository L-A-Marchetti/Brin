/**
 * @file    brin.c
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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
#endif

} Brin;

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
void brin_concat(Brin *b, const char *suffix)
{
    if (!b || !b->string || !suffix)
    {
        fprintf(stderr, "Error: one of the input is null\n");
        exit(EXIT_FAILURE);
    }
    size_t suffix_len = strlen(suffix);
    size_t new_length = b->length + suffix_len;
    char *new_string = realloc(b->string, new_length + 1);
    if (!new_string)
    {
        fprintf(stderr, "Error: memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    b->string = new_string;
    strcat(b->string, suffix);
    b->length = new_length;
}

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
int brin_contains(Brin *b, const char *string)
{
    if (!b || !b->string || !string)
    {
        fprintf(stderr, "Error: one of the input is null\n");
        exit(EXIT_FAILURE);
    }
    return strstr(b->string, string) != NULL;
}

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
int brin_equals(Brin *b, const char *string)
{
    if (!b || !b->string || !string)
    {
        fprintf(stderr, "Error: one of the inputs is null\n");
        exit(EXIT_FAILURE);
    }
    return strcmp(b->string, string) == 0;
}

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
int brin_index_of(Brin *b, const char *string)
{
    if (!b || !b->string || !string)
    {
        fprintf(stderr, "Error: one of the input is null\n");
        exit(EXIT_FAILURE);
    }
    char *index = strstr(b->string, string);
    if (index) return (int)(index - b->string);
    return -1;
}

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
void brin_insert(Brin *b, int index, const char *string)
{
    if (!b || !b->string || !string)
    {
        fprintf(stderr, "Error: one of the inputs is null\n");
        exit(EXIT_FAILURE);
    }
    if (index < 0 || index > (int)b->length)
    {
        fprintf(stderr, "Error: invalid index position\n");
        exit(EXIT_FAILURE);
    }

    size_t insert_len = strlen(string);
    size_t new_length = b->length + insert_len;

    char *new_string = malloc(new_length + 1);
    if (!new_string)
    {
        fprintf(stderr, "Error: memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    memcpy(new_string, b->string, index);
    memcpy(new_string + index, string, insert_len);
    memcpy(new_string + index + insert_len, b->string + index,
           b->length - index);
    new_string[new_length] = '\0';

    free(b->string);
    b->string = new_string;
    b->length = new_length;
}

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
int brin_is_empty(Brin *b)
{
    if (!b || !b->string)
    {
        fprintf(stderr, "Error: one of the inputs is null\n");
        exit(EXIT_FAILURE);
    }
    return b->length == 0;
}

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
int brin_is_whitespace(Brin *b)
{
    if (!b || !b->string)
    {
        fprintf(stderr, "Error: one of the inputs is null\n");
        exit(EXIT_FAILURE);
    }
    if (b->length == 0) return 0;
    for (size_t i = 0; i < b->length; ++i)
    {
        if (!isspace((unsigned char)b->string[i])) return 0;
    }
    return 1;
}

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
void brin_to_lower(Brin *b)
{
    if (!b || !b->string)
    {
        fprintf(stderr, "Error: one of the inputs is null\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < b->length; ++i)
    {
        b->string[i] = tolower((unsigned char)b->string[i]);
    }
}

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
void brin_to_upper(Brin *b)
{
    if (!b || !b->string)
    {
        fprintf(stderr, "Error: one of the inputs is null\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < b->length; ++i)
    {
        b->string[i] = toupper((unsigned char)b->string[i]);
    }
}

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
void brin_trim_start(Brin *b)
{
    if (!b || !b->string)
    {
        fprintf(stderr, "Error: input is null\n");
        exit(EXIT_FAILURE);
    }

    char *start = b->string;
    while (*start && isspace((unsigned char)*start))
        start++;

    size_t new_len = strlen(start);
    memmove(b->string, start, new_len + 1);
    char *new_str = realloc(b->string, new_len + 1);
    if (!new_str)
    {
        fprintf(stderr, "Error: realloc failed\n");
        exit(EXIT_FAILURE);
    }

    b->string = new_str;
    b->length = new_len;
}

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
void brin_trim_end(Brin *b)
{
    if (!b || !b->string)
    {
        fprintf(stderr, "Error: input is null\n");
        exit(EXIT_FAILURE);
    }

    char *end = b->string + b->length - 1;
    while (end >= b->string && isspace((unsigned char)*end))
        end--;

    size_t new_len = (size_t)(end - b->string + 1);
    b->string[new_len] = '\0';

    char *new_str = realloc(b->string, new_len + 1);
    if (!new_str)
    {
        fprintf(stderr, "Error: realloc failed\n");
        exit(EXIT_FAILURE);
    }

    b->string = new_str;
    b->length = new_len;
}

/**
 * @brief Removes leading and trailing whitespace characters from the Brin string.
 *
 * Calls brin_trim_end to remove trailing spaces, then brin_trim_start
 * to remove leading spaces, effectively trimming the string on both ends.
 *
 * @param[in,out] b Pointer to the Brin instance.
 */
void brin_trim(Brin *b)
{
    brin_trim_end(b);
    brin_trim_start(b);
}

/**
 * @brief Frees the memory used by the string in the Brin instance and resets its state.
 *
 * This function releases the allocated memory for the string inside the given Brin object,
 * sets the string pointer to NULL, and resets the length to zero.
 * If the BRIN_LITE mode is not enabled, it also clears all function pointers to avoid dangling references.
 *
 * @param b Pointer to the Brin instance to destroy.
 */
void brin_destroy(Brin *b)
{
    if (b && b->string) free(b->string);
    b->string = NULL;
    b->length = 0;
#ifndef BRIN_LITE
    b->destroy = NULL;
    b->concat = NULL;
    b->contains = NULL;
    b->equals = NULL;
    b->index_of = NULL;
    b->insert = NULL;
    b->is_empty = NULL;
    b->is_whitespace = NULL;
    b->to_lower = NULL;
    b->to_upper = NULL;
    b->trim_start = NULL;
    b->trim_end = NULL;
    b->trim = NULL;
#endif
}

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
Brin brin_new(const char *string)
{
    if (!string)
    {
        fprintf(stderr, "Error: null string input\n");
        exit(EXIT_FAILURE);
    }
    Brin b;
    b.length = strlen(string);
    b.string = malloc(b.length + 1);
    if (!b.string)
    {
        fprintf(stderr, "Error: memory allocation\n");
        exit(EXIT_FAILURE);
    }
    strcpy(b.string, string);
#ifndef BRIN_LITE
    b.destroy = brin_destroy;
    b.concat = brin_concat;
    b.contains = brin_contains;
    b.equals = brin_equals;
    b.index_of = brin_index_of;
    b.insert = brin_insert;
    b.is_empty = brin_is_empty;
    b.is_whitespace = brin_is_whitespace;
    b.to_lower = brin_to_lower;
    b.to_upper = brin_to_upper;
    b.trim_start = brin_trim_start;
    b.trim_end = brin_trim_end;
    b.trim = brin_trim;
#endif
    return b;
}

int main(void)
{
#ifndef BRIN_LITE
    Brin txt = brin_new("");

    printf("Brin instance weight: %lldB\n", sizeof(txt));

    if (txt.is_empty(&txt)) printf("True\n");
    else printf("False\n");

    txt.insert(&txt, 0, "          ");

    if (txt.is_whitespace(&txt)) printf("True\n");
    else printf("False\n");

    txt.insert(&txt, 5, "This Text Is Capitalized");
    printf("%s\n", txt.string);

    txt.to_lower(&txt);
    printf("%s\n", txt.string);

    txt.to_upper(&txt);
    printf("%s\n", txt.string);

    txt.trim_start(&txt);
    printf("trimmed start:%s\n", txt.string);

    txt.trim_end(&txt);
    printf("%s:trimmed end\n", txt.string);

    txt.destroy(&txt);

    Brin msg = brin_new("Bonjour");

    printf("Index of 'jour' in 'Bonjour': %d\n",
           msg.index_of(&msg, "jour"));

    msg.concat(&msg, " Lucas");
    msg.concat(&msg, " comment ca va ?");
    printf("Hello, World + %s\n", msg.string);

    if (msg.contains(&msg,
                     "Lucas")) printf("Lucas is contained in the message\n");
    else printf("Lucas is not contained in the message\n");
    if (msg.contains(&msg,
                     "Mathias")) printf("Mathias is contained in the message\n");
    else printf("Mathias is not contained in the message\n");

    if (msg.equals(&msg, "Bonjour Lucas comment ca va ?"))
        printf("Messages are equals\n");
    else printf("Messages aren't equals\n");

    msg.insert(&msg, 7, " Mathias et");

    printf("%s\n", msg.string);

    msg.destroy(&msg);
#else
    Brin txt = brin_new("");

    printf("Lite Brin instance weight: %zuB\n", sizeof(txt));

    printf("%s\n", brin_is_empty(&txt) ? "True" : "False");

    brin_insert(&txt, 0, "          ");

    printf("%s\n", brin_is_whitespace(&txt) ? "True" : "False");

    brin_insert(&txt, 5, "This Text Is Capitalized");
    printf("%s\n", txt.string);

    brin_to_lower(&txt);
    printf("%s\n", txt.string);

    brin_to_upper(&txt);
    printf("%s\n", txt.string);

    brin_trim_start(&txt);
    printf("trimmed start:%s\n", txt.string);

    brin_trim_end(&txt);
    printf("%s:trimmed end\n", txt.string);

    brin_destroy(&txt);

    Brin msg = brin_new("Bonjour");

    printf("Index of 'jour' in 'Bonjour': %d\n",
           brin_index_of(&msg, "jour"));

    brin_concat(&msg, " Lucas");
    brin_concat(&msg, " comment ca va ?");
    printf("Hello, World + %s\n", msg.string);

    printf("%s\n", brin_contains(&msg, "Lucas") ?
           "Lucas is contained in the message" :
           "Lucas is not contained in the message");

    printf("%s\n", brin_contains(&msg, "Mathias") ?
           "Mathias is contained in the message" :
           "Mathias is not contained in the message");

    printf("%s\n", brin_equals(&msg, "Bonjour Lucas comment ca va ?") ?
           "Messages are equals" :
           "Messages aren't equals");

    brin_insert(&msg, 7, " Mathias et");

    printf("%s\n", msg.string);

    brin_destroy(&msg);
#endif
    return 0;
}