#include <iostream>
#include <cmath>

using namespace std;

// Global Variable
static int calculationCount = 0;

// Calculator Class
class Calculator {
private:
    double num1, num2;
    char operation;

public:
    // Constructor
    Calculator() {
        cout << "?? Enter first number: ";
        while (!(cin >> num1)) {
            cout << "? Error! Enter a valid number: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cout << "?? Enter operator (+, -, *, /, %, ^): ";
        cin >> operation;

        cout << "?? Enter second number: ";
        while (!(cin >> num2)) {
            cout << "? Error! Enter a valid number: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    // Friend Function to Perform Calculation
    friend void performCalculation(Calculator &);

    // Destructor
    ~Calculator() {
        cout << "? Calculation Completed!\n";
    }
};

// Friend Function to Access Private Members
void performCalculation(Calculator &calc) {
    static int instanceCount = 0; // Static Variable
    instanceCount++;
    calculationCount++;

    cout << "\n?? Result: ";
    switch (calc.operation) {
        case '+': cout << calc.num1 + calc.num2; break;
        case '-': cout << calc.num1 - calc.num2; break;
        case '*': cout << calc.num1 * calc.num2; break;
        case '/': 
            if (calc.num2 != 0) cout << calc.num1 / calc.num2; 
            else cout << "? Error: Division by zero!";
            break;
        case '%': 
            if (floor(calc.num1) == calc.num1 && floor(calc.num2) == calc.num2 && calc.num2 != 0)
                cout << (int)calc.num1 % (int)calc.num2; 
            else 
                cout << "? Error: Modulus requires integers!";
            break;
        case '^': cout << pow(calc.num1, calc.num2); break;
        default: cout << "? Invalid operator!";
    }
    cout << "\n------------------------\n";
}

int main() {
    string choice;
    do {
        Calculator calc;  // Object Creation
        performCalculation(calc);

        cout << "?? Kya aap aage badhna chahte hain? (aage badhna hai / aage nahi badhna hai): ";
        cin >> ws;  // Clears leading whitespace
        getline(cin, choice);  // Takes full input

    } while (choice == "aage badhna hai");

    cout << "\n?? Total Calculations Performed: " << calculationCount << "\n";
    cout << "?? Dhanyawad! Phir milenge! ??\n";
    return 0;
}


