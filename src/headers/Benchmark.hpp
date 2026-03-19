#pragma once
#ifndef BENCHMARK_HPP_
#define BENCHMARK_HPP_

#include <vector>
#include <string>

class Benchmark
{
public:
	Benchmark()
	{
		benchmarks.push_back(this);
	}
	virtual ~Benchmark(){}
	virtual std::string Tag() const = 0;
	virtual std::string Help() const = 0;
	virtual size_t Argc() const = 0;
	virtual double Run(const std::vector<unsigned int>&) const = 0;
public:
	static std::vector<const Benchmark*> benchmarks;
};
std::vector<const Benchmark*> Benchmark::benchmarks(0);

#endif // #ifndef BENCHMARK_HPP_