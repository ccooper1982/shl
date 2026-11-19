# shl
SHell Language, an alternative for shell scripting.

```
pipeline := proc("seq", 1, 100)
          | proc("grep", 5)
          | proc("wc", "-l");

result := exec(pipeline);

print(result);
```

# Aim
- A programmer friendly scripting language
- No config files or virtual environment
- Integrated knowledge of pipes and processes
- No memory management
- Type safety


# Build
```
cd grammar && tree-sitter generate
cd ..
meson setup build -Dbuildtype=release
meson compile -C build
```

Or to use `clang` explicitly:

```
meson setup build --native-file meson/clang.ini -Dbuildtype=release
```

# Tests
```
meson test -C build
```
