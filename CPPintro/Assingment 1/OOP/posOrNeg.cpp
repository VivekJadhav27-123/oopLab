#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;

    if (n > 0)
        cout << n << " is Positive." << endl;
    else if (n < 0)
        cout << n << " is Negative." << endl;
    else
        cout << "The number is Zero." << endl;

    return 0;
}