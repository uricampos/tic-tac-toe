#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void create_game_board(char board[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            board[i][j] = '-';
        }
    }
}

void create_game_board_check(int board[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            board[i][j] = 0;
        }
    }
}

void show_game_board(char board[3][3])
{
    printf("\n\n");
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            printf("  %c  ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

// Get inputs from user to put the X in the board
void player_game(char board[3][3], int board_check[3][3])
{
    int line, col;
    printf("\n\nDigite a linha e a coluna de onde deseja inserir o X:\n");

    // verifies if line and col are possible to the game
    do
    {
        scanf("%i %i", &line, &col);
    } while (line < 1 || line > 3 || col < 1 || col > 3 || board_check[line - 1][col - 1] != 0);

    // changes the board_check
    board[line - 1][col - 1] = 'X';
    board_check[line - 1][col - 1] = 1;
    
}

void machine_game(char board[3][3], int board_check[3][3])
{
    int line, col;

    // uses randoms numbers between 0 and 3 and puts an O in game;
    do
    {
        line = rand() % 3;
        col = rand() % 3;
    } while (board_check[line][col] != 0);

    board[line][col] = 'O';
    board_check[line][col] = -1;
    
}

int verify_win(int board_check[3][3])
{
    int win = 0, player = 0, machine = 0, velha = 0;

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board_check[i][j] == 1) player++;
            if(board_check[i][j] == -1) machine++;
        }

        if(player == 3)
        {
            win = 1;
            break;
        }
        else player = 0;

        if(machine == 3)
        {
            win = -1;
            break;
        }
        else machine = 0;
    }

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board_check[j][i] == 1) player++;
            if(board_check[j][i] == -1) machine++;
        }

        if(player == 3)
        {
            win = 1;
            break;
        }
        else player = 0;

        if(machine == 3)
        {
            win = -1;
            break;
        }
        else machine = 0;
    }

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(j == i)
            {
                if(board_check[i][j] == 1) player++;
                if(board_check[i][j] == -1) machine++;
            }
        }
    }

    if(player == 3)
    {
        win = 1;
    }
    else player = 0;

    if(machine == 3)
    {
        win = -1;
    }
    else machine = 0;

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(i + j == 2)
            {
                if(board_check[i][j] == 1) player++;
                if(board_check[i][j] == -1) machine++;
            }
        }
    }

    if(player == 3)
    {
        win = 1;
    }
    else player = 0;

    if(machine == 3)
    {
        win = -1;
    }
    else machine = 0;

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board_check[i][j] != 0) velha++;
        }
    }

    if(velha == 9)
    {
        win = 2;
    }
    else velha = 0;

    return win;
}

int main()
{
    srand(time(NULL));
    char board[3][3];
    int board_check[3][3], win = 0;
    create_game_board_check(board_check);
    create_game_board(board);
    show_game_board(board);
    while(1)
    {
        if(win) break;
        player_game(board, board_check);
        show_game_board(board);
        win = verify_win(board_check);
        if(win) break;
        machine_game(board, board_check);
        show_game_board(board);
        win = verify_win(board_check);
    }

    if(win == 1) printf("\nJOGADOR GANHOU!\n");
    if(win == -1) printf("\nCOMPUTADOR GANHOU!\n");
    if(win == 2) printf("\nVELHA!\n");
}