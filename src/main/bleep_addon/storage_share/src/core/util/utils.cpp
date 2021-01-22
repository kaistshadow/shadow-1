//
// Created by csrc on 20. 12. 24..
//

#include "utils.h"

#include "../datatypes/datatype.h"

#include <string>
#include <unistd.h>
#include <cstdio>

int init_fd_assignment_system() {
    FILE* f = fopen("bleep_fd_assign", "a");
    int basefd = dup(fileno(f));
    fclose(f);
	return basefd;
}
int try_assign_unused_fd() {
	static int basefd = init_fd_assignment_system();
    return dup(basefd);
}
int free_fd(int fd) {
    return close(fd);
}

// filemode parsing function
int parse_filemode(const char* mode) {
    int flag = 0;

    // parse fisrt letter
    switch(mode[0]) {
    case 'r':
        flag |= _FILEMODE_READ;
        break;
    case 'w':
        flag |= _FILEMODE_WRITE;
        flag |= _FILEMODE_CREATE;
        flag |= _FILEMODE_TRUNCATE;
        break;
    case 'a':
        flag |= _FILEMODE_READ;
        flag |= _FILEMODE_CREATE;
        flag |= _FILEMODE_APPEND;
        break;
    default:
        // error case
        return 0;
    }

    int i = 1;
    while(mode[i] != 0) {
        if (mode[i] == 'b') {
            flag |= _FILEMODE_BINARY;
        } else if (mode[i] == '+') {
            flag |= _FILEMODE_READ;
            flag |= _FILEMODE_WRITE;
        }
        i++;
    }

    return flag;
}

int random_name_base = 0;
std::string generate_filename(datatype* dtype, size_t* startoffset) {
    char random_text[30];
    sprintf(random_text, "%d-%d.txt", dtype->get_typeid(), random_name_base++);
    *startoffset = 0;

    return std::string(random_text);
}