#include <vector>
#include <iostream>

#define ROWS 6
#define COLS 7

using namespace std;

class Bingo
{
    public:
    int board [ROWS][COLS] = {0};
    bool result;

    void printBoard();
    bool isValid(int i, int j, int player);
    bool eval();
};

void Bingo::printBoard()
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

bool Bingo::isValid(int i, int j, int player)
{
    if (i < ROWS && i >= 0 && j < COLS && j >= 0)
    {
        if (board[i][j] == 0)
        {
            if (i == ROWS-1)
            {
                board[i][j] = player;
                return true;
            }
            else
            {
                if (board[i+1][j] == 0)
                {
                    cout << "Can't Capture The Given Position. Please Try Again";
                    return false;
                }
                else
                {
                    board[i][j] = player;
                    return true;
                }
            }
        }
        else
        {
            cout << "Invalid Position. Please Try Again" << endl;
            return false;
        }
    }
    else
    {
        cout << "Invalid Position. Please Try Again." << endl;
        return false;
    }
}

bool Bingo::eval()
{
    // horizontal check
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS-3; j++)
        {
            if (board[i][j] == 1 || board[i][j] ==2)
            {
                if (board[i][j] == board[i][j+1] && board[i][j+1] == board[i][j+2] && board[i][j+2] == board[i][j+3])
                {
                    result = 1;
                    return false;
                }
            }
        }
    } 

    // vecrtical check
    for (int i = 0; i < ROWS-3; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j] == 1 || board[i][j] ==2)
            {
                if (board[i][j] == board[i+1][j] && board[i+1][j] == board[i+2][j] && board[i+2][j] == board[i+3][j])
                {
                    result = 1;
                    return false;
                }
            }
        }
    } 

    // positive diagonal check

    // negative diagonal check

    // tie check
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS-2; j++)
        {
            if (board[i][j] == 0)
            {
                return true;
            }
        }
    } 
    return false;
}

int main()
{
    Bingo B;
    B.printBoard();
    int player = 1;

    while(B.eval())
    {
        // accept the coordinates
        int i, j;
        cout << "Please enter the position: ";
        cin >> i >> j;

        if (B.isValid(i, j, player))
        {
            // invert the player
            if (player == 1)
            {
                player = 2;
            }
            else
            {
                player = 1;
            }
        }
        B.printBoard();
    }

    if (B.result)
    {
        cout << "//////////" << endl << "Player " << player << " Wins!" << endl << "//////////" << endl;
    }
    else
    {
        cout << "////" << endl << "Draw" << endl << "////" << endl;
    }
    
    return 0;
}