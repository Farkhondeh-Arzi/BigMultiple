#include <iostream>
#include "BigInt.h"

using namespace std;

int main() {

    string s;

    BigInt a("123");
    BigInt b("45");

    BigInt result = a * b;


    cout << "hello!" << endl;
    cout << result.getNum();

    return 0;
}
