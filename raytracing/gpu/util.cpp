#include "util.h"

#include <spdlog/fmt/fmt.h>

namespace rt
{
void gpu_init()
{
	cudaFree(nullptr);

	int device_version;
	CUDA_CHECK(cudaDriverGetVersion(&device_version));

	int runtime_version;
	CUDA_CHECK(cudaRuntimeGetVersion(&runtime_version));
	auto version_to_string = [](int version) {
		int major = version / 1000;
		int minor = (version - major * 1000) / 10;
		return fmt::format("{}.{}", major, minor);
	};
	LOGD("GPU CUDA driver %s, CUDA runtime %s", version_to_string(device_version),
	     version_to_string(runtime_version));

	constexpr int device = 0;
	LOGD("Selecting GPU device %d", device);
	CUDA_CHECK(cudaSetDevice(device));

	int has_unified_addressing;
	CUDA_CHECK(cudaDeviceGetAttribute(&has_unified_addressing, cudaDevAttrUnifiedAddressing, device));

	if (has_unified_addressing == 0)
	{
		LOGE("GPU device %d does not support unified addressing", device);
	}

	CUDA_CHECK(cudaDeviceSetLimit(cudaLimitStackSize, 8192));
	size_t stack_size;
	CUDA_CHECK(cudaDeviceGetLimit(&stack_size, cudaLimitStackSize));
	LOGD("GPU stack size: %zu", stack_size);

	CUDA_CHECK(cudaDeviceSetLimit(cudaLimitPrintfFifoSize, static_cast<size_t>(32) * 1024 * 1024));

	CUDA_CHECK(cudaDeviceSetCacheConfig(cudaFuncCachePreferL1));
}
}        // namespace rt
