// C++11 C API with common catch clauses example

#include "cxx11_common_catch_clause_eg_api.h"
#include <stdexcept>
#include <new>
#include <exception>

namespace
{
  status_t handle_exception( std::exception_ptr ep )
  {
    try
    {
      std::rethrow_exception( ep );
    }
    catch ( std::bad_alloc const & )
    {
      return no_memory;
    }
    catch ( std::range_error const & )
    {
      return value_out_of_range;
    }
    catch (std::invalid_argument const & )
    {// for simplicity we assume all bad arguments are bad pointers
      return bad_pointer; 
    }
    catch ( ... )
    {
      return unknown_error;
    }
  }

  void check_pointer( void const * p )
  {
    if ( p==nullptr )
    {
      throw std::invalid_argument("bad pointer");
    }
  }
}

extern "C"
{
  struct widget 
  {
  private:
    unsigned attrib = 10u;

  public:
    unsigned get_attrib() const { return attrib; }
    void set_attrib( unsigned v )
    {
      if ( v < 10 || v >= 100 )
      {
        throw std::range_error
          ( "widget::set_widget_attribute: attribute value out of range [10,100)" );
      }
      attrib = v;
    }
  };

  status_t make_widget( widget ** ppw, unsigned v )
  {
    status_t status{ OK };
    try
    {
      check_pointer( ppw );
      *ppw = new widget;
      (*ppw)->set_attrib( v );
    }
    catch ( ... )
    {
      status = handle_exception( std::current_exception() );
    }
    return status;
  }

  status_t get_widget_attribute( widget const * pcw, unsigned * pv )
  {
    status_t status{ OK };
    try
    {
      check_pointer( pcw );
      check_pointer( pv );
      *pv = pcw->get_attrib();
    }
    catch ( ... )
    {
      status = handle_exception( std::current_exception() );
    }
    return status;
  }

  status_t set_widget_attribute( widget * pw, unsigned v )
  {
    status_t status{ OK };
    try
    {
      check_pointer( pw );
      pw->set_attrib( v );
    }
    catch ( ... )
    {
      status = handle_exception( std::current_exception() );
    }
    return status;
  }

  status_t destroy_widget( widget * pw )
  {
    status_t status{ OK };
    try
    {
      check_pointer( pw );
      delete pw;
    }
    catch ( ... )
    {
      status = handle_exception( std::current_exception() );
    }
    return status;
  }
}
