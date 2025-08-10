#include "ssh.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void read_input(char* buffer, size_t size) {
    if (fgets(buffer, (int)size, stdin)) {
        char* newline = strchr(buffer, '\n');
        if (newline) *newline = '\0';
    }
}

void create_new_connection(SSHConfig* existing) {
    SSHConfig cfg = { 0 };
    if (existing) cfg = *existing;

    printf("Name [%s]: ", cfg.name);
    read_input(cfg.name, MAX_LEN);

    printf("User [%s]: ", cfg.username);
    read_input(cfg.username, MAX_LEN);

    printf("IP [%s]: ", cfg.ip);
    read_input(cfg.ip, MAX_LEN);

    printf("Port [%s] (default 22): ", cfg.port);
    read_input(cfg.port, MAX_LEN);
    if (strlen(cfg.port) == 0) strcpy_s(cfg.port, MAX_LEN, "22");

    save_config(&cfg);
}

void start_connectionnw(const char* name) {
    SSHConfig cfg = { 0 };
    char filename[256];
    sprintf_s(filename, sizeof(filename), "%s\\%s.ezssh", ".", name);
    if (!load_config(filename, &cfg)) {
        printf("Connection %s does not exist.\n", name);
        return;
    }
    char command[512];
    sprintf_s(command, sizeof(command), "start cmd /k ssh %s@%s -p %s", cfg.username, cfg.ip, cfg.port);
    printf("Running: %s\n", command);
    system(command);
}
void start_connection(const char* name) {
    SSHConfig cfg = { 0 };
    char filename[256];
    sprintf_s(filename, sizeof(filename), "%s\\%s.ezssh", ".", name);
    if (!load_config(filename, &cfg)) {
        printf("Connection %s does not exist.\n", name);
        return;
    }
    char command[512];
    sprintf_s(command, sizeof(command), "ssh %s@%s -p %s", cfg.username, cfg.ip, cfg.port);
    printf("Running: %s\n", command);
    system(command);
}