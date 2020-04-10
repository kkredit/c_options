# C Options

A poor man's `Option` types in C.

See example code for usage.

Operations:

- `OPTION(type)`: the signature for options of a given base type `type`
- `NONE`: empty constructor
- `JUST`: non-empty constructor
- `IS_NONE`: checks whether the option type is empty
- `IS_JUST`: checks whether the option type is non-empty
- `UNWRAP`: unwraps the option type after asserting it is non-empty
- `UNWRAP_OR`: unwraps the option type if present, else returns the default
- `EQ`: compares two options using `==`; none matches none
- `EQUAL`: compares two options using `==`; none does not match none
- `OR`: return the first option if present, else the second
- `AND`: return the first option if not present, else the second
