# Enigma

The function in online C++ compiler: https://onlinegdb.com/TG2Gft6y4

## How to use

Like an another void function, the only thing necessary is to allocate memory to a char array variable and pass it to fun:

```cpp
char *result = new char[64]; // 64 or as much as need
```
----
What is what in fun:

```cpp
enigma(
  result,                               // char *result             Where encoded/decoded data will be write
  "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",   // const char *DATA         A data that will be encoded/decoded
  "AAA",                                // const char *RINGS        Pre-installation rings of rotors
  "AAA"                                 // const char *POSITIONS    Pre-installation positions of rotors
);

std::cout << result << std::endl;       // FTZMGISXIPJWGDNJJCOQTYRIGDMXFIES
```
### Note
And here with configure of RINGS and POSITIONS appears a small code annoyance - values of RINGS/POSITIONS by sequence is mismatch with sequrnce of the rotors, to be more specifically: they are mirrored. So rotors setting by ring or position happens like: in "BAA" 'B' affects to last rotor that is defined in the code, not to first. And rotors themselves inversed too.

----
Reflector and rotors is pre-installed by hands in code. Also can be passed your custom rotors, not just historical ones, and more than three too.

```cpp
void enigma(char *result, const char *DATA, const char *RINGS, const char *POSITIONS) {
  const char REFLECTOR[] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";  // UKW-B
  const char ROTOR[3][27] = {                             // Don't forget to increase the amount of memory
    "EKMFLGDQVZNTOWYHXUSPAIBRCJ",                         // I      last
    "AJDKSIRUXBLHWTMCQGZNPYFVOE",                         // II     second
    "BDFHJLCPRTXVZNYEIWGAKMUSQO",                         // III    first
  };
  
...
```
