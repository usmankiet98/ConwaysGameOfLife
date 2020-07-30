#include "split-the-board.h"

int view_board(thread_param_t* t_list, int t_count, int rows, int columns)
{

    if ((rows / t_count) != 0)
    {
        int new_row = rows % t_count;

        int max_per = rows / t_count;

        int current_row = 0;

        for (int i = 0; i < t_count; ++i)
        {
            if (new_row > 0)
            {
                t_list[i].f_row = current_row;

                t_list[i].f_col = 0;

                t_list[i].length = (max_per + 1) * columns;

                current_row += max_per + 1;

                --new_row;
            }
            else
            {
                t_list[i].f_row = current_row;

                t_list[i].f_col = 0;

                t_list[i].length = max_per * columns;

                current_row += max_per;
            }
        }
    }
    else if (t_count > (rows * columns))
    {
        int extra = 0;

        extra = t_count - (rows * columns);

        int current_row = 0;

        int current_col = 0;

        for (int i = 0; i < t_count; ++i)
        {
            if ((t_count - i) > extra)
            {
                t_list[i].f_row = current_row;

                t_list[i].f_col = current_col;

                t_list[i].length = 1;

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
                t_list[i].f_row = 0;

                t_list[i].f_col = 0;

                t_list[i].length = 0;
            }
        }
    }
    else
    {
        int current_row = 0;

        int current_col = 0;

        for (int i = 0; i < t_count; ++i)
        {

            if ((t_count - i) > (rows - current_row))
            {
                t_list[i].f_row = current_row;

                t_list[i].f_col = current_col;

                t_list[i].length = 1;

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
                    int columns_left = columns - current_col;

                    t_list[i].f_row = current_row;

                    t_list[i].f_col = current_col;

                    t_list[i].length = columns_left;

                    current_col = 0;

                    ++current_row;
                }
                else
                {
                    t_list[i].f_row = current_row;

                    t_list[i].f_col = current_col;

                    t_list[i].length = columns;

                    ++current_row;
                }
            }
        }
    }

    return 0;
}
