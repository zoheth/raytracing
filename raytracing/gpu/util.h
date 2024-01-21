#pragma once

#include <cassert>

#include <cuda.h>
#include <cuda_runtime_api.h>

#include "common/logging.h"

#define CUDA_CHECK(EXPR)                                                       \
  if ((EXPR) != cudaSuccess) {                                                 \
    cudaError_t error = cudaGetLastError();                                    \
    LOGE("CUDA error: %s", cudaGetErrorString(error));                    \
  } else /* eat semicolon */

#define CU_CHECK(EXPR)                                                         \
  do {                                                                         \
    CUresult result = EXPR;                                                    \
    if (result != CUDA_SUCCESS) {                                              \
      const char *str;                                                         \
      assert(CUDA_SUCCESS == cuGetErrorString(result, &str));                  \
      LOGE("CUDA error: %s", str);                                        \
    }                                                                          \
  } while (false) /* eat semicolon */

namespace rt {
void gpu_init();
}
