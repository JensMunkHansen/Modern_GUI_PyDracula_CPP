cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

string(
    APPEND _opts
    "$<IF:$<CXX_COMPILER_ID:MSVC>,"
        "/W4;$<$<CONFIG:RELEASE>:/O2>,"
        "-Wall;-Wextra;-Werror;"
            "$<$<CONFIG:RELEASE>:-O3>"
            "$<$<CXX_COMPILER_ID:Clang>:-stdlib=libc++>"
    ">"
)

add_compile_options("${_opts}")

project(Dracula6)

set(USE_QT6 0)
option(Dracula_USE_QT6 "Use Qt6 for GUI" ON)
if (Dracula_USE_QT6)
  set(USE_QT6 1)
endif()

if (USE_QT6)
  find_package(Qt6 QUIET COMPONENTS Core Gui Widgets OpenGL)
else()
  find_package(Qt5 QUIET COMPONENTS Core Gui Widgets OpenGL)
endif()

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (0)
# TEST BEGIN
function(assign_source_group)
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endfunction(assign_source_group)

function(target_link_libraries _target)
    set(_mode "PUBLIC")
    foreach(_arg IN LISTS ARGN)
        if (_arg MATCHES "INTERFACE|PUBLIC|PRIVATE|LINK_PRIVATE|LINK_PUBLIC|LINK_INTERFACE_LIBRARIES")
            set(_mode "${_arg}")
        else()
            if (NOT _arg MATCHES "debug|optimized|general")
                set_property(GLOBAL APPEND PROPERTY GlobalTargetDepends${_target} ${_arg})
            endif()
        endif()
    endforeach()
    _target_link_libraries(${_target} ${ARGN})
endfunction()

function(get_link_dependencies _target _listvar)
    set(_worklist ${${_listvar}})
    if (TARGET ${_target})
        list(APPEND _worklist ${_target})
        get_property(_dependencies GLOBAL PROPERTY GlobalTargetDepends${_target})
        foreach(_dependency IN LISTS _dependencies)
            if (NOT _dependency IN_LIST _worklist)
                get_link_dependencies(${_dependency} _worklist)
            endif()
        endforeach()
        set(${_listvar} "${_worklist}" PARENT_SCOPE)
    endif()
endfunction()
# TEST END
endif()

if (NOT "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

set(UIs app.ui)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

if (USE_QT6)
  qt6_wrap_ui(UI_Srcs ${UIs})
  qt6_add_resources(QRC resources.qrc)
else()
  qt5_wrap_ui(UI_Srcs ${UIs})
  qt5_add_resources(QRC resources.qrc)
endif()


set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/qt5app.rc")

set(Srcs
  main.cpp
  app.cpp
)

if (USE_QT6)
  qt_add_executable(${PROJECT_NAME} ${Srcs} ${UI_Srcs} ${QRC} ${APP_ICON_RESOURCE_WINDOWS})
else()
  add_executable(${PROJECT_NAME} ${Srcs} ${UI_Srcs} ${QRC} ${APP_ICON_RESOURCE_WINDOWS})
endif()

target_compile_features(${PROJECT_NAME} PUBLIC cxx_lambda_init_captures)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE true)
endif()

add_subdirectory(modules)
add_subdirectory(widgets)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if (USE_QT6)
  target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::OpenGL)
else()
  target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpenGL)
endif()


if (0)

# TEST BEGIN
get_target_property(my_sources ${PROJECT_NAME} SOURCES)
message(${my_sources})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "sources\\inc" FILES ${my_sources})

# TEST
get_link_dependencies(${PROJECT_NAME} _deps)
foreach(_dep IN LISTS _deps)
    get_target_property(_srcs ${_dep} SOURCES)
    get_target_property(_src_dir ${_dep} SOURCE_DIR)
    foreach(_src IN LISTS _srcs)
        message("${_src_dir}/${_src}")
    endforeach()
endforeach()
endif()
# TEST END
