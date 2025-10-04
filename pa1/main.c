
#include "myheader.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

#define MAX_LINE_LENGTH 8192

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        const char* err_msg = "Usage: ./pa1 <search_file>\n";
        write(STDERR_FILENO, err_msg, strlen(err_msg));
        return 1;
    }

    const char* search_filename = argv[1];

    int query_fd = STDIN_FILENO;

    char read_char_buf[1];
    char query_line_buffer[MAX_LINE_LENGTH];
    int line_idx = 0;

    while (read(query_fd, read_char_buf, 1) > 0) {
        if (read_char_buf[0] != '\n') {
            if (line_idx < MAX_LINE_LENGTH - 1) {
                query_line_buffer[line_idx++] = read_char_buf[0];
            }
        } else {
            query_line_buffer[line_idx] = '\0';

            if (strcmp(query_line_buffer, "PA1EXIT") == 0) {
                break;
            }
    
            if (strchr(query_line_buffer, '"') != NULL) {
                operation3(search_filename, query_line_buffer);
            } 
            else if (strchr(query_line_buffer, '*') != NULL) {
                operation4(search_filename, query_line_buffer);
            } 
            else if (strchr(query_line_buffer, ' ') != NULL) {
                operation2(search_filename, query_line_buffer);
            } 
            else {
                operation1(search_filename, query_line_buffer);
            }
            line_idx = 0;
        }
    }

    if (line_idx > 0) {
        query_line_buffer[line_idx] = '\0';
        if (strcmp(query_line_buffer, "PA1EXIT") != 0) {
            if (strchr(query_line_buffer, '"') != NULL) {
                operation3(search_filename, query_line_buffer);
            } 
            else if (strchr(query_line_buffer, '*') != NULL) {
                operation4(search_filename, query_line_buffer);
            } 
            else if (strchr(query_line_buffer, ' ') != NULL) {
                operation2(search_filename, query_line_buffer);
            } 
            else {
                operation1(search_filename, query_line_buffer);
            }
        }
    }
    
    return 0;
}

