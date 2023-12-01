#include <vector>
#include <iostream>
#include <utility>

#define ROWS 5
#define COLS 5

using namespace std;

// utility functions
void printBoard(vector <vector <int>> board)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int evaluate(vector <vector <int>> board)
{
    // return 1 if player 1 wins, 2 if player 2 wins, 3 if its a draw and 0 otherwise.
    
    // horizontal check
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS-3; j++)
        {
            if (board[i][j] == 1 || board[i][j] ==2)
            {
                if (board[i][j] == board[i][j+1] && board[i][j+1] == board[i][j+2] && board[i][j+2] == board[i][j+3])
                {
                    return board[i][j];
                }
            }
        }
    } 

    // vertical check
    for (int i = 0; i < ROWS-3; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j] == 1 || board[i][j] ==2)
            {
                if (board[i][j] == board[i+1][j] && board[i+1][j] == board[i+2][j] && board[i+2][j] == board[i+3][j])
                {
                    return board[i][j];
                }
            }
        }
    } 

    // Diagonal check (positive slope)
    for (int i = 0; i < ROWS - 3; i++)
    {
        for (int j = 0; j < COLS - 3; j++)
        {
            if (board[i][j] == 1 || board[i][j] == 2)
            {
                if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1] == board[i + 2][j + 2] && board[i + 2][j + 2] == board[i + 3][j + 3])
                {
                    return board[i][j];
                }
            }
        }
    }

    // Diagonal check (negative slope)
    for (int i = 3; i < ROWS; i++)
    {
        for (int j = 0; j < COLS - 3; j++)
        {
            if (board[i][j] == 1 || board[i][j] == 2)
            {
                if (board[i][j] == board[i - 1][j + 1] && board[i - 1][j + 1] == board[i - 2][j + 2] && board[i - 2][j + 2] == board[i - 3][j + 3])
                {
                    return board[i][j];
                }
            }
        }
    }

    // check if game can be continued
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j] == 0)
            {
                return 0;
            }
        }
    } 

    // draw condition
    return 3;
}

bool isValid(vector <vector <int>> &board, int c)
{
    if (board[0][c] == 0)
    {
        return true;
    }
    return false;
}

void insert (vector <vector <int>> &board, int c, int player)
{
    if (board[ROWS-1][c] == 0)
    {
        board[ROWS-1][c] = player;
        return;
    }

    for (int i = 1; i < ROWS; i++)
    {
        if (board[i][c] > 0)
        {
            board[i-1][c] = player;
            break;
        }
    }
}

int main ()
{
    vector <vector <int>> board (ROWS, vector <int> (COLS));
    printBoard(board);

    while (evaluate(board) == 0)
    {
        cout << "Player 1 plays....\n";
        int c;
        cout << "Enter your column: ";
        cin >> c;
        while (!isValid(board, c))
        {
            cout << "Invalid choice. Please choose your column: ";
            cin >> c;
        }
        insert(board, c, 1);

        printBoard(board);

        if (evaluate(board) != 0)
        {
            break;
        }

        cout << "Player 2 plays....\n";
        cout << "Enter your column: ";
        cin >> c;
        while (!isValid(board, c))
        {
            cout << "Invalid choice. Please choose your column: ";
            cin >> c;
        }
        insert(board, c, 2);
        printBoard(board);
    }

    int x = evaluate(board);
    if (x == 1)
    {
        cout << "Bingo! Player 1 wins the game.";
    }
    else if (x == 2)
    {
        cout << "Bingo! Player 2 win the game.";
    }
    else
    {
        cout << "The game ends as a draw!";
    }
    cout << endl;

    return 0;
}