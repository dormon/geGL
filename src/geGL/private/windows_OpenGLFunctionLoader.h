#pragma once

#if defined(_MSC_VER) || defined(__MINGW64__)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <geGL/gegl_export.h>

namespace ge{
  namespace gl{
    class OpenGLFunctionLoader;
  }
}

class GEGL_EXPORT ge::gl::OpenGLFunctionLoader{
  public:
    void*operator()(char const*name);
    ~OpenGLFunctionLoader();
  protected:
    bool triedToLoadOpenGL = false;
    bool triedToLoadGetProcAddress = false;
    HMODULE openglLib = nullptr;
    using PROC = int(*)();
    using WGLGETPROCADDRESS = PROC(__stdcall*)(LPCSTR);
    WGLGETPROCADDRESS wglGetProcAddress = nullptr;
};
#endif
