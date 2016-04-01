#ifndef __FILELISTGEN_H_
#define __FILELISTGEN_H_

typedef struct __FileList
{
	char* filePath;
	struct __FileList *next;
} FileList;

FileList* GetFileList (char* dir);
void FreeFileList(FileList* root);

#endif