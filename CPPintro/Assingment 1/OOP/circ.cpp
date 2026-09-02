#include <iostream>
using namespace std;

int main() {
    const float Pi = 3.14;
    float radius;
    cout << "Enter radius: ";
    cin >> radius;

    cout << "Area = " << Pi * radius * radius << endl;
    cout << "Circumference = " << 2 * Pi * radius << endl;
    return 0;
}