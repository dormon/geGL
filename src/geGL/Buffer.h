#pragma once

#include <geGL/OpenGLObject.h>
#include <iostream>
#include <set>
#include <vector>

class GEGL_EXPORT ge::gl::Buffer : public OpenGLObject {
 public:
  enum ReallocFlags {
    NEW_BUFFER = 0u,
    KEEP_ID    = 1u << 0u,
    KEEP_DATA  = 1u << 1u,
  };
  Buffer();
  Buffer(GLsizeiptr const&    size,
         GLvoid const* const& data  = nullptr,
         GLbitfield const&    flags = GL_STATIC_DRAW);
  Buffer(FunctionTablePointer const& table);
  Buffer(FunctionTablePointer const& table,
         GLsizeiptr const&           size,
         GLvoid const* const&        data  = nullptr,
         GLbitfield const&           flags = GL_STATIC_DRAW);
  template <typename T>
  Buffer(std::vector<T> const& data, GLbitfield const& flags = GL_STATIC_DRAW);
  template <typename T>
  Buffer(FunctionTablePointer const& table,
         std::vector<T> const&       data,
         GLbitfield const&           flags = GL_STATIC_DRAW);
  virtual ~Buffer();
  void    alloc(GLsizeiptr const&    size,
                GLvoid const* const& data  = nullptr,
                GLbitfield const&    flags = GL_STATIC_DRAW);
  GLvoid* map(GLbitfield const& access = GL_MAP_READ_BIT |
                                         GL_MAP_WRITE_BIT) const;
  GLvoid* map(GLintptr const&   offset,
              GLsizeiptr const& size,
              GLbitfield const& access = GL_MAP_READ_BIT |
                                         GL_MAP_WRITE_BIT) const;
  void    unmap() const;
  void    setData(GLvoid const* const& data,
                  GLsizeiptr const&    size   = 0,
                  GLintptr const&      offset = 0) const;
  void    getData(GLvoid* const&    data,
                  GLsizeiptr const& size   = 0,
                  GLintptr const&   offset = 0) const;
  void    bind(GLenum const& target) const;
  void    bindRange(GLenum const&     target,
                    GLuint const&     index,
                    GLintptr const&   offset,
                    GLsizeiptr const& size) const;
  void    bindBase(GLenum const& target, GLuint const& index) const;
  void    unbind(GLenum const& target) const;
  void    unbindRange(GLenum const& target, GLuint const& index) const;
  void    unbindBase(GLenum const& target, GLuint const& index) const;
  void    realloc(GLsizeiptr const&   newSize,
                  ReallocFlags const& flags = NEW_BUFFER);
  void    copy(Buffer const& buffer) const;
  void    flushMapped(GLsizeiptr const& size   = 0,
                      GLintptr const&   offset = 0) const;
  void invalidate(GLsizeiptr const& size = 0, GLintptr const& offset = 0) const;
  void clear(GLenum const&        internalFormat,
             GLenum const&        format,
             GLenum const&        type,
             GLvoid const* const& Data = nullptr) const;
  void clear(GLenum const&        internalFormat,
             GLintptr const&      offset,
             GLsizeiptr const&    size,
             GLenum const&        format,
             GLenum const&        type,
             GLvoid const* const& Data = nullptr) const;
  GLsizeiptr getSize() const;
  GLbitfield getUsage() const;
  GLenum     getAccess() const;
  GLbitfield getAccessFlags() const;
  GLboolean  isMapped() const;
  GLintptr   getMapOffset() const;
  GLsizeiptr getMapSize() const;
  GLvoid*    getMapPointer() const;
  GLboolean  isImmutable() const;

 private:
  BufferImpl* impl = nullptr;
  friend class VertexArray;
};

template <typename T>
ge::gl::Buffer::Buffer(std::vector<T> const& data, GLbitfield const& flags)
    : Buffer(data.size() * sizeof(T), data.data(), flags)
{
}

template <typename T>
ge::gl::Buffer::Buffer(FunctionTablePointer const& table,
                       std::vector<T> const&       data,
                       GLbitfield const&           flags)
    : Buffer(table, data.size() * sizeof(T), data.data(), flags)
{
}
