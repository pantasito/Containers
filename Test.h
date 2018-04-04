#pragma once
#include <queue>
#include <ctime> 
#include <map>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <cstdlib>

using namespace std;

#define THROW(mes)     { stringstream ss; ss << mes; throw ss.str().c_str(); }
#define LOG(level,mes) { if ((log_level)>=(level)) cout << "  -= " <<  mes << endl; }

template<class T>
class a_queue
{
  public: 
    // ƒобавить элемент в конце очереди
    virtual void push(T t) = 0;   

    // ¬озращает первый элемент в очереди (не извлекает его)
    virtual T front() = 0;

    // ¬озращает последний элемент в очереди (не извлекает его)
    virtual T back() = 0;

    // «абрать первого в очереди
    virtual T pop() = 0;

    // ќчистить очередь
    virtual void clear() = 0;

    // –азмер контейнера
    virtual size_t size() = 0;

    // ѕустой ли контейнер
    virtual bool empty() = 0;
};

template<class T>
class stl_queue : public a_queue<T>
{
  queue<T> q;
public:
  void push(T t)        { q.push(t); }
  virtual T front()     { return q.front(); }
  virtual T back()      { return q.back(); }
  virtual T pop()       { T res = q.front(); q.pop(); return res; }
  virtual void clear()  { while (q.empty() == false) q.pop(); } 
  virtual size_t size() { return q.size(); }
  virtual bool empty()  { return q.empty();  }
};


class Test_int_queue
{
  // queue with string name
  struct named_queue 
  {
    string name;
    a_queue<int>* q;

    named_queue(string _name, a_queue<int>& _q):name(_name), q(&_q) {}
    a_queue<int>& get_q() { return *q; }
  };

  // All queues for testing
  vector<named_queue> all_queues;


  public:
    // level of debug information. More level - more information
    // key - test num, value - log_level for this test (default 0)
    map<int,int> log_levels;
    
    void add_queue_to_test(a_queue<int>& q, string name)
    {
      all_queues.push_back(named_queue(name, q));
    }

    void run_all_tests(int iterations = 10000)
    {      
      const int TESTS_COUNT = 3;
      double** results = new double*[all_queues.size()];
      for (int i = 0; i < all_queues.size(); i++) {
        results[i] = new double[TESTS_COUNT];

        cout << "Test queue: " << all_queues[i].name << endl;
        results[i][0] = Test_1(all_queues[i].get_q(), iterations);
        results[i][1] = Test_2(all_queues[i].get_q(), iterations);
        results[i][2] = Test_3(all_queues[i].get_q(), iterations*2);
        cout << endl;
      }

      // Print results
      stringstream ss;
      ss << setw(10) << "queue name" << "| Test 1 | Test 2 | Test 3 |" << endl;
      for (int i = 0; i < all_queues.size(); i++) {
        ss << setw(10) << all_queues[i].name << "|";
        for (int j = 0; j < TESTS_COUNT; j++) {
          ss << setw(8) << results[i][j] << "|";
        }
        ss << endl;
      }
      cout << ss.str() << endl;
    }

    // ============================ TESTS ============================ //
    
    // 1 add, 1 remove, 1 add, 1 remove
    double Test_1(a_queue<int>& q, int iterations = 10000)
    {
        int log_level = 0;
        if (log_levels.find(1) != log_levels.end())
            log_level = log_levels[1];
      LOG(1,"Clear queue");
      q.clear();
      unsigned int start_time = clock(); // начальное врем€
      try
      {
        for (int i = 0; i < iterations; i++) {
          LOG(1,"Push " << i << " to queue");
          q.push(i);

          LOG(1,"Get front() of queue");
          int res = q.front();
          LOG(1,"Check correct of front: " << res);
          if (res != i) THROW("front() return " << res << " but expected " << i);
          
          LOG(1,"Get pop() of queue");
          res = q.pop();
          if (res != i) THROW("pop() return " << res << " but expected " << i);

          LOG(1,"Check empty of queue");
          if (q.empty() == false) THROW("empty return false, but expected true");
        }
        LOG(1,"Check size of queue");
        if (q.size() != 0) THROW("size return " << q.size() << ". Expected 0");
      }
      catch (const char* ex)
      {
        cout << "Test_1: -=Error=-: " << ex << endl;
        return 0;
      }
      unsigned int end_time = clock(); // конечное врем€
      unsigned int search_time = end_time - start_time; // искомое врем€
      cout << "Test_1 completed. Time " << double(search_time) / 1000.0 << " sec" << endl;
      return double(search_time) / 1000.0;
    }

    // 2 add, 1 remove, 2 add, 1 remove, ...
    double Test_2(a_queue<int>& q, int iterations = 10000)
    {
        int log_level = 0;
        if (log_levels.find(1) != log_levels.end())
            log_level = log_levels[2];
        LOG(1,"Clear queue");
      q.clear();
      unsigned int start_time = clock(); // начальное врем€
      try
      {
        for (int i = 0; i < iterations; i++) {
          LOG(1,"Push " << i << " to queue");
          q.push(i);
          LOG(1,"Push " << i+1 << " to queue");
          q.push(i + 1);

          LOG(1,"Get pop() of queue");
          int res = q.pop();

          LOG(1,"Check correct of pop: " << res);
          if (res != (i+1) / 2)   THROW("pop() return " << res << " but expected " << i / 2);
          LOG(1,"Check size of queue: ");
          if (q.size() != i + 1)  THROW("size return " << q.size() << ". Expected " << i + 1);
        }
        LOG(1,"Check empty of queue");
        if (q.empty() != false) THROW("empty return true, but expected false");
      }
      catch (const char* ex)
      {
        cout << "Test_2: -=Error=-: " << ex << endl;
        return 0;
      }
      unsigned int end_time = clock(); // конечное врем€
      unsigned int search_time = end_time - start_time; // искомое врем€
      cout << "Test_2 completed. Time " << double(search_time) / 1000.0 << " sec" << endl;
      return double(search_time) / 1000.0;
    }

    // Random add - 70% chanse, random remove 30% chanse
    double Test_3(a_queue<int>& q, int iterations = 10000)
    {
        int log_level = 0;
        if (log_levels.find(1) != log_levels.end())
            log_level = log_levels[3];
      LOG(1,"Clear queue");
      q.clear();
      unsigned int start_time = clock(); // начальное врем€
      try
      {
        int size = 0;
        for (int i = 0; i < iterations; i++) {
          if (rand() % 100 < 70) {
            int el = rand() % 1000;
            LOG(1,"Push " << el << " to queue");
            q.push(el);
            size++;
          } else {
            if (q.empty() != false) {
              LOG(1,"Get pop() of queue");
              q.pop();
              if (size > 0) size--;
            }
          }

          LOG(1,"Check size of queue");
          if (size != q.size()) THROW("size() return " << q.size() << " but expected " << size);
        }
      }
      catch (const char* ex)
      {
        cout << "Test_3: -=Error=-: " << ex << endl;
        return 0;
      }
      unsigned int end_time = clock(); // конечное врем€
      unsigned int search_time = end_time - start_time; // искомое врем€
      cout << "Test_3 completed. Time " << double(search_time) / 1000.0 << " sec " << endl;
      return double(search_time) / 1000.0;
    }    
};
