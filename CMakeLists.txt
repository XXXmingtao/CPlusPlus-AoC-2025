cmake_minimum_required(VERSION 3.23)

project(AdvantOfCode)

add_executable(DayOne)

target_sources(DayOne
    PRIVATE
        day1/main.cpp
        Utils/LinkedList.cpp
)

target_include_directories(DayOne
    PUBLIC
    /home/ci-mingtaol-linux/dev/CPlusPlus-AoC-2025/Utils
)


# install(FILES "day1/input.txt"
# DESTINATION "build/${AdvantOfCode}")
# message("Content of input.txt: ${file_content}")