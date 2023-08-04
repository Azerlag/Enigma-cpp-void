# Enigma

The Enigma function in online C++ compiler: https://onlinegdb.com/cQbkdFXAQ

## How to use

Like an another void function, the only thing necessary is to allocate memory to a char array variable and pass it to fun:

```cpp
char *result = new char[32];          // 32 or as much as need
if (result == nullptr) return 0;
```
----
What is what in fun:

```cpp
for (uint16_t i = 0; i < 32; i++) result[i] = 'A';

enigma(
  result,                             // char *result             Passed data that will mutated to encoded/decoded
  "BAA",                              // const char *RINGS        Pre-installation rings of rotors
  "AAA"                               // const char *POSITIONS    Pre-installation positions of rotors
);

std::cout << result << std::endl;     // NFTZMGISXIPJWGDNEJCOQTYRIGDMXFIE
```
Reflector and rotors configurations themselves are defined by hands in code. Also can be passed your custom rotors, not just historical ones, and more than three too.

```cpp
void enigma(char *data, const char *RINGS, const char *POSITIONS) {
  const char REFLECTOR[] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";  // UKW-B
  const char ROTOR[3][27] = {                             //
    "EKMFLGDQVZNTOWYHXUSPAIBRCJ",                         // I
    "AJDKSIRUXBLHWTMCQGZNPYFVOE",                         // II
    "BDFHJLCPRTXVZNYEIWGAKMUSQO",                         // III
  };
  
...
```
