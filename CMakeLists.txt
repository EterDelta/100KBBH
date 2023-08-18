cmake_minimum_required(VERSION 3.10)

project(100KBBH VERSION 1.0.1 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

find_package(Python3 REQUIRED)
set(RESOURCES_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/gen_resources.py")

set(RESOURCES
    "resources/assets/model/bullet.obj"
    "resources/assets/model/bullet_source.obj"
    "resources/assets/model/player.obj"
    "resources/assets/model/quad.obj"
    "resources/assets/shader/background.frag"
    "resources/assets/shader/foreground.frag"
    "resources/assets/shader/main.vert"
    "resources/assets/shader/object.frag"
    "resources/assets/texture/font_atlas.bmp"
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources.c
    COMMAND ${Python3_EXECUTABLE} gen_resources.py ${CMAKE_CURRENT_BINARY_DIR}/resources.c ${RESOURCES}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/gen_resources.py ${RESOURCES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

set(GLAD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad")

add_executable(100KBBH WIN32
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
    src/Main.cpp
    resources.c
)

target_include_directories(100KBBH PRIVATE
    ${GLAD_DIR}/include
    include
)

find_package(OpenGL REQUIRED)

target_link_libraries(100KBBH PRIVATE
    OpenGL::GL
    gdi32
)
