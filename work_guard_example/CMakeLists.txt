project(work_guard_example)
set(target work_guard_example)

file(GLOB src "*.h" "*.cpp")
add_executable(       ${target} ${src})
target_link_libraries(${target} ${CMAKE_THREAD_LIBS_INIT})
