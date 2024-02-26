#pragma once
#include <cmath>

namespace rt
{
template <std::size_t N, typename T>
class Vector
{
  public:
	T data[N];

	Vector()
	{
		for (std::size_t i = 0; i < N; i++)
		{
			data[i] = T();
		}
	}

	Vector(std::initializer_list<T> list)
	{
		std::size_t i = 0;
		for (auto &elem : list)
		{
			if (i < N)
			{
				data[i++] = elem;
			}
		}
	}

	T &operator[](std::size_t index)
	{
		return data[index];
	}

	const T &operator[](std::size_t index) const
	{
		return data[index];
	}

	Vector &operator+=(const Vector &rhs)
	{
		for (std::size_t i = 0; i < N; ++i)
		{
			data[i] += rhs[i];
		}
		return *this;
	}
};

template <std::size_t N, typename T>
Vector<N, T> operator+(const Vector<N, T> &lhs, const Vector<N, T> &rhs)
{
	Vector<N, T> result = lhs;
	result += rhs;
	return result;
}

template <std::size_t N, typename T>
Vector<N, T> operator-(const Vector<N, T> &lhs, const Vector<N, T> &rhs)
{
	Vector<N, T> result = lhs;
	for (std::size_t i = 0; i < N; ++i)
	{
		result[i] -= rhs[i];
	}
	return result;
}

template <std::size_t N, typename T>
Vector<N, T> operator*(const Vector<N, T> &lhs, const T &rhs)
{
	Vector<N, T> result = lhs;
	for (std::size_t i = 0; i < N; ++i)
	{
		result[i] *= rhs;
	}
	return result;
}

template <std::size_t N, typename T>
T dot(const Vector<N, T> &lhs, const Vector<N, T> &rhs)
{
	T result = T();
	for (std::size_t i = 0; i < N; ++i)
	{
		result += lhs[i] * rhs[i];
	}
	return result;
}

using Vector2f = Vector<2, float>;
using Vector3f = Vector<3, float>;

// Cross product for 3D vectors
template <typename T>
Vector<3, T> cross(const Vector<3, T> &lhs, const Vector<3, T> &rhs)
{
	return Vector<3, T>{
	    lhs[1] * rhs[2] - lhs[2] * rhs[1],
	    lhs[2] * rhs[0] - lhs[0] * rhs[2],
	    lhs[0] * rhs[1] - lhs[1] * rhs[0]};
}

}        // namespace rt