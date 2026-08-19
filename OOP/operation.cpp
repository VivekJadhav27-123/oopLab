#include <iostream>
using namespace std;

int main() {
    int a, b, choice;
    cout << "Enter two integers: ";
    cin >> a >> b;

    cout << "\n--- Menu ---\n";
    cout << "1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n5. Modulo\n";
    cout << "Enter your choice (1-5): ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "Result: " << a + b << endl;
            break;
        case 2:
            cout << "Result: " << a - b << endl;
            break;
        case 3:
            cout << "Result: " << a * b << endl;
            break;
        case 4:
            if (b != 0)
                cout << "Result: " << (float)a / b << endl;
            else
                cout << "Error: Division by zero!" << endl;
            break;
        case 5:
            if (b != 0)
                cout << "Result: " << a % b << endl;
            else
                cout << "Error: Modulo by zero!" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
    }
    return 0;
}