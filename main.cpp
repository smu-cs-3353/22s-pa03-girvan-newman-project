//
// Created by mikec_g1kgiu8 on 3/30/2022.
//
#include <iostream>
#include <boost/array.hpp>

using namespace std;

int main() {
    cout << "Hello World!" << endl;
    boost::array<int, 4> arr = {{1,2,3,4}};
    cout << arr[2] << endl;

    return 0;
}