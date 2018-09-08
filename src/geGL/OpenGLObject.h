#pragma once

#include<geGL/OpenGLContext.h>

class ge::gl::OpenGLObject{
  public:
    GEGL_EXPORT OpenGLObject(GLuint id = 0u);
	GEGL_EXPORT OpenGLObject(FunctionTablePointer const&table,GLuint id = 0u);
	GEGL_EXPORT virtual ~OpenGLObject();
	GEGL_EXPORT GLuint getId()const;
	GEGL_EXPORT Context const&getContext()const;
	GEGL_EXPORT OpenGLObject(OpenGLObject const&) = delete;
  protected:
    GLuint _id = 0u;///<object id
    Context _gl;
};

