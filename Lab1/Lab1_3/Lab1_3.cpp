#include "iostream"
#include <vector>
#include <algorithm>

bool IsVectorContains(const std::vector<size_t>& positions, size_t value);

// 1.3. [# 5]
//		Реализовать алгоритм порождения случайной перестановки.
int main(size_t argc, char* argv[])
{
	std::vector<size_t> inputVector = {1, 2, 3, 4,5 ,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
    const size_t vectorSize = inputVector.size();
	std::srand(std::time(nullptr));

	std::cout << "Start vector: ";
	copy(inputVector.begin(), inputVector.end(), std::ostream_iterator<size_t>(std::cout, " "));
	std::cout << std::endl;

    for (size_t i = 0; i < vectorSize; i++)
	{
	    std::swap(inputVector[i], inputVector[std::rand() % inputVector.size() + 1]);
	}

	std::cout << "Result vector: ";
	copy(inputVector.begin(), inputVector.end(), std::ostream_iterator<size_t>(std::cout, " "));
	std::cout << std::endl;
	return 0;
}