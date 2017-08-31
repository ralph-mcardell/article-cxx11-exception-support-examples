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
# include <memory>

namespace std
{
  using the_game::renderer_error;
  template <> struct is_error_code_enum<renderer_error> : true_type {};
  using the_game::appengine_error;
  template <> struct is_error_code_enum<appengine_error> : true_type {};
}

namespace the_game
{
// Declarations for make_error_code overloads for our  error codes enum types
  std::error_code make_error_code(renderer_error);
  std::error_code make_error_code(appengine_error);

// Some pretend game types
  struct renderer
  {
    virtual int min_dimension() const = 0;
    virtual int max_dimension() const = 0;
  };

  struct oops_renderer : renderer
  {
    int min_dimension() const override;
    int max_dimension() const override;
  };

  struct fine_renderer : renderer
  {
    int min_dimension() const override;
    int max_dimension() const override;
  };

  class appengine
  {
    std::unique_ptr<renderer> rp_;

  public:
    std::error_code take_renderer( std::unique_ptr<renderer> && rp );
    std::error_code update_game_board();
  };

  appengine & get_appengine();
}
#endif // CXX11_EXCEPTION_SUPPORT_CUSTOM_ERROR_CODE_BITS_THE_GAME_H
