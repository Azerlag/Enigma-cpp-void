#include <iostream>

using namespace std;

void enigma(char *result, const char *DATA, const char *RINGS, const char *POSITIONS) {
  const char REFLECTOR[] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
  const char ROTOR[3][27] = {
    "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
    "AJDKSIRUXBLHWTMCQGZNPYFVOE",
    "BDFHJLCPRTXVZNYEIWGAKMUSQO",
  };
  
  uint8_t ringsCount = 0;

  for (uint8_t i = 0;; i++) {
    if (RINGS[i]) ringsCount++; else break;
  }
  
  uint8_t *offset = new uint8_t[ringsCount];
  
   for (uint8_t i = 0;; i++) {
    if (POSITIONS[i]) offset[i] = POSITIONS[i] - 'A'; else break;
  }
  
  for (uint32_t i = 0; DATA[i]; i++) {
    int16_t a = 0;

    for (uint8_t l = 0; l < ringsCount; l++) {
      if (l > 0) {
        if (offset[l] > 25) {
          offset[l] = 0;
        }
      } else {
        if (!((offset[l + 1] + 21) % 25)) {
            offset[l + 2]++;
            offset[l + 1]++;
        }
        if (!((offset[l] + 9) % 25)) {
          offset[l + 1]++;
        }
        if (offset[l] < 25) offset[l]++;
        else {
          offset[l] = 0;
        }
      }
      // cout << "offset[" << l+0 << "] " << offset[l]+0 << endl;

    }

    for (uint8_t l = 0; l < ringsCount + 1; l++) {
      if (l == 0) {
        a = ((('Z'+1 - (RINGS[l] - 'A')) - 'A') + DATA[i] - 'A');
        a = a > 25 ? a - ('Z' - 'A' + 1) : a;
        a = a + offset[l];
        a = a > 25 ? a - ('Z' - 'A' + 1) : a;
        a = ROTOR[l][a];
        
        // cout << "FIRST ROTOR l " << l+0 << " a " << a+0 << " " << (char)(a+0) << endl;
      } else if (l == ringsCount) {
        a = a - ('Z'+1 - (RINGS[l-1] - 'A'));
        a = a < 0 ? a + ('Z' - 'A' + 1) : a;
        a = a - offset[l-1];
        a = a < 0 ? a + ('Z' - 'A' + 1) : a;
        a = REFLECTOR[a];
        a = a + offset[l-1];
        a = a > 90 ? a - ('Z' - 'A' + 1) : a;
        // cout << "REFLECTOR l " << l+0 << " a " << a+0 << " " << (char)(a+0) << endl;
      } else {
        if (offset[l - 1]) a = a - offset[l - 1];
        a = a < 65 ? a + ('Z' - 'A' + 1) : a;

        a = (a + (('Z'+1 - (RINGS[l] - 'A')) - ('Z'+1 - (RINGS[l-1] - 'A')))) - 'A';

        a = a > 25 ? a - ('Z' - 'A' + 1) : a;
        a = a < 0 ? a + ('Z' - 'A' + 1) : a;

        if (l > 0) a = a + offset[l];
        a = a > 25 ? a - ('Z' - 'A' + 1) : a;

        a = ROTOR[l][a];
        
        // cout << "OTHER ROTORS l " << l+0 << " a " << a+0 << " " << (char)(a+0) << endl;
      }
    }

    for (int8_t l = ringsCount; l > -1; l--) {
      if (l == ringsCount) {
        a = a - 'A' + ('Z'+1 - (RINGS[l-1] - 'A')) - 'A';
        a = a > 25 ? a - ('Z' - 'A' + 1) : a;
        for (uint8_t b = 0; b < 26; b++) {
          if (a == ROTOR[l - 1][b] - 'A') {
            a = b + 'A';
            break;
          }
        }
        
        // cout << "AFTER REFLECTOR l " << l+0 << " a " << a+0 << " " << (char)(a+0) << endl;
      } else if (l == 0) {
        a = a < 0 ? a + ('Z' - 'A' + 1) : a;
        a = a - ('Z'+1 - (RINGS[l] - 'A'));
        a = a < 0 ? a + ('Z' - 'A' + 1) : a;
        a = a + 'A';
        a = a - offset[l];
        a = a < 65 ? a + ('Z' - 'A' + 1) : a;
        
        // cout << "LAST ROTOR l " << l+0 << " a " << a+0 << " " << (char)(a+0) << endl;
      } else {
        if (offset[l - 1]) a = a + offset[l - 1];

        a = a - (('Z'+1 - (RINGS[l] - 'A')) - ('Z'+1 - (RINGS[l-1] - 'A'))) - 'A';
        a = a < 0 ? a + ('Z' - 'A' + 1) : a;
        a = a > 25 ? a - ('Z' - 'A' + 1) : a;

        if (l > 0) a = a - offset[l];
        a = a < 0 ? a + ('Z' - 'A' + 1) : a;

        for (uint8_t b = 0; b < 26; b++) {
          if (a == ROTOR[l - 1][b] - 'A') {
            a = b + 'A';
            break;
          }
        }
        
        // cout << "OTHER ROTORS l " << l+0 << " a " << a+0 << " " << (char)(a+0) << endl;
      }
    }

    // cout << " i " << i+0 << " a " << a+0 << " " << (char)(a+0) << endl;

    result[i] = a;
  }
  free(offset);
}

int main() {
  char *result = new char[4];
    
  enigma(
    result,
    "AAAAAAAAAAAAAAAAAAAAAAAA",
    "DAA",
    "AAA"
  );
  
  std::cout << result << std::endl;
  
  enigma(
    result,
    result,
    "DAA",
    "AAA"
  );
  
  std::cout << result << std::endl;

  free(result);
  
  return 0;
}