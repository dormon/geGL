#pragma once

#include<geGL/OpenGLObject.h>
#include<iostream>
#include<vector>
#include<memory>

class ge::gl::VertexArray: public OpenGLObject{
  friend class Buffer;
  public:
  enum AttribPointerType{
    NONE,
    I,
    L
  };
  GEGL_EXPORT VertexArray ();
  GEGL_EXPORT VertexArray (FunctionTablePointer const&table);
  GEGL_EXPORT ~VertexArray();
  GEGL_EXPORT void addAttrib(
      std::shared_ptr<Buffer>const&buffer                      ,
      GLuint                       index                       ,
      GLint                        nofComponentsa              ,
      GLenum                       type                        ,
      GLsizei                      stride            = 0       ,
      GLintptr                     offset            = 0       ,
      GLboolean                    normalized        = GL_FALSE,  
      GLuint                       divisor           = 0       ,
      enum AttribPointerType       attribPointerType = NONE    );
  GEGL_EXPORT void addElementBuffer(
      std::shared_ptr<Buffer>const&buffer);
  GEGL_EXPORT void bind  ()const;
  GEGL_EXPORT void unbind()const;
  GEGL_EXPORT GLuint    getAttribBufferBinding (GLuint index)const;
  GEGL_EXPORT GLboolean isAttribEnabled        (GLuint index)const;
  GEGL_EXPORT GLint     getAttribSize          (GLuint index)const;
  GEGL_EXPORT GLsizei   getAttribStride        (GLuint index)const;
  GEGL_EXPORT GLenum    getAttribType          (GLuint index)const;
  GEGL_EXPORT GLboolean isAttribNormalized     (GLuint index)const;
  GEGL_EXPORT GLboolean isAttribInteger        (GLuint index)const;
  GEGL_EXPORT GLboolean isAttribLong           (GLuint index)const;
  GEGL_EXPORT GLuint    getAttribDivisor       (GLuint index)const;
  GEGL_EXPORT GLuint    getAttribBinding       (GLuint index)const;
  GEGL_EXPORT GLuint    getAttribRelativeOffset(GLuint index)const;
  GEGL_EXPORT GLuint    getElementBuffer()const;
  GEGL_EXPORT std::string getInfo()const;
  GEGL_EXPORT std::shared_ptr<Buffer>const&getElement()const;
  GEGL_EXPORT std::shared_ptr<Buffer>const&getBuffer(GLuint index)const;
  GEGL_EXPORT size_t getNofBuffers()const;
  protected:
  size_t _getNofBufferUsages(std::shared_ptr<Buffer>const&buffer)const;
  std::vector<std::shared_ptr<Buffer>>_buffers;
  std::shared_ptr<Buffer>_elementBuffer = nullptr;
  GLint _getAttrib(GLuint index,GLenum pname)const;
};

