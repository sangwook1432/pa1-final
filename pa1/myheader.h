#ifndef HEADER_H
#define HEADER_H

#include <stddef.h>
#include<stdint.h>

void* memset(void *ptr,int value,size_t num);
char* strchr(const char* str,int character);
char* strstr(const char* str1,const char *str2);
int strcmp(const char* s1, const char* s2);
char *strcpy(char *str1, const char *str2);
size_t strlen(const char* str);
size_t strcspn(const char* s1,const char* s2);
int to_string(char *buffer,uint64_t integer);
static char to_lower(char c);

void operation1(const char* filename,const char* query);
void operation2(const char* filename,const char* query);
void operation3(const char* filename,const char* query);
void operation4(const char* filename,const char* query);

#endif
