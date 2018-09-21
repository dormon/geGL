#include<geGL/VertexArray.h>
#include<geGL/VertexArrayImpl.h>
#include<geGL/Buffer.h>
#include<geGL/OpenGLUtil.h>
#include<geGL/BufferImpl.h>
//#include<GPUEngine/geCore/ErrorPrinter/ErrorPrinter.h>
#include<sstream>
#include<cassert>

using namespace ge::gl;

/**
 * @brief Creates empty vertex array object
 */
ge::gl::VertexArray::VertexArray ():VertexArray(nullptr){}

VertexArray::VertexArray (
    FunctionTablePointer const&table):OpenGLObject(table){
  assert(this!=nullptr);
  getContext().glCreateVertexArrays(1,&getId());
  impl = new VertexArrayImpl();
}

/**
 * @brief Destroyes vertex array object
 */
VertexArray::~VertexArray(){
  assert(this!=nullptr);
  getContext().glDeleteVertexArrays(1,&getId());
  for(auto const&x:impl->buffers)
    if(x)x->impl->vertexArrays.erase(this);
  if(impl->elementBuffer)impl->elementBuffer->impl->vertexArrays.erase(this);
  delete impl;
}

/**
* @brief Adds vertex attrib into vertex array object
*
* @param buffer        a buffer where a attrib is stored
* @param index         index of attrib layout(location=index)
* @param nofComponents number of components of attrib vec3 = 3
* @param type          type of attrib vec3 = float, ivec2 = int
* @param stride        distance between attribs
* @param offset        offset to the first attrib
* @param normalized    should the attrib be normalized?
* @param divisor       rate of incrementation of attrib per instance, 0 = per VS invocation
* @param apt           NONE - getContext().glVertexAttribPointer, I - getContext().glVertexAttribIPointer, L - getContext().glVertexAttribLPointer
*/
void VertexArray::addAttrib(
  Buffer*                buffer,
  GLuint                 index,
  GLint                  nofComponents,
  GLenum                 type,
  GLsizei                stride,
  GLintptr               offset,
  GLboolean              normalized,
  GLuint                 divisor,
  enum AttribPointerType apt) {
  assert(this != nullptr);
  if (buffer == nullptr) {
    throw std::invalid_argument("geGL: VertexArray::addAttrib - buffer is nullptr");
    return;
  }
  //std::cout<<this<<"->addAttrib("<<buffer<<","<<index<<","<<nofComponents<<","<<type<<","<<stride<<","<<offset<<","<<normalized<<","<<divisor<<","<<apt<<")"<<std::endl;
  if (stride == 0)
    stride = ge::gl::getTypeSize(type)*nofComponents;
  getContext().glVertexArrayAttribBinding(getId(), index, index);
  getContext().glEnableVertexArrayAttrib(getId(), index);

  if (apt == VertexArray::AttribPointerType::NONE)
    getContext().glVertexArrayAttribFormat(getId(), index, nofComponents, type, normalized, 0);
  else if (apt == VertexArray::AttribPointerType::I)
    getContext().glVertexArrayAttribIFormat(getId(), index, nofComponents, type, 0);
  else if (apt == VertexArray::AttribPointerType::L)
    getContext().glVertexArrayAttribLFormat(getId(), index, nofComponents, type, 0);

  getContext().glVertexArrayVertexBuffer(getId(), index, buffer->getId(), offset, stride);
  getContext().glVertexArrayBindingDivisor(getId(), index, divisor);
  if (index >= impl->buffers.size())impl->buffers.resize(index + 1, nullptr);
  if (impl->buffers.at(index)) {
    size_t nofBufferUsages = _getNofBufferUsages(impl->buffers.at(index));
    if (nofBufferUsages == 1)
      impl->buffers[index]->impl->vertexArrays.erase(this);
  }
  impl->buffers[index] = buffer;
  buffer->impl->vertexArrays.insert(this);
}

