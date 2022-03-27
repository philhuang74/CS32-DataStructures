////
////  oddvector.cpp
////  CS32_HW4
////
////  Created by Philip Huang on 3/1/22.
////
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

  // Remove the odd integers from v.
  // It is acceptable if the order of the remaining even integers is not
  // the same as in the original vector.
void removeOdd(vector<int>& v)
{

    for(int i = 0; i <v.size();i++){
        if(v.at(i)%2 == 1){ //at throws exception error if i is invalid, since we are doing within v.size(), v[i] also works
            v.erase(v.begin()+i);
            i--; //since i will be added in the next loop, we want to subtract by i so that it can get the correct v[i] item since the ith item was just erased
        }
    }
    
// While Loop Version
//    int i = 0;
//    while (i<v.size()){
//        if (v[i]%2 == 1){
//            v.erase(v.begin()+i);
//        }
//        else{
//            i++;
//        }
//    }
}

void test()
{
    int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
    vector<int> x(a, a+8);  // construct x from the array
    assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
    removeOdd(x);
    assert(x.size() == 4);
    sort(x.begin(), x.end());
    int expect[4] = { 2, 4, 6, 8 };
    for (int k = 0; k < 4; k++)
        assert(x[k] == expect[k]);
//    int a[8] = { 10, 8, 5, 6, 7, 3, 4, 1 };
//    vector<int> x(a, a+8);  // construct x from the array
//    assert(x.size() == 8 && x.front() == 10 && x.back() == 1);
//    removeOdd(x);
//    assert(x.size() == 4);
//    sort(x.begin(), x.end());
//    int expect[4] = {4, 6, 8, 10};
//    for (int k = 0; k < 4; k++)
//        assert(x[k] == expect[k]);
}

int main()
{
    test();
    cout << "Passed" << endl;
}
