#ifndef CONFIG_H
#define CONFIG_H

#define MAX_LEN 128

typedef struct {
    char name[MAX_LEN];
    char username[MAX_LEN];
    char ip[MAX_LEN];
    char port[MAX_LEN];
} SSHConfig;

int load_config(const char* filename, SSHConfig* cfg);
void save_config(const SSHConfig* cfg);
void print_info(const char* name);
void edit_connection(const char* name);
void delete_connection(const char* name);
void list_connections();

#endif // CONFIG_H
