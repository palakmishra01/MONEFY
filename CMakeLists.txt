cmake_minimum_required(VERSION 3.10)
project(Monefy VERSION 2.0 LANGUAGES CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# For Windows
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

# Find CURL
find_package(CURL REQUIRED)

# Source files
set(SOURCES
    main.cpp
    transaction.cpp
    currency_converter.cpp
    transaction_manager.cpp
)

# Header files
set(HEADERS
    transaction.hpp
    currency_converter.hpp
    transaction_manager.hpp
)

# Create executable
add_executable(monefy ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(monefy PRIVATE ${CURL_LIBRARIES})

# Include directories
target_include_directories(monefy PRIVATE ${CURL_INCLUDE_DIRS})

# For Windows, ensure proper linking
if(WIN32)
    target_link_libraries(monefy PRIVATE ws2_32 winmm)
endif()

# Installation
install(TARGETS monefy RUNTIME DESTINATION bin)

message(STATUS "Monefy C++ Transaction Tracker (Windows)")
message(STATUS "==========================================")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "CURL Library: ${CURL_LIBRARIES}")
message(STATUS "Build complete!")