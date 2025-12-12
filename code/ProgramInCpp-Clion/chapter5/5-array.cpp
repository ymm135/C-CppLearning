#include <iostream>
using namespace std;

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // 不推荐
    for (int i = 0; i <= 9; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}