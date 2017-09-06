// Plugging custom error codes into std::error_code etc. machinery example

#include "custom_error_code_bits/the_game_api.h"
#include <system_error>
#include <iostream>
#include <string>
#include <new>

void log_bad_status_codes( std::error_code ec )
{
  if ( ec )
  {
    std::clog << ec << " " << ec.message() << "\n";
  }
}

int main()
{
  auto & engine{ the_game::get_appengine() };

  // Should fail as setting renderer supporting invalid dimension range
  std::unique_ptr<the_game::renderer> rend{new the_game::oops_renderer};
  log_bad_status_codes( engine.take_renderer( std::move(rend) ) );

  // Should fail as no renderer successfully set to draw board
  // a) non-throwing overload
  log_bad_status_codes( engine.update_game_board(std::nothrow) );
  // b) throwing overload
  try
  {
    engine.update_game_board();
  }
  catch ( std::exception & e )
  {
    std::cerr << "Caught exception: " << e.what() << "\n";
  }
  // OK - nothing to report, this renderer is fine and dandy
  rend.reset( new the_game::fine_renderer );
  log_bad_status_codes( engine.take_renderer( std::move(rend)) );

  // OK - now have renderer to render board updates
  log_bad_status_codes( engine.update_game_board(std::nothrow) );
}
