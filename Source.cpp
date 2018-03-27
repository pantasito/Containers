#include <iostream>
#include "Test.h"


using namespace std;

template <class T>
class arr_queue : public a_queue<T>
{
  static const int MEMORY_START_SIZE = 100;
  
    T* data; // Указатель на массив данных (где храним элементы)
    size_t last_ind; // Индекс в массиве, указывающий на пооследний элемент

    size_t array_length; // Текущий максимальный размер массива
    
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

    // Добавить элемент в конце очереди
    void push(T t) 
    {
      // Добавление элемента в пустую очередь
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
          array_length *= 2;         
        }
        
        last_ind++;
        data[last_ind] = t;        
      }    
    } 
    
    // Возращает первый элемент в очереди (не извлекает его)
    T front() {}

    // Возращает последний элемент в очереди (не извлекает его)
    T back() {} 

    // Забрать первого в очереди
    T pop() {} 
    
    // Очистить очередь
    void clear() {} 

    // Размер контейнера
    size_t size() {}

    // Пустой ли контейнер
    bool empty() 
    {}
};

int main()
{
  // Uncomment this if you want testing
  stl_queue<int> stl_q;
  arr_queue<int> arr_q;
  Test_int_queue test;
  test.add_queue_to_test(stl_q,"STL");
  test.add_queue_to_test(arr_q,"ARR");
  test.run_all_tests();

 // f<int>(3);
//  f<string>("Hell");
  //system("pause");
}