/**
 * @brief Adds vertex attrib into vertex array object
 *
 * @param buffer        a buffer where a attrib is stored
 * @param index         index of attrib layout(location=index)
 * @param nofComponents number of components of attrib vec3 = 3
 * @param type          type of attrib vec3 = float, ivec2 = int
 * @param stride        distance between attribs 
 * @param offset        offset to the first attrib
 * @param normalized    should the attrib be normalized?
 * @param divisor       rate of incrementation of attrib per instance, 0 = per VS invocation
 * @param apt           NONE - getContext().glVertexAttribPointer, I - getContext().glVertexAttribIPointer, L - getContext().glVertexAttribLPointer
 */
void VertexArray::addAttrib(
    std::shared_ptr<Buffer>const&buffer           ,
    GLuint                       index            ,
    GLint                        nofComponents    ,
    GLenum                       type             ,
    GLsizei                      stride           ,
    GLintptr                     offset           ,
    GLboolean                    normalized       ,  
    GLuint                       divisor          ,
    enum AttribPointerType       apt              ){
  addAttrib(&*buffer, index, nofComponents, type, stride, offset, normalized, divisor, apt);
}

void VertexArray::addElementBuffer(
  Buffer*buffer) {
  assert(this != nullptr);
  if (impl->elementBuffer) {
    size_t nofBufferUsages = _getNofBufferUsages(impl->elementBuffer);
    if (nofBufferUsages == 1)
      impl->elementBuffer->impl->vertexArrays.erase(this);
  }
  impl->elementBuffer = buffer;
  getContext().glVertexArrayElementBuffer(getId(), buffer->getId());
  buffer->impl->vertexArrays.insert(this);
}

void VertexArray::addElementBuffer(
    std::shared_ptr<Buffer>const&buffer){
  addElementBuffer(&*buffer);
}

void VertexArray::bind()const{
  assert(this!=nullptr);
  //std::cout<<this<<"->bind()"<<std::endl;
  getContext().glBindVertexArray(getId());
}

void VertexArray::unbind()const{
  assert(this!=nullptr);
  //std::cout<<this<<"->unbind()"<<std::endl;
  getContext().glBindVertexArray(0);
}

GLint VertexArray::_getAttrib(GLuint index,GLenum pname)const{
  assert(this!=nullptr);
  GLint param;
  getContext().glGetVertexArrayIndexediv(getId(),index,pname,&param);
  return param;
}

GLuint    VertexArray::getAttribBufferBinding (GLuint index)const{
  assert(this!=nullptr);
  return _getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING);
}

GLboolean VertexArray::isAttribEnabled        (GLuint index)const{
  assert(this!=nullptr);
  return (GLboolean)_getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_ENABLED);
}

GLint     VertexArray::getAttribSize          (GLuint index)const{
  assert(this!=nullptr);
  return _getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_SIZE);
}

GLsizei   VertexArray::getAttribStride        (GLuint index)const{
  assert(this!=nullptr);
  return _getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_STRIDE);
}

GLenum    VertexArray::getAttribType          (GLuint index)const{
  assert(this!=nullptr);
//return _getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_TYPE);
//AMD bug in 15.9 on Linux getContext().glGetVertexArrayIndexediv return type's number instead of type
  GLuint oldId;
  getContext().glGetIntegerv(GL_VERTEX_ARRAY_BINDING,(GLint*)&oldId);
  getContext().glBindVertexArray(getId());
  GLint data;
  getContext().glGetVertexAttribiv(index,GL_VERTEX_ATTRIB_ARRAY_TYPE,&data);
  getContext().glBindVertexArray(oldId);
  return data;

}

GLboolean VertexArray::isAttribNormalized    (GLuint index)const{
  assert(this!=nullptr);
  return (GLboolean)_getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_NORMALIZED);
}

GLboolean VertexArray::isAttribInteger       (GLuint index)const{
  assert(this!=nullptr);
  return (GLboolean)_getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_INTEGER);
}

GLboolean VertexArray::isAttribLong          (GLuint index)const{
  assert(this!=nullptr);
  return (GLboolean)_getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_LONG);
}

