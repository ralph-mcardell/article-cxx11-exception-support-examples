// Plugging custom error codes into std::error_code etc. machinery example

#include "custom_error_code_bits/the_game.h"
#include "custom_error_code_bits/renderer_error_codes.h"
#include "custom_error_code_bits/appengine_error_codes.h"
#include <iostream>
#include <string>

void log_bad_status_codes( std::error_code ec )
{
  if ( ec )
  {
    std::clog << ec << " " << ec.message() << "\n";
  }
}

int main()
{
  log_bad_status_codes( {the_game::renderer_error::board_not_square} );
  log_bad_status_codes( {the_game::appengine_error::bad_draw_context} );
}
