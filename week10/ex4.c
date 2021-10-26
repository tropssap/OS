#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <malloc.h>

int main() {
    int counter = 0;
    char **names = malloc(sizeof(char) * 256);
    int inum[1000];
    DIR *dir_pointer = opendir("tmp");
    struct dirent *dp;
    struct stat *st;
    for (; (dp = readdir(dir_pointer)) != NULL; counter++) {
        stat(dp->d_name, st);
        names[counter] = dp->d_name;
        inum[counter] = dp->d_ino;
    }
    for (int i = 0; i < counter; i++) {
        int count = 0;
        for (int j = 0; j < counter; j++) {
            if (inum[i] == inum[j]) { count++; }
        }
        if (count >= 2) {
            printf("%s: ", names[i]);
            for (int j = 0; j < counter; j++) {
                if (inum[i] == inum[j] &&
                    names[i] != names[j]) {
                    printf("%s ", names[j]);
                }
            }
            printf("\n");
        }
    }
}
