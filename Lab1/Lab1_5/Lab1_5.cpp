#include <algorithm>
#include <iostream>
#include <vector>

size_t GeneratePermutationWithNarayanaAlgorithm(unsigned short vectorSize);

/* 1.5. [# 15]
	Реализовать алгоритм порождения композиции положительного числа 𝑛 в последовательность положительных целых чисел {𝑧_1, 𝑧_2, …, 𝑧_𝑘 \}, 𝑧_1+𝑧_2+…+𝑧_𝑘=𝑛.
	Здесь учитывается порядок чисел 𝑧_𝑖 и 𝑧_𝑖>0. */
int main(int argc, char *argv[])
{
    constexpr unsigned short vectorSize = 5;
   
   // добавить алгоритм сочетания  ( не нарайяна)  
    //    6 slide
    
    GeneratePermutationWithNarayanaAlgorithm(vectorSize);
    return 0;
}

size_t GeneratePermutationWithNarayanaAlgorithm(const unsigned short vectorSize)
{
    size_t iterablesCount = 0;
    std::vector<size_t> result;
    for (int i = 1; i <= vectorSize; i++)
        result.push_back(i);
    std::sort(result.begin(), result.end());
    do
    {
        std::cout << "Result vector: ";
        copy(result.begin(), result.end(), std::ostream_iterator<size_t>(std::cout, " "));
        iterablesCount++;
        std::cout << std::endl;
    }
    while (std::next_permutation(result.begin(), result.end()));
    return iterablesCount;
}
