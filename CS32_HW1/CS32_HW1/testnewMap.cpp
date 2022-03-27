//
//  main.cpp
//  CS32_HW1
//
//  Created by Philip Huang on 1/14/22.
//

//#include "newMap.h"
//#include <iostream>
//#include <cassert>
//using namespace std;

//int main(){
//    Map mm;
//    mm.insert("Little Ricky", 3.206);
//    mm.insert("Ethel", 3.538);
//    mm.insert("Ricky", 3.350);
//    mm.insert("Lucy", 2.956);
//    mm.insert("Ethel", 3.538);
//    mm.insert("Fred", 2.956);
//    mm.insert("Lucy", 2.956);
//    assert(mm.size() == 5);  // duplicate "Ethel" and "Lucy" were not added
//    string x;
//    double y;
//    mm.get(0, x, y);
//    assert(x == "Ethel");  // "Ethel" is greater than exactly 0 items in mm
//    mm.get(4, x, y);
//    assert(x == "Ricky");  // "Ricky" is greater than exactly 4 items in mm
//    mm.get(2, x, y);
//    assert(x == "Little Ricky");  // "Little Ricky" is greater than exactly 2 items in mm
//    assert(y == 3.206);  // the value corresponding to the key "Little Ricky"
//    mm.dump();
//    cout << "Passed all tests" << endl;
//
//}

//int main (){
//    Map m1;
//    m1.insert("Fred", 2.956);
//    Map m2;
//    m2.insert("Ethel", 3.538);
//    m2.insert("Lucy", 2.956);
//    m1.swap(m2);
//    assert(m1.size() == 2  &&  m1.contains("Ethel")  &&  m1.contains("Lucy")  &&
//           m2.size() == 1  &&  m2.contains("Fred"));
//    m1.dump();
//    m2.dump();
//    cout << "Passed all tests" << endl;
//}

//int main()
//{
//    Map gpas;
//    gpas.insert("Fred", 2.956);
//    assert(!gpas.contains(""));
//    gpas.insert("Ethel", 3.538);
//    gpas.insert("", 4.000);
//    gpas.insert("Lucy", 2.956);
//    assert(gpas.contains(""));
//    gpas.erase("Fred");
//    assert(gpas.size() == 3  &&  gpas.contains("Lucy")  &&  gpas.contains("Ethel")  &&
//                gpas.contains(""));
//    string k;
//    double v;
//    gpas.dump();
//    assert(gpas.get(1, k, v)  &&  k == "Ethel");
//    assert(gpas.get(3, k, v) == false);
//    assert(gpas.get(2,k,v) && k == "Lucy");
//    gpas.dump();
//    assert(gpas.get(0, k, v)  &&  k == "");
//    gpas.dump();
//    cout << "Passed all tests" << endl;
//}

//int main()
//{
//   Map m;  // maps strings to doubles
//   assert(m.empty());
//   ValueType v = -1234.5;
//   assert( !m.get("abc", v)  &&  v == -1234.5); // v unchanged by get failure
//   m.insert("xyz", 9876.5);
//   assert(m.size() == 1);
//   KeyType k = "hello";
//   assert(m.get(0, k, v)  &&  k == "xyz"  &&  v == 9876.5);
//   cout << "Passed all tests" << endl;
//}


//Tests for change in aliases
//int main()
//{
//    Map m;  // maps ints to strings
//    assert(m.empty());
//    ValueType v = "Ouch";
//    assert( !m.get(42, v)  &&  v == "Ouch"); // v unchanged by get failure
//    m.insert(123456789, "Wow!");
//    assert(m.size() == 1);
//    KeyType k = 9876543;
//    assert(m.get(0, k, v)  &&  k == 123456789  &&  v == "Wow!");
//    cout << "Passed all tests" << endl;
//}

//int main(){
//    Map a(1000);   // a can hold at most 1000 key/value pairs
//    Map b(5);      // b can hold at most 5 key/value pairs
//    Map c;         // c can hold at most DEFAULT_MAX_ITEMS key/value pairs
//    KeyType k[6] = {"hi","bo","jo","do","lo","so"};// { a list of six distinct keys of the appropriate type };
//    ValueType v  = 12; //a value of the appropriate type;
//
//      // No failures inserting pairs with 5 distinct keys into b
//    for (int n = 0; n < 5; n++)
//        assert(b.insert(k[n], v));
//
//      // Failure if we try to insert a pair with a sixth distinct key into b
////    assert(!b.insert(k[5], v));
//
//      // When two Maps' contents are swapped, their capacities are swapped
//      // as well:
//    a.swap(b);
//    a.dump();
//    b.dump();
//    assert(!a.insert(k[5], v)  &&  b.insert(k[5], v));
//    cout << "Passed all tests" << endl;
//}

#include "newMap.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
   Map m;
   assert(m.insert("Fred", 2.956));
   assert(m.insert("Ethel", 3.538));
   assert(m.size() == 2);
   ValueType v = 42;
   assert(!m.get("Lucy", v)  &&  v == 42);
   assert(m.get("Fred", v)  &&  v == 2.956);
   v = 42;
   KeyType x = "Lucy";
   assert(m.get(0, x, v)  &&
          ((x == "Fred"  &&  v == 2.956)  ||  (x == "Ethel"  &&  v == 3.538)));
   KeyType x2 = "Ricky";
   assert(m.get(1, x2, v)  &&
          ((x2 == "Fred"  &&  v == 2.956)  ||  (x2 == "Ethel"  &&  v == 3.538))  &&
          x != x2);
}

int main()
{
   test();
   cout << "Passed all tests" << endl;
}

//#include "newMap.h"
//#include <string>
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void test()
//{
//    Map m;
//    assert(m.insert(10, "diez"));
//    assert(m.insert(20, "veinte"));
//    assert(m.size() == 2);
//    ValueType v = "cuarenta y dos";
//    assert(!m.get(30, v)  &&  v == "cuarenta y dos");
//    assert(m.get(10, v)  &&  v == "diez");
//    v = "cuarenta y dos";
//    KeyType x = 30;
//    assert(m.get(0, x, v)  &&
//           ((x == 10  &&  v == "diez")  ||  (x == 20  &&  v == "veinte")));
//    KeyType x2 = 40;
//    assert(m.get(1, x2, v)  &&
//           ((x2 == 10  &&  v == "diez")  ||  (x2 == 20  &&  v == "veinte"))  &&
//           x != x2);
//}
//
//int main()
//{
//    test();
//    cout << "Passed all tests" << endl;
//}
