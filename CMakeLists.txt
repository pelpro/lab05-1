cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_TESTS "Build tests" OFF)

project(print)

add_library(print STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/print.cpp)

target_include_directories(print PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

if(BUILD_TESTS)
  add_subdirectory(banking)
  include_directories(banking)

  enable_testing()
  add_subdirectory(third-party/gtest)
  file(GLOB ${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
  add_executable(check ${${PROJECT_NAME}_TEST_SOURCES})
  target_link_libraries(check ${PROJECT_NAME} gtest_main gmock_main banking)
  add_test(NAME check COMMAND check)
endif()

if(BUILD_EXAMPLES)
  file(GLOB EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp")
  foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE})
    target_link_libraries(${EXAMPLE_NAME} print)
    install(TARGETS ${EXAMPLE_NAME}
      RUNTIME DESTINATION bin
    )
  endforeach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
endif()

#################
# К сожалению, проэкт следует компилировать библиотеки в
# определённой последовательности
# Эта часть её задаёт

add_subdirectory(${CMAKE_SOURCE_DIR}/formatter_lib 
		${CMAKE_SOURCE_DIR}/formatter_lib)

add_subdirectory(${CMAKE_SOURCE_DIR}/formatter_ex_lib 
                ${CMAKE_SOURCE_DIR}/formatter_ex_lib)

add_subdirectory(${CMAKE_SOURCE_DIR}/solver_lib
                ${CMAKE_SOURCE_DIR}/solver_lib)


#################
# Эта часть компилирует все прилажения
# Нам не важно в каком порядке
file(GLOB EXE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*application")
foreach(EXE_NAME ${EXE_SOURCES})
	add_subdirectory(${EXE_NAME} ${EXE_NAME})
endforeach(EXE_NAME ${EXE_SOURCES})

install(TARGETS print
    EXPORT print-config
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)
install(EXPORT print-config DESTINATION cmake)

