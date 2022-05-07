#ifndef _BIG_INT_H
#define _BIG_INT_H

#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <list>

struct Array {
    int *arr;
    int size;
};

using namespace std;

class BigInt {
private:

    // the value of the input
    string num;

    // for destruction
    list<int *> arrs;

    Array multiply(Array, Array);

    Array add(Array, Array);

public:
    // required constructors
    explicit BigInt(string);

    ~BigInt();

    // Check if characters of the input are between '0' and '9'
    bool isValid();

    // return the value of the num
    string getNum() const;


    BigInt operator*(BigInt const &);


};

BigInt::BigInt(string num) : num(std::move(num)) {

}

BigInt::~BigInt() {

    while (!arrs.empty()) {
        delete[] arrs.back();
        arrs.pop_back();
    }
}

bool BigInt::isValid() {

    for (char character : num) {
        if (character < '0' || character > '9') {
            return false;
        }
    }
    return true;
}

string BigInt::getNum() const {
    return num;
}

BigInt BigInt::operator*(BigInt const &other) {

    Array X{}, Y{};

    X.size = this->num.length();
    Y.size = other.num.length();

    X.arr = new int[X.size];
    Y.arr = new int[Y.size];

    arrs.push_back(X.arr);
    arrs.push_back(Y.arr);

    for (int i = 0; i < X.size; ++i) {
        X.arr[i] = (int) (this->num.at(i)) - 48;
    }

    for (int i = 0; i < Y.size; ++i) {
        Y.arr[i] = (int) (other.num.at(i)) - 48;
    }

    Array mulArray = multiply(X, Y);

    string result;

    for (int i = mulArray.size - 1; i >= 0; i--) {
        result += to_string(mulArray.arr[i]);
    }

    return BigInt(result);
}

Array BigInt::multiply(const Array x, const Array y) {

    if (x.size == 1 && y.size == 1) {

        Array result{};
        result.size = 1;
        result.arr = new int[result.size];
        result.arr[0] = x.arr[0] * y.arr[0];

        arrs.push_back(result.arr);

        return result;
    }

    Array mulArray{};
    mulArray.size = x.size + y.size;

    Array a{}, b{}, c{}, d{};

    a.size = (x.size + 1) / 2;
    b.size = (x.size + 1) / 2;
    c.size = (y.size + 1) / 2;
    d.size = (y.size + 1) / 2;

    a.arr = new int[a.size];
    b.arr = new int[b.size];
    c.arr = new int[c.size];
    d.arr = new int[d.size];

    arrs.push_back(a.arr);
    arrs.push_back(b.arr);
    arrs.push_back(c.arr);
    arrs.push_back(d.arr);

    for (int i = 0; i < a.size; ++i) {
        a.arr[i] = x.arr[i];
    }

    for (int i = a.size; i < x.size; ++i) {
        b.arr[i] = x.arr[i];
    }

    for (int i = 0; i < c.size; ++i) {
        c.arr[i] = y.arr[i];
    }

    for (int i = c.size; i < y.size; ++i) {
        d.arr[i] = y.arr[i];
    }

    Array ac{};
    ac.size = a.size + c.size + max(x.size, y.size); 
    ac.arr = new int[ac.size];
    ac.arr = {0};

    arrs.push_back(ac.arr);

    Array acTemp{};
    acTemp.arr = multiply(a, c).arr;
    acTemp.size = a.size + c.size;

    for (int i = 0; i < acTemp.size; ++i) {
        ac.arr[i] = acTemp.arr[i];
    }

    Array adbc{};
    adbc.size = a.size + b.size + c.size + d.size + max(x.size, y.size) / 2;
    adbc.arr = new int[adbc.size];
    adbc.arr = {0};

    arrs.push_back(adbc.arr);

    Array adbcTemp{};
    adbcTemp.arr = add(multiply(a, d), multiply(b, c)).arr;
    adbcTemp.size = a.size + b.size + c.size + d.size;

    for (int i = 0; i < adbcTemp.size; ++i) {
        adbc.arr[i] = adbcTemp.arr[i];
    }

    mulArray.arr = add(add(multiply(b, d), ac), adbc).arr;

    return mulArray;
}

Array BigInt::add(Array first, Array second) {

    int carryOver = 0, sum;
    Array sumArray{};

    sumArray.size = max(first.size, second.size) + 1;
    sumArray.arr = new int[sumArray.size];

    arrs.push_back(sumArray.arr);

    for (int i = 0; i < min(first.size, second.size); ++i) {

        sum = carryOver + first.arr[i] + second.arr[i];

        if (sum >= 10) {
            carryOver = sum / 10;
            sum %= 10;
        } else carryOver = 0;

        sumArray.arr[i] = sum;

    }

    for (int i = min(first.size, second.size); i < sumArray.size - 1; ++i) {

        if (first.size > second.size) {

            sum = carryOver + first.arr[i];

            if (sum >= 10) {
                carryOver = sum / 10;
                sum %= 10;
            } else carryOver = 0;

            sumArray.arr[i] = sum;

        } else if (first.size < second.size) {

            sum = carryOver + second.arr[i];

            if (sum >= 10) {
                carryOver = sum / 10;
                sum %= 10;
            } else carryOver = 0;

            sumArray.arr[i] = sum;
        }

    }

    if (carryOver != 0) {
        sumArray.arr[sumArray.size - 1] = carryOver;
    } else sumArray.size--;

    return sumArray;
}

#endif

