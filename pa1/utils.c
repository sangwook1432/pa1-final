#include "myheader.h"
#include <stdint.h>

size_t strlen(const char* str) {
    size_t len; // size_t로 타입 일치
    for (len = 0; str[len] != '\0'; len++);
    return len;
}

void* memset(void *ptr,int value,size_t num){
    int i;
    unsigned char *p = ptr;
    i = 0;
    while(num > 0){
        *p = value;
        p++;
        num--;
    }
    return ptr;
}

char* strchr(const char *str,int character){
    for(;*str != '\0';++str){
        if(*str == (char)character) return (char*)str;
    }
    if(character == '\0') return (char*)str;
    return NULL;
}
// string에서 찾고자하는 integer값이 처음으로 발견되는 곳의 주소를 넘김

int strcmp(const char* s1, const char* s2){
    int ret = 0;
    while(!(ret = *(unsigned char *)s1 - *(unsigned char *)s2) && *s2){
        s1++;
        s2++;
    }
    if(ret < 0) ret = -1;
    else if(ret > 0) ret = 1;
    return ret;
}

size_t strcspn(const char* s1,const char* s2){
    size_t count = 0;
    char char_map[256] = {0};

    while(*s2 != '\0'){
        char_map[(unsigned char)*s2] = 1;
        s2++;
    }
    while(*s1 != '\0'){
        if(char_map[(unsigned char)*s1] == 1){
            return count;
        }
        count++;
        s1++;
    }
    return count;
}
// string에서 찾고자하는 string의 위치 integer로 rtn (d는 str1[3]이므로 3 return)

static char to_lower(char c){
	if(c >= 'A' && c <= 'Z'){
		return c + ('a' - 'A');
	}
	return c;
}

char* strstr(const char* str1,const char *str2){
    if(*str2 == '\0') return (char*) str1;
    for(; *str1 != '\0' ; str1++){
        const char *h = str1;
        const char *n = str2;
    
        while(*h != '\0' && *n != '\0' && to_lower(*h) == to_lower(*n)){
            h++;
            n++;
        }

        if(*n == '\0'){
            return (char*)str1;
        }
    }
    return NULL;
}

char *strcpy(char *str1, const char *str2){
   char *saved = str1;
   while(*str2){
        *str1++ = *str2++;
    }
    *str1 = 0;
    return saved;
}


int to_string(char *buffer,uint64_t integer) {
    char temp_buf[21];
    int i = 20;
    temp_buf[i] = '\0';
    i--;
    if(integer == 0){
        buffer[0] = '0';
        buffer[1] = '\0';
        return 1;
    }

    uint64_t n = integer;
    while(n > 0){
        temp_buf[i] = (n % 10) + '0';
        n /= 10;
        i--;
    }

    strcpy(buffer,&temp_buf[i+1]);
    int len = 20 - (i+1);
    return len;
}
