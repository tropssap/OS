#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "stdio.h"
#include "string.h"
#include "linux/input.h"
#include "linux/input-event-codes.h"

static const char *const evval[3] = {
        "RELEASED",
        "PRESSED ",
        "REPEATED"
};

int main() {
    struct input_event inputEvent;
    ssize_t n;
    int fd = open("/dev/input/by-path/pci-0000:00:14.0-usb-0:8.2:1.2-event-kbd", O_RDONLY);

    while (1) {
        n = read(fd, &inputEvent, sizeof(inputEvent));
        if (n == (ssize_t)-1) {
            if (errno == EINTR)
                continue;
            else
                break;
        } else
        if (n != sizeof(inputEvent)) {
            errno = EIO;
            break;
        }
        if (inputEvent.type == EV_KEY && inputEvent.value >= 0 && inputEvent.value <= 2) {
            printf("%s 0x%04x (%d)\n", evval[inputEvent.value], (int)inputEvent.code, (int)inputEvent.code);
        }

    }
    return 0;
}
