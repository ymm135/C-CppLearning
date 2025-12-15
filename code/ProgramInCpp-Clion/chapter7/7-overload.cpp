#include <iostream>
#include <ostream>
using namespace std;
int add(int a, int b) {
        return a + b;
}

double add(double a, double b) {
    return a + b;
}

int main()
{
    int result = 0;
    result = add(1,2);
    cout << result << endl;

    result = add(1.0, 2.0);
    cout << result << endl;

    return 0;
}
