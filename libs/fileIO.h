#ifndef __FILEIO_H_
#define __FILEIO_H_

#include <stdbool.h>

char* readFile(const char* file);
bool writeFile(const char* file, char* data);

#endif