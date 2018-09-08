#pragma once

#include<iostream>
#include<memory>
#include<set>
#include<map>

#include<geGL/Shader.h>
#include<geGL/ProgramInfo.h>

class ge::gl::Program: public OpenGLObject, public std::enable_shared_from_this<Program>{
  public:
    using ShaderPointer  = std::shared_ptr<Shader>;
    using ShaderPointers = std::vector<ShaderPointer>;
	GEGL_EXPORT Program(ShaderPointers const&shaders);
	GEGL_EXPORT Program(
        FunctionTablePointer const&table       ,
        ShaderPointers       const&shaders = {});
	GEGL_EXPORT ~Program();
	GEGL_EXPORT void create       ();
	GEGL_EXPORT void attachShaders(ShaderPointers const&shaders = {});
	GEGL_EXPORT void detachShaders(ShaderPointers const&shaders = {});
	GEGL_EXPORT void link         (ShaderPointers const&shaders = {});
	GEGL_EXPORT GLboolean isProgram()const;
	GEGL_EXPORT void use ()const;
	GEGL_EXPORT void validate()const;
	GEGL_EXPORT GLboolean   getDeleteStatus                     ()const;
	GEGL_EXPORT GLboolean   getLinkStatus                       ()const;
	GEGL_EXPORT GLboolean   getValidateStatus                   ()const;
	GEGL_EXPORT GLuint      getInfoLogLength                    ()const;
	GEGL_EXPORT GLuint      getNofShaders                       ()const;
	GEGL_EXPORT GLuint      getNofActiveAtomicCounterBuffers    ()const;
	GEGL_EXPORT GLuint      getNofActiveAttributes              ()const;
	GEGL_EXPORT GLuint      getActiveAttributeMaxLength         ()const;
	GEGL_EXPORT GLuint      getNofActiveUniforms                ()const;
	GEGL_EXPORT GLuint      getActiveUniformMaxLength           ()const;
	GEGL_EXPORT GLuint      getBinaryLength                     ()const;
	GEGL_EXPORT GLenum      getTransformFeedbackBufferMode      ()const;
	GEGL_EXPORT GLuint      getNofTransfromFeedbackVaryings     ()const;
	GEGL_EXPORT GLuint      getTransformFeedbackVaryingMaxLength()const;
	GEGL_EXPORT GLuint      getNofGeometryVerticesOut           ()const;
	GEGL_EXPORT GLenum      getGeometryInputType                ()const;
	GEGL_EXPORT GLenum      getGeometryOutputType               ()const;
	GEGL_EXPORT std::string getInfoLog                          ()const;
	GEGL_EXPORT void        getComputeWorkGroupSize(GLint*x                                )const;
	GEGL_EXPORT GLint       getUniformLocation     (std::string const&name                 )const;
	GEGL_EXPORT GLint       getAttribLocation      (std::string const&name                 )const;
	GEGL_EXPORT GLint       getInterfaceParam      (GLenum interf,GLenum pname             )const;
	GEGL_EXPORT std::string getResourceName        (GLenum interf,GLuint index             )const;
	GEGL_EXPORT GLint       getResourceParam       (GLenum interf,GLenum pname,GLuint index)const;
	GEGL_EXPORT Program const*set1f         (std::string const&name,float    v0                                                       )const;
	GEGL_EXPORT Program const*set2f         (std::string const&name,float    v0,float    v1                                           )const;
	GEGL_EXPORT Program const*set3f         (std::string const&name,float    v0,float    v1,float    v2                               )const;
	GEGL_EXPORT Program const*set4f         (std::string const&name,float    v0,float    v1,float    v2,float    v3                   )const;
	GEGL_EXPORT Program const*set1i         (std::string const&name,int32_t  v0                                                       )const;
	GEGL_EXPORT Program const*set2i         (std::string const&name,int32_t  v0,int32_t  v1                                           )const;
	GEGL_EXPORT Program const*set3i         (std::string const&name,int32_t  v0,int32_t  v1,int32_t  v2                               )const;
	GEGL_EXPORT Program const*set4i         (std::string const&name,int32_t  v0,int32_t  v1,int32_t  v2,int32_t  v3                   )const;
	GEGL_EXPORT Program const*set1ui        (std::string const&name,uint32_t v0                                                       )const;
	GEGL_EXPORT Program const*set2ui        (std::string const&name,uint32_t v0,uint32_t v1                                           )const;
	GEGL_EXPORT Program const*set3ui        (std::string const&name,uint32_t v0,uint32_t v1,uint32_t v2                               )const;
	GEGL_EXPORT Program const*set4ui        (std::string const&name,uint32_t v0,uint32_t v1,uint32_t v2,uint32_t v3                   )const;
    GEGL_EXPORT Program const*set1fv        (std::string const&name,float    const*v0,GLsizei count = 1                               )const;
    GEGL_EXPORT Program const*set2fv        (std::string const&name,float    const*v0,GLsizei count = 1                               )const;
    GEGL_EXPORT Program const*set3fv        (std::string const&name,float    const*v0,GLsizei count = 1                               )const;
    GEGL_EXPORT Program const*set4fv        (std::string const&name,float    const*v0,GLsizei count = 1                               )const;
    GEGL_EXPORT Program const*set1iv        (std::string const&name,int32_t  const*v0,GLsizei count = 1                               )const;
    GEGL_EXPORT Program const*set2iv        (std::string const&name,int32_t  const*v0,GLsizei count = 1                               )const;
    GEGL_EXPORT Program const*set3iv        (std::string const&name,int32_t  const*v0,GLsizei count = 1                               )const;
    GEGL_EXPORT Program const*set4iv        (std::string const&name,int32_t  const*v0,GLsizei count = 1                               )const;
    GEGL_EXPORT Program const*set1uiv       (std::string const&name,uint32_t const*v0,GLsizei count = 1                               )const;
    GEGL_EXPORT Program const*set2uiv       (std::string const&name,uint32_t const*v0,GLsizei count = 1                               )const;
    GEGL_EXPORT Program const*set3uiv       (std::string const&name,uint32_t const*v0,GLsizei count = 1                               )const;
    GEGL_EXPORT Program const*set4uiv       (std::string const&name,uint32_t const*v0,GLsizei count = 1                               )const;
    GEGL_EXPORT Program const*setMatrix4fv  (std::string const&name,float    const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
    GEGL_EXPORT Program const*setMatrix3fv  (std::string const&name,float    const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
    GEGL_EXPORT Program const*setMatrix2fv  (std::string const&name,float    const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
    GEGL_EXPORT Program const*setMatrix4x3fv(std::string const&name,float    const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
    GEGL_EXPORT Program const*setMatrix4x2fv(std::string const&name,float    const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
    GEGL_EXPORT Program const*setMatrix3x4fv(std::string const&name,float    const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
    GEGL_EXPORT Program const*setMatrix3x2fv(std::string const&name,float    const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
    GEGL_EXPORT Program const*setMatrix2x4fv(std::string const&name,float    const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
    GEGL_EXPORT Program const*setMatrix2x3fv(std::string const&name,float    const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
    GEGL_EXPORT Program const*setMatrix4dv  (std::string const&name,double   const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
    GEGL_EXPORT Program const*setMatrix3dv  (std::string const&name,double   const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
    GEGL_EXPORT Program const*setMatrix2dv  (std::string const&name,double   const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
    GEGL_EXPORT Program const*setMatrix4x3dv(std::string const&name,double   const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
    GEGL_EXPORT Program const*setMatrix4x2dv(std::string const&name,double   const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
    GEGL_EXPORT Program const*setMatrix3x4dv(std::string const&name,double   const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
    GEGL_EXPORT Program const*setMatrix3x2dv(std::string const&name,double   const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
    GEGL_EXPORT Program const*setMatrix2x4dv(std::string const&name,double   const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
    GEGL_EXPORT Program const*setMatrix2x3dv(std::string const&name,double   const*v0,GLsizei count = 1,GLboolean transpose = GL_FALSE)const;
    GEGL_EXPORT void set(std::string const&name,float    v0                                    );
    GEGL_EXPORT void set(std::string const&name,float    v0,float    v1                        );
    GEGL_EXPORT void set(std::string const&name,float    v0,float    v1,float    v2            );
    GEGL_EXPORT void set(std::string const&name,float    v0,float    v1,float    v2,float    v3);
    GEGL_EXPORT void set(std::string const&name,int32_t  v0                                    );
    GEGL_EXPORT void set(std::string const&name,int32_t  v0,int32_t  v1                        );
    GEGL_EXPORT void set(std::string const&name,int32_t  v0,int32_t  v1,int32_t  v2            );
    GEGL_EXPORT void set(std::string const&name,int32_t  v0,int32_t  v1,int32_t  v2,int32_t  v3);
    GEGL_EXPORT void set(std::string const&name,uint32_t v0                                    );
    GEGL_EXPORT void set(std::string const&name,uint32_t v0,uint32_t v1                        );
    GEGL_EXPORT void set(std::string const&name,uint32_t v0,uint32_t v1,uint32_t v2            );
    GEGL_EXPORT void set(std::string const&name,uint32_t v0,uint32_t v1,uint32_t v2,uint32_t v3);
    GEGL_EXPORT void set1v(std::string const&name,float    const*v0,GLsizei count = 1);
    GEGL_EXPORT void set2v(std::string const&name,float    const*v0,GLsizei count = 1);
    GEGL_EXPORT void set3v(std::string const&name,float    const*v0,GLsizei count = 1);
    GEGL_EXPORT void set4v(std::string const&name,float    const*v0,GLsizei count = 1);
    GEGL_EXPORT void set1v(std::string const&name,int32_t  const*v0,GLsizei count = 1);
    GEGL_EXPORT void set2v(std::string const&name,int32_t  const*v0,GLsizei count = 1);
    GEGL_EXPORT void set3v(std::string const&name,int32_t  const*v0,GLsizei count = 1);
    GEGL_EXPORT void set4v(std::string const&name,int32_t  const*v0,GLsizei count = 1);
    GEGL_EXPORT void set1v(std::string const&name,uint32_t const*v0,GLsizei count = 1);
    GEGL_EXPORT void set2v(std::string const&name,uint32_t const*v0,GLsizei count = 1);
    GEGL_EXPORT void set3v(std::string const&name,uint32_t const*v0,GLsizei count = 1);
    GEGL_EXPORT void set4v(std::string const&name,uint32_t const*v0,GLsizei count = 1);
    GEGL_EXPORT Program const*bindBuffer(std::string const&name,std::shared_ptr<Buffer>const&buffer)const;
    GEGL_EXPORT Program const*dispatch(GLuint nofWorkGroupsX = 1,GLuint nofWorkGroupsY = 1,GLuint nofWorkGroupsZ = 1)const;

	GEGL_EXPORT std::shared_ptr<ProgramInfo> const&getInfo()const{return this->_info;}
	GEGL_EXPORT static void setNonexistingUniformWarning(bool enableWarning = true);
	GEGL_EXPORT static bool isNonexistingUniformWarningEnabled();

	GEGL_EXPORT GLuint static const nonExistingBufferBinding;
	GEGL_EXPORT GLuint getBufferBinding(std::string const&name)const;
  public:
    template<typename...ARGS>
      Program(ARGS...shaders);
    template<typename...ARGS>
      Program(
          FunctionTablePointer const&table  ,
          ARGS...                            shaders);
    template<typename...ARGS>
      void attachShaders(ARGS... shaders);
    template<typename...ARGS>
      void detachShaders(ARGS... shaders);
    template<typename...ARGS>
      void link         (ARGS... shaders);
  protected:
    std::set<ShaderPointer>_shaders;
    GLint _getParam(GLenum pname)const;
    std::map<std::string,GLint>_name2Uniform;
    GLint _getUniform(std::string name);
    std::shared_ptr<ProgramInfo> _info;
    void _fillUniformInfo();
    void _fillAttribInfo();
    void _fillBufferInfo();
    void _fillInfo();
    std::string _chopIndexingInPropertyName(std::string name)const;
    friend class Shader;
};

template<typename...ARGS>
ge::gl::Program::Program(ARGS...shaders):Program(ShaderPointers({shaders...})){}
template<typename...ARGS>
ge::gl::Program::Program(
    FunctionTablePointer const&table  ,
    ARGS...                            shaders):Program(table,ShaderPointers({shaders...})){}
template<typename...ARGS>
void ge::gl::Program::attachShaders(ARGS... shaders){
  assert(this!=nullptr);
  this->attachShaders(ShaderPointers({shaders...}));
}
template<typename...ARGS>
void ge::gl::Program::detachShaders(ARGS... shaders){
  assert(this!=nullptr);
  this->detachShaders(ShaderPointers({shaders...}));
}
template<typename...ARGS>
void ge::gl::Program::link(ARGS... shaders){
  assert(this!=nullptr);
  this->link(ShaderPointers({shaders...}));
}
inline void ge::gl::Program::set(std::string const&name,float v0                           ){assert(this!=nullptr);this->set1f(name,v0);}
inline void ge::gl::Program::set(std::string const&name,float v0,float v1                  ){assert(this!=nullptr);this->set2f(name,v0,v1);}
inline void ge::gl::Program::set(std::string const&name,float v0,float v1,float v2         ){assert(this!=nullptr);this->set3f(name,v0,v1,v2);}
inline void ge::gl::Program::set(std::string const&name,float v0,float v1,float v2,float v3){assert(this!=nullptr);this->set4f(name,v0,v1,v2,v3);}
inline void ge::gl::Program::set(std::string const&name,int32_t v0                                 ){assert(this!=nullptr);this->set1i(name,v0);}
inline void ge::gl::Program::set(std::string const&name,int32_t v0,int32_t v1                      ){assert(this!=nullptr);this->set2i(name,v0,v1);}
inline void ge::gl::Program::set(std::string const&name,int32_t v0,int32_t v1,int32_t v2           ){assert(this!=nullptr);this->set3i(name,v0,v1,v2);}
inline void ge::gl::Program::set(std::string const&name,int32_t v0,int32_t v1,int32_t v2,int32_t v3){assert(this!=nullptr);this->set4i(name,v0,v1,v2,v3);}
inline void ge::gl::Program::set(std::string const&name,uint32_t v0                                    ){assert(this!=nullptr);this->set1ui(name,v0);}
inline void ge::gl::Program::set(std::string const&name,uint32_t v0,uint32_t v1                        ){assert(this!=nullptr);this->set2ui(name,v0,v1);}
inline void ge::gl::Program::set(std::string const&name,uint32_t v0,uint32_t v1,uint32_t v2            ){assert(this!=nullptr);this->set3ui(name,v0,v1,v2);}
inline void ge::gl::Program::set(std::string const&name,uint32_t v0,uint32_t v1,uint32_t v2,uint32_t v3){assert(this!=nullptr);this->set4ui(name,v0,v1,v2,v3);}
inline void ge::gl::Program::set1v(std::string const&name,float const*v0,GLsizei count){assert(this!=nullptr);this->set1fv(name,v0,count);}
inline void ge::gl::Program::set2v(std::string const&name,float const*v0,GLsizei count){assert(this!=nullptr);this->set2fv(name,v0,count);}
inline void ge::gl::Program::set3v(std::string const&name,float const*v0,GLsizei count){assert(this!=nullptr);this->set3fv(name,v0,count);}
inline void ge::gl::Program::set4v(std::string const&name,float const*v0,GLsizei count){assert(this!=nullptr);this->set4fv(name,v0,count);}
inline void ge::gl::Program::set1v(std::string const&name,int32_t const*v0,GLsizei count){assert(this!=nullptr);this->set1iv(name,v0,count);}
inline void ge::gl::Program::set2v(std::string const&name,int32_t const*v0,GLsizei count){assert(this!=nullptr);this->set2iv(name,v0,count);}
inline void ge::gl::Program::set3v(std::string const&name,int32_t const*v0,GLsizei count){assert(this!=nullptr);this->set3iv(name,v0,count);}
inline void ge::gl::Program::set4v(std::string const&name,int32_t const*v0,GLsizei count){assert(this!=nullptr);this->set4iv(name,v0,count);}
inline void ge::gl::Program::set1v(std::string const&name,uint32_t const*v0,GLsizei count){assert(this!=nullptr);this->set1uiv(name,v0,count);}
inline void ge::gl::Program::set2v(std::string const&name,uint32_t const*v0,GLsizei count){assert(this!=nullptr);this->set2uiv(name,v0,count);}
inline void ge::gl::Program::set3v(std::string const&name,uint32_t const*v0,GLsizei count){assert(this!=nullptr);this->set3uiv(name,v0,count);}
inline void ge::gl::Program::set4v(std::string const&name,uint32_t const*v0,GLsizei count){assert(this!=nullptr);this->set4uiv(name,v0,count);}
