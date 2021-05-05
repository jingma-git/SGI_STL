cmake_minimum_required(VERSION 3.1)
project(chp3)

# add_executable(main 1auto_ptr.cpp)
add_executable(main 2my_list.cpp)
# add_executable(main 3traits.cpp)
# add_executable(main 4move.cpp)
# add_executable(main 5shared_ptr.cpp)
# set_property(TARGET main PROPERTY CXX_STANDARD 11)
target_compile_features(main PUBLIC cxx_std_11)

# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined")
# add_executable(main memleak_det.cpp)
# target_link_libraries(main -fsanitize=address)

# target_link_libraries(MyTarget PRIVATE -fsanitize=address)