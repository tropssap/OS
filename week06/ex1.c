#include "stdio.h"
#include "stdlib.h"

typedef struct times {
    int BT;
    int AT;
} times_t;

typedef struct table {
    times_t *times;
    int length;
} table_t;

typedef struct row {
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
} row_t;

int compareArrival(times_t *first, times_t *second) {
    return first->AT - second->AT;
}

int main() {
    FILE *file = fopen("new_input.csv", "r");
    if (file == NULL) {
        printf("File new_input.csv is not found");
        return(1);
    }
    int c = 0;
    for (char ch = getc(file); ch != EOF; ch = getc(file))
        if (ch == '\n')
            c++;
    freopen("new_input.csv", "r", file);
    times_t *timetable = malloc(c * sizeof(times_t));
    for (int i = 0; i < c; i++) {
        fscanf(file, "%d,%d", &timetable[i].AT, &timetable[i].BT);
    }
    fclose(file);
    table_t *table = malloc(sizeof(table_t));
    table->times = timetable;
    table->length = c;

    qsort(table->times, table->length, sizeof(times_t), compareArrival);

    row_t *rows = malloc(table->length * sizeof(row_t));
    int time = 0;
    for (int i = 0; i < table->length; i++) {
        if (time == 0 || time < table->times[i].AT)
            time = table->times[i].AT;
        int waiting = time - table->times[i].AT;
        rows[i].AT = table->times[i].AT;
        rows[i].BT = table->times[i].BT;
        rows[i].CT = table->times[i].AT + waiting + table->times[i].BT;
        rows[i].TAT = waiting + table->times[i].BT;
        rows[i].WT = waiting;
        time = rows[i].CT;
    }

    printf("P#	AT	BT	CT	TAT	WT\n");
    double turnaroundSum = 0.0;
    double waitingSum = 0.0;
    for (int i = 0; i < table->length; i++) {
        turnaroundSum += rows[i].TAT;
        waitingSum += rows[i].WT;
        printf("P%d	%d	%d	%d	%d	%d\n", i + 1, rows[i].AT, rows[i].BT, rows[i].CT, rows[i].TAT, rows[i].WT);
    }
    printf("\nAverage Turnaround Time: %f\nAverage Waiting Time: %f\n", turnaroundSum/table->length, waitingSum/table->length);

    free(rows);
    free(table->times);
    free(table);

}
