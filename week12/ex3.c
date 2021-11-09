#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "stdio.h"
#include "string.h"
#include "linux/input.h"
#include "linux/input-event-codes.h"

int checkCombination(struct input_event pressed[], int combination[], int n) {
    int exist = 1;
    for (int i = 0; i < n; i++) {
        int localExist = 0;
        for (int j = 0; j < 6; j++) {
            if (pressed[j].code == combination[i]) {
                localExist = 1;
            }
        }
        if (!localExist) {
            exist = 0;
            break;
        }
    }
    if (n == 0) return 0;
    return exist;
}

void deleteCombination(struct input_event pressed[], int combination[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 6; j++) {
            if (pressed[j].code == combination[i]) {
                struct input_event empty;
                empty.code = 0;
                empty.value = 0;
                empty.type = 0;
                empty.time.tv_sec = 0;
                empty.time.tv_usec = 0;
                pressed[j] = empty;
                break;
            }
        }
    }
}

static const char *const evval[3] = {
        "RELEASED",
        "PRESSED ",
        "REPEATED"
};

int main() {
    struct input_event inputEvent;
    ssize_t n;
    int fd = open("/dev/input/by-path/pci-0000:00:14.0-usb-0:8.2:1.2-event-kbd", O_RDONLY);
    struct input_event pressed[6];
    struct input_event empty;
    empty.code = 0;
    empty.value = 0;
    empty.type = 0;
    empty.time.tv_sec = 0;
    empty.time.tv_usec = 0;
    for (int i = 0; i < 6; i++) {
        pressed[i] = empty;
    }
    printf("Shortcuts:\nP + E\nC + A + P\nC + U + S\n");

    while (1) {
        n = read(fd, &inputEvent, sizeof(inputEvent));
        if (n == (ssize_t) -1) {
            if (errno == EINTR)
                continue;
            else
                break;
        } else if (n != sizeof(inputEvent)) {
            errno = EIO;
            break;
        }
        if (inputEvent.type == EV_KEY && inputEvent.value == 0) { // RELEASED
            for (int i = 0; i < 6; i++) {
                if (pressed[i].code == inputEvent.code) {
                    pressed[i] = empty;
                    break;
                }
            }
        }
        if (inputEvent.type == EV_KEY && inputEvent.value == 1) { // PRESSED

            for (int i = 0; i < 6; i++) {
                if (pressed[i].code == empty.code && pressed[i].type == empty.type && pressed[i].value == empty.value) {
                    pressed[i] = inputEvent;
                    break;
                }
            }
        }
        {
            int combination[] = {KEY_P, KEY_E};
            if (checkCombination(pressed, combination, 2)) {
                deleteCombination(pressed, combination, 2);
                printf("I passed the Exam!\n");
            }

        }
        {
            int combination[] = {KEY_C, KEY_A, KEY_P};
            if (checkCombination(pressed, combination, 3)) {
                deleteCombination(pressed, combination, 3);
                printf("Get some cappuccino!\n");
            }
        }
        {
            int combination[] = {KEY_C, KEY_U, KEY_S};
            if (checkCombination(pressed, combination, 3)) {
                deleteCombination(pressed, combination, 3);
                printf("custom shortcut of my choice\n");
            }
        }
    }
    return 0;
}
