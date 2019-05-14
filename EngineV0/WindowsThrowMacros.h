#pragma once

//macros
// error exception helper macro
#define WND_EXCEPT( hr ) Window::HrException( __LINE__,__FILE__,(hr) )
#define WND_LAST_EXCEPT() Window::HrException( __LINE__,__FILE__,GetLastError() )
#define WND_NOGFX_EXCEPT() Window::NoGfxException( __LINE__,__FILE__ )