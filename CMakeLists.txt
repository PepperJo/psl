cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE PSL_SRC "./src/*.cpp")

project (psl)
add_library(psl SHARED ${PSL_SRC})
target_link_libraries(psl rt)
target_include_directories(psl PUBLIC include)
target_compile_options(psl PUBLIC -std=c++11)
target_compile_options(psl PUBLIC -Wall -Werror)
set_target_properties(psl PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

