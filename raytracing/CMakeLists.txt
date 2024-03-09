project ("raytracing" LANGUAGES CUDA C CXX)

find_package(CUDAToolkit REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CUDAToolkit_INCLUDE_DIRS}) 


# Add source to this project's executable.
add_executable (raytracing "raytracing.cpp" "raytracing.h" "gpu/util.h" "gpu/util.cpp" "common/logging.h" "common/check.h" "common/rstd.h" "common/rstd.cpp" "scene.h" "scene.cpp" "common/math.h" "common/math.cpp" "mesh.h" "mesh.cpp" "material.h" "material.cpp" "test.cpp" "camera.h" "camera.cpp" "ray.h" "render.h" "render.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET raytracing PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC
    spdlog
    assimp
    tinyxml2
    CUDA::cudart
    glm
)
