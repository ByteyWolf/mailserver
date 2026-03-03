#ifndef CONFIG_H
#define CONFIG_H

struct poshta_config {
    char* srv_addr;
    int allow_linux_users;
    char* mailroot;
};

int parse_configs(struct poshta_config* cfg);

#endif // CONFIG_H