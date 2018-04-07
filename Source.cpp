#include <iostream>
#include <assert.h>
#include "arr_queue.h"
//#include "Test.h"

using namespace std;


int main()
{
  // Uncomment this if you want testing
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

  

 // f<int>(3);
//  f<string>("Hell");
  //system("pause");
}
