#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "fileIO.h"

char* readFile(const char* file) { 
  long size;
  char* data = NULL;
  FILE *fPtr = fopen(file, "rb");
  if (fPtr) {
    fseek(fPtr, 0, SEEK_END);
    size = ftell(fPtr);
    fseek(fPtr, 0, SEEK_SET);

    data = (char*) malloc(size + 1);
    if (data) fread(data, 1, size, fPtr);
    fclose(fPtr);
  }
  return data;
}

bool writeFile(const char* file, char* data) {
  bool rc = false;
  FILE *fPtr = fopen(file, "wb+");
  if (fPtr) {
    if (fputs (data, fPtr) != EOF) rc = true;
    if (fclose (fPtr) == EOF) rc = false;
  }
  return rc;
}