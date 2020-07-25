#include "Board_Splitter.h"

int Board(thread_param_t* list, int counter, int rows, int columns)
{
    if ((rows / counter) != 0)
    {
        int row = rows % counter;
        int row_per = rows / counter;

        int current_row = 0;
        for (int i = 0; i < counter; ++i)
        {
            if (row > 0)
            {
                list[i].first_row = current_row;
                list[i].firstCol = 0;
                list[i].length = (row_per + 1) * columns;
                current_row += row_per + 1;
                --row;
            }
            else
            {
                list[i].first_row = current_row;
                list[i].firstCol = 0;
                list[i].length = row_per * columns;
                current_row += row_per;
            }
        }
    }
    else if (counter > (rows * columns))
    {
        int overflow = 0;
        overflow = counter - (rows * columns);
        int current_row = 0;
        int current_col = 0;

        for (int i = 0; i < counter; ++i)
        {
            if ((counter - i) > overflow)
            {
                list[i].first_row = current_row;
                list[i].firstCol = current_col;
                list[i].length = 1;

                if ((current_col + 1) >= columns)
                {
                    current_col = 0;
                    ++current_row;
                }
                else
                {
                    ++current_col;
                }
            }
            else
            {
                list[i].first_row = 0;
                list[i].firstCol = 0;
                list[i].length = 0;
            }
        }
    }
    else
    {
        int current_row = 0;
        int current_col = 0;

        for (int i = 0; i < counter; ++i)
        {
            if ((counter - i) > (rows - current_row))
            {
                list[i].first_row = current_row;
                list[i].firstCol = current_col;
                list[i].length = 1;

                if ((current_col + 1) >= columns)
                {
                    current_col = 0;
                    ++current_row;
                }
                else
                {
                    ++current_col;
                }
            }
            else
            {             
                if (current_col != 0)
                {
                    int columnsLeft = columns - current_col;
                    list[i].first_row = current_row;
                    list[i].firstCol = current_col;
                    list[i].length = columnsLeft;

                    current_col = 0;
                    ++current_row;
                }
                else
                {
                    list[i].first_row = current_row;
                    list[i].firstCol = current_col;
                    list[i].length = columns;

                    ++current_row;
                }
            }
        }
    }

    return 0;
}