#pragma once

#include<geGL/OpenGLObject.h>
#include<iostream>
#include<vector>
#include<set>
#include<memory>
#include<cassert>

class ge::gl::Shader:public OpenGLObject{
  friend class Program;
  public:
  using Source  = std::string;
  using Sources = std::vector<Source>;
  GEGL_EXPORT Shader();
  GEGL_EXPORT Shader(GLenum type,Sources const& sources = {});
  GEGL_EXPORT Shader(FunctionTablePointer const&table);
  GEGL_EXPORT Shader(
      FunctionTablePointer const&table       ,
      GLenum               const&type        ,
      Sources              const&sources = {});
  GEGL_EXPORT virtual ~Shader();
  GEGL_EXPORT void        create(GLenum type);
  GEGL_EXPORT void        setSource(Sources const& sources = {});
  GEGL_EXPORT void        compile  (Sources const& sources = {});
  GEGL_EXPORT GLboolean   isShader        ()const;
  GEGL_EXPORT GLenum      getType         ()const;
  GEGL_EXPORT GLboolean   getDeleteStatus ()const;
  GEGL_EXPORT GLboolean   getCompileStatus()const;
  GEGL_EXPORT GLuint      getInfoLogLength()const;
  GEGL_EXPORT GLuint      getSourceLength ()const;
  GEGL_EXPORT std::string getInfoLog      ()const;
  GEGL_EXPORT Source      getSource       ()const;
  GEGL_EXPORT static std::string define(std::string const&name);
  GEGL_EXPORT static std::string define(std::string const&name,uint32_t value);
  GEGL_EXPORT static std::string define(std::string const&name,uint32_t value0,uint32_t value1);
  GEGL_EXPORT static std::string define(std::string const&name,uint32_t value0,uint32_t value1,uint32_t value2);
  GEGL_EXPORT static std::string define(std::string const&name,uint32_t value0,uint32_t value1,uint32_t value2,uint32_t value3);
  GEGL_EXPORT static std::string define(std::string const&name,uint32_t vectorSize,uint32_t const*values);
  GEGL_EXPORT static std::string define(std::string const&name,int32_t value);
  GEGL_EXPORT static std::string define(std::string const&name,int32_t value0,int32_t value1);
  GEGL_EXPORT static std::string define(std::string const&name,int32_t value0,int32_t value1,int32_t value2);
  GEGL_EXPORT static std::string define(std::string const&name,int32_t value0,int32_t value1,int32_t value2,int32_t value3);
  GEGL_EXPORT static std::string define(std::string const&name,uint32_t vectorSize,int32_t const*values);
  GEGL_EXPORT static std::string define(std::string const&name,float value);
  GEGL_EXPORT static std::string define(std::string const&name,float value0,float value1);
  GEGL_EXPORT static std::string define(std::string const&name,float value0,float value1,float value2);
  GEGL_EXPORT static std::string define(std::string const&name,float value0,float value1,float value2,float value3);
  GEGL_EXPORT static std::string define(std::string const&name,uint32_t vectorSize,float const*values);
  GEGL_EXPORT static std::string define(std::string const&name,std::string const&value);
  template<typename...ARGS>
    Shader(GLenum type,ARGS...args);
  template<typename...ARGS>
    Shader(
        FunctionTablePointer const&table  ,
        GLenum               const&type   ,
        ARGS...                    sources);
  template<typename...ARGS>
    void        setSource(ARGS const&... sources);
  template<typename...ARGS>
    void        compile  (ARGS const&... sources);
  protected:
  GLint _getParam(GLenum pname)const;
  std::set<Program*>_programs;
};

template<typename...ARGS>
ge::gl::Shader::Shader(GLenum type,ARGS...args):
  Shader(type,Sources({args...}))
{
}

template<typename...ARGS>
ge::gl::Shader::Shader(
    FunctionTablePointer const&table  ,
    GLenum                       const&type   ,
    ARGS...                            sources):
  Shader(table,type,Sources({sources...}))
{
}

template<typename...ARGS>
void ge::gl::Shader::setSource(ARGS const&... sources){
  assert(this!=nullptr);
  this->setSource(Sources({sources...}));
}

template<typename...ARGS>
void ge::gl::Shader::compile(ARGS const&... sources){
  assert(this!=nullptr);
  this->compile(Sources({sources...}));
}

