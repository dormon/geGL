cmake_minimum_required(VERSION 3.10.1)

project(geGL)

SET(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(MAJOR_VERSION 1)
set(MINOR_VERSION 0)
set(REVISION_VERSION 0)

include(GenerateExportHeader)

set(LIB_NAME geGL)

set(SOURCES
  src/${LIB_NAME}/Buffer.cpp
  src/${LIB_NAME}/VertexArray.cpp
  src/${LIB_NAME}/Framebuffer.cpp
  src/${LIB_NAME}/Texture.cpp
  src/${LIB_NAME}/Sampler.cpp
  src/${LIB_NAME}/ProgramPipeline.cpp
  src/${LIB_NAME}/Shader.cpp
  src/${LIB_NAME}/Program.cpp
  src/${LIB_NAME}/Renderbuffer.cpp
  src/${LIB_NAME}/AsynchronousQuery.cpp
  src/${LIB_NAME}/DebugMessage.cpp
  src/${LIB_NAME}/OpenGLObject.cpp
  src/${LIB_NAME}/geGL.cpp
  src/${LIB_NAME}/OpenGLContext.cpp
  src/${LIB_NAME}/OpenGL.cpp
  src/${LIB_NAME}/OpenGLUtil.cpp
  src/${LIB_NAME}/StaticCalls.cpp
  src/${LIB_NAME}/GLSLNoise.cpp
  )

set(INCLUDES
  src/${LIB_NAME}/Fwd.h
  src/${LIB_NAME}/Definitions.h
  src/${LIB_NAME}/Buffer.h
  src/${LIB_NAME}/VertexArray.h
  src/${LIB_NAME}/Framebuffer.h
  src/${LIB_NAME}/Texture.h
  src/${LIB_NAME}/Sampler.h
  src/${LIB_NAME}/ProgramPipeline.h
  src/${LIB_NAME}/Shader.h
  src/${LIB_NAME}/Program.h
  src/${LIB_NAME}/ProgramInfo.h
  src/${LIB_NAME}/Renderbuffer.h
  src/${LIB_NAME}/OpenGL.h
  src/${LIB_NAME}/OpenGLUtil.h
  src/${LIB_NAME}/AsynchronousQuery.h
  src/${LIB_NAME}/DebugMessage.h
  src/${LIB_NAME}/OpenGLObject.h
  src/${LIB_NAME}/geGL.h
  src/${LIB_NAME}/ConvertTo.h
  src/${LIB_NAME}/OpenGLCommands.h
  src/${LIB_NAME}/OpenGLFunctionTable.h
  src/${LIB_NAME}/OpenGLContext.h
  src/${LIB_NAME}/OpenGLCapabilities.h
  src/${LIB_NAME}/FunctionLoaderInterface.h
  src/${LIB_NAME}/DefaultLoader.h
  src/${LIB_NAME}/LoaderTableDecorator.h
  src/${LIB_NAME}/DSATableDecorator.h
  src/${LIB_NAME}/TrapTableDecorator.h
  src/${LIB_NAME}/CapabilitiesTableDecorator.h
  src/${LIB_NAME}/StaticCalls.h
  src/${LIB_NAME}/GLSLNoise.h
  src/${LIB_NAME}/Generated/ContextCalls.h
  src/${LIB_NAME}/Generated/ContextDeclarations.h
  src/${LIB_NAME}/Generated/FunctionTableCalls.h
  src/${LIB_NAME}/Generated/LoaderImplementation.h
  src/${LIB_NAME}/Generated/LoaderLoadingCalls.h
  src/${LIB_NAME}/Generated/NumberOfFunctions.h
  src/${LIB_NAME}/Generated/MemberOpenGLFunctions.h
  src/${LIB_NAME}/Generated/MemberOpenGLPFN.h
  src/${LIB_NAME}/Generated/OpenGLConstants.h
  src/${LIB_NAME}/Generated/OpenGLFunctions.h
  src/${LIB_NAME}/Generated/OpenGLPFN.h
  src/${LIB_NAME}/Generated/OpenGLTypes.h
  src/${LIB_NAME}/Generated/TrapCalls.h
  src/${LIB_NAME}/Generated/TrapImplementation.h
  )

add_library(${LIB_NAME} SHARED ${SOURCES} ${INCLUDES})
add_library(${LIB_NAME}::${LIB_NAME} ALIAS ${LIB_NAME})

target_include_directories(${LIB_NAME} PUBLIC $<INSTALL_INTERFACE:src>)
target_include_directories(${LIB_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

set(LIB_NAME_LOWER)
string(TOLOWER ${LIB_NAME} LIB_NAME_LOWER)

generate_export_header(${LIB_NAME} EXPORT_FILE_NAME ${LIB_NAME}/${LIB_NAME_LOWER}_export.h)

set(${LIB_NAME}_VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${REVISION_VERSION})

set_property(TARGET ${LIB_NAME} PROPERTY VERSION ${${LIB_NAME}_VERSION})
set_property(TARGET ${LIB_NAME} PROPERTY SOVERSION 1)
set_property(TARGET ${LIB_NAME} PROPERTY INTERFACE_${LIB_NAME}_MAJOR_VERSION 1)
set_property(TARGET ${LIB_NAME} APPEND PROPERTY COMPATIBLE_INTERFACE_STRING ${LIB_NAME}_MAJOR_VERSION)

install(TARGETS ${LIB_NAME} EXPORT ${LIB_NAME}Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
  )

install(
  FILES
  ${INCLUDES}
  ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME_LOWER}_export.h
  DESTINATION
  include/${LIB_NAME}
  COMPONENT
  Devel
  )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}ConfigVersion.cmake
  VERSION ${${LIB_NAME}_VERSION}
  COMPATIBILITY SameMajorVersion
  )

export(EXPORT ${LIB_NAME}Targets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}Targets.cmake
  NAMESPACE ${LIB_NAME}::
  )

set(ConfigPackageLocation lib/cmake/${LIB_NAME})
install(EXPORT ${LIB_NAME}Targets
  FILE
  ${LIB_NAME}Targets.cmake
  NAMESPACE
  ${LIB_NAME}::
  DESTINATION
  ${ConfigPackageLocation}
  )

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}Config.cmake
  "include($" "{CMAKE_CURRENT_LIST_DIR}/${LIB_NAME}Targets.cmake)"
  )

install(
  FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}Config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}ConfigVersion.cmake
  DESTINATION
  ${ConfigPackageLocation}
  COMPONENT
  Devel
  )

