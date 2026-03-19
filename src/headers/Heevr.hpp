#pragma once
#ifndef HEEVR_HPP_
#define HEEVR_HPP_

#include <random>
#include <complex>

#include "lapacke.h"
#include "util.hpp"

template<class T>
struct HeevrStruct{};

template<>
struct HeevrStruct<float>
{
	template<class...Args>
	static auto Heevr(Args&&...args)
	{
		return LAPACKE_ssyevr(std::forward<Args>(args)...);
	}
};

template<>
struct HeevrStruct<double>
{
	template<class...Args>
	static auto Heevr(Args&&...args)
	{
		return LAPACKE_dsyevr(std::forward<Args>(args)...);
	}
};

template<>
struct HeevrStruct<std::complex<float>>
{
	template<class...Args>
	static auto Heevr(Args&&...args)
	{
		return LAPACKE_cheevr(std::forward<Args>(args)...);
	}
};

template<>
struct HeevrStruct<std::complex<double>>
{
	template<class...Args>
	static auto Heevr(Args&&...args)
	{
		return LAPACKE_zheevr(std::forward<Args>(args)...);
	}
};

template<class T>
double HeevrBench(unsigned int seed, unsigned int N)
{
	std::mt19937 rng(seed);
	auto A = MakeHPD(RandomVector<T>(rng, N * N));
	auto V = RandomVector<T>(rng, N * N);
	auto D = std::vector<typename scalar_traits<T>::real_type>(N, 0.0);
	std::vector<int> S(2 * N, 0);
	auto lambda = [N](decltype(A)& a, decltype(V)& v, decltype(D)& d, decltype(S)& s)
	{
		int M = 0;
		HeevrStruct<T>::Heevr(
			LAPACK_ROW_MAJOR,
			'V',
			'A',
			'L',
			N,
			reinterpret_cast<typename scalar_traits<T>::lapack_this_type*>(a.data()),
			N,
			0.0, 0.0,
			0, 0,
			0.0,
			&M,
			d.data(),
			reinterpret_cast<typename scalar_traits<T>::lapack_this_type*>(v.data()),
			N,
			s.data()
		);
	};
	return Measure(lambda, A, V, D, S);
}

namespace HeevrBenchmarks
{

class SSYEVR: public Benchmark
{
public:
	virtual std::string Tag() const override
	{
		return "--ssyevr";
	}
	virtual std::string Help() const override
	{
		return
			"--ssyevr <Seed> <N>\n"
			"	Single precision eigenvalue decomposition.\n"
			"	Measures A = V D V^T decomposition of (N * N) symmetric matrix."
		;
	}
	virtual size_t Argc() const override
	{
		return 2;
	}
	virtual double Run(const std::vector<unsigned int>& v) const override
	{
		return HeevrBench<float>(v.at(0), v.at(1));
	}
};

class DSYEVR: public Benchmark
{
public:
	virtual std::string Tag() const override
	{
		return "--dsyevr";
	}
	virtual std::string Help() const override
	{
		return
			"--dsyevr <Seed> <N>\n"
			"	Double precision eigenvalue decomposition.\n"
			"	Measures A = V D V^T decomposition of (N * N) symmetric matrix."
		;
	}
	virtual size_t Argc() const override
	{
		return 2;
	}
	virtual double Run(const std::vector<unsigned int>& v) const override
	{
		return HeevrBench<double>(v.at(0), v.at(1));
	}
};

class CHEEVR: public Benchmark
{
public:
	virtual std::string Tag() const override
	{
		return "--cheevr";
	}
	virtual std::string Help() const override
	{
		return
			"--cheevr <Seed> <N>\n"
			"	Single precision complex eigenvalue decomposition.\n"
			"	Measures A = V D V^T decomposition of (N * N) Hermitian matrix."
		;
	}
	virtual size_t Argc() const override
	{
		return 2;
	}
	virtual double Run(const std::vector<unsigned int>& v) const override
	{
		return HeevrBench<std::complex<float>>(v.at(0), v.at(1));
	}
};

class ZHEEVR: public Benchmark
{
public:
	virtual std::string Tag() const override
	{
		return "--zheevr";
	}
	virtual std::string Help() const override
	{
		return
			"--zheevr <Seed> <N>\n"
			"	Double precision complex eigenvalue decomposition.\n"
			"	Measures A = V D V^T decomposition of (N * N) Hermitian matrix."
		;
	}
	virtual size_t Argc() const override
	{
		return 2;
	}
	virtual double Run(const std::vector<unsigned int>& v) const override
	{
		return HeevrBench<std::complex<double>>(v.at(0), v.at(1));
	}
};

static SSYEVR ssyevr;
static DSYEVR dsyevr;
static CHEEVR cheevr;
static ZHEEVR zheevr;

};

#endif // #ifndef HEEVR_HPP_