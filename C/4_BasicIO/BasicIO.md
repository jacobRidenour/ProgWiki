# Basic Input and Output

Most of what you'll typically need for I/O is in `<stdio.h>`. Reference [here](https://en.cppreference.com/w/c/io).

For functions in this file, `const`s and `restrict`s omitted for space.

## File I/O

The pattern for handling files is similar to memory allocation's "one malloc, one free" - one open, one close.

`FILE` structs are a handle to a stream of a data (a file, the terminal, a network socket). Their structure is implementation-defined, and opaque to the standard library. Besides stream handling, `FILE` typically buffers I/O operations (fewer syscalls), tracks its error status (`ferror()`), and tracks its position in the stream.

`<stdio.h>` predefines 3 standard `FILE*` streams: `stdin`, `stdout`, `stderr`.

**General file access**

Several modes are supported when opening streams:

| Mode   | Effect              | If file exists   | If file doesn't exist |
| ------ | ------------------- | ---------------- | --------------------- |
| `"r"`  | Open for reading    | Read from start  | Fail to open          |
| `"w"`  | Open for writing    | Destroy contents | Create it             |
| `"a"`  | Open for appending  | Write to the end | Create it             |
Add `+` to set to update mode, which allows for both reading and writing. Add `x` to `w` modes to force failure if file exists<sup>C11</sup>.

| Function                                                       | Usage                                                                                                                                                                                                                                                                                                  |
| -------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `FILE* fopen(char* fn, char* mode)`                            | Open the file `fn`, return pointer to stream                                                                                                                                                                                                                                                           |
| `FILE* freopen(char* fn, char* mode, FILE* stream)`            | Close `fn`, ignoring errors, attempt to open `fn`;<br>if `fn` is `NULL`, attempt to reopen file associated with `stream`                                                                                                                                                                               |
| `int fclose(FILE* stream)`                                     | Close `stream`, disassociate its buffers with the file;<br>Return `0` on success, else `EOF`                                                                                                                                                                                                           |
| `int fflush(FILE* stream)`                                     | Write unwritten data from buffer to output device;<br>if `stream` is `NULL`, flush all open output streams                                                                                                                                                                                             |
| `int setvbuf(FILE* stream, char* buff, int mode, size_t size)` | Change mode of `stream` to `mode`, which is one of 3 implementation-defined values: `_IOFBF` (full buffering), `_IOLBF` (line buffering), `_IONBF` (no buffering);<br>if `buff` is `NULL`, resize internal buffer to `size`;<br>else set `stream` to use `size`-sized `buff`<br>Returns `0` on success |
| `void setbuf(FILE* stream, char* buff)`                        | Sets `stream`'s internal buffer, should be at least `BUFSIZ` in length<br>If `buff` is `NULL`, == `setvbuf(stream, NULL, _IONBF, 0)`<br>else == `setvbuc(stream, buff, _IOFBF, BUFSIZ)`                                                                                                                |

**Unformatted I/O**

Reading (`*get*`)

| Function                                              | Usage                                                                                                                                        |
| ----------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------- |
| `int fgetc(FILE* stream)`<br>`int getc(FILE* stream)` | Read a char from `stream`<br>else return `EOF`                                                                                               |
| `char* fgets(char* str, int n, FILE* stream)`         | Read up to `n-1` chars from `stream`;<br>place them in `str` and null-terminate.<br>Stop at newline (put in `str`) or `EOF`                  |
| `int getchar()`                                       | Read a char from `stdin`<br>== `getc(stdin)`                                                                                                 |
| `char* gets_s(char* str, rsize_t n)`                  | Read a string from `stdin`;<br>place it in `str`<br><sub>formerly `gets`, removed for being unsafe</sub><br><sub>not included in glibc</sub> |

Writing (`*put*`)

| Function                                                              | Usage                                                                                                                                |
| --------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------ |
| `int fputc(int ch, FILE* stream)`<br>`int putc(int ch, FILE* stream)` | Write `ch` to `stream`, return it on success;<br>else return `EOF`                                                                   |
| `int fputs(char* str, FILE* stream)`                                  | Write `str` to  `stream`; return >=0 on success;<br>else return `EOF`                                                                |
| `int putchar(int ch)`                                                 | Write `ch` to `stdout`, return it on success;<br>else return `EOF`                                                                   |
| `int puts(char* str)`                                                 | Write `str` + `\n` to `stdout`;`\0` not written;<br>return >=0 on success, else return `EOF`                                         |
| `int ungetc(int ch, FILE* stream)`                                    | Write `ch` into `stream`'s input buffer;<br>multiple calls in a row may fail;<br>effects discarded by stream repositioning functions |

