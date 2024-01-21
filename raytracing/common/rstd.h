#pragma once
#include <cstddef>

namespace rstd
{
namespace pmr
{
class memory_resource
{
	static constexpr size_t max_align = alignof(std::max_align_t);

  public:
	virtual ~memory_resource() = default;
	void *allocate(size_t bytes, size_t alignment = max_align)
	{
		if (bytes == 0)
			return nullptr;
		return do_allocate(bytes, alignment);
	}

	void deallocate(void *p, size_t bytes, size_t alignment = max_align)
	{
		if (p == nullptr)
			return;
		do_deallocate(p, bytes, alignment);
	}

	bool is_equal(const memory_resource &other) const noexcept
	{
		return this == &other || do_is_equal(other);
	}

  private:
	virtual void *do_allocate(size_t bytes, size_t alignment)              = 0;
	virtual void  do_deallocate(void *p, size_t bytes, size_t alignment)   = 0;
	virtual bool  do_is_equal(const memory_resource &other) const noexcept = 0;
};

class alignas(64) monotonic_buffer_resource : public memory_resource
{
  public:
	explicit monotonic_buffer_resource(memory_resource *upstream) noexcept;

  private:
	struct block
	{
		void  *ptr;
		size_t size;
		block *next;
	};
	block *allocate_block(size_t bytes);

	void free_block(block *b);
};

}        // namespace pmr
}        // namespace rstd