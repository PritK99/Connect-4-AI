#include <vector>
#include <iostream>
#include <utility>

#define ROWS 4
#define COLS 4

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
pair<int, int> minimax(std::vector<std::vector<int>> board, bool maximizer, int alpha, int beta)
{
    int check = evaluate(board);

    if (check == 1)
        return {1, 0};
    else if (check == 2)
        return {-1, 0};
    else if (check == 3)
        return {0, 0};
    else
    {
        pair<int, int> best = {0, 0};
        vector<int> moves = moveGen(board);

        if (maximizer)
        {
            best.first = INT_MIN;

            for (int i = 0; i < moves.size(); i++)
            {
                vector<vector<int>> copy = board;
                insert(copy, moves[i], 1);
                pair<int, int> x = minimax(copy, false, alpha, beta);

                if (x.first > best.first)
                {
                    best.first = x.first;
                    best.second = moves[i];
                }

                alpha = max(alpha, best.first);
                if (alpha >= beta)
                    break; // Beta pruning
            }
        }
        else
        {
            best.first = INT_MAX;

            for (int i = 0; i < moves.size(); i++)
            {
                vector<std::vector<int>> copy = board;
                insert(copy, moves[i], 2);
                pair<int, int> x = minimax(copy, true, alpha, beta);

                if (x.first < best.first)
                {
                    best.first = x.first;
                    best.second = moves[i];
                }

                beta = min(beta, best.first);
                if (alpha >= beta)
                    break; // Alpha pruning
            }
        }
        return best;
    }
}

int main()
{
    std::vector<std::vector<int>> board(ROWS, std::vector<int>(COLS, 0));
    printBoard(board);

    while (evaluate(board) == 0)
    {
        std::cout << "AI plays....\n";
        std::pair<int, int> p = minimax(board, true, INT_MIN, INT_MAX);
        insert(board, p.second, 1);
        std::cout << "AI is trying to obtain " << p.first << " value\n";
        printBoard(board);

        if (evaluate(board) != 0)
        {
            break;
        }

        std::cout << "Human plays....\n";
        int c;
        std::cout << "Enter your column: ";
        std::cin >> c;
        while (!isValid(board, c))
        {
            std::cout << "Invalid choice. Please choose your column: ";
            std::cin >> c;
        }
        insert(board, c, 2);
        printBoard(board);
    }

    int x = evaluate(board);
    if (x == 1)
    {
        std::cout << "Bingo! AI wins the game.";
    }
    else if (x == 2)
    {
        std::cout << "Bingo! You win the game.";
    }
    else
    {
        std::cout << "The game ends as a draw!";
    }
    std::cout << std::endl;

    return 0;
}