#pragma once

#include<geGL/OpenGLObject.h>
#include<iostream>
#include<set>
#include<vector>

class ge::gl::Buffer:
  public OpenGLObject,
  public std::enable_shared_from_this<Buffer>
{
  public:
    enum ReallocFlags{
      NEW_BUFFER = 0u    ,
      KEEP_ID    = 1u<<0u,
      KEEP_DATA  = 1u<<1u,
    };
	GEGL_EXPORT Buffer();
	GEGL_EXPORT Buffer(
        GLsizeiptr       const&size                  ,
        GLvoid     const*const&data  = nullptr       ,
        GLbitfield       const&flags = GL_STATIC_DRAW);
	GEGL_EXPORT Buffer(
        FunctionTablePointer const&table);
	GEGL_EXPORT Buffer(
        FunctionTablePointer      const&table,
        GLsizeiptr                const&size                  ,
        GLvoid              const*const&data  = nullptr       ,
        GLbitfield                const&flags = GL_STATIC_DRAW);
    template<typename T>
    Buffer(
        std::vector<T>const&data                  ,
        GLbitfield    const&flags = GL_STATIC_DRAW);
    template<typename T>
    Buffer(
        FunctionTablePointer const&table                 ,
        std::vector<T>       const&data                  ,
        GLbitfield           const&flags = GL_STATIC_DRAW);
	GEGL_EXPORT virtual ~Buffer();
	GEGL_EXPORT void alloc(
        GLsizeiptr       const&size                  ,
        GLvoid     const*const&data  = nullptr       ,
        GLbitfield       const&flags = GL_STATIC_DRAW);
	GEGL_EXPORT GLvoid*map(
        GLbitfield const&access = GL_MAP_READ_BIT|GL_MAP_WRITE_BIT)const;
	GEGL_EXPORT GLvoid*map(
        GLintptr   const&offset                                   ,
        GLsizeiptr const&size                                     ,
        GLbitfield const&access = GL_MAP_READ_BIT|GL_MAP_WRITE_BIT)const;
	GEGL_EXPORT void unmap()const;
	GEGL_EXPORT void setData(
        GLvoid     const*const&data      ,
        GLsizeiptr       const&size   = 0,
        GLintptr         const&offset = 0)const;
	GEGL_EXPORT void getData(
        GLvoid*    const&data      ,
        GLsizeiptr const&size   = 0,
        GLintptr   const&offset = 0)const;
	GEGL_EXPORT void bind       (
        GLenum const&target)const;
	GEGL_EXPORT void bindRange  (
        GLenum     const&target,
        GLuint     const&index ,
        GLintptr   const&offset,
        GLsizeiptr const&size  )const;
	GEGL_EXPORT void bindBase   (
        GLenum const&target,
        GLuint const&index)const;
	GEGL_EXPORT void unbind     (
        GLenum const&target)const;
	GEGL_EXPORT void unbindRange(
        GLenum const&target,
        GLuint const&index)const;
	GEGL_EXPORT void unbindBase (
        GLenum const&target,
        GLuint const&index )const;
	GEGL_EXPORT bool realloc(
        GLsizeiptr   const&newSize             ,
        ReallocFlags const&flags   = NEW_BUFFER);
	GEGL_EXPORT void copy(
        Buffer const&buffer)const;
	GEGL_EXPORT void flushMapped(
        GLsizeiptr const&size   = 0,
        GLintptr   const&offset = 0)const;
	GEGL_EXPORT void invalidate(
        GLsizeiptr const&size   = 0,
        GLintptr   const&offset = 0)const;
	GEGL_EXPORT void clear(
        GLenum       const&internalFormat          ,
        GLenum       const&format                  ,
        GLenum       const&type                    ,
        GLvoid const*const&Data           = nullptr)const;
	GEGL_EXPORT void clear(
        GLenum           const&internalFormat          ,
        GLintptr         const&offset                  ,
        GLsizeiptr       const&size                    ,
        GLenum           const&format                  ,
        GLenum           const&type                    ,
        GLvoid     const*const&Data           = nullptr)const;
	GEGL_EXPORT GLsizeiptr getSize       ()const;
	GEGL_EXPORT GLbitfield getUsage      ()const;
	GEGL_EXPORT GLenum     getAccess     ()const;
	GEGL_EXPORT GLbitfield getAccessFlags()const;
	GEGL_EXPORT GLboolean  isMapped      ()const;
	GEGL_EXPORT GLintptr   getMapOffset  ()const;
	GEGL_EXPORT GLsizeiptr getMapSize    ()const;
	GEGL_EXPORT GLvoid*    getMapPointer ()const;
	GEGL_EXPORT GLboolean  isImmutable   ()const;
  private:
    GLint   _getBufferParameter(
        GLenum const&pname)const;
    GLvoid* _getBufferPointer  (
        GLenum const&pname)const;
    void    _bufferData(
        GLsizeiptr       const&size,
        GLvoid     const*const&data,
        GLbitfield       const&flags)const;
    std::set<VertexArray*>_vertexArrays;
    void _updateVertexArrays();
    friend class VertexArray;
};

template<typename T>
ge::gl::Buffer::Buffer(
    std::vector<T>const&data ,
    GLbitfield    const&flags):Buffer(data.size()*sizeof(T),data.data(),flags){}

template<typename T>
ge::gl::Buffer::Buffer(
    FunctionTablePointer const&table,
    std::vector<T>       const&data ,
    GLbitfield           const&flags):Buffer(table,data.size()*sizeof(T),data.data(),flags){}
