#include <stdio.h>

#include <stdlib.h>

#include <ctype.h>

#include <string.h>

#include <pthread.h>

#include "Board_Splitter.h"

FILE* output;

time_t start;

time_t end;

int row = 0, column = 0, genr_num = 0, view_size = 0, *view;

#define thread_numbs 1

void input_file(char* f_name)
{
    FILE* read;

    read = fopen(f_name, "read_file");
    
    if (!read)
    {
        printf("Failed !");
        exit(EXIT_FAILURE);
    }

    fscanf(read, "%d %d %d", &genr_num, &row, &c);
    view_size = row * column;
    view = malloc(sizeof(int) * view_size);

    int read_char = 0;
    int pointer = 0;

    do 
    {
        read_char = fgetc(read);
        if (EOF != read_char) 
        {
            // Ignore whitsespace in reading in the string
            if (!isspace(read_char)) 
            {
                if ('*' == read_char)
                {
                    view[pointer] = 1;
                    pointer = pointer + 1;
                }
                else if ('.' == read_char)
                {
                    view[pointer] = 0;
                    pointer = pointer + 1;
                }                
            }
        }
    } while (EOF != read_char);

    fclose(read);
    if (pointer != view_size)
    {
        printf("Input Error !");
        free(view);
        exit(EXIT_FAILURE);
    }
}

void BoardClass(void)
{
    memcpy(view, copy, view_size * sizeof(int));
}

int main(int argc, char** argv)
{
   input_file(argv[1]);
   
   copy = malloc(sizeof(int) * view_size);

   memcpy(copy, view, view_size * sizeof(int));

   pthread_t* threads;
   thread_param_t* param;
    
  

    threads = malloc(thread_numbs * sizeof(pthread_t));
    param = malloc(thread_numbs * sizeof(thread_param_t));

    splitview(param, thread_numbs, row, c);
    
    start = clock();

    for (i = 0; i < thread_numbs; i++) 
    {
        pthread_join(threads[i], NULL);
    }

    end = clock();

    
    free(threads);
    free(param);

    return 0;
}
