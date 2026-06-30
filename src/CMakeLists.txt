add_executable(ot-editor
    main.cpp
    primitive.cpp
    model.cpp
    view.cpp
    renderer.cpp
    controller.cpp
    ui_handlers.cpp
)

if (MSVC)
    target_compile_options(ot-editor PRIVATE /W4)
else()
    target_compile_options(ot-editor PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Installation

install(TARGETS ot-editor RUNTIME DESTINATION bin)