GLuint    VertexArray::getAttribDivisor       (GLuint index)const{
  assert(this!=nullptr);
  return _getAttrib(index,GL_VERTEX_ATTRIB_ARRAY_DIVISOR);
}

GLuint    VertexArray::getAttribBinding       (GLuint index)const{
  assert(this!=nullptr);
  return _getAttrib(index,GL_VERTEX_ATTRIB_BINDING);
}

GLuint    VertexArray::getAttribRelativeOffset(GLuint index)const{
  assert(this!=nullptr);
  return _getAttrib(index,GL_VERTEX_ATTRIB_RELATIVE_OFFSET);
}

GLuint    VertexArray::getElementBuffer()const{
  assert(this!=nullptr);
  GLint id;
  getContext().glGetVertexArrayiv(getId(),GL_ELEMENT_ARRAY_BUFFER_BINDING,&id);
  return id;
}

std::string VertexArray::getInfo()const{
  assert(this!=nullptr);
  std::stringstream ss;
  GLint maxVertexAttribs;
  getContext().glGetIntegerv(GL_MAX_VERTEX_ATTRIBS,&maxVertexAttribs);
  ss<<"vao: "<<getId()<<std::endl;
  ss<<"GL_MAX_VERTEX_ATTRIBS: "<<maxVertexAttribs<<std::endl;
  for(GLint a=0;a<maxVertexAttribs;++a){
    if(isAttribEnabled(a)==GL_FALSE)continue;
    ss<<"attrib: "<<a<<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_ENABLED:        "<<ge::gl::translateBoolean(
        /*                                         */isAttribEnabled        (a))<<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING: "<<getAttribBufferBinding (a) <<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_SIZE:           "<<getAttribSize          (a) <<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_STRIDE:         "<<getAttribStride        (a) <<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_TYPE:           "<<ge::gl::translateAttribType(
        /*                                         */getAttribType          (a))<<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_NORMALIZED:     "<<ge::gl::translateBoolean(
        /*                                         */isAttribNormalized     (a))<<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_INTEGER:        "<<ge::gl::translateBoolean(
        /*                                         */isAttribInteger        (a))<<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_LONG:           "<<ge::gl::translateBoolean(
        /*                                         */isAttribLong           (a))<<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_ARRAY_DIVISOR:        "<<getAttribDivisor       (a) <<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_BINDING:              "<<getAttribBinding       (a) <<std::endl;
    ss<<"  GL_VERTEX_ATTRIB_RELATIVE_OFFSET:      "<<getAttribRelativeOffset(a) <<std::endl;
  }
  return ss.str();
}

Buffer*VertexArray::getElement()const{
  assert(this!=nullptr);
  return impl->elementBuffer;
}

Buffer*VertexArray::getBuffer(GLuint index)const{
  assert(this!=nullptr);
  assert(index<impl->buffers.size());
  return impl->buffers.at(index);
}

size_t VertexArray::getNofBuffers()const{
  assert(this!=nullptr);
  return impl->buffers.size();
}


size_t VertexArray::_getNofBufferUsages(Buffer const*buffer)const{
  assert(this!=nullptr);
  size_t counter = size_t(impl->elementBuffer == buffer);
  for(auto const&x:impl->buffers)
    if(x==buffer)++counter;
  return counter;
}

//OpenGL 3.3
//glBindBuffer
//glBindVertexArray
//glDeleteVertexArrays
//glEnableVertexAttribArray
//glGenVertexArrays   
//glGetIntegerv
//glGetVertexAttribiv
//glVertexAttribPointer 
//glVertexAttribIPointer

//OpenGL 4.2
//glVertexAttribDivisor    
//glVertexAttribLPointer

//
//OpenGL 4.5
//glCreateVertexArrays
//glEnableVertexArrayAttrib  
//glGetVertexArrayIndexediv
//glGetVertexArrayiv
//glVertexArrayAttribBinding 
//glVertexArrayAttribFormat  
//glVertexArrayAttribIFormat 
//glVertexArrayAttribLFormat 
//glVertexArrayBindingDivisor
//glVertexArrayElementBuffer
//glVertexArrayVertexBuffer

