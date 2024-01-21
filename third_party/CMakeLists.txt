cmake_minimum_required(VERSION 3.10)

project(third_party LANGUAGES C CXX)

# spdlog
add_subdirectory(spdlog)
set_property(TARGET spdlog PROPERTY FOLDER "ThirdParty")