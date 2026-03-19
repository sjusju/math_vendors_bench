#pragma once
#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <type_traits>
#include <complex>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <tuple>

template<class T>
struct scalar_traits{};

template<>
struct scalar_traits<float>
{
	using real_type = float;
	using complex_type = std::complex<real_type>;
	using this_type = real_type;
	using lapack_real_type = real_type;
	using lapack_complex_type = lapack_complex_float;
	using lapack_this_type = lapack_real_type;
};

template<>
struct scalar_traits<double>
{
	using real_type = double;
	using complex_type = std::complex<real_type>;
	using this_type = real_type;
	using lapack_real_type = real_type;
	using lapack_complex_type = lapack_complex_double;
	using lapack_this_type = lapack_real_type;
};

template<>
struct scalar_traits<std::complex<float>>
{
	using real_type = float;
	using complex_type = std::complex<real_type>;
	using this_type = real_type;
	using lapack_real_type = real_type;
	using lapack_complex_type = lapack_complex_float;
	using lapack_this_type = lapack_complex_type;
};

template<>
struct scalar_traits<std::complex<double>>
{
	using real_type = double;
	using complex_type = std::complex<real_type>;
	using this_type = real_type;
	using lapack_real_type = real_type;
	using lapack_complex_type = lapack_complex_double;
	using lapack_this_type = lapack_complex_type;
};

template<bool B, class T>
auto ptr_if_true(T& obj)
{
	if constexpr (B)
	{
		return &obj;
	}
	else
	{
		return obj;
	}
}

template<class T>
auto conjugate(const T& value)
{
	if constexpr (std::is_same_v<T, typename scalar_traits<T>::real_type>)
	{
		return value;
	}
	else
	{
		return std::conj(value);
	}
}

template<class T, class RNG>
std::vector<T> RandomVector(RNG& rng, size_t N)
{
	std::vector<T> ret(N);
	std::uniform_real_distribution<typename scalar_traits<T>::real_type> dist(-1.0, 1.0);
	for (auto& value: ret)
	{
		if constexpr (std::is_same_v<T, typename scalar_traits<T>::complex_type>)
		{
			auto real = dist(rng);
			auto imag = dist(rng);
			value = {real, imag};
		}
		else
		{
			value = dist(rng);
		}
	}
	return ret;
}

template<class T>
constexpr T isqrt(T x)
{
    T i = std::numeric_limits<T>::max();
    i -= i >> 1;
    T ret = 0;
    while (i)
    {
        T test = ret + i;
        if (x / test >= test)
        {
            ret += i;
        }
        i >>= 1;
    }
    return ret;
}

template<class T>
std::vector<T> MakeHPD(const std::vector<T>& A)
{
	size_t N = isqrt(A.size());
	if (N * N != A.size())
	{
		throw std::runtime_error("MakeHPD requires square matrix. (std::vector of perfect-square size)");
	}
	std::vector<T> ret(A.size(), 0.0);
	// Triple loop that calculate A^H @ A.
	// Maybe just assume BLAS is always there?
	for (size_t i = 0; i < N; i ++)
	{
		for (size_t j = 0; j < N; j ++)
		{
			for (size_t k = 0; k < N; k ++)
			{
				ret[i * N + j] += A[i * N + k] * conjugate(A[k * N + j]);
			}
		}
	}
	return ret;
}

template<class Lambda, class...Args>
double Measure(Lambda lambda, Args&...args)
{
	auto backup = std::make_tuple(args...);
	lambda(args...);
	std::tie(args...) = backup;
	auto start = std::chrono::steady_clock::now();
	lambda(args...);
	auto end = std::chrono::steady_clock::now();
	return std::chrono::duration<double>(end - start).count();
}



#endif // #ifndef UTIL_HPP_