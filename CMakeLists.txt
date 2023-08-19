cmake_minimum_required(VERSION 3.10)

project(100KBBH VERSION 1.0.1 LANGUAGES C CXX)

# autogenerate .gitignore in build directory: scivision.dev/cmake-auto-gitignore-build-dir
if(NOT PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  file(GENERATE OUTPUT .gitignore CONTENT "*")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

find_package(Python3 REQUIRED)
set(RESOURCES_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/gen_resources.py")
set(RESOURCES_C "${CMAKE_CURRENT_BINARY_DIR}/resources.c")
set(RESOURCES
    "resources/assets/model/bullet.obj"
    "resources/assets/model/bullet_source.obj"
    "resources/assets/model/player.obj"
    "resources/assets/model/quad.obj"
    "resources/assets/shader/background.frag"
    "resources/assets/shader/foreground.frag"
    "resources/assets/shader/main.vert"
    "resources/assets/shader/object.frag"
    "resources/assets/texture/font_atlas.bmp")

add_custom_command(OUTPUT ${RESOURCES_C}
  COMMAND ${Python3_EXECUTABLE} ${RESOURCES_SCRIPT} ${RESOURCES_C} ${RESOURCES}
  DEPENDS ${RESOURCES_SCRIPT} ${RESOURCES}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(GLAD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad")

set(SOURCE
  ${GLAD_DIR}/src/gl.c
  src/model/Model.cpp
  src/model/Models.cpp
  src/object/Bullet.cpp
  src/object/BulletSource.cpp
  src/object/Object.cpp
  src/object/Player.cpp
  src/object/wave/WaveHandler.cpp
  src/shader/Shader.cpp
  src/shader/Shaders.cpp
  src/texture/Texture.cpp
  src/texture/Textures.cpp
  src/util/Util.cpp
  src/Game.cpp
  ${RESOURCES_C})

find_package(OpenGL REQUIRED)

if(WIN32)
  add_executable(100KBBH ${SOURCE} src/MainWin32.cpp)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
  target_link_options(100KBBH PRIVATE /INCREMENTAL:NO; /MANIFEST:NO)
  target_link_libraries(100KBBH PRIVATE OpenGL::GL gdi32)
  target_compile_options(100KBBH PRIVATE /MD /nologo /showIncludes /utf-8 /W2 /EHsc /permissive- /Gw)
else()
  add_executable(100KBBH ${SOURCE} src/MainGLFW.cpp)
  find_package(glfw3 3.3 REQUIRED)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
  target_link_libraries(100KBBH PRIVATE OpenGL::GL glfw dl)
endif()

target_include_directories(100KBBH PRIVATE ${GLAD_DIR}/include include)
