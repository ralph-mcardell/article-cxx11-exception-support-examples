// Plugging custom error codes into std::error_code etc. machinery example

// In game/renderer_panic.hpp
namespace TheGame
{
  enum class RendererPanic
  {
    GameDimensionTooSmall = 100 // Panics raised by GetSupportedGameDimensions
  , GameDimensionBadRange
  , BoardTooSmall         = 200 // Panics raised by GetSupportedBoardSizes
  , BoardBadRange
  , GameDimensionBad
  , BoardNotSquare        = 300 // Panics raised by NewGameRenderer
  , BoardSizeBad
  , BadRegion             = 400 // Panics raised by DrawBoard
  , CellCoordinateBad     = 500 // Panics raised by DrawCell
  , NewStateInvalid
  , PrevStateInvalid
  };
}

// In game/appengine_panic.hpp
namespace TheGame
{
  enum class AppEnginePanic
  {
    NoObjectConIx       = 100 // Panics raised by AppSession
  , NoRendererContainer
  , NullDrawAction      = 200 // Panics raised by GameSession
  , BadDrawContext      = 300 // Panics raised by DrawAction or specialisations
  , BadGameObject
  , NullPlayer          = 400 // Panics raised by GameSession
  };
}


// In game/error_codes.hpp
// Specialise std::is_error_code_enum for our panic codes enum types
#include <system_error>
namespace std
{
  using TheGame::RendererPanic;
  template <> struct is_error_code_enum<RendererPanic> : true_type {};
  using TheGame::AppEnginePanic;
  template <> struct is_error_code_enum<AppEnginePanic> : true_type {};
}

namespace TheGame
{
  enum class RendererPanic;
  std::error_code make_error_code(RendererPanic);

  enum class AppEnginePanic;
  std::error_code make_error_code(AppEnginePanic);
}

// In game/error_codes.cpp
#include <string>

namespace
{
  struct RendererPanicCategory : std::error_category
  {
    const char* name() const noexcept override;
    std::string message(int ev) const override;
  };

  const char* RendererPanicCategory::name() const noexcept 
  {
    return "renderer";
  }

  std::string RendererPanicCategory::message( int ev ) const
  {
    using TheGame::RendererPanic;
    switch( static_cast<RendererPanic>(ev) )
    {
    case RendererPanic::GameDimensionTooSmall:
      return "Renderer reported min. supported game grid less than 3 x 3";
    case RendererPanic::GameDimensionBadRange:
      return "Render reported a max. supported game grid less than the min.";
    case RendererPanic::BoardTooSmall:
      return "Renderer reported a min. supported pixel length less than 1";
    case RendererPanic::BoardBadRange:
      return "Render reported a max. supported pixel length less than the min.";
    case RendererPanic::GameDimensionBad:
      return "Game dimension passed to GetSupportedBoardSizes is not supported";
    case RendererPanic::BoardNotSquare:
      return "Game rect. passed to NewGameRenderer must be square";
    case RendererPanic::BoardSizeBad:
      return "Game rect. passed to NewGameRenderer not supported but this renderer";
    case RendererPanic::BadRegion:
      return "DrawBoard only accepts positive height and width values.";
    case RendererPanic::CellCoordinateBad:
      return "DrawCell only accepts positive cell X and Y index values.";
    case RendererPanic::NewStateInvalid:
      return "DrawCell: passed in requested new state is invalid";
    case RendererPanic::PrevStateInvalid:
      return "DrawCell: passed in value of previous state is invalid";
    default:
      return "?? unrecognised error ??";
    }
  }

  const RendererPanicCategory theRendererPanicCategoryObj {};

  struct AppEnginePanicCategory : std::error_category
  {
    const char* name() const noexcept override;
    std::string message(int ev) const override;
  };

  const char* AppEnginePanicCategory::name() const noexcept 
  {
    return "app-engine";
  }

  std::string AppEnginePanicCategory::message( int ev ) const
  {
    using TheGame::AppEnginePanic;
    switch( static_cast<AppEnginePanic>(ev) )
    {
    case AppEnginePanic::NoObjectConIx:
      return "No object container index to create object container from";
    case AppEnginePanic::NoRendererContainer:
      return "No renderer container to access renderers through";
    case AppEnginePanic::NullDrawAction:
      return "Null draw action pointer";
    case AppEnginePanic::BadDrawContext:
      return "Draw action context has NULL graphics context or renderer pointer";
    case AppEnginePanic::BadGameObject:
      return "Draw action context has NULL game object pointer";
    case AppEnginePanic::NullPlayer:
      return "Current player pointer is null";
    default:
      return "?? unrecognised error ??";
    }
  }

  const AppEnginePanicCategory theAppEnginePanicCategoryObj {};
}

namespace TheGame
{
  std::error_code make_error_code(RendererPanic e)
  {
    return {static_cast<int>(e), theRendererPanicCategoryObj};
  }

  std::error_code make_error_code(AppEnginePanic e)
  {
    return {static_cast<int>(e), theAppEnginePanicCategoryObj};
  }
}

#include <iostream>

int main()
{
  std::error_code r_ec{ TheGame::RendererPanic::BoardNotSquare };
  std::error_code ae_ec{ TheGame::AppEnginePanic::BadDrawContext };
  std::cout << r_ec << " " << r_ec.message() << "\n" 
            << ae_ec << " " << ae_ec.message() << std::endl;
}
