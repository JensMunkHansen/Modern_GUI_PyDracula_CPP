# Controllers
set(HEADERS
  ${CMAKE_CURRENT_LIST_DIR}/ui_functions.hpp
  ${CMAKE_CURRENT_LIST_DIR}/ui_styles.hpp
  ${CMAKE_CURRENT_LIST_DIR}/app_settings.hpp
  ${CMAKE_CURRENT_LIST_DIR}/app_functions.hpp
  )


# Not working
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "modules" FILES ${HEADERS})

# Not working
set(_src_root_path "${CMAKE_CURRENT_LIST_DIR}/..")
foreach(_source IN ITEMS ${HEADERS})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${_src_root_path}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

list(APPEND PUBLIC_HEADERS ${HEADERS})
set(PUBLIC_HEADERS ${PUBLIC_HEADERS} PARENT_SCOPE)

target_sources(${PROJECT_NAME}
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/ui_functions.cpp
  ${CMAKE_CURRENT_LIST_DIR}/ui_styles.cpp
  ${CMAKE_CURRENT_LIST_DIR}/app_settings.cpp
  ${CMAKE_CURRENT_LIST_DIR}/app_functions.cpp
  ${HEADERS}
  )
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})


