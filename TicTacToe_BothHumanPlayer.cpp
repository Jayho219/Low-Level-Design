// Optimized Code O(1)--> checking winning moves
// Both Players are human

#include <iostream>
#include <vector>

using namespace std;

enum class CellState { Empty, X, O };

class TicTacToe {
private:
    vector<vector<CellState>> board;
    vector<int> rowCount;
    vector<int> colCount;
    int diagCount;
    int antiDiagCount;
    int size;
    int totalMoves;
    int currentPlayer;

public:
    TicTacToe(int size) : 
        board(size, vector<CellState>(size, CellState::Empty)),
        rowCount(size, 0),
        colCount(size, 0),
        diagCount(0),
        antiDiagCount(0),
        size(size),
        currentPlayer(1),
        totalMoves(0) {}

    bool isWinningMove(int row, int col, CellState player) {
        if (abs(rowCount[row]) == size || 
            abs(colCount[col]) == size ||
            abs(diagCount) == size ||
            abs(antiDiagCount) == size) {
            return true;
        }
        return false;
    }

    bool makeMove(int row, int col, CellState player) {
        if (row < 0 || row >= size || col < 0 || col >= size || board[row][col] != CellState::Empty)
            return false;
        
        board[row][col] = player;
        totalMoves++;
        currentPlayer = 3 - currentPlayer;
        
        int playerVal = (player == CellState::X) ? 1 : -1;
        rowCount[row] += playerVal;
        colCount[col] += playerVal;
        
        if (row == col) diagCount += playerVal;
        if (row + col == size - 1) antiDiagCount += playerVal;
       
        return true;
    }
    
    bool isBoardFull(){
        return totalMoves == size*size;
    }
    
    int getCurrentPlayer(){
        return currentPlayer;
    }

    void printBoard() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                char symbol;
                switch (board[i][j]) {
                    case CellState::X: symbol = 'X'; break;
                    case CellState::O: symbol = 'O'; break;
                    default: symbol = ' '; break;
                }
                cout << symbol;
                if (j < size - 1) cout << '|';
            }
            cout << endl;
            if (i < size - 1) {
                for (int k = 0; k < 2 * size - 1; ++k) cout << '-';
                cout << endl;
            }
        }
    }
};

int main() {
    TicTacToe game(3);
    int row, column;
    bool flag = false;
    
    while (!game.isBoardFull() && !flag) {
        game.printBoard();
        cout << "Player " << game.getCurrentPlayer()
             << ", enter your move (row and column): ";
        cin >> row >> column;
 
        if (game.makeMove(row, column, game.getCurrentPlayer() == 1 ? CellState::X : CellState::O)) {
            cout << "Move successful!" << endl;
            
            CellState player = game.getCurrentPlayer() == 1 ? CellState::X : CellState::O;
            
            if(game.isWinningMove(row, column, player)){
                flag = true;
            }
        }
        else {
            cout << "Invalid move. Try again." << endl;
        }
    }
 
    game.printBoard();
 
    if (flag) {
        cout << "Player " << (3 - game.getCurrentPlayer())
             << " wins!" << endl;
    }
    else {
        cout << "It's a draw!" << endl;
    }

    return 0;
}
