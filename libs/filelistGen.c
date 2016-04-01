#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

#include "filelistGen.h"

void __fileListGen_AddToList(FileList** rootNode, char* fileName) {
	FileList *tmpNode = (FileList *)malloc(sizeof(FileList));/*allocates an extra node for the list*/
	(*rootNode)->filePath = fileName;
	tmpNode->next = (*rootNode); /*Goes back to the last input on the list*/
	(*rootNode) = tmpNode;
}

void __fileListGen_GetFileListHelper (FileList** rootNode, char* dir) {
  DIR *dfd;
	struct dirent *dp;
  char* filename_qfd;
	if (dfd = opendir(dir)) {
		while ((dp = readdir(dfd)) != NULL) {
			if (strcmp(dp->d_name,"..") && strcmp(dp->d_name,".")) {        
        filename_qfd = (char*) malloc(strlen(dir) + strlen(dp->d_name) + 2);
        sprintf(filename_qfd , "%s/%s", dir, dp->d_name);
				if ( dp->d_type == DT_DIR ) {
				  __fileListGen_GetFileListHelper(rootNode, filename_qfd);
				} else if (dp->d_type == DT_REG) {
				  __fileListGen_AddToList(rootNode, filename_qfd);
				}
			}
		}
    closedir(dfd);
	}
}

FileList* GetFileList (char* dir) {
	FileList* tmpNode;
    FileList* rootNode = (FileList *)malloc(sizeof(FileList));
	rootNode->next = NULL;
	__fileListGen_GetFileListHelper(&rootNode, dir);
	tmpNode = rootNode->next;
	free(rootNode);
	rootNode = tmpNode;
	return rootNode;
}

void FreeFileList(FileList* rootNode) {
  FileList* currentNode;
  while (rootNode) {
    currentNode = rootNode;
    rootNode = rootNode->next;
    free(currentNode);
  }
}

