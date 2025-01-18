cmake_minimum_required(VERSION 3.16)

project(leetcode)

add_executable(189_Rotate_Array "189. Rotate Array.cpp")

target_compile_features(189_Rotate_Array PRIVATE cxx_std_23)

add_executable(1368_Minimum_Cost_to_Make_at_Least_One_Valid_Path_in_a_Grid "1368. Minimum Cost to Make at Least One Valid Path in a Grid.cpp")

target_compile_features(1368_Minimum_Cost_to_Make_at_Least_One_Valid_Path_in_a_Grid PRIVATE cxx_std_23)
