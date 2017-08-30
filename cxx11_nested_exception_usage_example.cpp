// C++11 Using nested exceptions

#include <exception>
#include <string>
#include <iostream>
#include <stdexcept>

void log_exception( std::exception const & e, unsigned level = 0u )
{
  const std::string indent( 3*level, ' ' );
  const std::string prefix( indent + (level?"Nested":"Outer") + " exception: " );
  std::cerr << prefix << e.what() << "\n";
  try
  {
    std::rethrow_if_nested( e );
  }
  catch ( std::exception const & ne )
  {
    log_exception( ne, level + 1 );
  }
  catch( ... ) {}
}

void sub_task4()
{ // do something which fails...
  throw std::overflow_error{ "sub_task4 failed: calculation overflowed" };
}

void task2()
{
  try
  { // pretend sub tasks 1, 2 and 3 are performed OK...
    sub_task4();
  }
  catch ( ... )
  {
    std::throw_with_nested
      ( std::runtime_error{ "task2 failed performing sub tasks" } );
  }
}

void do_tasks()
{
  try
  { // pretend task 1 performed OK...
    task2();
  }
  catch ( ... )
  {
    std::throw_with_nested
      ( std::runtime_error{ "Execution failed performing tasks" } );
  }
}

int main()
{
  try
  {
    do_tasks();
  }
  catch ( std::exception const & e )
  {
    log_exception( e );
  }
}
