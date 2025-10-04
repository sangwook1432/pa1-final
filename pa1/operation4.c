#include "myheader.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_LEN 8192
#define USER_MAX_INPUT 4096

char* search_in_line4(const char* line_buffer, const char* word) {
    const char* w_p = line_buffer;
    size_t word_length = strlen(word);
    
    while (1) {
        w_p = strstr(w_p, word);
        if (w_p == NULL) return NULL;
        if((w_p == line_buffer) || (*(w_p - 1) == ' ')){
            if((*(w_p + word_length) == ' ') || (*(w_p + word_length) == '\0')){
                return (char*) w_p;
            }
        }
        w_p++;
    }
}

void operation4(const char* filename,const char* query){
    int fd = open(filename,O_RDONLY);
    if(fd < 0) {
        write(STDOUT_FILENO,"\n",1);
        return;
    }
    size_t capacity = MAX_LEN;
    char* line_buffer = malloc(sizeof(char) * capacity);
    if (line_buffer == NULL) {
        close(fd);
        write(STDOUT_FILENO, "\n", 1);
        return;
    }
    char buffer[1];
    int line_idx = 0;
    uint64_t line_number = 1;

    if (strchr(query, ' ') != NULL || strchr(query, '*') == NULL) {
        write(STDOUT_FILENO,"\n",1);
        return;
    }
    char query_1[USER_MAX_INPUT];
    strcpy(query_1,query);

    char* word1 = query_1;
    char* star_pos = strchr(query_1, '*');
    
    if (star_pos == query_1 || *(star_pos + 1) == '\0') {
        write(STDOUT_FILENO,"\n",1); // 규칙 위반: '*'가 맨 앞이나 맨 뒤에 있는 경우
        return;
    }

    *star_pos = '\0';
    char *word2 = star_pos + 1;

    while(read(fd,buffer,1) > 0){
        if (line_idx >= capacity - 1) {
            capacity *= 2;
            char* new_buffer = realloc(line_buffer, capacity);
            if (new_buffer == NULL) {
                free(line_buffer);
                close(fd);
                write(STDOUT_FILENO, "\n", 1);
                return;
            }
            line_buffer = new_buffer;
        }
        if(buffer[0] != '\n'){
            if(line_idx < MAX_LEN - 1){
                line_buffer[line_idx++] = buffer[0];
            }
        }
        else{
            line_buffer[line_idx] = '\0';
            char *pos1 = search_in_line4(line_buffer,word1);
            if(pos1 != NULL){
                pos1 += strlen(word1);
                if(search_in_line4(pos1,word2) != NULL){
                    char line_num[21];
                    int len = to_string(line_num,line_number);
                    write(STDOUT_FILENO,line_num,len);
                    write(STDOUT_FILENO," ",1);
                }
            }
            line_idx = 0;
            line_number++;
        }
    }

    if (line_idx > 0) {
        line_buffer[line_idx] = '\0';
        char* pos1_l = search_in_line4(line_buffer, word1);
        if (pos1_l != NULL) {
            pos1_l += strlen(word1);
            if (search_in_line4(pos1_l, word2) != NULL) {
                    char line_num[21];
                    int len = to_string(line_num,line_number);
                    write(STDOUT_FILENO,line_num,len);
                    write(STDOUT_FILENO," ",1);
            }
        }
    }
    free(line_buffer);
    write(STDOUT_FILENO,"\n",1);
    close(fd);
}
