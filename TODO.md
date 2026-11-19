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
- `str_iequals() -> bool`
- `str_contains() -> bool`

## Time
- `time() -> int` 
- `time_add() -> int`
- `time_add_seconds() -> int`
- `time_add_days() -> int`

# Language

## lists
```
names := ["bob", "jim", "alf"];

# "bob", "jim", "alf"
list_append(names, "mary", "john");
"bob", "jim", "alf", "mary", "john"
list_rmv(names, 1);
"bob", "alf", "mary", "john"
list_rmv(names, "john");
# "bob", "alf", "mary",
list_rmv(names, ["alf", "mary"]);
# "bob"
```

## for each
```
for ([variable_decl_assign_expr] in [variable:list])
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

for (name, details in contacts)
{
  for (key, value in details) {
  
  }
}
```
