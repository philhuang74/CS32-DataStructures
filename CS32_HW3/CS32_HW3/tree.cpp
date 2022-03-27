//
//  tree.cpp
//  CS32_HW3
//
//  Created by Philip Huang on 2/6/22.
//

// Return the number of ways that all n2 elements of a2 appear in
// the n1 element array a1 in the same order (though not necessarily
// consecutively).  The empty sequence (i.e. one where n2 is 0)
// appears in a sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//        10 50 40 20 50 40 30
// then for this value of a2     the function must return
//        10 20 40                        1
//        10 40 30                        2
//        20 10 40                        0
//        50 40 30                        3
int countContains(const double a1[], int n1, const double a2[], int n2)
{
    if(n2<=0){
        return 1;
    }
    if(n2>n1 or n1<=0){
        return 0;
    }
    if (a1[0] == a2[0]){
        return countContains(a1+1,n1-1,a2,n2)+countContains(a1+1,n1-1,a2+1,n2-1);
    }
    else{
        return countContains(a1+1,n1-1,a2,n2);
    }
}
//We want to keep going until we either hit n2<=0 or n1<=0, where one list's elements has been exhausted. If n1<=0 is exhausted first, then we know the sequence of a2 has not been found in a1, return 0. If n2<=0 is exhausted first, return 1, which means we have found a2 in a1. If the current element in a1 is the same as a2, we want to search the next element in a1, but keep the current pattern of a2 the same (We ignore our discovery to see if there are more a2's in a1), or search the next element in a1 and the next element in a2 (to proceed with our newfound discovery). We want to return the count of both these paths, hence the addition. Otherwise, if the current elements of a1 and a2 are not equal, we know that we can continue onto the next element in a1 and search for the same current a2 elements.

//Another way to do it by saving it into a int variable
//int countContains(const double a1[], int n1, const double a2[], int n2)
//{
//    if(n2<=0){
//        return 1;
//    }
//    if(n2>n1 or n1<=0){
//        return 0;
//    }
//    int total = 0;
//    if (a1[0] == a2[0]){
//        total+=(countContains(a1+1,n1-1,a2,n2)+countContains(a1+1,n1-1,a2+1,n2-1));
//    }
//    else{
//        total+=countContains(a1+1,n1-1,a2,n2);
//    }
//    return total;
//}

// Exchange two doubles
void exchange(double& x, double& y)
{
  double t = x;
  x = y;
  y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is > separator come before all the other elements,
// and all the elements whose value is < separator come after all
// the other elements.  Upon return, firstNotGreater is set to the
// index of the first element in the rearranged array that is
// <= separator, or n if there is no such element, and firstLess is
// set to the index of the first element that is < separator, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotGreater, a[i] > separator
//   * for firstNotGreater <= i < firstLess, a[i] == separator
//   * for firstLess <= i < n, a[i] < separator
// All the elements > separator end up in no particular order.
// All the elements < separator end up in no particular order.
void separate(double a[], int n, double separator,
                  int& firstNotGreater, int& firstLess)
{
  if (n < 0)
  n = 0;

    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
    //  Every element earlier than position firstNotGreater is > separator
    //  Every element from position firstNotGreater to firstUnknown-1 is
    //    == separator
    //  Every element from firstUnknown to firstLess-1 is not known yet
    //  Every element at position firstLess or later is < separator

  firstNotGreater = 0;
  firstLess = n;
  int firstUnknown = 0;
  while (firstUnknown < firstLess)
  {
  if (a[firstUnknown] < separator)
  {
      firstLess--;
      exchange(a[firstUnknown], a[firstLess]);
  }
  else
  {
      if (a[firstUnknown] > separator)
      {
      exchange(a[firstNotGreater], a[firstUnknown]);
      firstNotGreater++;
      }
      firstUnknown++;
  }
  }
}

// Rearrange the elements of the array so that
// a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
// If n <= 1, do nothing.
void order(double a[], int n)
{
    if (n<=1){
        return;
    }
    int seperator = a[0];
    int firstNotGreaterIndex, firstLessIndex;
    separate(a,n,seperator,firstNotGreaterIndex,firstLessIndex);
    order(a, firstNotGreaterIndex);
    order(a+firstLessIndex,n-firstLessIndex);
}
//We want to keep ordering until the size of the list is equal to 1. At this point we know the a one list element is in order. First we will seperate the list by a separator number that is the first element of the array. This will change the array. Then we continue to order everything from a to first greater index - 1. This sub array will not necessarily be ordered. We do the same for everything that is above first less index. Anything in between including first not greater and first less index (not including) will be equal to separator, and so we know that it is in the right place. Let's say we have an array [6,1,5,4,3,8,9]. Then our separator is 6. We separate according to 6. This means we will have [8,9,6,1,5,4,3] and first not greater will be at index 2 and first less will be at index 3. We want to continue ordering [8,9] and [1,5,4,3]. If we order [8,9] it will select 8 as the separator and 9 will be before 8. After calling the ordering of 9 and empty, those will be the base case and 9 8 will be in order.

//#include<iostream>
//using namespace std;
//int main(){
//    //COUNTCONTAINS() TESTS
//    //can choose 5 at index 1, 4 at index 2, 3 at index 6
//    //can choose 5 at index 1, 4 at index 5, 3 at index 6
//    //can choose 5 at index4, 4 at index 5, 3 at index 6
//    const double a1[] = {1,5,4,2,5,4,3};
////    const double a1[] = {};
////    const double a1[] = {1,5,4,2,2};
//    const double a2[] = {5,4,3};
//    cout << countContains(a1,7,a2,3) << "\n"; //should be 3
//
//    //ORDER() TESTS
//    double a3[] = {5,4,2,7,4,2,9,12};
//    order(a3,8);
//    for (int i = 0; i<8; i++){
//        cout << a3[i] << " ";
//    }
//    cout << "\n";
//
//    double a4[] = {10,3,2};
//    order(a4,3);
//    for (int i = 0; i<3; i++){
//        cout << a4[i] << " ";
//    }
//    cout << "\n";
//
//    double a5[] = {};
//    order(a5,0);
//    for (int i = 0; i<0; i++){
//        cout << a5[i] << " ";
//    }
//    cout << "\n";
//
//    double a6[] = {-1,7,5,-6,88};
//    order(a6,5);
//    for (int i = 0; i<5; i++){
//        cout << a6[i] << " ";
//    }
//    cout << "\n";
//}

