#include <iostream>
#include <vector>
using namespace std;

// Base class to track game stats
class GameBase {
protected:
    static int totalGames; // Static variable for total games
public:
    GameBase() { totalGames++; }
    static int getTotalGames() { return totalGames; } // Scope resolution operator
    virtual ~GameBase() {}
};

// Initialize static member
int GameBase::totalGames = 0;

// Tic-Tac-Toe game class
class TicTacToe : public GameBase {
private:
    vector<vector<char>> board = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}}; // Numbered grid
    char currentPlayer = 'X';
    int status = 0; // 0 = ongoing, 1 = win, 2 = draw

    // Friend function to display the board
    friend void showBoard(const TicTacToe& game);

    // Inline function to check for a win
    inline int checkWin() {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) return 1;
            if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer) return 1;
        }
        if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) return 1;
        if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer) return 1;
        return 0;
    }

    // Inline function to check for a draw
    inline int checkDraw() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] != 'X' && board[i][j] != 'O') return 0;
        return 2;
    }

public:
    TicTacToe() {}

    // Inline function to make a move
    inline int makeMove(int pos) {
        int row = (pos - 1) / 3;
        int col = (pos - 1) % 3;
        if (pos >= 1 && pos <= 9 && board[row][col] >= '1' && board[row][col] <= '9') {
            board[row][col] = currentPlayer;
            return 1; // Success
        }
        return 0; // Failure
    }

    // Inline function to switch players
    inline void switchTurn() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        cout << "Nice move! Now it's " << currentPlayer << "'s turn!\n";
    }

    // Inline function to get game status
    inline int getStatus() {
        if (status == 0) {
            if (checkWin() == 1) status = 1;
            else if (checkDraw() == 2) status = 2;
        }
        return status;
    }

    // Public getter for currentPlayer to fix the private access error
    inline char getCurrentPlayer() const {
        return currentPlayer;
    }
};

// Friend function to display the board
void showBoard(const TicTacToe& game) {
    cout << "\nTic-Tac-Toe Board:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << " " << game.board[i][j] << " ";
            if (j < 2) cout << "|";
        }
        cout << "\n";
        if (i < 2) cout << "---------\n";
    }
    cout << endl;
}

// Game manager class
class GamePlay {
private:
    TicTacToe game;

public:
    void play() {
        cout << "Welcome to Tic-Tac-Toe!\n";
        cout << "Pick a number 1-9 to place your mark. Let's go!\n";
        showBoard(game);

        while (game.getStatus() == 0) {
            int move;
            cout << "Player " << game.getCurrentPlayer() << ", enter your move (1-9): ";
            if (!(cin >> move)) { // Check for invalid input
                cout << "Please enter a valid number between 1 and 9!\n";
                cin.clear(); // Clear error flags
                cin.ignore(10000, '\n'); // Ignore remaining input
                continue;
            }
            if (move < 1 || move > 9) {
                cout << "Number must be between 1 and 9! Try again.\n";
                continue;
            }

            if (game.makeMove(move)) {
                showBoard(game);
                int newStatus = game.getStatus();
                if (newStatus == 1) {
                    cout << "Player " << game.getCurrentPlayer() << " wins! Congrats!\n";
                } else if (newStatus == 2) {
                    cout << "It's a draw! Good game!\n";
                } else {
                    game.switchTurn();
                }
            } else {
                cout << "Sorry, that spot is taken! Try again.\n";
            }
        }

        cout << "Total games played: " << GameBase::getTotalGames() << "\n";
        char again;
        cout << "Play again? (y/n): ";
        cin >> again;
        if (again == 'y' || again == 'Y') {
            game = TicTacToe(); // Reset game
            play();
        } else {
            cout << "Thanks for playing! Total games: " << GameBase::getTotalGames() << "\n";
        }
    }
};

int main() {
    GamePlay manager;
    manager.play();
    return 0;
}
