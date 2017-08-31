// Plugging custom error codes into std::error_code etc. machinery example

// In game/renderer_panic.hpp
namespace TheGame
{
  enum class RendererError
  { GameDimensionTooSmall = 100
  , GameDimensionBadRange
  , BoardTooSmall         = 200
  , BoardBadRange
  , GameDimensionBad
  , BoardNotSquare        = 300
  , BoardSizeBad
  , BadRegion             = 400
  , CellCoordinateBad     = 500
  , NewStateInvalid
  , PrevStateInvalid
  };
}

// In game/appengine_panic.hpp
namespace TheGame
{
  enum class AppEngineError
  { NoObjectConIx       = 100
  , NoRendererContainer
  , NullDrawAction      = 200
  , BadDrawContext      = 300
  , BadGameObject
  , NullPlayer          = 400
  };
}


// In game/error_codes.hpp
// Specialise std::is_error_code_enum for our panic codes enum types
#include <system_error>
namespace std
{
  using TheGame::RendererError;
  template <> struct is_error_code_enum<RendererError> : true_type {};
  using TheGame::AppEngineError;
  template <> struct is_error_code_enum<AppEngineError> : true_type {};
}

namespace TheGame
{
  enum class RendererError;
  std::error_code make_error_code(RendererError);

  enum class AppEngineError;
  std::error_code make_error_code(AppEngineError);
}

// In game/error_codes.cpp
#include <string>

namespace
{
  struct RendererErrorCategory : std::error_category
  {
    const char* name() const noexcept override;
    std::string message(int ev) const override;
  };

  const char* RendererErrorCategory::name() const noexcept 
  {
    return "renderer";
  }

  std::string RendererErrorCategory::message( int ev ) const
  {
    using TheGame::RendererError;
    switch( static_cast<RendererError>(ev) )
    {
    case RendererError::GameDimensionTooSmall:
      return "Reported min. supported game grid less than 3 x 3";
    case RendererError::GameDimensionBadRange:
      return "Reported a max. supported game grid less than the min.";
    case RendererError::BoardTooSmall:
      return "Reported a min. supported pixel length less than 1";
    case RendererError::BoardBadRange:
      return "Reported a max. supported pixel length less than the min.";
    case RendererError::GameDimensionBad:
      return "Game dimension is not supported";
    case RendererError::BoardNotSquare:
      return "Game rect. must be square";
    case RendererError::BoardSizeBad:
      return "Game rect. size not supported by this renderer";
    case RendererError::BadRegion:
      return "Negative height and width values are invalid";
    case RendererError::CellCoordinateBad:
      return "Negative board cell X and Y index values are invalid";
    case RendererError::NewStateInvalid:
      return "Requested new board cell state value is invalid";
    case RendererError::PrevStateInvalid:
      return "Claimed previous state value is invalid";
    default:
      return "?? unrecognised error ??";
    }
  }

  const RendererErrorCategory theRendererErrorCategoryObj {};

  struct AppEngineErrorCategory : std::error_category
  {
    const char* name() const noexcept override;
    std::string message(int ev) const override;
  };

  const char* AppEngineErrorCategory::name() const noexcept 
  {
    return "app-engine";
  }

  std::string AppEngineErrorCategory::message( int ev ) const
  {
    using TheGame::AppEngineError;
    switch( static_cast<AppEngineError>(ev) )
    {
    case AppEngineError::NoObjectConIx:
      return "No object container index to create object container from";
    case AppEngineError::NoRendererContainer:
      return "No renderer container to access renderers through";
    case AppEngineError::NullDrawAction:
      return "Null draw action pointer";
    case AppEngineError::BadDrawContext:
      return "Draw action context has null graphics context or renderer pointer";
    case AppEngineError::BadGameObject:
      return "Draw action context has null game object pointer";
    case AppEngineError::NullPlayer:
      return "Current player pointer is null";
    default:
      return "?? unrecognised error ??";
    }
  }

  const AppEngineErrorCategory theAppEngineErrorCategoryObj {};
}

namespace TheGame
{
  std::error_code make_error_code(RendererError e)
  {
    return {static_cast<int>(e), theRendererErrorCategoryObj};
  }

  std::error_code make_error_code(AppEngineError e)
  {
    return {static_cast<int>(e), theAppEngineErrorCategoryObj};
  }
}

#include <iostream>

int main()
{
  std::error_code r_ec{ TheGame::RendererError::BoardNotSquare };
  std::error_code ae_ec{ TheGame::AppEngineError::BadDrawContext };
  std::cout << r_ec << " " << r_ec.message() << "\n" 
            << ae_ec << " " << ae_ec.message() << std::endl;
}
