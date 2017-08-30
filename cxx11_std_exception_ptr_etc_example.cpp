// C++11 passing exceptions around using std::exception_ptr

#include <exception>
#include <thread>
#include <iostream>
#include <cassert>

std::exception_ptr g_stashed_exception_ptr;

auto bad_task() -> void
{
  try
  {
    std::thread().detach(); // Oops !!
  }
  catch ( ... )
  {
    g_stashed_exception_ptr = std::current_exception();
  }
}

auto main() -> int
{
  assert( g_stashed_exception_ptr == nullptr );
  assert( !g_stashed_exception_ptr );

  std::thread task( bad_task );
  task.join();

  assert( g_stashed_exception_ptr != nullptr );
  assert( g_stashed_exception_ptr );

  try
  {
    std::rethrow_exception( g_stashed_exception_ptr );
  }
  catch ( std::exception & e )
  {
    std::cerr << "Task failed exceptionally: " << e.what() << "\n";
  }
}
