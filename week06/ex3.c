#include "stdio.h"
#include "stdlib.h"

typedef struct times {
    int burst;
    int arrival;
    int completed;
} times_t;

typedef struct table {
    times_t *times;
    int length;
} table_t;


typedef struct row {
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
} row_t;


int compareArrival(times_t *first, times_t *second) {
    return first->arrival - second->arrival;
}
int compareCompletion(row_t *first, row_t *second) {
    return first->completion - second->completion;
}

row_t *create_rows(int length) {
    row_t *rows = malloc(length * sizeof(row_t));
    for (int i = 0; i < length; i++) {
        rows[i].arrival = 0;
        rows[i].burst = 0;
        rows[i].completion = 0;
        rows[i].turnaround = 0;
        rows[i].waiting = 0;
    }
    return rows;
}


int main(int argc, char **argv) {
    if (argc <= 1) {
        printf("Please enter the quantum as a first parameter\n");
        return (1);
    }
    int quantum = atoi(argv[1]);
    if (quantum < 0) {
        printf("Invalid quantum\n");
        return (1);
    }

    FILE *file = fopen("new_input.csv", "r");
    if (file == NULL) {
        printf("File %s is not found", "new_input.csv");
        return (1);
    }
    int count = 0;
    for (char c = getc(file); c != EOF; c = getc(file))
        if (c == '\n') // Increment count if this character is newline
            count++;
    freopen("new_input.csv", "r", file);
    times_t *timetable = malloc(count * sizeof(times_t));
    for (int i = 0; i < count; i++) {
        fscanf(file, "%d,%d", &timetable[i].arrival, &timetable[i].burst);
        timetable[i].completed = 0;
    }
    fclose(file);
    table_t *table = malloc(sizeof(table_t));
    table->times = timetable;
    table->length = count;
    qsort(table->times, table->length, sizeof(times_t), compareArrival);

    row_t *rows = create_rows(table->length);
    int *quantums = malloc(table->length * sizeof(int));
    int running = 0;
    int time = 0;
    int completed = 0;
    while (!completed) {
        completed = 1;
        for (int i = 0; i < table->length; i++) {
            if (table->times[i].completed) continue;
            completed = 0;
            if (running == 0 && time < table->times[i].arrival) {
                time = table->times[i].arrival;
                running = 1;
            }
            if (time < table->times[i].arrival) continue;
            running = 1;

            if (quantums[i] + quantum >= table->times[i].burst) {
                table->times[i].completed = 1;
                rows[i].arrival = table->times[i].arrival;
                rows[i].burst = table->times[i].burst;
                rows[i].completion = time + (table->times[i].burst - quantums[i]);
                rows[i].waiting = rows[i].completion - (rows[i].arrival + rows[i].burst);
                rows[i].turnaround = rows[i].burst + rows[i].waiting;
                time = rows[i].completion;
                running = 0;
                continue;
            }
            quantums[i] += quantum;
            time += quantum;
        }
    }
    free(quantums);
    qsort(rows, table->length, sizeof(row_t), compareCompletion);
    printf("P#	AT	BT	CT	TAT	WT\n");
    double turnaroundSum = 0.0;
    double waitingSum = 0.0;
    for (int i = 0; i < table->length; i++) {
        turnaroundSum += rows[i].turnaround;
        waitingSum += rows[i].waiting;
        printf("P%d	%d	%d	%d	%d	%d\n", i + 1, rows[i].arrival, rows[i].burst, rows[i].completion, rows[i].turnaround, rows[i].waiting);
    }
    printf("\nAverage Turnaround Time: %f\nAverage Waiting Time: %f\n", turnaroundSum/table->length, waitingSum/table->length);

    free(rows);
    free(table->times);
    free(table);
}