cmake_minimum_required(VERSION 3.22.1)

project(localif)

add_library(localif SHARED localif.cpp)

# Link against the log library
find_library(log-lib log)

# Link against the Android NDK asset manager library
find_library(asset-manager-lib android)

# Link against the asset manager and log libraries
target_link_libraries(localif ${log-lib} ${asset-manager-lib})
