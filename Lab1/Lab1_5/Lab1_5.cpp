#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
vector<vector<size_t>> GetCombination(size_t digitsCount, size_t maxDigit);
size_t VectorSumma(vector<size_t> &vector);
/* 1.5. [# 15]
	Реализовать алгоритм порождения композиции положительного числа 𝑛 в последовательность положительных целых чисел {𝑧_1, 𝑧_2, …, 𝑧_𝑘 \}, 𝑧_1+𝑧_2+…+𝑧_𝑘=𝑛.
	Здесь учитывается порядок чисел 𝑧_𝑖 и 𝑧_𝑖>0.
Понимание задачи. Должно быть так: вводишь число (например 5)
Программа должна выдать все перестановки, сумма которых равна 5
Пример: задача, которую писали на доске. Про яблоки, какими вариантами их можно поделить
*/
int main(int argc, char *argv[])
{
    constexpr unsigned short vectorSize = 5;

    // добавить алгоритм сочетания  ( не нарайяна)  
    //    6 slide
    vector<vector<size_t>> test = GetCombination(2, 4);
    return 0;
}

/**  
 * Возвращает все сочетания в лексикографическом порядке, для {3,5} - пары будут 123 124 125 134 etc
 * @param digitsCount - количество цифр в сочетании
 * @param maxDigit - максимальное число
 */
vector<vector<size_t>> GetCombination(const size_t digitsCount, const size_t maxDigit)
{
    vector<size_t> combination(digitsCount + 1, 0);
    vector<vector<size_t>> combinationResult;
    combination[0] = -1;
    for (size_t i = 1; i <= digitsCount; i++)
    {
        combination[i] = i;
    }
    size_t m = 1;
    while (m != 0)
    {
        combinationResult.push_back(combination);
        copy(combination.begin() + 1, combination.end(), std::ostream_iterator<size_t>(std::cout, " "));
        cout << endl;
        m = digitsCount;
        while (combination[m] == maxDigit - digitsCount + m)
            m--;

        combination[m] = combination[m] + 1;

        for (size_t i = m + 1; i <= digitsCount; i++)
        {
            combination[i] = combination[i - 1] + 1;
        }
    }
    return combinationResult;
}

size_t VectorSumma(vector<size_t> &vector)
{
    size_t vectorSum = 0;

    // тут единица так как игнорирует 0 элемент вектора, там мусор
    for (size_t i = 1; i < vector.size(); i++)
        vectorSum += vector[i];
    return vectorSum;
}
