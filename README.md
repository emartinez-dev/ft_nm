# ft_nm
Recreating UNIX name mangling program

## Requisites

### General requisites

- [ ] Assume `a.out` if no filename is given
- [ ] List every symbol value in hexadecimal radix
- [ ] Lowercase symbols types are usually local.
- [ ] Uppercase symbols types are global, but "u", "v" and "w" symbols are special global ones.
- [ ] The output should be `symbol value | symbol type | symbol name`.

### Symbol types
- "A": The symbol's value is absolute, will not be changed by further linking.
- "B"/"b": The symbol is in the BSS data section.
- "C"/"c": The symbol is common, unitialized. Multiple common symbols may appear with the same name.
- "D"/"d": The symbol is in the initialized data section.
- "G"/"g": The symbol is in an initialized data section for small objects.
- More in the doc `man nm`

### Formats handled

- [ ] ELF binaries
- [ ] x86_32
- [ ] x64
- [ ] object files
- [ ] .so

### Other considerations

- [ ] There are many ways to lead your program out of the mapped content, may it
be with non-null terminated string, incorrect offsets... Check everything.
- [ ] Make sure that every value that you parse is correct: for instance, when
parsing flags, architecture, match your result with a reference to ensure its
value is correct

## Bonus

Implement the following flags:

- [ ] -a. Display debug symbols too
- [ ] -g. Display only external symbols
- [ ] -u. Display only undefined symbols
- [ ] -r. Reverse sort symbols
- [ ] -p. Don't sort symbols