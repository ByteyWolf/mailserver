#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <poll.h>

#include "config.h"

int main() {
    struct poshta_config cfg = {0};
    int result = parse_configs(&cfg);
    if (result) {
        fprintf(stderr, "Failed to parse config file with error code %d\n", result);
        return 1;
    }
    printf("ok\n");
    return 0;
}