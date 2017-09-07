//
#ifndef CXX11_EXCEPTION_SUPPORT_CUSTOM_ERROR_CODE_BITS_APPENGINE_ERROR_CODES_H
# define CXX11_EXCEPTION_SUPPORT_CUSTOM_ERROR_CODE_BITS_APPENGINE_ERROR_CODES_H

# include <system_error>

namespace the_game
{
  enum class appengine_error
  { no_object_index     = 100
  , no_renderer
  , null_draw_action     = 200
  , bad_draw_context     = 300
  , bad_game_object
  , null_player          = 400
  };
  std::error_code make_error_code(appengine_error e);
}

namespace std
{
  using the_game::appengine_error;
  template <> struct is_error_code_enum<appengine_error> : true_type {};
}

#endif // CXX11_EXCEPTION_SUPPORT_CUSTOM_ERROR_CODE_BITS_APPENGINE_ERROR_CODES_H
