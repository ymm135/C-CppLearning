#include <bitset>
#include <iostream>
using namespace std;

int main() {
    char a1 = 0x63; // 0110 0011
    a1 = (a1 << 4); // 0011 0000
    printf("0x%x\n", a1);

    a1 = 0x63; // 0110 0011
    a1 = (a1 >> 4); // 0000 0110 逻辑右移
    printf("0x%x\n", a1);

    char a2 = 0x95; // 1001 0101
    a2 = (a2 << 4); // 0101 0000
    printf("0x%x\n", a2);

    a2 = 0x95; // 1001 0101
    a2 = (a2 >> 4); // 1111 1001 算术右移
    printf("0x%x\n", a2);

    // 0000 0000
    const unsigned char priv = 0xFF;
    const unsigned char P_BACKUP = (1 << 7);
    const unsigned char P_ADMIN = (1 << 8); // 已经超出8位了.结果是0

    if (priv & P_BACKUP) {
        cout << "P_BACKUP is present" << endl;
    }

    if (priv & P_ADMIN) {
        cout << "P_ADMIN is present" << endl;
    }

    // 使用C++的bitset
    bitset<10> bPriv = 0xFF;
    bitset<10> bP_BACKUP = (1 << 7);
    bitset<10> bP_ADMIN = (1 << 8);

    cout << bPriv << endl;
    cout << bP_BACKUP << endl;
    cout << bP_ADMIN << endl;

    return 0;
}