#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

// Define a function to list files in a directory and return them as a 2D array of strings.
char **listFilesInDirectory(const char *directoryPath, int *count) {
    struct dirent *entry;
    DIR *dp = opendir(directoryPath);
    
    if (!dp) {
        perror("opendir");
        return NULL;
    }

    // Count the files in the directory.
    int fileCount = 0;
    while ((entry = readdir(dp))) {
        if (entry->d_type == DT_REG) {
            fileCount++;
        }
    }

    // Allocate memory for the 2D array.
    char **fileList = (char **)malloc(fileCount * sizeof(char *));
    if (!fileList) {
        perror("malloc");
        closedir(dp);
        return NULL;
    }

    // Rewind the directory stream and populate the 2D array.
    rewinddir(dp);
    int index = 0;
    while ((entry = readdir(dp))) {
        if (entry->d_type == DT_REG) {
            fileList[index] = (char *)malloc(strlen(entry->d_name) + 1);
            strcpy(fileList[index], entry->d_name);
            index++;
        }
    }

    closedir(dp);
    *count = fileCount;
    return fileList;
}

int main() {
    const char *directoryPath = "/bin";
    int fileCount;
    char **files = listFilesInDirectory(directoryPath, &fileCount);

    if (files) {
        for (int i = 0; i < fileCount; i++) {
            printf("File %d: %s\n", i, files[i]);
            free(files[i]); // Free each file name string.
        }
        free(files); // Free the array of file name strings.
    }

    return 0;
}
