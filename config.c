#include "config.h"
#include <stdio.h>
#include <string.h>
#include <io.h>      // for _findfirst etc.
#include <stdlib.h>

static char folder[] = ".";

int load_config(const char* filename, SSHConfig* cfg) {
    FILE* f = NULL;
    if (fopen_s(&f, filename, "r") != 0 || f == NULL) return 0;

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        char key[64] = { 0 };
        char value[128] = { 0 };
        sscanf_s(line, "%63[^=]=%127s", key, (unsigned)_countof(key), value, (unsigned)_countof(value));
        if (strcmp(key, "name") == 0) strcpy_s(cfg->name, MAX_LEN, value);
        else if (strcmp(key, "username") == 0) strcpy_s(cfg->username, MAX_LEN, value);
        else if (strcmp(key, "ip") == 0) strcpy_s(cfg->ip, MAX_LEN, value);
        else if (strcmp(key, "port") == 0) strcpy_s(cfg->port, MAX_LEN, value);
    }

    fclose(f);
    return 1;
}

void save_config(const SSHConfig* cfg) {
    char filename[256];
    sprintf_s(filename, sizeof(filename), "%s\\%s.ezssh", folder, cfg->name);

    FILE* f = NULL;
    if (fopen_s(&f, filename, "w") != 0 || f == NULL) {
        printf("Failed to save.\n");
        return;
    }

    fprintf(f, "name=%s\n", cfg->name);
    fprintf(f, "username=%s\n", cfg->username);
    fprintf(f, "ip=%s\n", cfg->ip);
    fprintf(f, "port=%s\n", cfg->port);
    fclose(f);
    printf("Connection '%s' saved successfully.\n", cfg->name);
}

void print_info(const char* name) {
    SSHConfig cfg = { 0 };
    char filename[256];
    sprintf_s(filename, sizeof(filename), "%s\\%s.ezssh", folder, name);
    if (!load_config(filename, &cfg)) {
        printf("Connection %s does not exist.\n", name);
        return;
    }
    printf("Connection: %s\n", cfg.name);
    printf("User: %s\n", cfg.username);
    printf("IP: %s\n", cfg.ip);
    printf("Port: %s\n", cfg.port);
}

void edit_connection(const char* name) {
    SSHConfig cfg = { 0 };
    char filename[256];
    sprintf_s(filename, sizeof(filename), "%s\\%s.ezssh", folder, name);
    if (!load_config(filename, &cfg)) {
        printf("Connection %s does not exist.\n", name);
        return;
    }
    // Call the edit function here, which can be in ssh.c (see below)
}

void delete_connection(const char* name) {
    char filename[256];
    sprintf_s(filename, sizeof(filename), "%s\\%s.ezssh", folder, name);
    if (remove(filename) == 0) {
        printf("Connection '%s' deleted.\n", name);
    }
    else {
        printf("Failed to delete connection.\n");
    }
}

void list_connections() {
    struct _finddata_t c_file;
    intptr_t hFile;
    char path[256];
    sprintf_s(path, sizeof(path), "%s\\*.ezssh", folder);
    hFile = _findfirst(path, &c_file);
    if (hFile == -1L) {
        printf("No saved connections.\n");
        return;
    }

    printf("List of connections:\n");
    do {
        char name[128];
        strncpy_s(name, sizeof(name), c_file.name, _TRUNCATE);
        char* dot = strchr(name, '.');
        if (dot) *dot = '\0';
        printf(" - %s\n", name);
    } while (_findnext(hFile, &c_file) == 0);
    _findclose(hFile);
}
