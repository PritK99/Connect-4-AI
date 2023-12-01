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

// moveGen function to generate valid positions
vector <int> moveGen (vector <vector <int>> board)
{
    vector <int> valid;
    for (int i = 0; i < COLS; i++)
    {
        if (board[0][i] == 0)
        {
            valid.push_back(i);
        }
    }
    return valid;
}

// minimax algorithm
pair <int, int> minimax(vector <vector <int>> board, bool maximizer)
{
    int check = evaluate(board);

    if (check == 1)
    {
        pair <int, int> p = {1, 0};
        return p;
    }
    else if (check == 2)
    {
        pair <int, int> p = {-1, 0};
        return p;
    }
    else if (check == 3)
    {
        pair <int, int> p = {0, 0};
        return p;
    }
    else
    {
        pair <int, int> best = {0, 0};
        vector <int> moves = moveGen(board);

        if (maximizer)
        {
            best.first = INT_MIN;

            for (int i = 0; i < moves.size(); i++)
            {
                vector <vector <int>> copy = board;
                insert(copy, moves[i], 1);
                pair <int, int> x = minimax(copy, 0);

                if (x.first > best.first)
                {
                    best.first = x.first;
                    best.second = moves[i];
                }
            }
        }
        else
        {
            best.first = INT_MAX;

            for (int i = 0; i < moves.size(); i++)
            {
                vector <vector <int>> copy = board;
                insert(copy, moves[i], 2);
                pair <int, int> x = minimax(copy, 1);

                if (x.first < best.first)
                {
                    best.first = x.first;
                    best.second = moves[i];
                }
            }
        }
        return best;   
    }
}

int main ()
{
    vector <vector <int>> board (ROWS, vector <int> (COLS));
    printBoard(board);

    while (evaluate(board) == 0)
    {
        cout << "AI plays....\n";
        pair <int, int> p = minimax(board, 1);
        insert(board, p.second, 1);
        cout << "AI is trying to obtain " << p.first << " value\n";
        printBoard(board);

        if (evaluate(board) != 0)
        {
            break;
        }

        cout << "Human plays....\n";
        int c;
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
        cout << "Bingo! AI wins the game.";
    }
    else if (x == 2)
    {
        cout << "Bingo! You win the game.";
    }
    else
    {
        cout << "The game ends as a draw!";
    }
    cout << endl;

    return 0;
}