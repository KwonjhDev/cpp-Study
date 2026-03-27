#include <iostream>

using namespace std;

// a, b is two number, A is answer.
int a, b, A;

int gcd(int x, int y) {
    while(y != 0) {
        int tmp = x % y;
        x = y;
        y = tmp;
    }
    return x;
}

int main() {
    cin >> a >> b;
    A = gcd(a, b);
    cout << A << '\n' << a * b / A;
    return 0;
}
