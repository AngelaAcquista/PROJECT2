cmake_minimum_required(VERSION 3.30)
project(RestaurantFinder)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Use FetchContent to automatically grab SFML 2.6.2
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.2        # Stable release (2.6.2)
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)
FetchContent_MakeAvailable(SFML)

add_executable(RestaurantFinder
        main.cpp
        MainPage.h
        LocationPage.cpp
        LocationPage.h
        FoodTypePage.h
        # Add any other source files here later
)

target_compile_features(RestaurantFinder PRIVATE cxx_std_20)
target_link_libraries(RestaurantFinder PRIVATE sfml-graphics sfml-window sfml-system)
