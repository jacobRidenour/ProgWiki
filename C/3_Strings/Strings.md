# Strings

In C, strings are arrays of characters that end with a null-termination character, `\0` - a specific layout of data rather than a type of their own. This character is included in the string's length. Since `char` is a single byte, a C string may be referred to as a null-terminated byte string (NTBS). NTBS function reference [here](https://en.cppreference.com/w/c/string/byte).

```C
char str[] = "hello, world"; // char[13]
```

String literals are implicitly null-terminated. In all other cases, null-termination of a string should be done explicitly. String-associated standard library functions typically null-terminate the result for you (space-allowing).

```C
char str[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
```

Without the `\0` in the above, `str` would be an array of characters and not a string.

Most of the standard library's string functions expect null-terminated strings; assume this unless otherwise explicitly stated. Often, string functions that include an argument for the number of bytes to copy into the output buffer (`n`) are of the format `strn*(dest, src, n)`.

Not including the `\0` typically leads to undefined behavior with string functions. 

## String Functions

Focusing on the standard library, no glibc extensions. 

### `#include <string.h>`

Notice that the `dest, src` pattern is backwards from what you typically see from Unix commands (`src, dest`).

Non-string specific functions (`mem*`) - can be used for generic memory manipulation, and can also be useful for strings (probably why they're in `<string.h>`).

`const`s omitted for space.

| Function                                                                                                                                     | Usage                                                                                                                                                                            |
| -------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `char* strcpy(char* dest, char* src)`<br>`char* strncpy(char* dest, char* src, size_t n)`<br>`void* memcpy(void* dest, void* src, size_t n)` | Copy (first `n` bytes of) `src` into `dest`<br>Note: `strncpy` doesn't null-terminate if `dest` is filled                                                                        |
| `void* memccpy(void* dest, void* src, int c, size_t n)`<sup>C23</sup>                                                                        | Copy <= `n` bytes from `src` to `dest`, stopping at `c`.<br>Return position of `c` in `dest` + 1 or `NULL`                                                                       |
| `void* memmove(void* dest, void* src, size_t n)`                                                                                             | Copy `n` bytes from `src` to `dest`, where `src` and `dest`'s memory may overlap                                                                                                 |
| `void* memset(void* dest, int c, size_t n)`                                                                                                  | Set first `n` bytes in `dest` to `c`                                                                                                                                             |
| `char* strcat(char* dest, char* src)`<br>`char* strncat(char* dest, char* src, size_t n)`                                                    | Append (first `n` bytes of) `src` onto `dest`                                                                                                                                    |
| `char* strdup(char* src)`<br>`char* strndup(char* src, size_t n)`                                                                            | Create a copy of (first `n` bytes of) `src` on the heap, null-terminate and return a pointer to it.                                                                              |
| `size_t strlen (const char* str)`<br>`size_t strnlen (const char* str, size_t n)`                                                            | Returns the length of `str`, not including `\0`<br>`strnlen` returns `0` if `str` is `NULL`, and `n` if `\0` not found in the first `n` bytes of `str`                           |
| `int strcmp(char* s1, char* s2)`<br>`int strncmp(char* s1, char* s2, size_t n)`<br>`int memcmp(void* s1, void* s2, size_t n)`                | Compare (first `n` bytes of) `s1` and `s2`; return 0 if equal, some other value otherwise                                                                                        |
| `int strcoll(char* s1, char* s2)`                                                                                                            | Compare `s1` and `s2` based on the alphabet order (locale) prescribed in `LC_COLLATE` (implementation-defined);<br>`s1 == s2` return 0, `s1 < s2` return <0, `s1 > s2` return >0 |
| `size_t strxfrm(char* dest, char* src, size_t n`                                                                                             | Transform the first `n` bytes of `src` such that pre-transformation comparison with `strcoll`has the same result as comparison with  `strcmp` after transformation.              |
| `char* strchr(char* str, int c)`<br>`void* memchr(void* str, int c, size_t n)`                                                               | Find first occurrence of `c` in (the first `n` bytes of)  `str`, return its address or `NULL`                                                                                    |
| `char* strrchr(char* str, int c)`<br>                                                                                                        | Find last occurrence of `c` in `str`, return its address or `NULL`                                                                                                               |
| `size_t strspn(char* dest, char* src)`                                                                                                       | Returns the length of largest initial span of `dest` that contains `src`                                                                                                         |
| `size_t strcspn(char* dest, char* src)`                                                                                                      | Returns the length of largest initial span of `dest` that does not contain `src`                                                                                                 |
| `char* strpbrk(char* dest, char* src)`                                                                                                       | Returns a pointer to the first character in `dest` that matches any character in `src`                                                                                           |
| `char* strstr(char* str, char* substr)`                                                                                                      | Returns a pointer to the first occurrence of `substr` in `str`                                                                                                                   |
| `char* strtok(char* str, char* delim)`                                                                                                       | Returns a pointer to the first occurrence of `delim` in `str`, having replaced it with `\0`. Subsequent calls with `NULL` for `str` produce further tokens of `str`.             |
| `char* strerror(int errno)`                                                                                                                  | Returns a pointer to the textual description of the provided `errno`                                                                                                             |
### `#include <stdlib.h>`

Conversion to different formats (`ato*` aka ASCII to \*)

| Function                                                                                       | Usage                                                          |
| ---------------------------------------------------------------------------------------------- | -------------------------------------------------------------- |
| `double atof(char* str)`                                                                       | string to float                                                |
| `int atoi(char* str)`<br>`long atol(char* str)`<br>`long long atoll(char* str)`<sup>C99</sup>  | string to (long) int                                           |
| `strtol(char* str)`<br>`strtoll(char* str)`<sup>C99</sup>                                      | string to (long) long                                          |
| `strtoul(char* str)`<br>`strtoull(char* str)`                                                  | string to unsigned (long) long                                 |
| `strtof(char* str)`<sup>C99</sup><br>`strtod(char* str)`<br>`strtold(char* str)`<sup>C99</sup> | string to float / double / long double                         |
| `strfromf()`<sup>C23</sup><br>`strfromd()`<sup>C23</sup><br>`strfroml()`<sup>C23</sup>         | floating-point value to string                                 |
| `strtoimax()`<sup>C99</sup><br>`strtoumax()`<sup>C99</sup>                                     | string to largest (un)signed integer<br>similar to `strto(u)l` |
### `#include <ctype.h>`

Check if a character is... or change a character to...

| Function                           | Usage                                      |
| ---------------------------------- | ------------------------------------------ |
| `isalnum(char* str)`               | returns whether `str` is alphanumeric      |
| `isalpha(char* str)`               | returns whether `str` is alphabetic        |
| `islower(char* str)`               | returns whether `str` is lowercase         |
| `isupper(char* str)`               | returns whether `str` is uppercase         |
| `isdigit(char* str)`               | returns whether `str` is a digit           |
| `isxdigit(char* str)`              | returns whether `str` is a hex digit       |
| `iscntrl(char* str)`               | returns whether `str` is a control char    |
| `isgraph(char* str)`               | returns whether `str` is a graphical char  |
| `isspace(char* str)`               | returns whether `str` is a whitespace char |
| `isblank(char* str)`<sup>C99</sup> | returns whether `str` is a blank char      |
| `isprint(char* str)`               | returns whether `str` is a printing cha r  |
| `ispunct(char* str)`               | returns whether `str` is punctuation char  |
| `tolower(int c)`                   | returns lowercase copy of `c`              |
| `toupper(int c)`                   | returns uppercase copy of `c`              |
