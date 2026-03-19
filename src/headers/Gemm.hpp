#pragma once
#ifndef GEMM_HPP_
#define GEMM_HPP_

#include <random>
#include <complex>

#include "cblas.h"
#include "util.hpp"
#include "Benchmark.hpp"

template<class T>
struct GemmStruct{};

template<>
struct GemmStruct<float>
{
	template<class...Args>
	static auto Gemm(Args&&...args)
	{
		return cblas_sgemm(std::forward<Args>(args)...);
	}
};

template<>
struct GemmStruct<double>
{
	template<class...Args>
	static auto Gemm(Args&&...args)
	{
		return cblas_dgemm(std::forward<Args>(args)...);
	}
};

template<>
struct GemmStruct<std::complex<float>>
{
	template<class...Args>
	static auto Gemm(Args&&...args)
	{
		return cblas_cgemm(std::forward<Args>(args)...);
	}
};

template<>
struct GemmStruct<std::complex<double>>
{
	template<class...Args>
	static auto Gemm(Args&&...args)
	{
		return cblas_zgemm(std::forward<Args>(args)...);
	}
};

template<class T>
double GemmBench(unsigned int seed, unsigned int N, unsigned int M, unsigned int L)
{
	std::mt19937 rng(seed);
	auto A = RandomVector<T>(rng, N * M);
	auto B = RandomVector<T>(rng, M * L);
	auto C = RandomVector<T>(rng, N * L);
	auto lambda = [N, M, L](decltype(A)& a, decltype(B)& b, decltype(C)& c)
	{
		const T alpha = 1.0;
		const T beta = 0.0;
		GemmStruct<T>::Gemm(
			CblasRowMajor, CblasNoTrans, CblasNoTrans,
			N, L, M,
			ptr_if_true<std::is_same_v<T, typename scalar_traits<T>::complex_type>>(alpha),
			a.data(), M,
			b.data(), L,
			ptr_if_true<std::is_same_v<T, typename scalar_traits<T>::complex_type>>(beta),
			c.data(), L
		);
	};
	return Measure(lambda, A, B, C);
}

namespace GemmBenchmarks
{

class SGEMM: public Benchmark
{
public:
	virtual std::string Tag() const override
	{
		return "--sgemm";
	}
	virtual std::string Help() const override
	{
		return
			"--sgemm <Seed> <N> <M> <L>\n"
			"	Single precision matrix multiplication.\n"
			"	Measures (N * M) @ (M * L) -> (N * L)."
		;
	}
	virtual size_t Argc() const override
	{
		return 4;
	}
	virtual double Run(const std::vector<unsigned int>& v) const override
	{
		return GemmBench<float>(v.at(0), v.at(1), v.at(2), v.at(3));
	}
};

class DGEMM: public Benchmark
{
public:
	virtual std::string Tag() const override
	{
		return "--dgemm";
	}
	virtual std::string Help() const override
	{
		return
			"--dgemm <Seed> <N> <M> <L>\n"
			"	Double precision matrix multiplication.\n"
			"	Measures (N * M) @ (M * L) -> (N * L)."
		;
	}
	virtual size_t Argc() const override
	{
		return 4;
	}
	virtual double Run(const std::vector<unsigned int>& v) const override
	{
		return GemmBench<double>(v.at(0), v.at(1), v.at(2), v.at(3));
	}
};

class CGEMM: public Benchmark
{
public:
	virtual std::string Tag() const override
	{
		return "--cgemm";
	}
	virtual std::string Help() const override
	{
		return
			"--cgemm <Seed> <N> <M> <L>\n"
			"	Single precision complex matrix multiplication.\n"
			"	Measures (N * M) @ (M * L) -> (N * L)."
		;
	}
	virtual size_t Argc() const override
	{
		return 4;
	}
	virtual double Run(const std::vector<unsigned int>& v) const override
	{
		return GemmBench<std::complex<float>>(v.at(0), v.at(1), v.at(2), v.at(3));
	}
};

class ZGEMM: public Benchmark
{
public:
	virtual std::string Tag() const override
	{
		return "--zgemm";
	}
	virtual std::string Help() const override
	{
		return
			"--zgemm <Seed> <N> <M> <L>\n"
			"	Double precision complex matrix multiplication.\n"
			"	Measures (N * M) @ (M * L) -> (N * L)."
		;
	}
	virtual size_t Argc() const override
	{
		return 4;
	}
	virtual double Run(const std::vector<unsigned int>& v) const override
	{
		return GemmBench<std::complex<double>>(v.at(0), v.at(1), v.at(2), v.at(3));
	}
};

static SGEMM sgemm;
static DGEMM dgemm;
static CGEMM cgemm;
static ZGEMM zgemm;

};

#endif // #ifndef GEMM_HPP_