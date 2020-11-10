## Viewing a dynamically-allocated array with the Xcode debugger?
```
memory read -t int -c8 `array_name`
memory read -t char -c16 `this->value`
```

## Print unsigned long long in hex
```
type format add --format hex "unsigned long long"
type format add --format hex char
print
```
