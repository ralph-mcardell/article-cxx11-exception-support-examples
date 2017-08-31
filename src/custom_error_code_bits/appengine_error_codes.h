//
#ifndef CXX11_EXCEPTION_SUPPORT_CUSTOM_ERROR_CODE_BITS_APPENGINE_ERROR_CODES_H
# define CXX11_EXCEPTION_SUPPORT_CUSTOM_ERROR_CODE_BITS_APPENGINE_ERROR_CODES_H
// In game/appengine_panic.hpp
namespace the_game
{
  enum class appengine_error
  { no_object_con_ix     = 100
  , no_renderer_container
  , null_draw_action     = 200
  , bad_draw_context     = 300
  , bad_game_object
  , null_player          = 400
  };
}
#endif // CXX11_EXCEPTION_SUPPORT_CUSTOM_ERROR_CODE_BITS_APPENGINE_ERROR_CODES_H
