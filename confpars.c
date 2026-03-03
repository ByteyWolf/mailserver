#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include "config.h"

const char* SRV_CONFIG_PATHS[] = {
    "/etc/poshta/poshta.conf",
    "/usr/local/etc/poshta/poshta.conf",
    "./poshta.conf",
};

#define KEY_MEANINGFUL 1
#define VALUE_MEANINGFUL 2
#define LINE_VALID 8

int parse_configs(struct poshta_config* cfg) {
    FILE* config_file = NULL;
    for (size_t i = 0; i < sizeof(SRV_CONFIG_PATHS) / sizeof(SRV_CONFIG_PATHS[0]); i++) {
        config_file = fopen(SRV_CONFIG_PATHS[i], "r");
        if (config_file) {
            break;
        }
    }
    if (!config_file) {
        return 1;
    }
    char line[1024];
    while (fgets(line, sizeof(line), config_file)) {
        char* p = line;
        while (*p == ' ' || *p == '\t') p++;
        if (*p == '\0' || *p == '\n' || *p == '#') continue;

        char* eq = strchr(p, '=');
        if (!eq) continue;

        *eq = '\0';
        char* key = p;
        char* value = eq + 1;

        char* end = key + strlen(key) - 1;
        while (end > key && (*end == ' ' || *end == '\t')) *end-- = '\0';

        while (*value == ' ' || *value == '\t') value++;

        end = value + strlen(value) - 1;
        while (end > value && (*end == '\n' || *end == '\r' || *end == '#')) *end-- = '\0';

        // handle escapes in-place
        char* src = value;
        char* dst = value;
        while (*src) {
            if (*src == '\\') {
                src++;
                switch (*src) {
                    case 'n': *dst++ = '\n'; break;
                    case 't': *dst++ = '\t'; break;
                    case '\\': *dst++ = '\\'; break;
                    case '\0': goto done_escapes;
                    default: *dst++ = *src; break;
                }
            } else {
                *dst++ = *src;
            }
            src++;
        }
    done_escapes:
        *dst = '\0';

        if (strcmp(key, "srv_addr") == 0) {
            if (cfg->srv_addr) free(cfg->srv_addr);
            cfg->srv_addr = strdup(value);
        } else if (strcmp(key, "allow_linux_users") == 0) {
            cfg->allow_linux_users = atoi(value);
        } else if (strcmp(key, "mailroot") == 0) {
            if (cfg->mailroot) free(cfg->mailroot);
            cfg->mailroot = strdup(value);
        } else {
            fprintf(stderr, "Unknown key '%s' in config\n", key);
        }
    }
    
    fclose(config_file);
    return 0;
}