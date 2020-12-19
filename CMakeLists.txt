project(senegal C)
cmake_minimum_required(VERSION 3.17)
set(CMAKE_C_STANDARD 99)

file(GLOB src "*/*.h" "*/*.c")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(senegal ${src} libs/includes/ssocketlib.h libs/ssocketlib.c libs/includes/sfilelib.h libs/sfilelib.c libs/includes/scurseslib.h libs/scurseslib.c)

if (WIN32)
	set(SENEGAL_EXEC senegal.exe)
	target_link_libraries(senegal ws2_32 ${CURSES_LIBRARIES})
else()
	set(SENEGAL_EXEC senegal)
	target_link_libraries(senegal m ${CURSES_LIBRARIES})
endif()

add_custom_command(TARGET senegal
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy ${SENEGAL_EXEC} ${CMAKE_SOURCE_DIR})

add_custom_command(TARGET senegal
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy ${SENEGAL_EXEC} ${CMAKE_SOURCE_DIR}/test)
