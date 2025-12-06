# Regex

REGular EXpression - sequence of characters that specifies a match pattern in text

There are many different regex implementations.

## Meta Characters

Almost always need escaping if you're trying to match text containing them.

```txt
. ^ $ * + ? ( ) [ ] { } | \
```

## Character Classes

```txt
[pattern]
```

Word-like character class (uppercase, lowercase, digit, underscore):

```txt
[A-Za-z0-9_]
```

Inside a character class:

- `]` ends the class EXCEPT
  - if it's first `[]A-Za-z]` ("\]Word")
  - if it's escaped `[\\]]` ("\]")
- `-` signifies a range TODO ranges examples besides A-Z
- `^` signifies a NEGATED class

## Shorthand Character Classes

- `\d` - digit `[0-9]`
- `\w` - word `[A-Za-z0-9_]`
- `\s` - whitespace (space, tab)
- Uppercase for negation, i.e. `\D`, `\W`, `\S`

## Anchors (Positions)

e.g. start/end of line, word boundaries

- `^` - start of line / start of string
- `$` - end of line / end of string
- `\b` - word boundary (negated with `\B`)

## Quantifiers (How many of x)

- `?` - 0 or 1
- `*` - 0+
- `+` - 1+
- `{m}` - exactly `m`
- `{m,}` - `m`+
- `{m,n}` - between `m` and `n`

## Common Patterns

X to end of line
`foo.*$`

X to end of line (excluding newline)
`foo[^\n]*`

All lines NOT containing X
`^(?!.*foo).*$`

Everything except X up to some delimiter
`[^,]*`
`[^,]*/[^,\n]*` (path fragment)

with lookahead
^(?!.*Y)X.*$


