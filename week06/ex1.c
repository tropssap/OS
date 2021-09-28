#include "stdio.h"
#include "stdlib.h"

typedef struct times {
	int burst;
	int arrival;
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

int main() {
	FILE *file = fopen("new_input.csv", "r");
        if (file == NULL) {
                printf("File %s is not found", "new_input.csv");
                return(1);
        }
        int c = 0;
        for (char ch = getc(file); ch != EOF; ch = getc(file))
                if (ch == '\n')
                        c++;
        freopen("new_input.csv", "r", file);
        times_t *timetable = malloc(c * sizeof(times_t));
        for (int i = 0; i < c; i++) {
                fscanf(file, "%d,%d", &timetable[i].arrival, &timetable[i].burst);
        }
        fclose(file);
        table_t *table = malloc(sizeof(table_t));
        table->times = timetable;
        table->length = c;       

	qsort(table->times, table->length, sizeof(times_t), compareArrival);
	
	row_t *rows = malloc(table->length * sizeof(row_t));
	int time = 0;
	for (int i = 0; i < table->length; i++) {
		if (time == 0 || time < table->times[i].arrival)
			 time = table->times[i].arrival;
		int waiting = time - table->times[i].arrival;
		rows[i].arrival = table->times[i].arrival;
		rows[i].burst = table->times[i].burst;
		rows[i].completion = table->times[i].arrival + waiting + table->times[i].burst;
		rows[i].turnaround = waiting + table->times[i].burst;
		rows[i].waiting = waiting;
		time = rows[i].completion;
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
