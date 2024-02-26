cmake_minimum_required(VERSION 3.10)

project(third_party LANGUAGES C CXX)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# spdlog
add_subdirectory(spdlog)
set_property(TARGET spdlog PROPERTY FOLDER "ThirdParty")

# assimp
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "Do not build Assimp tools" FORCE)
set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "Do not build Assimp samples" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Do not build Assimp tests" FORCE)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF CACHE BOOL "Do not build all default exporters" FORCE)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "Do not build all default importers" FORCE)
set(ASSIMP_BUILD_DOCS OFF CACHE BOOL "Do not build Assimp docs" FORCE)
set(ASSIMP_BUILD_DRACO OFF CACHE BOOL "Do not build Draco" FORCE)
set(ASSIMP_BUILD_ASSIMP_VIEW OFF CACHE BOOL "Do not build Assimp view" FORCE)

set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "Do not treat warnings as errors" FORCE)

set(ASSIMP_BUILD_OBJ_IMPORTER TRUE)

add_subdirectory(assimp)

get_directory_property(ASSIMP_TARGETS DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/assimp BUILDSYSTEM_TARGETS)
message(STATUS "Assimp targets: ${ASSIMP_TARGETS}")

set_property(TARGET assimp PROPERTY FOLDER "ThirdParty")

# tinyxml2
add_subdirectory(tinyxml2)
set_property(TARGET tinyxml2 PROPERTY FOLDER "ThirdParty")