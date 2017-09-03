// Custom error codes: interface file for the game internals client code

#ifndef CXX11_EXCEPTION_SUPPORT_CUSTOM_ERROR_CODE_BITS_THE_GAME_H
# define CXX11_EXCEPTION_SUPPORT_CUSTOM_ERROR_CODE_BITS_THE_GAME_H

# include <memory>
# include <system_error>

namespace the_game
{
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
    std::error_code take_renderer( std::unique_ptr<renderer> && rp ) noexcept;
    std::error_code update_game_board() noexcept;
  };

  appengine & get_appengine();
}
#endif // CXX11_EXCEPTION_SUPPORT_CUSTOM_ERROR_CODE_BITS_THE_GAME_H
