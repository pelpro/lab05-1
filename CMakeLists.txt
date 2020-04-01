cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lab04)

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

