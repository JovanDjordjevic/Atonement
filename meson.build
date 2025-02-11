project('dagger', 'c', 'cpp', default_options : ['cpp_std=c++17' ])
add_global_link_arguments([ '-lstdc++fs' ], language: 'cpp')

deps = [
    dependency('glfw3'),
    dependency('fmt')
]

if (host_machine.system() == 'linux')
    add_global_link_arguments([ '-lstdc++fs' ], language: 'cpp')

    deps += [
        dependency('tbb'),
        meson.get_compiler('c').find_library('dl')
    ]
endif

includes = [
    include_directories('source/dagger'),
    include_directories('libs/sparse-map/include'),
    include_directories('libs/entt/single_include'),
    include_directories('libs/glm/include'),
    include_directories('libs/glad/include'),
    include_directories('libs/json/include'),
    include_directories('libs/stb/include'),
    include_directories('libs/spdlog/include'),
    include_directories('libs/imgui/include'),
    include_directories('libs/imgui/include/imgui'),
    include_directories('libs/imgui/include/imgui/backends'),
    include_directories('libs/spdlog/include'),
    include_directories('libs/simpleini')
]

sources = [
    'source/dagger/core/game/transforms.cpp',
    'source/dagger/core/graphics/animation.cpp',
    'source/dagger/core/graphics/animations.cpp',
    'source/dagger/core/graphics/gui.cpp',
    'source/dagger/core/graphics/shader.cpp',
    'source/dagger/core/graphics/shaders.cpp',
    'source/dagger/core/graphics/sprite_render.cpp',
    'source/dagger/core/graphics/sprite.cpp',
    'source/dagger/core/graphics/textures.cpp',
    'source/dagger/core/graphics/text.cpp',
    'source/dagger/core/graphics/window.cpp',
    'source/dagger/core/graphics/tool_render.cpp',
    'source/dagger/core/input/inputs.cpp',
    'source/dagger/core/audio_linux.cpp',
    'source/dagger/core/engine.cpp',
    'source/dagger/core/game.cpp',
    'source/dagger/gameplay/editor/editor_defs.cpp',
    'source/dagger/gameplay/editor/editor_main.cpp',
    'source/dagger/gameplay/common/aiming_system.cpp',
    'source/dagger/gameplay/common/camera_focus.cpp',
    'source/dagger/gameplay/common/jiggle.cpp',
    'source/dagger/gameplay/common/particles.cpp',
    'source/dagger/gameplay/common/simple_collisions.cpp',
    'source/dagger/gameplay/atonement/atonement_controller.cpp',
    'source/dagger/gameplay/atonement/atonement_main.cpp',
    'source/dagger/gameplay/atonement/char_controller_fsm.cpp',
    'source/dagger/gameplay/atonement/systems/atonement_pause_menu.cpp',
    'source/dagger/gameplay/atonement/systems/atonement_pause_system.cpp',
    'source/dagger/gameplay/atonement/systems/atonement_start_menu.cpp',
    'source/dagger/gameplay/atonement/systems/atonement_end_screen.cpp',
    'source/dagger/gameplay/atonement/systems/character_collisions.cpp',
    'source/dagger/gameplay/common/cooldown_manager.cpp',
    'source/dagger/gameplay/atonement/systems/atonement_pause_system.cpp',
    'source/dagger/gameplay/atonement/systems/checkpoint_system.cpp',
    'source/dagger/gameplay/atonement/systems/collision_handler_system.cpp',
    'source/dagger/gameplay/atonement/systems/groundedness_detection_system.cpp',
    'source/dagger/gameplay/atonement/systems/interaction_system.cpp',
    'source/dagger/gameplay/atonement/systems/parallax.cpp',

    'source/dagger/tools/console.cpp',
    'source/dagger/tools/diagnostics.cpp',
    'source/dagger/tools/plotvar.cpp',
    'source/dagger/tools/toolmenu.cpp',
    'source/dagger/main.cpp',
    'libs/glad/include/glad/glad.c',
    'libs/imgui/include/imgui/imgui.cpp',
    'libs/imgui/include/imgui/imgui_widgets.cpp',
    'libs/imgui/include/imgui/imgui_draw.cpp',
    'libs/imgui/include/imgui/backends/imgui_impl_glfw.cpp',
    'libs/imgui/include/imgui/backends/imgui_impl_opengl3.cpp'
]

executable('dagger', sources, dependencies : deps, include_directories : includes, cpp_args : '-DIMGUI_IMPL_OPENGL_LOADER_GLAD')