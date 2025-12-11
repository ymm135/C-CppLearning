#include <iostream>
#include <vector>
using namespace std;

// 传递的是一个指针,也就是数组的首地址. 数组就退化为指针了.
double average1(int arr[]) {
    double sum = 0;
    // arr是地址的长度,arr[0]是int类型,所以8/4=2
    int len = sizeof(arr) / sizeof(arr[0]);
    cout <<"average1 len:" << len << endl;

    for (int i = 0; i < len; i++) {
        sum += arr[i];
    }
    return sum / len;
}

double average2(int arr[], int len) {
    double sum = 0;
    for (int i = 0; i < len; i++) {
        sum += arr[i];
    }
    return sum / len;
}

double average3(int *arr, int len) {
    double sum = 0;
    for (int i = 0; i < len; i++) {
        sum += arr[i];
    }
    return sum / len;
}

double average4(vector<int>& v) {
    double sum = 0;
    for (const int i : v) {
        sum += i;
    }
    return sum / v.size();
}

double average5(vector<vector<int>>& vv) {
    double sum = 0;
    int len = 0;
    for (int i = 0; i < vv.size(); i++) {
        for (int j = 0; j < vv[i].size(); j++) {
            sum += vv[i][j];
            len++;
        }
    }
    return sum / len;
}

int main() {
    int array1[10] = {1,2,3,4,5,6,7,8,9,10};
    int len = sizeof(array1) / sizeof(array1[0]);
    double avg = average1(array1);
    double avg2 = average2(array1, len);
    double avg3 = average3(array1, len);
    cout <<"len:" << len << ", avg:" << avg << endl;
    cout <<"len:" << len << ", avg2:" << avg2 << endl;
    cout <<"len:" << len << ", avg3:" << avg3 << endl;

    vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    cout << "avg4:" << average4(v) << endl;

    vector<vector<int>> vv = {{1,2,3,4,5,6,7,8,9,10}};
    cout << "avg5:" << average5(vv) << endl;
    return 0;
}