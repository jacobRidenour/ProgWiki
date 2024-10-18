When output with standard library `*f` functions, thei

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



