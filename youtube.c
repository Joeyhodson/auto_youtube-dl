/*        Written by: Joey Hodson
            Date: 12/04/2020
Purpose: To download multiple youtube videos
       at a time using 'youtube-dl'    */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char** readLinks(FILE* inFile, int numLinks) {

    if (inFile == NULL) {
        printf("Error reading input file.\n");
        return NULL;
    }

    char link[45];
    char** files = (char**)malloc(sizeof(char*)*numLinks);

    for (int x = 0; x < numLinks; x++) {

        fscanf(inFile, "%s ", link);
        int linkLen = strlen(link) + 1;

        char command[60] = "youtube-dl ";
        strcat(command, link);
        int totalLen = strlen(command) + 1;

        files[x] = (char*)malloc(sizeof(char)*totalLen);
        strcpy(files[x], command);
        //printf("%s\n", files[x]);
    }

    return files;
}

void downloadLinks(char** links, int numLinks) {

    for (int x = 0; x < numLinks; x++) {

        system(links[x]);
    }
}

void freeLinks(char** links, int numLinks) {

    for (int x = 0; x < numLinks; x++) {

        free(links[x]);
    }

    free(links);
}

int main (void) {

    FILE* inFile;
    inFile = fopen("URLs.txt", "r");
    int numLinks;

    fscanf(inFile, "%d", &numLinks);
    char** links = readLinks(inFile, numLinks);
    downloadLinks(links, numLinks);

    freeLinks(links, numLinks);
    fclose(inFile);
}