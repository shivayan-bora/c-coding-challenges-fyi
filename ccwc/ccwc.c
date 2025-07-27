#include <ctype.h>   // for isspace
#include <stdbool.h> // for boolean
#include <stdio.h>
#include <string.h> // for using string functions

long countBytes(FILE *file);
long countLines(FILE *file);
long countWords(FILE *file);
long countCharacters(FILE *file);
void resetFilePointer(FILE *file);

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    printf("Invalid Command\n");
    return 1;
  }

  FILE *file = fopen(argv[argc - 1], "r");

  if (file == NULL) {
    printf("Error: '%s' is not a valid file or cannot be opened.\n",
           argv[argc - 1]);
    return 1;
  }

  if (argc == 2) {
    printf("%ld ", countLines(file));
    printf("%ld ", countWords(file));
    printf("%ld ", countBytes(file));
  } else {
    for (int i = 1; i < (argc - 1); i++) {
      if (strcmp(argv[i], "-c") == 0) {
        printf("%ld ", countBytes(file));
      } else if (strcmp(argv[i], "-l") == 0) {
        printf("%ld ", countLines(file));
      } else if (strcmp(argv[i], "-w") == 0) {
        printf("%ld ", countWords(file));
      } else if (strcmp(argv[i], "-m") == 0) {
        printf("%ld ", countCharacters(file));
      } else {
        printf("Invalid flag: %s\n", argv[i]);
        fclose(file);
        return 1;
      }
    }
  }

  printf("%s\n", argv[argc - 1]);

  fclose(file);

  return 0;
}

long countBytes(FILE *file) {
  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  resetFilePointer(file);
  return size;
}

long countLines(FILE *file) {
  long lines = 0;
  char ch;

  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\n') {
      lines = lines + 1;
    }
  }
  resetFilePointer(file);
  return lines;
}

long countWords(FILE *file) {
  long words = 0;
  bool inWord = false;
  char ch;
  while ((ch = fgetc(file)) != EOF) {
    if (isspace(ch)) {
      inWord = false;
    } else if (!inWord) {
      words = words + 1;
      inWord = true;
    }
  }
  resetFilePointer(file);
  return words;
}

long countCharacters(FILE *file) {
  long characters = 0;
  char ch;
  while ((ch = fgetc(file)) != EOF) {
    characters = characters + 1;
  }
  resetFilePointer(file);
  return characters;
}

void resetFilePointer(FILE *file) { fseek(file, 0, SEEK_SET); }
