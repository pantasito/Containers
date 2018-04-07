#include <iostream>
#include "Test.h"
#include <assert.h>

using namespace std;

template <class T>
class arr_queue : public a_queue<T>
{
  static const int MEMORY_START_SIZE = 100;
  
    T* data; // Pointer to data array (where elements are stored)
    size_t last_ind; // The index in the array that points to the last element

    size_t array_length; // Current maximum array size
    
  public:
    arr_queue() 
    {
      data = NULL;
      last_ind = 0;
      array_length = 0;
    }

    ~arr_queue() 
    {
      if (data != NULL) delete[] data;
    }

	// Add item at end of queue
    void push(T t) 
    {
	  // Adding an item to an empty queue
      if (data == NULL) {
        data = new T[MEMORY_START_SIZE];
        last_ind = 0;
        array_length = MEMORY_START_SIZE;
        data[0] = t;
      } else {
        if (last_ind == array_length-1) {          
          T* old_data = data;
          data = new T[array_length*2];
          //memcpy(data, old_data, (array_length / 2.0) * sizeof(T));
          for (int i = 0; i < array_length; i++) data[i] = old_data[i];
          delete[] old_data;
          array_length *= 2;         
        }
        
        last_ind++;
        data[last_ind] = t;        
      }    
    } 
    
	// Returns the first item in the queue (does not retrieve it)
    T front() {
		return data[0];
		}

	// Returns the last element in the queue (does not retrieve it)
    T back() {
		return data[last_ind];
		} 

	// Pick up first in line
    T pop() {		
   	  if (last_ind == 0 && array_length != 0) {
	    T result = data[0];
	    delete[] data;
	    data = NULL;
	    array_length = 0;
	    return result;
	  } else {
		assert(array_length > 0);
		if (last_ind > 0) {
		  T result = data[0];
		  for (int i = 0; i < last_ind; ++i) {
			  data[i] = data[i+1];
		  }
		  last_ind -= 1; 
	      return result;
		} else {
		  assert(false);
		}   
      }
	}
}    
	// Clear the queue
    void clear() {
		if (data != NULL)
			delete[] data;
		data = NULL;
		last_ind = 0;
        array_length = 0;
	} 

	// Container size
    size_t size() {
		if (array_length>0) return last_ind+1;
		return 0;
	}

	// If the container is empty
    bool empty() {
		if (data == NULL || array_length == 0) return true;
		else return false;
	}
};

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
