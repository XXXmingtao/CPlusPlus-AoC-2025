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

add_executable(DayTwo)

target_sources(DayTwo
    PRIVATE
        day2/main.cpp
)

add_executable(DayThree)

target_sources(DayThree
    PRIVATE
        day3/main.cpp)

target_include_directories(DayThree
    PUBLIC
    /home/ci-mingtaol-linux/dev/CPlusPlus-AoC-2025/Utils
)

add_executable(DayFour)

target_sources(DayFour
    PRIVATE
        day4/main.cpp)

add_executable(DayFive)

target_sources(DayFive
    PRIVATE
        day5/main.cpp)

target_include_directories(DayFive
    PUBLIC
    /home/ci-mingtaol-linux/dev/CPlusPlus-AoC-2025/Utils
)

add_executable(DaySix)

target_sources(DaySix
    PRIVATE
        day6/main.cpp)

target_include_directories(DaySix
    PUBLIC
    /home/ci-mingtaol-linux/dev/CPlusPlus-AoC-2025/Utils
)



# install(FILES "day1/input.txt"
# DESTINATION "build/${AdvantOfCode}")
# message("Content of input.txt: ${file_content}")