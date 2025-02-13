#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Class that represents the number guessing game
class NumberGuessingGame {
private:
    int secretNumber; // The secret number the player needs to guess

public:
    // Constructor: Initializes the game
    NumberGuessingGame() {
        srand(time(0));  // Seed random number generator
        secretNumber = rand() % 10 + 1; // Random number between 1 and 10
        cout << "I've chosen a number between 1 and 10. Guess it!\n";
    }

    // Destructor: Called when the game ends
    ~NumberGuessingGame() {
        cout << "Thanks for playing!\n";
    }

    // Function to check if the player's guess is correct
    bool checkGuess(int guess) {
        if (guess > secretNumber) {
            cout << "Too high! Try again.\n";
            return false;
        } else if (guess < secretNumber) {
            cout << "Too low! Try again.\n";
            return false;
        } else {
            cout << "Congratulations! You guessed the correct number.\n";
            return true;
        }
    }
};

// Main function to handle user interaction
int main() {
    NumberGuessingGame game;
    int guess;
    bool correct = false;

    while (!correct) {
        cout << "Enter your guess: ";
        cin >> guess;
        correct = game.checkGuess(guess);
    }

    return 0;
}

