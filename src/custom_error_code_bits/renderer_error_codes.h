// Custom error codes example : renderer error codes

#ifndef CXX11_EXCEPTION_SUPPORT_CUSTOM_ERROR_CODE_BITS_RENDERER_ERROR_CODES_H
# define CXX11_EXCEPTION_SUPPORT_CUSTOM_ERROR_CODE_BITS_RENDERER_ERROR_CODES_H
namespace the_game
{
  enum class renderer_error
  { game_dimension_too_small = 100
  , game_dimension_bad_range
  , board_too_small          = 200
  , board_bad_range
  , game_dimension_bad
  , board_not_square         = 300
  , board_size_bad
  , bad_region               = 400
  , cell_coordinate_bad      = 500
  , new_state_invalid
  , prev_state_invalid
  };
}
#endif // CXX11_EXCEPTION_SUPPORT_CUSTOM_ERROR_CODE_BITS_RENDERER_ERROR_CODES_H
