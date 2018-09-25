## structure

```
 thread-1      thread-2
| main    |   | main    |
| cogo    |   | cogo    |
|\\\\\\\\\|   |\\\\\\\\\|
|\\\\\\\\\|   |\\\\\\\\\|
|\\\\\\\\\|   |\\\\\\\\\|
|\\\\\\\\\|   |\\\\\\\\\|
|\\\\\\\\\|   |\\\\\\\\\|
| comain  |   |\\\\\\\\\|
| coto    |   |\\\\\\\\\|
    ^         | comain  |
    |-------- | coto    |
```

## comain layout

```
| comain  |
| arg     | ---|
| p       | ---|
| i       |    |
| ...     |    |
| coarg   |    |
| count   | <--|
```

- `%p` of `&i` is different from `%p` of `p`
- `arg` is global based on `coarg`

## other

- `switch` only allows the topmost function to yield