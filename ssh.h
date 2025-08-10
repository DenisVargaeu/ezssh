#ifndef SSH_H
#define SSH_H

#include "config.h"

void start_connection(const char* name);
void create_new_connection(SSHConfig* existing);
void read_input(char* buffer, size_t size);

#endif // SSH_H
