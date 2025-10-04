#include "myheader.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_LEN 8192
#define USER_MAX_INPUT 4096

void search_in_line3(char* line_buffer, const char* query, uint64_t line_number) {
    char* w_p = line_buffer;
    size_t phrase_len = strlen(query);
    while (1) {
        w_p = strstr(w_p, query);
        if (w_p == NULL) break;
        
        if((w_p == line_buffer) || *(w_p - 1) == ' '){
		if((*(w_p + phrase_len) == ' ') || *(w_p + phrase_len) ==  '\0'){
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

void operation3(const char* filename,const char* query){
    size_t query_len = strlen(query);
    if(query_len < 2 || query[0] != '"' || query[query_len-1] != '"' ) return;

    char query1[USER_MAX_INPUT];
    strcpy(query1,query+1);
    query1[query_len - 2] = '\0';

    int fd = open(filename,O_RDONLY);
    if(fd < 0) return;

    char* line_buffer = (char*)malloc(MAX_LEN);
    if (!line_buffer) { 
        close(fd); 
        return; 
    }
    size_t buffer_size = MAX_LEN;

    char buffer[1];
    int line_idx = 0;
    uint64_t line_number = 1;

    while(read(fd,buffer,1) > 0){
        if(buffer[0] != '\n'){
            if (line_idx >= buffer_size - 1) {
                buffer_size *= 2;
                char* new_buffer = (char*)realloc(line_buffer, buffer_size);
                if (!new_buffer) {
                    free(line_buffer);
                    close(fd);
                    return;
                }
                line_buffer = new_buffer;
            }
            line_buffer[line_idx++] = buffer[0];
        }
        else{
            line_buffer[line_idx] = '\0';
            search_in_line3(line_buffer,query1,line_number);
            line_idx = 0;
            line_number++;
        }
    }

    if(line_idx > 0){
        line_buffer[line_idx] = '\0';
        search_in_line3(line_buffer,query1,line_number);
    }

    free(line_buffer);
    write(STDOUT_FILENO,"\n",1);
    close(fd);
}
