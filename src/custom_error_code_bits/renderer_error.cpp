// renerer_error: error category and make_error_code definitions

#include "renderer_error.h"
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
}

namespace the_game
{
  std::error_code make_error_code(renderer_error e)
  {
    static const renderer_error_category therenderer_error_categoryObj;
    return {static_cast<int>(e), therenderer_error_categoryObj};
  }
}
