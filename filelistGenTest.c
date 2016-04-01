#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#include "./libs/filelistGen.h"

#define CMD_LEN 255

void readCommand(char buffer[]) {
  fgets(buffer, CMD_LEN, stdin);
  buffer[strlen(buffer)-1] = '\0'; // overwrite the line feed with null term
}

void
printList(FileList* rootNode) {
  unsigned long count;
	while(rootNode) {
    count++;
		printf("File : %s \n", rootNode->filePath);
		rootNode = rootNode->next;
	}
  printf("Found %ul files!\n");
}

int main (void) {
	char dirPath[CMD_LEN];
	char userResponse[CMD_LEN];
	FileList* rootNode = NULL;
	int done = 0;
	do {
    printf("Enter dir path: ");
    readCommand(dirPath);
    
    rootNode = GetFileList(dirPath);
    printList(rootNode);
    printf("Test\n");
    
    printf("Are you done? (y/n) ");
    readCommand(userResponse);
  } while(toupper(userResponse[0]) != 'Y');
	
	
	return 1;
}
