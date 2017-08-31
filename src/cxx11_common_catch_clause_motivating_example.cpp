// C++11 C API with repeated catch clauses example

#include "cxx11_common_catch_clause_eg_api.h"
#include <stdexcept>
#include <new>

namespace
{
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
    catch ( std::invalid_argument const & )
    {
      return bad_pointer; 
    }
    catch ( std::bad_alloc const & )
    {
      status = no_memory;
    }
    catch ( std::range_error const & )
    {
      status = value_out_of_range;
    }
    catch ( ... )
    {
      status = unknown_error;
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
    catch ( std::invalid_argument const & )
    {
      return bad_pointer; 
    }
    catch ( ... )
    {
      status = unknown_error;
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
    catch ( std::invalid_argument const & )
    {
      return bad_pointer; 
    }
    catch ( std::range_error const & )
    {
      status = value_out_of_range;
    }
    catch ( ... )
    {
      status = unknown_error;
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
    catch ( std::invalid_argument const & )
    {
      return bad_pointer; 
    }
    catch ( ... )
    {
      status = unknown_error;
    }
    return status;
  }
}
