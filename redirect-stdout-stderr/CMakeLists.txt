cmake_minimum_required(VERSION 3.3)
add_compile_options(-Wall -Werror)
add_executable(redirect redirect.c)
add_executable(slave slave.c)
