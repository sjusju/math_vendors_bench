#include <charconv>
#include <vector>
#include <string>
#include <cstdlib>
#include <utility>
#include <sstream>
#include <exception>
#include <stdexcept>

#include "headers/cblas.h"
#include "headers/lapacke.h"
#include "headers/util.hpp"

#include "headers/Gemm.hpp"
#include "headers/Potrf.hpp"
#include "headers/Heevr.hpp"
#include "headers/FFTW3.hpp"

void help_and_exit_if_help(const std::vector<std::string>& args)
{
	for (const auto& str: args)
	{
		if (
			str == "?" ||
			str == "-?" ||
			str == "-h" ||
			str == "-help" ||
			str == "--help"
		)
		{
			std::cout << "Usage: " << args[0] << " [Option...] [BenchmarkSpec...]\n";
			std::cout << '\n';
			std::cout << "Option:\n";
			std::cout << "?, -?, -h, -help, --help	Prints this help message and exit.\n";
			std::cout << '\n';
			std::cout << "BenchmarkSpec:\n";
			for (auto bench: Benchmark::benchmarks)
			{
				std::cout << bench->Help() << '\n';
			}
			std::cout << std::flush;
			std::exit(0);
		}
	}
}

unsigned int to_uint(const std::string& str, size_t count)
{
	unsigned int value = 0;
	auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), value);
	if (ec == std::errc::invalid_argument || std::string(ptr).size())
	{
		std::stringstream sstr;
		sstr << "Expected integer at arg number " << count << ".";
		throw std::runtime_error(sstr.str());
	}
	else if (ec == std::errc::result_out_of_range)
	{
		std::stringstream sstr;
		sstr << "Number too large at arg number " << count << ".";
		throw std::runtime_error(sstr.str());
	}
	return value;
}

auto parse_args(const std::vector<std::string>& args)
{
	std::vector<std::vector<std::string>> options;
	std::vector<std::pair<const Benchmark*, std::vector<unsigned int>>> tasks;
	size_t integers = 0;
	size_t strings = 0;
	for (size_t arg_counter = 1; arg_counter < args.size(); arg_counter ++)
	{
		const auto& str = args[arg_counter];
		if (integers)
		{
			tasks.back().second.push_back(to_uint(str, arg_counter));
			integers -= 1;
		}
		else if (strings)
		{
			strings -= 1;
		}
		else
		{
			for (auto bench: Benchmark::benchmarks)
			{
				if (str == bench->Tag())
				{
					tasks.emplace_back(bench, 0);
					integers = bench->Argc();
					tasks.back().second.reserve(integers);
					break;
				}
			}
			if (integers) continue;
			// for ()
			// {
			// 	//TODO: Option parsing (for customizing executor)
			// }
		}
	}
	if (integers || strings)
	{
		throw std::runtime_error("Unexpected end of argument list.");
	}
	return std::pair(options, tasks);
}

class Executor
{
public:
	Executor(const std::vector<std::vector<std::string>>& options)
	{};
	void operator()(const Benchmark* bench, const std::vector<unsigned int>& v)
	{
		double time = bench->Run(v);
		std::cout << time;
		for (unsigned int value: v)
		{
			std::cout << ' ' << value;
		}
		std::cout << std::endl;
	}
};

int main(int argc, char** argv)
{
	try
	{
		std::vector<std::string> args(argv, argv + argc);
		help_and_exit_if_help(args);
		auto [options, tasks] = parse_args(args);
		auto executor = Executor(options);
		for (const auto& task: tasks)
		{
			executor(task.first, task.second);
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "An exception was thrown with this message:\n";
		std::cerr << e.what() << std::endl;
		return -1;
	}
	return 0;
}