**Formatted I/O**

Reading (`*scan*`)

| Function                                      | Usage              |
| --------------------------------------------- | ------------------ |
| `int scanf(char* format, ...)`                | Read from `stdin`  |
| `int fscanf(FILE* stream, char* format, ...)` | Read from `stream` |
| `int sscanf(char* buff, char* format, ...)`   | Read from `buff`   |
`v`-prepended versions of these functions take `va_list` (variadic functions), letting the list of args be populated at runtime instead of compile time.

Writing (`*print*`)

| Function                                                       | Usage                                                                       |
| -------------------------------------------------------------- | --------------------------------------------------------------------------- |
| `int printf(char* format, ...)`                                | Write to `stdout`                                                           |
| `int fprintf(FILE* stream, char* format, ...)`                 | Write to `stream`                                                           |
| `int sprintf(char* buff, char* format, ...)`                   | Write to `buff`                                                             |
| `int snprintf(char* buff, size_t buffsize, char* format, ...)` | Write to `buff`, writing t most `buffsize`-1 bytes, and null-terminating it |
`v`-prepended versions of these functions take `va_list` (variadic functions), letting the list of args be populated at runtime instead of compile time.
## Input Format Specifiers

`scan*` format specifiers follow this format:
`%[*][width][length]conversionSpecifier`

`*` (optional) indicates that the data is read from the stream and ignored
`[width]`  (optional) specifies the maximum number of chars to read in to this arg

The length specifier modifies the size (in bytes) of the conversion specifier, reflecting a different type. Be mindful of type conversions. `u` as shorthand for `unsigned` where possible.

| conversion specifier →<br>length specifier ↓ | `d`, `i `      | `u`, `o`, `x` | `f`, `e`,<br>`g`, `a` | `c`, `s`,<br>`[]`, `[^]` | `p`      | `n`            |
| -------------------------------------------- | -------------- | ------------- | --------------------- | ------------------------ | -------- | -------------- |
| none                                         | `int*`         | `uint*`       | `float*`              | `char*`                  | `void**` | `int*`         |
| `hh`                                         | `signed char*` | `uchar*`      |                       |                          |          | `signed char*` |
| `h`                                          | `short*`       | `ushort*`     |                       |                          |          | `short*`       |
| `l`                                          | `long*`        | `ulong*`      | `double*`             | `wchar_t*`               |          | `long*`        |
| `ll`                                         | `long long*`   | `ulong long*` |                       |                          |          | `long long*`   |
| `j`                                          | `intmax_t*`    | `uintmax_t*`  |                       |                          |          | `intmax_t*`    |
| `z`                                          | `size_t*`      | `size_t*`     |                       |                          |          | `size_t*`      |
| `t`                                          | `ptrdiff_t*`   | `ptrdiff_t*`  |                       |                          |          | `ptrdiff_t*`   |
| `L`                                          |                |               | `long double*`        |                          |          |                |

| Conversion specifier                           | Type         | Data read into arg                                                         |
| ---------------------------------------------- | ------------ | -------------------------------------------------------------------------- |
| `d`,`i`                                        | int          | decimal                                                                    |
| `u`                                            | unsigned int | decimal                                                                    |
| `o`                                            | unsigned int | octal                                                                      |
| `x`                                            | unsigned int | hex                                                                        |
| `f`<sup>C99</sup>, `e`, `g`, `a`<sup>C99</sup> | float        | float                                                                      |
| `c`                                            | char         | char + width. No `\0` appended.                                            |
| `s`                                            | char\[\]     | chars, stop at whitespace. `\0` appended.                                  |
| `p`                                            | pointer      | address                                                                    |
| `n`                                            | int*         | none, arg holds number of chars read in up to this point                   |
| `%`                                            | --           | %                                                                          |
| `[chars]`                                      | scanset      | read until encountering a char not in the scanset (or up to `[width]`)     |
| `^[chars]`                                     | !scanset     | read until encountering a char in the negated scanset (or up to `[width]`) |
Signs (`+-`) are allowed to precede numeric types. Decimal points and `e/E` optional for floating-point types.

