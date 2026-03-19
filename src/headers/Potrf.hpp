#pragma once
#ifndef POTRF_HPP_
#define POTRF_HPP_

#include <random>
#include <complex>

#include "lapacke.h"
#include "util.hpp"

template<class T>
struct PotrfStruct{};

template<>
struct PotrfStruct<float>
{
	template<class...Args>
	static auto Potrf(Args&&...args)
	{
		return LAPACKE_spotrf(std::forward<Args>(args)...);
	}
};

template<>
struct PotrfStruct<double>
{
	template<class...Args>
	static auto Potrf(Args&&...args)
	{
		return LAPACKE_dpotrf(std::forward<Args>(args)...);
	}
};

template<>
struct PotrfStruct<std::complex<float>>
{
	template<class...Args>
	static auto Potrf(Args&&...args)
	{
		return LAPACKE_cpotrf(std::forward<Args>(args)...);
	}
};

template<>
struct PotrfStruct<std::complex<double>>
{
	template<class...Args>
	static auto Potrf(Args&&...args)
	{
		return LAPACKE_zpotrf(std::forward<Args>(args)...);
	}
};

template<class T>
double PotrfBench(unsigned int seed, unsigned int N)
{
	std::mt19937 rng(seed);
	auto A = MakeHPD(RandomVector<T>(rng, N * N));
	auto lambda = [N](decltype(A)& a)
	{
		PotrfStruct<T>::Potrf(
			LAPACK_ROW_MAJOR,
			'L',
			N,
			reinterpret_cast<typename scalar_traits<T>::lapack_this_type*>(a.data()),
			N
		);
	};
	return Measure(lambda, A);
}

namespace PotrfBenchmarks
{

class SPOTRF: public Benchmark
{
public:
	virtual std::string Tag() const override
	{
		return "--spotrf";
	}
	virtual std::string Help() const override
	{
		return
			"--spotrf <Seed> <N>\n"
			"	Single precision Cholesky decomposition.\n"
			"	Measures LL^T decomposition of (N * N) matrix."
		;
	}
	virtual size_t Argc() const override
	{
		return 2;
	}
	virtual double Run(const std::vector<unsigned int>& v) const override
	{
		return PotrfBench<float>(v.at(0), v.at(1));
	}
};

class DPOTRF: public Benchmark
{
public:
	virtual std::string Tag() const override
	{
		return "--dpotrf";
	}
	virtual std::string Help() const override
	{
		return
			"--dpotrf <Seed> <N>\n"
			"	Double precision Cholesky decomposition.\n"
			"	Measures LL^T decomposition of (N * N) matrix."
		;
	}
	virtual size_t Argc() const override
	{
		return 2;
	}
	virtual double Run(const std::vector<unsigned int>& v) const override
	{
		return PotrfBench<double>(v.at(0), v.at(1));
	}
};

class CPOTRF: public Benchmark
{
public:
	virtual std::string Tag() const override
	{
		return "--cpotrf";
	}
	virtual std::string Help() const override
	{
		return
			"--cpotrf <Seed> <N>\n"
			"	Single precision complex Cholesky decomposition.\n"
			"	Measures LL^H decomposition of (N * N) matrix."
		;
	}
	virtual size_t Argc() const override
	{
		return 2;
	}
	virtual double Run(const std::vector<unsigned int>& v) const override
	{
		return PotrfBench<std::complex<float>>(v.at(0), v.at(1));
	}
};

class ZPOTRF: public Benchmark
{
public:
	virtual std::string Tag() const override
	{
		return "--zpotrf";
	}
	virtual std::string Help() const override
	{
		return
			"--zpotrf <Seed> <N>\n"
			"	Double precision complex Cholesky decomposition.\n"
			"	Measures LL^H decomposition of (N * N) matrix."
		;
	}
	virtual size_t Argc() const override
	{
		return 2;
	}
	virtual double Run(const std::vector<unsigned int>& v) const override
	{
		return PotrfBench<std::complex<double>>(v.at(0), v.at(1));
	}
};

static SPOTRF spotrf;
static DPOTRF dpotrf;
static CPOTRF cpotrf;
static ZPOTRF zpotrf;

};

#endif // #ifndef POTRF_HPP_