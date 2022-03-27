//
//  linear.cpp
//  CS32_HW3
//
//  Created by Philip Huang on 2/6/22.
//

//Need to comment this out at the end
bool somePredicate(double x)
{
    return x < 0;
}

// Return true if the somePredicate function returns false for at
    // least one of the array elements, false otherwise.
  bool anyFalse(const double a[], int n)
{
      if (n <= 0){ //base case, nothing left to check and all elements are true when passed in to predicate
          return false;
      }
      if (!somePredicate(a[0])){ //base case, if we hit an element in list where predicate is false, return true
          return true;
      }
      return anyFalse(a+1,n-1); //pass answer upstream once we hit a base case
}
// if at any point, we spot a false, we immediately return true and pass that upstream. If we checked all elements and all of them were true according to predicate, then we pass the false upstream.

    // Return the number of elements in the array for which the
    // somePredicate function returns false.
  int countFalse(const double a[], int n)
  {
      if(n<=0){
          return 0; //we have checked all the elements, pointer is one step out of array, and n is 0, return a 0
      }
      if (!somePredicate(a[0])){
          return countFalse(a+1,n-1) + 1; //Everytime predicate is false in array, we want to add one to final answer
      }
      else{
          return countFalse(a+1,n-1); //if predicate is true in array, just return the answer.
      }
  }
//If I have array [1,2,5,4,3], and predicate is x<3. Then we will keep calling until we hit base case (just one step out of bounds of array and n=0), in which we return 0, and then 0+1=1 because 3<3 is false, 1+1=2 because 4<3 is false, 1+1+1=3 because 5<3 is false, 3 because 2<3 is true, and 3 because 1<3 is true. The final answer is 3.

//You will not receive full credit if the anyFalse, countFalse, or firstTrue functions causes the value that each call of somePredicate returns to be examined more than once. Consider all operations comparing two doubles (e.g. <=, ==, etc.) that a function performs. You will not receive full credit if for nonnegative n or n1, the locateMax function causes operations on doubles like these to be performed more than n times, or the contains function causes them to be performed more than n1 times. (Notice that this limitation is for comparisons of doubles; there's no limit on comparisons of ints.)

    // Return the subscript of the first element in the array for which
    // the somePredicate function returns true.  If there is no such
    // element, return -1.
  int firstTrue(const double a[], int n)
  {
      if (n <= 0){
          return -1;
      }
      if (somePredicate(a[0])==true){
          return 0;
      }
      else{ //somePredicate of current element in array is false
          int firstTrueIndex = firstTrue(a+1,n-1);
          if (firstTrueIndex==-1){
              return -1;
          }
          return firstTrueIndex+1;
      }
  }
// From tracing through the code, this does not seem to cause the value that each call of somePredicate returns to be examined more than once. Lets assume a is [5,4,1,2,3], and predicate is x<3. Then we will hit 1<3 which returns 0, since previous was not -1, we will return 0+1=1 and lastly 1+1=2, which is correct since 1<3 occurs at second index. If we recurse all the way down the list and hit base case where everything is false according to predicate, then we return -1 and pass that value upstream.


    // Return the subscript of the largest element in the array (i.e.,
    // return the smallest subscript m such that a[m] >= a[k] for all
    // k such that k >= 0 and k < n).  If there is no such subscript,
    // return -1.
int locateMax(const double a[], int n)
{
    if (n<=0){
        return -1;
    }
    if (n==1){
        return 0;
    }
    int max = locateMax(a+1,n-1)+1;
    if (a[0] >= a[max]){
        return 0;
    }
    else{
        return max;
    }
}
//If I have an array a = [1,9,2,9,1]. Then we will hit base case when it is at last element 1. Then we return 0. Then we will go back to max=0+1=1. So we will compare 9 with 1. 9 is greater than 1, so we return 0. Then we will go back to max=0+1=1. So we will compare 2 with 9, 2 is less than 9, so we return max which in this case is 1. We go back to max=1+1=2. So we compare 9 with 9. 9 is >= 9, so we return 0. We go back to max=0+1=1, so we compare 1 with 9. 1 < 9, so we return max, which is 1, and 9 is at index 1. Lets say our array was a = [5,8,2,9,3]. Then we will hit base case when it goes to last element 3, we return 0. max=0+1=1, so is 9>=3, yes so return 0. Then max=0+1=1, so is 2>=9, no return 1. max=1+1=2. so is 8>=9, no, so we return 2. max=2+1=3. Is 5>=9, no, so we return 3. Thats that index of where 9 is, so this works.

    // If all n2 elements of a2 appear in the n1 element array a1, in
    // the same order (though not necessarily consecutively), then
    // return true; otherwise (i.e., if the array a1 does not contain
    // a2 as a not-necessarily-contiguous subsequence), return false.
    // (Of course, if a2 is empty (i.e., n2 is 0), return true.)
    // For example, if a1 is the 7 element array
    //    10 50 40 20 50 40 30
    // then the function should return true if a2 is
    //    50 20 30
    // or
    //    50 40 40
    // and it should return false if a2 is
    //    50 30 20
    // or
    //    10 20 20
  bool contains(const double a1[], int n1, const double a2[], int n2)
  {
      if(n2<=0){
          return true;
      }
      if(n2>n1 or n1<=0){
          return false;
      }
      if (a1[0] == a2[0]){
          return contains(a1+1,n1-1,a2+1,n2-1);
      }
      else{
          return contains(a1+1,n1-1,a2,n2);
      }
  }
//Here we know the base case will be when all n2 elements has been exhausted and n2 is now zero, we return true as that means all elements in a2 is in a1. If we somehow go through all n1 elements in a1, and n2 is not exhausted since the if statement comes before, we know we will return false as not all elements in a2 are in a1. If n2 is bigger than n1, there is no way n2 is contained in n1, so we should return false immediately, hence the n2>n1. Otherwise, we shall call recursively. If the current first element in a1 is equal to first element in a2, we can move on to the next element for both arrays. Otherwise, they are not equal, and we have to continue searching through a1 to find if that element maches the element in a2. 



//#include<iostream>
//using namespace std;
//int main(){
    
//    //anyFalse
//    const double a1[] = {1,-2,-3};
//    cout << anyFalse(a1, 3) << "\n";
    
//    //countFalse
//    const double a1[] = {-1,-2,-3};
//    cout << countFalse(a1, 3) << "\n";
    
//    //firstTrue
//    const double a1[] = {1,2,-3};
//    cout << firstTrue(a1, 3) << "\n";
    
//    //locateMax
//    const double a1[] = {5,5,5,10,30};
//    cout << locateMax(a1, 5) << "\n";
    
//    //contains
//    const double a1[] = {1,5,4,2,5,4,3};
//    const double a2[] = {5,2,3};
//    const double a3[] = {1,2,2};
//    cout << contains(a1,7,a2,3) << "\n";
//    cout << contains(a1,7,a3,3) << "\n";
    
//}
