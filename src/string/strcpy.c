/* Copyright (C) 2014 Leslie Zhai <xiangzhai83@gmail.com> */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define BUF_SIZE 80

char* LeslieStrcpy(char* dest, char* src) 
{
    while ((*dest++ = *src++) != '\0');

    return dest;
}

char* LeslieStrncpy(char* dest, char* src, size_t n) 
{
    while (n--) 
        *dest++ = *src++;

    return dest;
}

static void log_message(const char *message)                                    
{                                                                               
    FILE *fptr = NULL;                                                          
    char *log_str = NULL;                                                       
    size_t size = -1;                                                           
    time_t cur_time = time(NULL);                                               
    struct tm *local_tm = localtime(&cur_time);                                 
    char *time_str = asctime(local_tm);                                         
                                                                                
    if ((fptr = fopen("/tmp/leetcode.log", "a")) == NULL)        
        return;                                                                 
                                                                                
    size = strlen(time_str) + strlen(message) + 2;                              
    printf("%s\n", time_str);
    printf("%d\n", strlen(time_str));
    if ((log_str = malloc(size)) == NULL) {                                     
        fclose(fptr);                                                           
        fptr = NULL;                                                            
        return;                                                                 
    }                                                                           
    sprintf(log_str, "%s %s\n\n", time_str, message);
    printf("%s\n", log_str);
    printf("%d\n", strlen(log_str));
                                                                                
    fwrite(log_str, sizeof(char), strlen(log_str), fptr);                       
    fflush(fptr);                                                               
                                                                                
    fclose(fptr);                                                               
    fptr = NULL;                                                                
                                                                                
    free(log_str);                                                              
    log_str = NULL;                                                             
}

int main(int argc, char *argv[]) 
{
    char buf[BUF_SIZE] = {'\0'};

#if 0    
    strncpy(buf, "hello", BUF_SIZE);
#endif

    LeslieStrcpy(buf, "111.28.11.12");
#if 0
    LeslieStrncpy(buf, "hello", 3);
#endif
    printf("%s\n", buf);

    log_message("zhaixiang");

    return 0;
}
