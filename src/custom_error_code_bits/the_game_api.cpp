// Custom error code example : spoof game api functions
#include "the_game_api.h"
#include "renderer_error.h"
#include "appengine_error.h"
#include <system_error>
#include <memory>

namespace the_game
{
  std::error_code check_dimensions( int dim_min, int dim_max ) noexcept
  {
    if ( dim_min < 3 )
    {
      return renderer_error::game_dimension_too_small;
    }
    if ( dim_max < dim_min )
    {
      return renderer_error::game_dimension_bad_range;
    }
    return {};
  }

  std::error_code appengine::take_renderer( std::unique_ptr<renderer> && rp )
    noexcept
  {
    auto ec{ check_dimensions(rp->min_dimension(), rp->max_dimension()) };
    if ( !ec )
    {
      rp_ = std::move(rp);
    }
    return ec;
  }

  std::error_code appengine::update_game_board() noexcept
  { // good case demonstrates zero-initialising enum class instance 
    return rp_ ? appengine_error{} : appengine_error::no_renderer;
  }

  int oops_renderer::min_dimension() const
  {
    return 5;
  }
  int oops_renderer::max_dimension() const
  {
    return 3;
  }

  int fine_renderer::min_dimension() const
  {
    return 3;
  }
  int fine_renderer::max_dimension() const
  {
    return 5;
  }

  appengine & get_appengine()
  {
    static appengine the_appengine;
    return the_appengine;
  }
}
