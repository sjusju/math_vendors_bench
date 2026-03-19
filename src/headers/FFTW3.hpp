#pragma once
#ifndef FFTW3_HPP_
#define FFTW3_HPP_

#include <random>
#include <complex>
#include <stdexcept>

#include "fftw3.h"
#include "util.hpp"

template<class T>
struct FFTW3Struct{};

template<>
struct FFTW3Struct<std::complex<float>>
{
	using plan_type = fftwf_plan;
	using fftw3_value_type = fftwf_complex;
	using value_type = std::complex<float>;
	using vector_type = std::vector<value_type>;
	FFTW3Struct (int N, vector_type& A, vector_type& B):
		plan(fftwf_plan_dft_1d(
			N,
			reinterpret_cast<fftw3_value_type*>(A.data()),
			reinterpret_cast<fftw3_value_type*>(B.data()),
			FFTW_FORWARD,
			FFTW_ESTIMATE
		))
	{
		if (!plan)
		{
			throw std::runtime_error("Failed to create FFTW3 plan");
		}
	}
	auto FFT()
	{
		return fftwf_execute(plan);
	}
	~FFTW3Struct()
	{
		fftwf_destroy_plan(plan);
	}
private:
	plan_type plan;
};

template<>
struct FFTW3Struct<std::complex<double>>
{
	using plan_type = fftw_plan;
	using fftw3_value_type = fftw_complex;
	using value_type = std::complex<double>;
	using vector_type = std::vector<value_type>;
	FFTW3Struct (int N, vector_type& A, vector_type& B):
		plan(fftw_plan_dft_1d(
			N,
			reinterpret_cast<fftw3_value_type*>(A.data()),
			reinterpret_cast<fftw3_value_type*>(B.data()),
			FFTW_FORWARD,
			FFTW_ESTIMATE
		))
	{
		if (!plan)
		{
			throw std::runtime_error("Failed to create FFTW3 plan");
		}
	}
	auto FFT()
	{
		return fftw_execute(plan);
	}
	~FFTW3Struct()
	{
		fftw_destroy_plan(plan);
	}
private:
	plan_type plan;
};

template<class T>
double FFTW3Bench(unsigned int seed, unsigned int N)
{
	std::mt19937 rng(seed);
	auto A = RandomVector<T>(rng, N);
	auto B = RandomVector<T>(rng, N);
	auto fftw3 = FFTW3Struct<T>(N, A, B);
	auto lambda = [&fftw3](decltype(A)& a, decltype(B)& b)
	{
		fftw3.FFT();
	};
	return Measure(lambda, A, B);
}

template<class T>
double FFTW3InplaceBench(unsigned int seed, unsigned int N)
{
	std::mt19937 rng(seed);
	auto A = RandomVector<T>(rng, N);
	auto fftw3 = FFTW3Struct<T>(N, A, A);
	auto lambda = [&fftw3](decltype(A)& a)
	{
		fftw3.FFT();
	};
	return Measure(lambda, A);
}

namespace HeevrBenchmarks
{

class FFTW1DF: public Benchmark
{
public:
	virtual std::string Tag() const override
	{
		return "--fftw1df";
	}
	virtual std::string Help() const override
	{
		return
			"--fftw1df <Seed> <N>\n"
			"	Discrete Fourier transform of single precision complex 1D array, of length N."
		;
	}
	virtual size_t Argc() const override
	{
		return 2;
	}
	virtual double Run(const std::vector<unsigned int>& v) const override
	{
		return FFTW3Bench<std::complex<float>>(v.at(0), v.at(1));
	}
};

class FFTW1D: public Benchmark
{
public:
	virtual std::string Tag() const override
	{
		return "--fftw1d";
	}
	virtual std::string Help() const override
	{
		return
			"--fftw1d <Seed> <N>\n"
			"	Discrete Fourier transform of double precision complex 1D array, of length N."
		;
	}
	virtual size_t Argc() const override
	{
		return 2;
	}
	virtual double Run(const std::vector<unsigned int>& v) const override
	{
		return FFTW3Bench<std::complex<double>>(v.at(0), v.at(1));
	}
};

class FFTW1DFI: public Benchmark
{
public:
	virtual std::string Tag() const override
	{
		return "--fftw1dfi";
	}
	virtual std::string Help() const override
	{
		return
			"--fftw1dfi <Seed> <N>\n"
			"	Inplace discrete Fourier transform of single precision complex 1D array, of length N."
		;
	}
	virtual size_t Argc() const override
	{
		return 2;
	}
	virtual double Run(const std::vector<unsigned int>& v) const override
	{
		return FFTW3InplaceBench<std::complex<float>>(v.at(0), v.at(1));
	}
};

class FFTW1DI: public Benchmark
{
public:
	virtual std::string Tag() const override
	{
		return "--fftw1di";
	}
	virtual std::string Help() const override
	{
		return
			"--fftw1di <Seed> <N>\n"
			"	Inplace discrete Fourier transform of double precision complex 1D array, of length N."
		;
	}
	virtual size_t Argc() const override
	{
		return 2;
	}
	virtual double Run(const std::vector<unsigned int>& v) const override
	{
		return FFTW3InplaceBench<std::complex<double>>(v.at(0), v.at(1));
	}
};

static FFTW1DF fftw1df;
static FFTW1D fftw1d;
static FFTW1DFI fftw1dfi;
static FFTW1DI fftw1di;

};

#endif // #ifndef FFTW3_HPP_