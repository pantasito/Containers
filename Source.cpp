#include <iostream>
#include <assert.h>
#include "arr_queue.h"
//#include "Test.h"
#include "Matrix.h"

using namespace std;

void test_matrix()
{
    cout << "Start test matrix" << endl;
    Matrix a(3,3,1,4);
    //a.print();
    Matrix b(3,3,0,10);
    //b.print();
    //Matrix c("a.txt");
    //c.print();
    Matrix d = a.add(b);
    //d.print();
    Matrix e = a.mul(2);
    //e.print();
    Matrix f(3, 3);
    //f.print();
    //a.print();
    //a.set(3, 3, 10);
    //a.print();
    //float g = a.get_the_determinant();
    //cout << g;
    cout << a << b;
    a *= b;
    cout << a;


    Matrix m1(4,4,0,9);
    Matrix sub_m1_1 = m1.submatrix(2,2);
    Matrix sub_m1_2 = m1.submatrix(3,0);

    cout << "Matrix m1:"          << endl << m1       << endl;
    cout << "Submatrix m1 (2,2):" << endl << sub_m1_1 << endl;
    cout << "Submatrix m1 (3,0):" << endl << sub_m1_2 << endl;


    Matrix m2(3,3,0,9);
    cout << "Determinant of matrix: " << endl << m2 << " is : " << m2.get_the_determinant() << endl;

}


int main()
{
  // Uncomment this if you want testing
  /*
  stl_queue<int> stl_q;
  arr_queue<int> arr_q;
  Test_int_queue test;
  test.log_levels[1] = 0;
  test.log_levels[2] = 0;
  test.log_levels[3] = 0;
  test.add_queue_to_test(stl_q,"STL");
  test.add_queue_to_test(arr_q,"ARR");
  test.run_all_tests(10000);
  arr_q.clear();

  cout << double(clock())/CLOCKS_PER_SEC << endl;
  */

 test_matrix();


 // f<int>(3);
//  f<string>("Hell");
  //system("pause");
}