Scansets are a basic pattern matching tool, not to be confused with regex, though the syntax for some patterns is the same. Scansets don't have quantifiers nor can they handle complex structures, nor do they have concepts of character classes or special characters (e.g. whitespace).

## Output Format Specifiers

`print*` format specifiers follow this format:
`%[flags][width][.precision][length]conversionSpecifier`

Flags are optional.

| Flag | Effect                                                                              |
| ---- | ----------------------------------------------------------------------------------- |
| `-`  | left-justify within the `[width]`                                                   |
| `+`  | show sign even for positive numbers                                                 |
| ` `  | if no sign for the number, add a blank space                                        |
| `#`  | prepend nonzero hex/octal with `0x` or `0X`;<br>force a decimal point to be printed |
| `0`  | left-pad with `0` if `[width]` flag present                                         |

Width is optional.

| Width      | Effect                                                                    |
| ---------- | ------------------------------------------------------------------------- |
| `<number>` | minimum width of output, pad with whitespace;<br>don't truncate if longer |
| `*`        | dynamic width; `<number>` argument is placed before the specifier         |

Precision is optional.

| Precision   | Effect                                                                                                                                                                                                                      |
| ----------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `.<number>` | for ints, minimum digits to print, pad with 0s;<br>for floats, number of decimal place digits to print<br>for specifier `g`, max significant digits to print<br>for strings, max chars to print<br>don't truncate if longer |
| `.*`        | dynamic precision; `<number>` argument is placed before the specifier                                                                                                                                                       |

Length may be necessary for the type you want to output. Very similar to the input format table; note the separation of `c` and `s`. 

| conversion specifier →<br>length specifier ↓ | `d`, `i `     | `u`, `o`,<br>`x`, `X` | `f`, `F`, `e`, `E`,<br>`g`, `G`, `a`, `A` | `c`      | `s`        | `p`      | `n`            |
| -------------------------------------------- | ------------- | --------------------- | ----------------------------------------- | -------- | ---------- | -------- | -------------- |
| none                                         | `int`         | `uint`                | `float`                                   | `int`    | `char*`    | `void**` | `int*`         |
| `hh`                                         | `signed char` | `uchar`               |                                           |          |            |          | `signed char*` |
| `h`                                          | `short`       | `ushort`              |                                           |          |            |          | `short*`       |
| `l`                                          | `long`        | `ulong`               | `double`                                  | `wint_t` | `wchar_t*` |          | `long*`        |
| `ll`                                         | `long long`   | `ulong long`          |                                           |          |            |          | `long long*`   |
| `j`                                          | `intmax_t`    | `uintmax_t`           |                                           |          |            |          | `intmax_t*`    |
| `z`                                          | `size_t`      | `size_t`              |                                           |          |            |          | `size_t*`      |
| `t`                                          | `ptrdiff_t`   | `ptrdiff_t`           |                                           |          |            |          | `ptrdiff_t*`   |
| `L`                                          |               |                       | `long double`                             |          |            |          |                |

Conversion specifiers denote the basic types or general numeric formatting:

| Conversion Specifier   | Minimum width | Output format                                         |
| ---------------------- | ------------- | ----------------------------------------------------- |
| `d`,`i`                | int           | decimal                                               |
| `u`                    | unsigned int  | decimal                                               |
| `o`                    | unsigned int  | octal                                                 |
| `x`, `X`               | unsigned int  | hex, HEX                                              |
| `f`, `F`<sup>C99</sup> | float         | float, case affects NaN                               |
| `e`, `E`               | float         | scientific notation with e, E                         |
| `g`, `G`               | float         | shortest of `e` or `f`                                |
| `a`, `A`<sup>C99</sup> | float         | hex, HEX                                              |
| `c`                    | char          | char                                                  |
| `s`                    | char\[\]      | char\[\] (string)                                     |
| `p`                    | pointer       | address                                               |
| `n`                    | int*          | none, arg holds number of chars printed to this point |
| `%`                    | --            | %                                                     |



