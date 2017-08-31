// Custom error codes: interface file for the game internals client code

#ifndef CXX11_EXCEPTION_SUPPORT_CUSTOM_ERROR_CODE_BITS_THE_GAME_H
# define CXX11_EXCEPTION_SUPPORT_CUSTOM_ERROR_CODE_BITS_THE_GAME_H

namespace the_game
{
  enum class renderer_error;
  enum class appengine_error;
}

// Specialise std::is_error_code_enum for our error codes enum types
# include <system_error>
namespace std
{
  using the_game::renderer_error;
  template <> struct is_error_code_enum<renderer_error> : true_type {};
  using the_game::appengine_error;
  template <> struct is_error_code_enum<appengine_error> : true_type {};
}

// Declarations for make_error_code overloads for our  error codes enum types
namespace the_game
{
  std::error_code make_error_code(renderer_error);
  std::error_code make_error_code(appengine_error);
}
#endif // CXX11_EXCEPTION_SUPPORT_CUSTOM_ERROR_CODE_BITS_THE_GAME_H
