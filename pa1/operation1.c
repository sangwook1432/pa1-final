#include "myheader.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

#define MAX_LEN 8192

void search_in_line1(char* line_buffer, const char* query, uint64_t line_number) {
    char* w_p = line_buffer;
    size_t word_length = strlen(query);

    while (1) {
        w_p = strstr(w_p, query);
        if (w_p == NULL) break;
        if((w_p == line_buffer) || (*(w_p - 1) == ' ')){
            if((*(w_p + word_length) == ' ') || (*(w_p + word_length) == '\0')){
                int found_idx = w_p - line_buffer;
                char line_num[21];
                char found[21];
                int len1 = to_string(line_num,line_number);
                int len2 = to_string(found,found_idx);  
                write(STDOUT_FILENO,line_num,len1);
                write(STDOUT_FILENO,":",1);
                write(STDOUT_FILENO,found,len2);
                write(STDOUT_FILENO," ",1);  
            }
        }
        w_p++;
    }
}

void operation1(const char* filename,const char* query){
    int fd = open(filename,O_RDONLY);
    if(fd < 0) return;
    char buffer[1];
    char line_buffer[MAX_LEN];
    int line_idx = 0;
    uint64_t line_number = 1;

    while(read(fd,buffer,1) > 0){
        if(buffer[0] != '\n'){
            if(line_idx < MAX_LEN - 1){
                line_buffer[line_idx++] = buffer[0];
            }
        }
        else{
            line_buffer[line_idx] = '\0';
            search_in_line1(line_buffer,query,line_number);
            line_idx = 0;
            line_number++;
        }
    }

    if(line_idx > 0){
        line_buffer[line_idx] = '\0';
        search_in_line1(line_buffer,query,line_number);
    }
    write(STDOUT_FILENO, "\n", 1);
    close(fd);
}
