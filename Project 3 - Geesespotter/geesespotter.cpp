#include "geesespotter_lib.h"

void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim)
{
   for (std::size_t i = 0; i < (xdim*ydim); i++)
   {
       if (board[i] == 9)
       {
           continue;
       }

       int neighbour_number{};
       int xloc = i%xdim;
       int yloc = i/xdim;

       int searches[8] = {-xdim, -xdim-1, -xdim+1, -1, +1, xdim, xdim-1, xdim+1};

       if (xloc == 0)
       {
           searches[1] = 0;
           searches[3] = 0;
           searches[6] = 0;
       }

       if (xloc == xdim-1)
       {
           searches[2] = 0;
           searches[4] = 0;
           searches[7] = 0;
       }

       if (yloc == 0)
       {
           searches[0] = 0;
           searches[2] = 0;
           searches[1] = 0;
       }

       if(yloc == ydim-1)
       {
           searches[5] = 0;
           searches[7] = 0;
           searches[6] = 0;
       }

       for (int search_i = 0; search_i < 8; search_i++)
       {
           if (board[i+searches[search_i]] == 9)
           {
               ++neighbour_number;
           }
       }

       board[i] = neighbour_number;
   }
}

void hideBoard(char *board, std::size_t xdim, std::size_t ydim)
{
    for (int i = 0; i < (xdim*ydim); i++)
    {
        board[i] += 0x20;
    }
}

void printBoard(char *board, std::size_t xdim, std::size_t ydim)
{
    for (int i = 0; i < (xdim*ydim); i++)
    {
        if (board[i] & 0x10)
        {
            std::cout << "M";
        }
        else if (board[i] & 0x20)
        {
            std::cout << "*";
        }
        else
        {
            std::cout << int(board[i]);
        }


        if (i%(xdim) == xdim-1)
        {
            std::cout << std::endl;
        }
    }
}

int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc)
{
    size_t index = xloc + (xdim*yloc);

    if (board[index] & 0x10)
    {
        return 1;
    }
    else if (board[index] & 0x20)
    {
        board[index] -= 0x20;

        if (board[index] == 0x09)
        {
            return 9;
        }
        else
        {
            if (board[index] == 0)
            {
                int searches[8] = {-xdim, -xdim-1, -xdim+1, -1, +1, xdim, xdim-1, xdim+1};

                   if (xloc == 0)
                   {
                       searches[1] = 0;
                       searches[3] = 0;
                       searches[6] = 0;
                   }

                   if (xloc == xdim-1)
                   {
                       searches[2] = 0;
                       searches[4] = 0;
                       searches[7] = 0;
                   }

                   if (yloc == 0)
                   {
                       searches[0] = 0;
                       searches[2] = 0;
                       searches[1] = 0;
                   }

                   if(yloc == ydim-1)
                   {
                       searches[5] = 0;
                       searches[7] = 0;
                       searches[6] = 0;
                   }

                   for (int search_i = 0; search_i < 8; search_i++)
                   {
                       if (searches[search_i] == 0)
                       {
                           continue;
                       }

                       if (!(board[index+searches[search_i]] & 0x10))
                       {
                           if (board[index+searches[search_i]] & 0x20)
                           {
                              board[index+searches[search_i]] -= 0x20;
                           }
                       }
                   }
            }

            return 0;
        }
    }
    else
    {
        return 2;
    }
}

int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc)
{
    size_t index = xloc + (xdim*yloc);

    if (board[index] & 0x10)
    {
        board[index] -= 0x10;
    }
    else if (board[index] & 0x20)
    {
        board[index] += 0x10;
    }
    else
    {
        return 2;
    }

    return 0;
}

char *createBoard(std::size_t xdim, std::size_t ydim)
{
    int element_number{xdim*ydim};

    char *board{new char[element_number]{}};

    return board;
}

void cleanBoard(char *board)
{
    delete[] board;
    board = nullptr;
}

bool isGameWon(char *board, std::size_t xdim, std::size_t ydim)
{
    bool won{true};

    for (std::size_t index = 0; index < (xdim*ydim); index++)
    {
        if (board[index] & 0x10)
        {
            char temp{board[index]-0x30};
            if (temp != 0x9)
            {
                won = false;
            }
        }
        else if (board[index] & 0x20)
        {
            char temp{board[index]-0x20};
            if (temp != 0x9)
            {
                won = false;
            }
        }
    }

    return won;
}

