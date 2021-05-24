cmake_minimum_required(VERSION 3.1)

find_package(Eigen3)
if(Eigen3_FOUND)
message("--Eigen Found")
endif()

add_executable(func_param func_param.cpp)
target_link_libraries(func_param Eigen3::Eigen)

add_executable(keyword_template keyword_template.cpp)
target_link_libraries(keyword_template Eigen3::Eigen)

# add_executable(impl impl.cpp)
# target_link_libraries(impl Eigen3::Eigen)

add_executable(test test.cpp)
