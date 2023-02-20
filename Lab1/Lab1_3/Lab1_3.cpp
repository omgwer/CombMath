#include "iostream"
#include <vector>

bool IsVectorContains(const std::vector<size_t>& positions, size_t value);

// 1.3. [# 5]
//		Реализовать алгоритм порождения случайной перестановки.
int main(size_t argc, char* argv[])
{
	std::vector<size_t> v = {1, 2, 3, 4,5 ,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
	std::vector<size_t> result(v.size());
	std::vector<size_t> positions;
	std::srand(std::time(nullptr));

	std::cout << "Start vector: ";
	copy(v.begin(), v.end(), std::ostream_iterator<size_t>(std::cout, " "));
	std::cout << std::endl;
	while (positions.size() != v.size())
	{
		size_t randomVariable;
		do
		{
			randomVariable = std::rand() % v.size();
		} while (IsVectorContains(positions, randomVariable));
		positions.push_back(randomVariable);
	}

	for (size_t i = 0; i < positions.size(); i++)
	{
		result[positions[i]] = v[i];
	}

	std::cout << "Result vector: ";
	copy(result.begin(), result.end(), std::ostream_iterator<size_t>(std::cout, " "));
	std::cout << std::endl;
	return 0;
}

bool IsVectorContains(const std::vector<size_t>& positions,const size_t value)
{
	for (const size_t position : positions)
	{
		if (position == value)
		{
			return true;
		}
	}
	return false;
}
