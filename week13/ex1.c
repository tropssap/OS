#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define TRUE 1

typedef struct IntArray {
    int *array;
    int size;
} sized_array;

typedef struct Matrix {
    sized_array *sizedArray;
    int verticalSize;
    int horizontalSize;
} sized_matrix;

sized_array read_line(FILE *file) {
    int *buffer= malloc(255 * sizeof(int));;
    int n = 0;
    char *original_line = malloc(255 * sizeof(char));
    size_t length = 255;
    int chars = getline(&original_line, &length, file);
    if (chars == -1 || original_line[0] == '\n') {
        sized_array arr = {NULL, 0};
        return arr;
    }
    int number;
    char *line = malloc(length * sizeof(char));
    memcpy(line, original_line, length);
    char *newLine = malloc(length * sizeof(char));
    while (TRUE) {
        sscanf(line, "%d%255[^\n]s", &number, newLine);
        buffer[n] = number;
        n++;
        if (strcmp(line, newLine) == 0) {
            break;
        }
        memcpy(line, newLine, length);
    }
    free(line);
    free(newLine);
    free(original_line);
    sized_array array = {buffer, n};
    return array;
}

sized_matrix read_matrix(FILE *file) {
    sized_array *buffer= malloc(255 * sizeof(sized_array));;
    int n = 0;
    while (TRUE) {
        sized_array current = read_line(file);
        if (current.size == 0) break;
        buffer[n] = current;
        n++;
    }
    sized_matrix matrix = {buffer, n, buffer[0].size};
    return matrix;
}

int main() {
    FILE *fin = fopen("input.txt", "r");
    sized_array existing = read_line(fin);
    read_line(fin);
    sized_array available = read_line(fin);
    read_line(fin);
    sized_matrix allocated_matrix = read_matrix(fin);
    sized_matrix request_matrix = read_matrix(fin);
    fclose(fin);
    while (TRUE) {
        int available_exists = 0;
        int number_empty = 0;
        for (int i = 0; i < request_matrix.verticalSize; i++) {
            int ch = 1;
            for (int j = 0; j < request_matrix.horizontalSize; j++) {
                if (request_matrix.sizedArray[i].array[j] > 
available.array[j]) {
                    ch = 0;
                }
            }
            if (ch) {
                int empty = TRUE;
                for (int j = 0; j < request_matrix.horizontalSize; j++) {
                    if (request_matrix.sizedArray[i].array[j] != 0) {
                        empty = 0;
                        break;
                    }
                    if (allocated_matrix.sizedArray[i].array[j] != 0) {
                        empty = 0;
                        break;
                    }
                }
                if (empty == TRUE) {
                    number_empty++;
                    continue;
                }
                available_exists = TRUE;
                for (int j = 0; j < allocated_matrix.horizontalSize; j++) {
                    available.array[j] += 
allocated_matrix.sizedArray[i].array[j] + 
request_matrix.sizedArray[i].array[j];
                    request_matrix.sizedArray[i].array[j] = 0;
                    allocated_matrix.sizedArray[i].array[j] = 0;
                }
            }
        }
        if (number_empty == request_matrix.verticalSize) {
            printf("No deadlock occurs\n");
            return 0;
        }
        if (!available_exists) {
            printf("Deadlock occurs!\n");

            printf("Number of the deadlocked process: \n");
            for (int i = 0; i < request_matrix.verticalSize; i++) {
                for (int j = 0; j < request_matrix.horizontalSize; j++) {
                    if (request_matrix.sizedArray[i].array[j] != 0) {
                        printf("%d ", i);
                        break;
                    }
                }
            }
            break;
        }
    }
    free(existing.array);
    free(available.array);
    for (int i = 0; i < allocated_matrix.verticalSize; i++) {
        free(allocated_matrix.sizedArray[i].array);
    }
    for (int i = 0; i < request_matrix.verticalSize; i++) {
        free(request_matrix.sizedArray[i].array);
    }
    return 0;
}
