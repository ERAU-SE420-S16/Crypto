#ifndef __SECURITY_H_
#define __SECURITY_H_

#include <stdbool.h>

#include "cJSON.h"

cJSON* authenticateUser(const char* userFile);
void updateUser(const char* userFile, cJSON* userObject);

#endif