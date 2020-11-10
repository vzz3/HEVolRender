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


DONE:
*) copied every text I have to the DA
*) finishe implementation of an infinit (variabl) length Signed Big Int Class (add, sub, mul, div, mod, pow, sqrt, modPow, shiftLeft, shiftRight, sdetBit, clearBit, and many more utility methods)
*) modInverse / extended Euclidean Algorithm (gcd)
*) implement fast psydo random number generator that should be save from a security standpoint that can generat int with a specific bit length
*) implement a large prime number generator that can create 1024 bit long primes within some secounds. This is far from world record, but should be fine for the moment.
*) Based on those classe I implement Paillier key create, encrypt, decrypt, add and mul methods.
*) more than 1500 unit test

TODO:
*) Paillier Floating Point Classes
*) Fixed Len BigInt Classes that can bee implementet 1:1 in a GPU shader
*) Are there any limits for the size of a shader????
