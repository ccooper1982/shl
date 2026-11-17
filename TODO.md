# TODO

# Library

## filesystem
- `file_create_sym(src: str, target: str)`
- `file_set_perms(path: str, perms: int)` - set permissions
- `path_perms(path: str) -> int` - get permissions

### Future
- `dir_list(path: str) -> array<str>` - requires arrays

## string
- `str_empty() -> bool`
- `str_empty() -> bool`
- `str_equals() -> bool`
- `str_equals_icase() -> bool`
- `str_contains() -> bool`

## Time
- `time() -> int` 
- `time_add() -> int`
- `time_add_seconds() -> int`
- `time_add_days() -> int`

# Language

## for each
```
for (<variable_decl_assign_expr> in <variable:array>)
{
  <NodeBlock>
}
```

## for
```
for ([init_expr] ; <condition_expr:bool> ; [iteration_expr])
{
  <NodeBlock>
}
```

## Sequence

List:
- All elements must have the same type
- Variable size (implemented with an `std::list` or `std::vector`)
- Denoted with `[` and `]`

```
list_ok := ["abc", "def", "ghi"];
list_ok.append("jkl");
```

## Associative
Map:
- All keys must the same type
- All values must be the same type
- Implemented with `std::map`
- Denoted with `{` and `}`

```
contacts := {
  "john": ["12345", "16 Smith Drive"],
  "david": ["6789", "16 Park Street"]
};
```

```
contacts := {
  "john" : {"dob":"10-10-1990", "post_code":"abc def", "city":"London"}
};
```

`variable_decl_assign_expr`:
- similar to `VariableDecl` and `VariableAssign` because it is declaring a variable and assigning in one expression
- type is inferred from `<variable_ref>` (the element type of the `list`/`map`)


list:
```
my_files = file_list("some/dir");
for (file in my_files) {

}
```

map:
```
contacts := {
  "john" : {"dob":"10-10-1990", "post_code":"abc def", "city":"London"}
};

for (name, details in contacts) {
  
}
```
