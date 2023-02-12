#include "iostream"
#include "vector"
#include <boost/timer.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include "cmath"
using boost::multiprecision::cpp_int;

size_t GeneratePermutationWithNarayanaAlgorithm(unsigned short);
cpp_int Factorial(int);
void PrintResult(const double, size_t, unsigned short);

/**
	1.1. [# 5]
		1) Сгенерировать с помощью алгоритма Нарайаны порождения всех перестановок с выводом времени работы до сотых секунд для 𝑁=10.
		2) Записать время порождения всех перестановок для 𝑁=10, 𝑁=15, 𝑁=20 без вывода полученных последовательностей.
		3) Оценить время работы программы для входа 𝑁=50 и 𝑁=100.
 */
int main(int argc, char* argv[])
{
	constexpr unsigned short vectorSize = 10;
	boost::timer timer;
	timer.restart();
	const size_t iterableCount = GeneratePermutationWithNarayanaAlgorithm(vectorSize);
	PrintResult(timer.elapsed() , iterableCount, vectorSize);
	return 0;
}

size_t GeneratePermutationWithNarayanaAlgorithm(const unsigned short vectorSize)
{
	size_t iterablesCount = 0;
	std::vector<size_t> v;
	for (int i = 1; i <= vectorSize; i++)
		v.push_back(i);
	std::sort(v.begin(), v.end());
	do
	{
		iterablesCount++;
	} while (std::next_permutation(v.begin(), v.end()));
	return iterablesCount;
}

cpp_int Factorial(const int number)
{
	cpp_int num = 1;
	for (int i = 1; i <= number; i++)
		num = num * i;
	return num;
}

void PrintResult(const double elapsedTime, const size_t iterablesCount,const unsigned short vectorSize)
{
	std::cout << "Permutation for vector size = " << vectorSize << ", generate in " << round(elapsedTime * 100) / 100.0 << " seconds." << std::endl;
	std::cout << "Iteration count = " << iterablesCount << ".\n";
	const boost::multiprecision::cpp_dec_float_50 oneIterableTime = elapsedTime/ iterablesCount;
	std::cout << "Average for one Iteration = " << oneIterableTime << std::endl;
	
	std::cout << "Average for vector size = 10 is " << oneIterableTime *  Factorial(10).convert_to<boost::multiprecision::cpp_dec_float_50>() << " seconds." << std::endl;
	std::cout << "Average for vector size = 15 is " << oneIterableTime *  Factorial(15).convert_to<boost::multiprecision::cpp_dec_float_50>() << " seconds." << std::endl;
	std::cout << "Average for vector size = 20 is " << oneIterableTime *  Factorial(20).convert_to<boost::multiprecision::cpp_dec_float_50>() << " seconds." << std::endl;
	std::cout << "Average for vector size = 50 is " << oneIterableTime * Factorial(50).convert_to<boost::multiprecision::cpp_dec_float_50>() << " seconds." << std::endl;
	std::cout << "Average for vector size = 100 is " << oneIterableTime * Factorial(100).convert_to<boost::multiprecision::cpp_dec_float_50>() << " seconds." << std::endl;	
}
