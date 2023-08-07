project('100KBBH', 'c', 'cpp',
    version : '1.0.0',
    default_options : ['c_std=c11', 'cpp_std=c++17'])

resources = files(
    'resources/assets/model/bullet.obj',
    'resources/assets/model/bullet_source.obj',
    'resources/assets/model/player.obj',
    'resources/assets/model/quad.obj',
    'resources/assets/shader/background.frag',
    'resources/assets/shader/foreground.frag',
    'resources/assets/shader/main.vert',
    'resources/assets/shader/object.frag',
    'resources/assets/texture/font_atlas.bmp'
)

python = find_program('python')
resources_script = meson.current_source_dir() / 'gen_resources.py'

generated_resources = custom_target(
    input : resources,
    output : 'resources.c',
    command : [python, resources_script, '@OUTPUT@', '@INPUT@']
)

glad_dir = 'thirdparty' / 'glad'

sources = [
    glad_dir / 'src' / 'gl.c',
    'src/model/Model.cpp',
    'src/model/Models.cpp',
    'src/object/Bullet.cpp',
    'src/object/BulletSource.cpp',
    'src/object/Object.cpp',
    'src/object/Player.cpp',
    'src/object/wave/WaveHandler.cpp',
    'src/shader/Shader.cpp',
    'src/shader/Shaders.cpp',
    'src/texture/Texture.cpp',
    'src/texture/Textures.cpp',
    'src/util/Util.cpp',
    'src/Game.cpp',
    'src/Main.cpp',
    generated_resources
]

include_dirs = include_directories(
    glad_dir / 'include',
    'include'
)

gl32 = meson.get_compiler('c').find_library('opengl32', required : true)

executable('100KBBH', sources,
    include_directories : include_dirs,
    dependencies : gl32,
    win_subsystem : 'windows',
    build_by_default : true
)