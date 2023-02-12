#include "iostream"
#include "vector"
#include <boost/timer.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include "cmath"

#include <forward_list>
using boost::multiprecision::cpp_int;

size_t GeneratePermutationWithJohnsonAlgorithm(unsigned short);
cpp_int Factorial(int);
void PrintResult(const double, size_t, unsigned short);

void PrintVector(const std::vector<size_t>& vector)
{
	for (const size_t value : vector)
		std::cout << value << " ";
	std::cout << std::endl;
}

enum Direction
{
	LEFT,
	RIGHT
};

bool IsMoving(const std::vector<size_t>& currentPermutation, const size_t currentIndex, const size_t vectorSize, const Direction direction)
{
	if (direction == LEFT && (currentIndex < 1))
		return false;
	if (direction == RIGHT && (currentIndex >= vectorSize - 1))
		return false;
	if (direction == LEFT && (currentPermutation[currentIndex - 1] > currentPermutation[currentIndex]))
		return false;
	if (direction == RIGHT && (currentPermutation[currentIndex] < currentPermutation[currentIndex + 1]))
		return false;
	return true;
}

/**
   1.2. [# 15]
		1) Реализовать алгоритм Джонсона – Троттера с выводом времени работы до сотых секунд.
		2) Записать время порождения всех перестановок для 𝑁=10, 𝑁=15, 𝑁=20 без вывода полученных последовательностей.
		3) Оценить время работы программы для входа N=50 и N=100. 
 */
int main(int argc, char* argv[])
{
	constexpr unsigned short vectorSize = 10;
	boost::timer timer;
	timer.restart();
	const size_t iterableCount = GeneratePermutationWithJohnsonAlgorithm(vectorSize);
	PrintResult(timer.elapsed() , iterableCount, vectorSize);	
	return 0;
}

size_t GeneratePermutationWithJohnsonAlgorithm(const unsigned short vectorSize)
{
	size_t iterablesCount = 1;
	std::vector<size_t> currentPermutation;
	std::vector<Direction> direction;

	for (int i = 1; i <= vectorSize; i++)
	{
		currentPermutation.push_back(i);
		direction.push_back(LEFT);
	}
	std::sort(currentPermutation.begin(), currentPermutation.end());
	const size_t minElement = *currentPermutation.begin();
	size_t mobileElement = 0;
	size_t mobileElementIndex = 0;
	while (mobileElement != minElement)
	{
		/*std::cout << " " << iterablesCount << " ";
		PrintVector(currentPermutation);
		for (int i = 0; i < vectorSize;i++)
		{
			char test =  direction[i] == LEFT ? '<' : '>';
			std::cout << " " << test;
		}
		std::cout << std::endl;
		*/
		for (int i = 0; i < vectorSize; ++i) //Search Max moving element
		{
			size_t currentElement = currentPermutation.at(i);
			if (currentElement > mobileElement && IsMoving(currentPermutation, i, vectorSize, direction.at(i)))
			{
				mobileElement = currentElement;
				mobileElementIndex = i;
			}
		}
		if (mobileElement == minElement || mobileElement == 0) // if mobile and Max element == minElement in vector	or no such find elements
			break; 	
		for (int i = 0; i < vectorSize; i++) // change direction for all elements greater than mobileElement
		{
			if (currentPermutation.at(i) > mobileElement)
			{
				if (direction[i] == LEFT)
					direction[i] = RIGHT;
				else if (direction[i] == RIGHT)
					direction[i] = LEFT;
			}
		}
		if (direction.at(mobileElementIndex) == LEFT) // swap elements
			{
			std::swap(currentPermutation[mobileElementIndex], currentPermutation[mobileElementIndex - 1]);
			std::swap(direction[mobileElementIndex], direction[mobileElementIndex - 1]);
			}
		else if (direction.at(mobileElementIndex) == RIGHT)
		{
			std::swap(currentPermutation[mobileElementIndex], currentPermutation[mobileElementIndex + 1]);
			std::swap(direction[mobileElementIndex], direction[mobileElementIndex + 1]);
		}
		mobileElement = 0;
		iterablesCount++;
	}
	return iterablesCount;
}

cpp_int Factorial(const int number)
{
	cpp_int num = 1;
	for (int i = 1; i <= number; i++)
		num = num * i;
	return num;
}

void PrintResult(const double elapsedTime, const size_t iterablesCount, const unsigned short vectorSize)
{
	std::cout << "Permutation for vector size = " << vectorSize << ", generate in " << round(elapsedTime * 100) / 100.0 << " seconds." << std::endl;
	std::cout << "Iteration count = " << iterablesCount << ".\n";
	const boost::multiprecision::cpp_dec_float_50 oneIterableTime = elapsedTime / iterablesCount;
	std::cout << "Average for one Iteration = " << oneIterableTime << " secodns." << std::endl;

	std::cout << "Average for vector size = 10 is " << oneIterableTime * Factorial(10).convert_to<boost::multiprecision::cpp_dec_float_50>() << " seconds." << std::endl;
	std::cout << "Average for vector size = 15 is " << oneIterableTime * Factorial(15).convert_to<boost::multiprecision::cpp_dec_float_50>() << " seconds." << std::endl;
	std::cout << "Average for vector size = 20 is " << oneIterableTime * Factorial(20).convert_to<boost::multiprecision::cpp_dec_float_50>() << " seconds." << std::endl;
	std::cout << "Average for vector size = 50 is " << oneIterableTime * Factorial(50).convert_to<boost::multiprecision::cpp_dec_float_50>() << " seconds." << std::endl;
	std::cout << "Average for vector size = 100 is " << (oneIterableTime * Factorial(100).convert_to<boost::multiprecision::cpp_dec_float_50>()) << " seconds." << std::endl;
	std::cout << "Average for vector size = 100 is " << (oneIterableTime * Factorial(100).convert_to<boost::multiprecision::cpp_dec_float_50>()) << " seconds." << std::endl;
}
