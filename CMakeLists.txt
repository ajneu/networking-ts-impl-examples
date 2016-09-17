cmake_minimum_required(VERSION 2.8)

# c++14
if (NOT    CMAKE_VERSION VERSION_LESS 3.1)
  set(CMAKE_CXX_STANDARD   14)
  set(CMAKE_CXX_EXTENSIONS OFF)
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()


project(go)



find_package (Git REQUIRED)

execute_process (
  COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})



set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package (Threads) # found lib is in ${CMAKE_THREAD_LIBS_INIT}


include_directories(extern/networking-ts-impl/include)

add_subdirectory(tutorial)
add_subdirectory(work_guard_example)
