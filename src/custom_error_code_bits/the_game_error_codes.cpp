// Custom error code: error category and make_error_code definitions

#include "renderer_error.h"
#include "appengine_error.h"
#include <system_error>
#include <string>

namespace
{
  struct renderer_error_category : std::error_category
  {
    const char* name() const noexcept override;
    std::string message(int ev) const override;
  };

  const char* renderer_error_category::name() const noexcept 
  {
    return "renderer";
  }

  std::string renderer_error_category::message( int ev ) const
  {
    using the_game::renderer_error;
    switch( static_cast<renderer_error>(ev) )
    {
    case renderer_error::game_dimension_too_small:
      return "Reported min. supported game grid less than 3 x 3";
    case renderer_error::game_dimension_bad_range:
      return "Reported max. supported game grid less than the min.";
    case renderer_error::board_too_small:
      return "Reported a min. supported pixel length less than 1";
    case renderer_error::board_bad_range:
      return "Reported a max. supported pixel length less than the min.";
    case renderer_error::game_dimension_bad:
      return "Game dimension is not supported";
    case renderer_error::board_not_square:
      return "Game rect. must be square";
    case renderer_error::board_size_bad:
      return "Game rect. size not supported by this renderer";
    case renderer_error::bad_region:
      return "Negative height and width values are invalid";
    case renderer_error::cell_coordinate_bad:
      return "Negative board cell X and Y index values are invalid";
    case renderer_error::new_state_invalid:
      return "Requested new board cell state value is invalid";
    case renderer_error::prev_state_invalid:
      return "Claimed previous state value is invalid";
    default:
      return "?? unrecognised error ??";
    }
  }

  const renderer_error_category therenderer_error_categoryObj {};

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

  const appengine_error_category theappengine_error_categoryObj {};
}

namespace the_game
{
  std::error_code make_error_code(renderer_error e)
  {
    return {static_cast<int>(e), therenderer_error_categoryObj};
  }

  std::error_code make_error_code(appengine_error e)
  {
    return {static_cast<int>(e), theappengine_error_categoryObj};
  }
}
