#include "myheader.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

#define MAX_LEN 8192
#define USER_MAX_INPUT 4096

int search_in_line2(const char* line_buffer, const char* word) {
    const char* w_p = line_buffer;
    size_t word_length = strlen(word);

    while (1) {
        w_p = strstr(w_p, word);
        if (w_p == NULL) return -1;
        if((w_p == line_buffer) || (*(w_p - 1) == ' ')){
            if((*(w_p + word_length) == ' ') || (*(w_p + word_length) == '\0')){
                return 1; 
            }
        }
        w_p++;
    }
}

void operation2(const char* filename,const char* query){
    char query_1[USER_MAX_INPUT];
    strcpy(query_1,query);

    char *words[400];
    int idex = 0;

    char *curr_word = query_1;
    char *ptr = query_1;

    while(*ptr != '\0'){
        if(*ptr == ' '){
            *ptr = '\0';
            words[idex++] = curr_word;
            curr_word = ptr+1;
        }
        ptr++;
    }

    words[idex++] = curr_word;

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
            
            int flag = 1;
            for(int i = 0;i < idex;i++){
                if(search_in_line2(line_buffer,words[i]) != 1){
                    flag = -1;
                    break;
                }
            }

            if(flag == 1){
                char line_num[21];
                int len = to_string(line_num,line_number);
                write(STDOUT_FILENO,line_num,len);
                write(STDOUT_FILENO," ",1);
            }

            line_idx = 0;
            line_number++;
        }
    }

    if(line_idx > 0){
        line_buffer[line_idx] = '\0';
        int flag = 1;
        for(int i = 0;i < idex;i++){
            if(search_in_line2(line_buffer,words[i]) != 1){
                flag = -1;
                break;
            }
        }
        if(flag == 1){
            char line_num[21];
            int len = to_string(line_num,line_number);
            write(STDOUT_FILENO,line_num,len);
            write(STDOUT_FILENO," ",1);
        }
    }

    write(STDOUT_FILENO,"\n",1);
    close(fd);
}
