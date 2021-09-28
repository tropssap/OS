
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

times_t *nearest(times_t *times, int n, int time) {
    if (n == 0) return NULL;
    for (int i = 0; i < n; i++) {
        if (times[i].completed == 0 && times[i].arrival > time) return times + i;
    }
    return NULL;
}

int compareBurst(times_t **first, times_t **second) {
    return (*first)->burst - (*second)->burst;
}

int countWaiting(times_t *times, int length, int time) {
    int n = 0;
    for (int i = 0; i < length; i++) {
        if (times[i].completed) continue;
        if (times[i].arrival >= time) break;
        n++;
    }
    return n;
}

times_t **findWaiting(int waiting_length, times_t *times, int length, int time) {
    times_t **waiting = malloc(waiting_length * sizeof(times_t*));
    int n = 0;
    for (int i = 0; i < length; i++) {
        if (times[i].completed) continue;
        if (times[i].arrival >= time) break;
        waiting[n] = times + i;
        n++;
    }
    return waiting;
}

int compareArrival(times_t *first, times_t *second) {
    return first->arrival - second->arrival;
}

int main(){
    FILE *file = fopen("new_input.csv", "r");
    if (file == NULL) {
    printf("File %s is not found", "new_input.csv");
    return(1);
    }
    int c = 0;
    for (char ch = getc(file); ch != EOF; ch = getc(file))
    if (ch == '\n') // Increment count if this character is newline
    c++;
    freopen("new_input.csv", "r", file);
    times_t *timetable = malloc(c * sizeof(times_t));
    for (int i = 0; i < c; i++) {
    fscanf(file, "%d,%d", &timetable[i].arrival, &timetable[i].burst);
    timetable[i].completed = 0;
    }
    fclose(file);
    table_t *table = malloc(sizeof(table_t));
    table->times = timetable;
    table->length = c;

    qsort(table->times, table->length, sizeof(times_t), compareArrival);

    row_t *rows = malloc(table->length * sizeof(row_t));
    int waiting_length = 0;
    times_t **waiting = NULL;
    int time = 0;
    for (int i = 0; i < table->length; i++) {
        times_t *selected;
        if (waiting_length == 0) {

            selected = nearest(table->times, table->length, time);
            if (selected == NULL) break;
            time = selected->arrival;
        } else {
            qsort(waiting, waiting_length, sizeof(times_t*), compareBurst);
            selected = *waiting;
            free(waiting);
        }
        rows[i].arrival = selected->arrival;
        rows[i].burst = selected->burst;
        rows[i].completion = time + selected->burst;
        rows[i].turnaround = rows[i].completion - rows[i].arrival;
        rows[i].waiting = rows[i].turnaround - rows[i].burst;
        time = rows[i].completion;
        selected->completed = 1;
        waiting_length = countWaiting(table->times, table->length, time);
        waiting = findWaiting(waiting_length, table->times, table->length, time);
    }


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
