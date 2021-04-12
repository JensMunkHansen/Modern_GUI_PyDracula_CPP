# Controllers
set(HEADERS
  ${CMAKE_CURRENT_LIST_DIR}/ui_functions.hpp
  ${CMAKE_CURRENT_LIST_DIR}/ui_styles.hpp
  ${CMAKE_CURRENT_LIST_DIR}/app_settings.hpp
  ${CMAKE_CURRENT_LIST_DIR}/app_functions.hpp
  )

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
