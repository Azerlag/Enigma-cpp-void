#include <iostream>

void enigma(char *data, const char *RINGS, const char *POSITIONS) {
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
  
  for (uint32_t i = 0; data[i]; i++) {
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
    }

    for (uint8_t l = 0; l < ringsCount + 1; l++) {
      if (l == 0) {
        data[i] = ((('Z'+1 - (RINGS[l] - 'A')) - 'A') + data[i] - 'A');
        data[i] = data[i] > 25 ? data[i] - ('Z' - 'A' + 1) : data[i];
        data[i] = data[i] + offset[l];
        data[i] = data[i] > 25 ? data[i] - ('Z' - 'A' + 1) : data[i];
        data[i] = ROTOR[l][data[i]];
        
      } else if (l == ringsCount) {
        data[i] = data[i] - ('Z'+1 - (RINGS[l-1] - 'A'));
        data[i] = data[i] < 0 ? data[i] + ('Z' - 'A' + 1) : data[i];
        data[i] = data[i] - offset[l-1];
        data[i] = data[i] < 0 ? data[i] + ('Z' - 'A' + 1) : data[i];
        data[i] = REFLECTOR[data[i]];
        data[i] = data[i] + offset[l-1];
        data[i] = data[i] > 90 ? data[i] - ('Z' - 'A' + 1) : data[i];

      } else {
        if (offset[l - 1]) data[i] = data[i] - offset[l - 1];
        data[i] = data[i] < 65 ? data[i] + ('Z' - 'A' + 1) : data[i];

        data[i] = (data[i] + (('Z'+1 - (RINGS[l] - 'A')) - ('Z'+1 - (RINGS[l-1] - 'A')))) - 'A';
        data[i] = data[i] > 25 ? data[i] - ('Z' - 'A' + 1) : data[i];
        data[i] = data[i] < 0 ? data[i] + ('Z' - 'A' + 1) : data[i];

        if (l > 0) data[i] = data[i] + offset[l];
        data[i] = data[i] > 25 ? data[i] - ('Z' - 'A' + 1) : data[i];
        
        data[i] = ROTOR[l][data[i]];
        
      }
    }

    for (int8_t l = ringsCount; l > -1; l--) {
      if (l == ringsCount) {
        data[i] = data[i] - 'A' + ('Z'+1 - (RINGS[l-1] - 'A')) - 'A';
        data[i] = data[i] > 25 ? data[i] - ('Z' - 'A' + 1) : data[i];
        for (uint8_t b = 0; b < 26; b++) {
          if (data[i] == ROTOR[l - 1][b] - 'A') {
            data[i] = b + 'A';
            break;
          }
        }
        
      } else if (l == 0) {
        data[i] = data[i] < 0 ? data[i] + ('Z' - 'A' + 1) : data[i];
        data[i] = data[i] - ('Z'+1 - (RINGS[l] - 'A'));
        data[i] = data[i] < 0 ? data[i] + ('Z' - 'A' + 1) : data[i];
        data[i] = data[i] + 'A';
        data[i] = data[i] - offset[l];
        data[i] = data[i] < 65 ? data[i] + ('Z' - 'A' + 1) : data[i];
        
      } else {
        if (offset[l - 1]) data[i] = data[i] + offset[l - 1];

        data[i] = data[i] - (('Z'+1 - (RINGS[l] - 'A')) - ('Z'+1 - (RINGS[l-1] - 'A'))) - 'A';
        data[i] = data[i] < 0 ? data[i] + ('Z' - 'A' + 1) : data[i];
        data[i] = data[i] > 25 ? data[i] - ('Z' - 'A' + 1) : data[i];

        if (l > 0) data[i] = data[i] - offset[l];
        data[i] = data[i] < 0 ? data[i] + ('Z' - 'A' + 1) : data[i];

        for (uint8_t b = 0; b < 26; b++) {
          if (data[i] == ROTOR[l - 1][b] - 'A') {
            data[i] = b + 'A';
            break;
          }
        }
      }
    }
  }
  free(offset);
}

int main() {
  char *data = new char[32];
  if (data == nullptr) return 0;

  for (uint16_t i = 0; i < 32; i++) data[i] = 'A';

  enigma(
    data,
    "BAA",
    "AAA"
  );
  
  std::cout << data << std::endl;
  
  enigma(
    data,
    "BAA",
    "AAA"
  );
  
  std::cout << data << std::endl;

  free(data);
  
  return 1;
}
