#ifndef CONFIG_H
#define CONFIG_H

struct poshta_config {
    char* srv_addr;
    int srv_port;
    char* srv_root;
};

int parse_configs(struct poshta_config* cfg);

#endif // CONFIG_H