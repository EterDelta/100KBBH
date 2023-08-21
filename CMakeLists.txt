cmake_minimum_required(VERSION 3.10)

project(100KBBH VERSION 1.0.2 LANGUAGES C CXX)

# autogenerate .gitignore: scivision.dev/cmake-auto-gitignore-build-dir
if(NOT PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
	file(GENERATE OUTPUT .gitignore CONTENT "*")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

math(EXPR MAJOR_INDEX "${PROJECT_VERSION_MAJOR} + 52")
math(EXPR MINOR_INDEX "${PROJECT_VERSION_MINOR} + 52")
math(EXPR PATCH_INDEX "${PROJECT_VERSION_PATCH} + 52")
set(FG_FRAG_IN resources/assets/shader/foreground.frag.in)
set(FG_FRAG_OUT "${CMAKE_CURRENT_BINARY_DIR}/foreground.frag")
configure_file(${FG_FRAG_IN} ${FG_FRAG_OUT})

set(RESOURCES_C "${CMAKE_CURRENT_BINARY_DIR}/resources.c")
set(RESOURCES
	resources/assets/model/bullet.obj
	resources/assets/model/bullet_source.obj
	resources/assets/model/player.obj
	resources/assets/model/quad.obj
	resources/assets/shader/background.frag
	${FG_FRAG_OUT}
	resources/assets/shader/main.vert
	resources/assets/shader/object.frag
	resources/assets/texture/font_atlas.bmp)

foreach(resource_file ${RESOURCES})
	get_filename_component(filename ${resource_file} NAME)
	string(REPLACE "." "_" filename ${filename})
	if(resource_file MATCHES "\\.vert$|\\.frag$|\\.obj$")
		file(READ ${resource_file} data)
		string(REPLACE "\n" "\\n" data "${data}")
		set(c_result "${c_result}const char ${filename}[] = \"${data}\";\n")
	else()
		file(READ ${resource_file} data HEX)
		string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," data ${data})
		set(c_result "${c_result}const unsigned char ${filename}[] = {${data}};\n")
	endif()
endforeach()
file(WRITE ${RESOURCES_C} "${c_result}")

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
	src/Main.cpp
	${RESOURCES_C})

find_package(OpenGL REQUIRED)

add_executable(100KBBH WIN32 ${SOURCE})
target_link_options(100KBBH PRIVATE /INCREMENTAL:NO; /MANIFEST:NO)
target_link_libraries(100KBBH PRIVATE OpenGL::GL gdi32)
target_compile_options(100KBBH PRIVATE /MD /nologo /showIncludes /utf-8 /W2 /EHsc /permissive- /Gw)

target_include_directories(100KBBH PRIVATE ${GLAD_DIR}/include include)
