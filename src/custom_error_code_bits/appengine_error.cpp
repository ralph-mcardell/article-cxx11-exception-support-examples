// appengine_error: error category and make_error_code definitions

#include "appengine_error.h"
#include <system_error>
#include <string>

namespace
{
  struct appengine_error_category : std::error_category
  {
    const char* name() const noexcept override;
    std::string message(int ev) const override;
  };

  const char* appengine_error_category::name() const noexcept 
  {
    return "app-engine";
  }

  std::string appengine_error_category::message( int ev ) const
  {
    using the_game::appengine_error;
    switch( static_cast<appengine_error>(ev) )
    {
    case appengine_error::no_object_index:
      return "No object index";
    case appengine_error::no_renderer:
      return "No renderer currently set";
    case appengine_error::null_draw_action:
      return "Null draw action pointer";
    case appengine_error::bad_draw_context:
      return "Draw action context has null graphics context or renderer pointer";
    case appengine_error::bad_game_object:
      return "Draw action context has null game object pointer";
    case appengine_error::null_player:
      return "Current player pointer is null";
    default:
      return "?? unrecognised error ??";
    }
  }
}

namespace the_game
{
  std::error_code make_error_code(appengine_error e)
  {
    static const appengine_error_category theappengine_error_categoryObj;
    return {static_cast<int>(e), theappengine_error_categoryObj};
  }
}
