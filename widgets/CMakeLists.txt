# Controllers
set(HEADERS
  ${CMAKE_CURRENT_LIST_DIR}/custom_grips.hpp
  ${CMAKE_CURRENT_LIST_DIR}/toggle.hpp
  )

list(APPEND PUBLIC_HEADERS ${HEADERS})
set(PUBLIC_HEADERS ${PUBLIC_HEADERS} PARENT_SCOPE)

target_sources(${PROJECT_NAME}
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/custom_grips.cpp
  ${CMAKE_CURRENT_LIST_DIR}/toggle.cpp
  ${HEADERS}
  )
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
