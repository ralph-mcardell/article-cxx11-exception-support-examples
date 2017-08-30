// C++11 C API with common catch clauses example - C API

#ifndef CXX11_COMMON_CATCH_CLAUSE_EG_API_H
# define CXX11_COMMON_CATCH_CLAUSE_EG_API_H

# ifdef __cplusplus
extern "C"
{
# endif

  struct widget;
  enum status_t { OK, no_memory, bad_pointer, value_out_of_range, unknown_error };
  enum status_t make_widget( struct widget ** ppw, unsigned v );
  enum status_t get_widget_attribute( struct widget const * pcw, unsigned * pv );
  enum status_t set_widget_attribute( struct widget * pw, unsigned v );
  enum status_t destroy_widget( struct widget * pw );

# ifdef __cplusplus
}
# endif

#endif // CXX11_COMMON_CATCH_CLAUSE_EG_API_H
