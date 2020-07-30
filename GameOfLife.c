#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#include "split-the-board.h"
#include "cycle-of-barrier.h"

#define NUMBER_OF_THREADS 10

int rows = 0;
int columns = 0;
int production = 0;
int size = 0;
int* board;
int* duplicate;

// Returns a pointer to an int array corresponding to the board in f_name.
// The array is in row-major order.
void read_view(char* f_name)
{
    FILE* input;
    input = fopen(f_name, "r");
    if (!input)
    {
        printf("Opening file failed !");
        exit(EXIT_FAILURE);
    }

    fscanf(input, "%d %d %d", &production, &rows, &columns);
    size = rows * columns;
    board = malloc(sizeof(int) * size);

    int charac = 0;
    int pointer = 0;

    do 
    {
        charac = fgetc(input);
        if (EOF != charac) 
        {

            if (!isspace(charac)) 
            {
                if ('*' == charac)
                {
                    board[pointer] = 1;
                    pointer = pointer + 1;
                }
                else if ('.' == charac)
                {
                    board[pointer] = 0;
                    pointer = pointer + 1;
                }                
            }
        }
    } while (EOF != charac);

    fclose(input);
    // Make sure we actually initialized our board properly
    if (pointer != size)
    {
        printf("Invalid file input.");
        free(board);
        exit(EXIT_FAILURE);
    }
}

void show_view(FILE* output)
{
    for (int position = 0; position < size; ++position)
    {
        if (((position % columns) == 0) ^ (position == 0))
        {
	    fprintf(output, "\n");
        }
        fprintf(output, "%c", (board[position] == 0 ? '.' : '*'));
    }
}

void production_process(thread_param_t* original)
{
    int starting_point = (original->f_row * columns) + original->f_col;

    int row = 0;
    int col = 0;
    int related = 0;

    for (int index = starting_point; index < (starting_point + original->length); ++index)
    {
        related = 0;
        row = index / columns;
        col = index % (columns);

        // check previous row for related
        if (row != 0)
        {
            if (board[index - columns] == 1)
            {
                ++related;
            }

            if (col != 0)
            {
                if (board[index - columns - 1] == 1)
                    ++related;
            }
            if (col != (columns - 1))
            {
                if (board[index - columns + 1] == 1)
                    ++related;
            }
        }

        // check current row for related
        if (col != 0)
        {
            if (board[index - 1] == 1)
            {
                ++related;
            }
        }
        if (col != (columns - 1))
        {
            if (board[index + 1] == 1)
            {
                ++related;
            }
        }

        // check next row for related;
        if (row != (rows - 1))
        {
            if (board[index + columns] == 1)
            {
                ++related;
            }

            if (col != 0)
            {
                if (board[index + columns - 1] == 1)
                    ++related;
            }
            if (col != (columns - 1))
            {
                if (board[index + columns + 1] == 1)
                    ++related;
            }
        }
        if ((related >= 4) || (related <= 1))
        {
            duplicate[index] = 0;
        }
        if ((board[index] == 0) && (related == 3))
        {
            duplicate[index] = 1;
        }
    }
}

void* thread_run(void* arguments)
{
    thread_param_t* original;
    original = (thread_param_t*)arguments;
    int value = 0;

    for (int gen = 0; gen < production; ++gen)
    {
        production_process(original);

        value = cyclic_barrier_await(original->barrier);
    }

    return NULL;
}

void synchronizeBoard(void)
{
    memcpy(board, duplicate, size * sizeof(int));
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Run this program with the board file name argument.");
        exit(EXIT_FAILURE);
    }

    FILE* output;
    time_t start;
    time_t end;

    //initialize board
    read_view(argv[1]);
    duplicate = malloc(sizeof(int) * size);

    memcpy(duplicate, board, size * sizeof(int));

    //set up threading stuff
    pthread_t* threads;
    thread_param_t* parameters;
    cyclic_barrier_t barrier;
    int index = 0;

    threads = malloc(NUMBER_OF_THREADS * sizeof(pthread_t));
    parameters = malloc(NUMBER_OF_THREADS * sizeof(thread_param_t));

    view_board(parameters, NUMBER_OF_THREADS, rows, columns);

    cyclic_barrier_init(&barrier, NULL, NULL, NUMBER_OF_THREADS, synchronizeBoard);

    for (index = 0; index < NUMBER_OF_THREADS; index++) 
    {
        parameters[index].barrier = &barrier;
        pthread_create(&threads[index], NULL, thread_run, &parameters[index]);
    }

    start = clock();

    for (index = 0; index < NUMBER_OF_THREADS; index++) 
    {
        pthread_join(threads[index], NULL);
    }

    end = clock();

    printf("Runtime was %.6f\n", ((double)(end-start)) / 1.0E6);
    
    //print final board to specified output file or to stdout
    if(1 < argc)
    {
        output = fopen(argv[2], "w");
    }
    else
    {
       output = stdout;
    }
    
    show_view(output);
    
    if(output != stdout)
    {
	fclose(output);
    }

    cyclic_barrier_destroy(&barrier);

    free(board);
    free(duplicate);
    free(parameters);
    free(threads);

    return 0;
}
