project(timer1)
set(target timer1)

file(GLOB src "*.h" "*.cpp")
add_executable(       ${target} ${src})
target_link_libraries(${target} ${CMAKE_THREAD_LIBS_INIT})
