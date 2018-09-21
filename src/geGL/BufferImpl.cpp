#include <geGL/Buffer.h>
#include <geGL/BufferImpl.h>
#include <geGL/OpenGLUtil.h>
#include <geGL/VertexArray.h>
#include <geGL/VertexArrayImpl.h>

using namespace ge::gl;

BufferImpl::BufferImpl(Buffer *b) : buffer(b) {}

void BufferImpl::bufferData(GLsizeiptr    size,
                            GLvoid const *data,
                            GLbitfield    flags) const
{
  auto const &gl = buffer->getContext();
  if (areBufferFlagsMutable(flags))
    gl.glNamedBufferData(buffer->getId(), size, data, flags);
  else
    gl.glNamedBufferStorage(buffer->getId(), size, data, flags);
}

void BufferImpl::updateVertexArrays()
{
  auto const me = buffer;
  for (auto const &vao : vertexArrays) {
    if (vao->impl->elementBuffer == me) {
      vao->addElementBuffer(me);
    }
    std::vector<GLuint> attribs;
    GLuint              attribId = 0;
    for (auto const &y : vao->impl->buffers) {
      if (y == me) attribs.push_back(attribId);
      attribId++;
    }
    for (auto const &attribIndex : attribs) {
      auto type = VertexArray::NONE;
      if (vao->isAttribInteger(attribIndex)) type = VertexArray::I;
      if (vao->isAttribLong(attribIndex)) type = VertexArray::L;
      vao->addAttrib(me, attribIndex, vao->getAttribSize(attribIndex),
                     vao->getAttribType(attribIndex),
                     vao->getAttribStride(attribIndex),
                     vao->getAttribRelativeOffset(attribIndex),
                     vao->isAttribNormalized(attribIndex),
                     vao->getAttribDivisor(attribIndex), type);
    }
  }
}

GLint BufferImpl::getBufferParameter(GLenum pname) const
{
  GLint param;
  buffer->getContext().glGetNamedBufferParameteriv(buffer->getId(), pname,
                                                   &param);
  return param;
}

GLvoid *BufferImpl::getBufferPointer(GLenum pname) const
{
  GLvoid *param;
  buffer->getContext().glGetNamedBufferPointerv(buffer->getId(), pname, &param);
  return param;
}

void BufferImpl::realloc(GLsizeiptr size, Buffer::ReallocFlags f)
{
  if ((f & Buffer::KEEP_ID) && buffer->isImmutable()) {
    throw std::runtime_error(
        "Buffer::realloc - can't sustain buffer id, buffer is immutable");
  }

  GLbitfield bufferFlags = buffer->getUsage();
  if (f == (Buffer::KEEP_ID | Buffer::KEEP_DATA))
    resizeBufferKeepDataKeepId(size, bufferFlags);
  else if (f == Buffer::KEEP_ID)
    resizeBuffer(size, bufferFlags);
  else if (f == Buffer::KEEP_DATA)
    resizeBufferKeepData(size, bufferFlags);
  else if (f == Buffer::NEW_BUFFER)
    newBuffer(size, bufferFlags);
  else
    throw std::runtime_error(
        "Buffer::realloc - invalid buffer reallocation flags.");
}

void BufferImpl::resizeBuffer(GLsizeiptr size, GLbitfield flags)
{
  bufferData(size, nullptr, flags);
}

void BufferImpl::resizeBufferKeepData(GLsizeiptr size, GLbitfield flags)
{
  auto newBuffer = new Buffer(size, nullptr, flags);
  assert(newBuffer != nullptr);
  newBuffer->copy(*buffer);
  auto swapId        = buffer->getId();
  buffer->getId()    = newBuffer->getId();
  newBuffer->getId() = swapId;
  delete newBuffer;
  updateVertexArrays();
}

void BufferImpl::resizeBufferKeepDataKeepId(GLsizeiptr size, GLbitfield flags)
{
  Buffer *temp = new Buffer(size, nullptr, flags);
  assert(temp != nullptr);
  temp->copy(*buffer);
  bufferData(size, nullptr, flags);
  buffer->copy(*temp);
  delete temp;
}

void BufferImpl::newBuffer(GLsizeiptr size, GLbitfield flags)
{
  buffer->getContext().glDeleteBuffers(1, &buffer->getId());
  buffer->alloc(size, nullptr, flags);
  updateVertexArrays();
}
