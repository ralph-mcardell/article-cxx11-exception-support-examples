#include "cxx11_common_catch_clause_eg_api.h"

#include <assert.h>
#include <stdlib.h>

int main( void )
{
  struct widget * pw = NULL;
  assert(make_widget(NULL, 19u) == bad_pointer);
  assert(make_widget(&pw, 9u) == value_out_of_range);
  if (make_widget(&pw, 45u) != OK)
  {
    return EXIT_FAILURE;
  }
  unsigned value = 0u;
  assert(get_widget_attribute(pw, &value) == OK);
  assert(get_widget_attribute(NULL, &value) == bad_pointer);
  assert(value == 45u);
  assert(set_widget_attribute(pw, 67u) == OK);
  assert(set_widget_attribute(NULL, 11u) == bad_pointer);
  assert(set_widget_attribute(pw, 123u) == value_out_of_range);
  get_widget_attribute(pw, &value);
  assert(value == 67u);
  assert(destroy_widget(pw) == OK);
  assert(destroy_widget(NULL) == bad_pointer);
}
