#include <iostream>
using namespace std;

double getSum(int n) {
    double sum = 0.0;
    for (int i = 1; i < n; i++) {
        // sum += 1.0/i; // 整形除以整形还是一个整形值,最终结果都是0.
        sum += static_cast<double>(1)/i;
    }
    return sum;
}

int main() {
    // 第一个问题
    int arr[]={1,2,3,4,5,6,7,8,9};
    cout << sizeof(arr)/sizeof(arr[0]) << endl;
    int threshold = -1;
    cout << (unsigned int)threshold << endl;
    cout << "staic_cast: " << static_cast<unsigned int>(threshold) << endl;

    if (sizeof(arr)/sizeof(arr[0]) > threshold) {
        cout << "positive number array" << endl;
    }else {
        cout << "negative number array" << endl;
    }

    int len = static_cast<int>(sizeof(arr)/sizeof(arr[0]));
    if (len > threshold) {
        cout << "len positive number array" << endl;
    }else {
        cout << "len negative number array" << endl;
    }

    // 第二个问题
    // 累加和: 1+1/2+1/3+1/4+
    int n = 10;
    // cin >> n;
    cout << getSum(n) << endl;
    return 0;
}