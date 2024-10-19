# Basic Input and Output

Most of what you'll typically need for I/O is in `<stdio.h>`. Reference [here](https://en.cppreference.com/w/c/io).

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

| Function                                              | Effect                                                                                                                                       |
| ----------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------- |
| `int fgetc(FILE* stream)`<br>`int getc(FILE* stream)` | Read a char from `stream`<br>else return `EOF`                                                                                               |
| `char* fgets(char* str, int n, FILE* stream)`         | Read up to `n-1` chars from `stream`;<br>place them in `str` and null-terminate.<br>Stop at newline (put in `str`) or `EOF`                  |
| `int getchar()`                                       | Read a char from `stdin`<br>== `getc(stdin)`                                                                                                 |
| `char* gets_s(char* str, rsize_t n)`                  | Read a string from `stdin`;<br>place it in `str`<br><sub>formerly `gets`, removed for being unsafe</sub><br><sub>not included in glibc</sub> |

Writing (`*put*`)

| Function                                                              | Effect                                                                                                                               |
| --------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------ |
| `int fputc(int ch, FILE* stream)`<br>`int putc(int ch, FILE* stream)` | Write `ch` to `stream`, return it on success;<br>else return `EOF`                                                                   |
| `int fputs(char* str, FILE* stream)`                                  | Write `str` to  `stream`; return >=0 on success;<br>else return `EOF`                                                                |
| `int putchar(int ch)`                                                 | Write `ch` to `stdout`, return it on success;<br>else return `EOF`                                                                   |
| `int puts(char* str)`                                                 | Write `str` + `\n` to `stdout`;`\0` not written;<br>return >=0 on success, else return `EOF`                                         |
| `int ungetc(int ch, FILE* stream)`                                    | Write `ch` into `stream`'s input buffer;<br>multiple calls in a row may fail;<br>effects discarded by stream repositioning functions |

**Formatted I/O**

<>
## Format Specifiers

Commonly used with `*printf`-style functions.

Format specifiers follow this format:
`%[flags][width][.precision][length]specifier`

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

Specifiers are used for specific types or general numeric formatting:

| Specifier | Use with     | Output                                                |
| --------- | ------------ | ----------------------------------------------------- |
| `d`,`i`   | int          | decimal                                               |
| `u`       | unsigned int | decimal                                               |
| `o`       | unsigned int | octal                                                 |
| `x`, `X`  | unsigned int | hex, HEX                                              |
| `f`, `F`  | float        | float, case affects NaN                               |
| `e`, `E`  | float        | scientific notation with e, E                         |
| `g`, `G`  | float        | shortest of `e` or `f`                                |
| `a`, `A`  | float        | hex, HEX                                              |
| `c`       | char         | char                                                  |
| `s`       | char\[\]     | char\[\] (string)                                     |
| `p`       | pointer      | address                                               |
| `n`       | int*         | none, arg holds number of chars printed to this point |
| `%`       | --           | %                                                     |



