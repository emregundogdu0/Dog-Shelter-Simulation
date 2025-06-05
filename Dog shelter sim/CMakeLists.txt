cmake_minimum_required(VERSION 3.10)
project(DogProgram C)

set(CMAKE_C_STANDARD 99)

add_executable(DogProgram
        main.c
        Dog.c
        dogShelterSimulation.c
        list.c
        queue.c
)
