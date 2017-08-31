// simple raising of C++11 new exceptions examples

#include <memory>
#include <iostream>
#include <cassert>
void raise_bad_weak_ptr()
{
  std::weak_ptr<int> int_wptr;
  assert( int_wptr.expired() );
  try
  {
    std::shared_ptr<int> int_sptr{ int_wptr };
    std::cerr << "No exception thrown!\n";
  }
  catch ( std::bad_weak_ptr & e )
  {
    std::cerr << "Expired or default initialised weak_ptr: " << e.what() << "\n";
  }
  catch ( ... )
  {
    std::cerr << "Caught unexpected exception\n";
  }
}

#include <functional>
#include <iostream>
#include <cassert>
void raise_bad_function_call()
{
  std::function<void()> fn_wrapper;
  assert( static_cast<bool>(fn_wrapper)==false );
  try
  {
    fn_wrapper();
    std::cerr << "No exception thrown!\n";
  }
  catch ( std::bad_function_call & e )
  {
    std::cerr << "Function wrapper is empty: " << e.what() << "\n";
  }
  catch ( ... )
  {
    std::cerr << "Caught unexpected exception\n";
  }
}

#include <new>
#include <iostream>
void raise_bad_array_new_length()
{ 
  int len = -1;
  try
  {
    int * int_array = new int[len];
    std::cerr << "No exception thrown!\n";
    delete [] int_array;
  }
  catch ( std::bad_array_new_length & e )
  {
    std::cerr << "Bad array length: " << e.what() << "\n";
  }
  catch ( ... )
  {
    std::cerr << "Caught unexpected exception\n";
  }
}

#include <future>
#include <iostream>
void raise_future_error()
{
  std::promise<int> int_vow;
  auto int_future = int_vow.get_future();
  try
  {
    int_future = int_vow.get_future();
    std::cerr << "No exception thrown!\n";
  }
  catch ( std::future_error & e )
  {
    std::cerr << "Error from promise/future: " << e.what() << "\n";
  }
  catch ( ... )
  {
    std::cerr << "Caught unexpected exception\n";
  }
}

#include <system_error>
#include <thread>
#include <iostream>
void raise_system_error()
{
  try
  {
    std::thread().detach(); // Oops no thread to detach
    std::cerr << "No exception thrown!\n";
  }
  catch ( std::system_error & e )
  {
    std::cerr << "System error from thread detach: " << e.what() << "\n";
  }
  catch ( ... )
  {
    std::cerr << "Caught unexpected exception\n";
  }
}

#include <ios>
#include <fstream>
#include <iostream>
void raise_ios_base_failure()
{
  std::ofstream out;
  out.exceptions( std::ios::failbit | std::ios::badbit );
  try
  {
    out << "Oops! no file open on stream."; 
    std::cerr << "No exception thrown!\n";
  }
  catch ( std::ios_base::failure & e )
  {
    std::cerr << "IOStream failure: " << e.what() << "\n";
  }
  catch ( ... )
  {
    std::cerr << "Caught unexpected exception\n";
  }
}

int main()
{
  raise_bad_weak_ptr();
  raise_bad_function_call();
  raise_bad_array_new_length();
  raise_future_error();
  raise_system_error();
  raise_ios_base_failure();
}
