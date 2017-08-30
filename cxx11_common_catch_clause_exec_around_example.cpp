// C++11 C API with common catch clauses execute around example

#include "cxx11_common_catch_clause_eg_api.h"
#include <stdexcept>
#include <new>
#include <exception>

namespace
{
  template <class FnT>
  status_t try_it( FnT && fn )
  {
    try
    {
      fn();
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
    return OK;
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
    return try_it( [ppw,v]() -> void
                    {
                      check_pointer( ppw );
                      *ppw = new widget;
                      (*ppw)->set_attrib( v );
                    }
                  );
  }

  status_t get_widget_attribute( widget const * pcw, unsigned * pv )
  {
    return try_it( [pcw, pv]() -> void
                    {
                      check_pointer( pcw );
                      check_pointer( pv );
                      *pv = pcw->get_attrib();
                    }
                  );
  }

  status_t set_widget_attribute( widget * pw, unsigned v )
  {
    return try_it( [pw, v]() -> void
                    {
                      check_pointer( pw );
                      pw->set_attrib( v );
                    }
                  );
  }

  status_t destroy_widget( widget * pw )
  {
    return try_it( [pw]() -> void
                    {
                      check_pointer( pw );
                      delete pw;
                    }
                  );
  }
}
