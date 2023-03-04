#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
vector<vector<size_t>> GetCombinations(size_t digitsCount, size_t maxDigit);
size_t VectorSumma(vector<size_t> &vector);
vector<size_t> GetSumm(size_t arraySizeForCombinations, size_t numbersCountForDelemiter, vector<size_t> &combinations);
vector<vector<size_t>> GetSummVector(size_t arraySizeForCombinations, size_t numbersCountForDelemiter,
                                     vector<vector<size_t>> &combinations);
void PrintVector(vector<vector<size_t>> &summVector);
/* 1.5. [# 15]
	Реализовать алгоритм порождения композиции положительного числа 𝑛 в последовательность положительных целых чисел {𝑧_1, 𝑧_2, …, 𝑧_𝑘 \}, 𝑧_1+𝑧_2+…+𝑧_𝑘=𝑛.
	Здесь учитывается порядок чисел 𝑧_𝑖 и 𝑧_𝑖>0.
Понимание задачи. Должно быть так: вводишь число (например 5)
Программа должна выдать все перестановки, сумма которых равна 5
Пример: задача, которую писали на доске. Про яблоки, какими вариантами их можно поделить
*/
int main(int argc, char *argv[])
{
    // число для разложения
    size_t numberForComposition = 3;
    cout << "For number is :" << numberForComposition << endl;
    cout << numberForComposition << endl;
    for (size_t i = 2; i < numberForComposition; i++)
    {
        // количество чисел, на которое раскладываем
        size_t numbersCountForDelemiter = i; // это значение мы отложили, нужно потом запомнить
        size_t arrayDelemiters = numbersCountForDelemiter - 1;
        // размер массива для получения комбинаций
        size_t arraySizeForCombinations = numberForComposition - numbersCountForDelemiter + arrayDelemiters;
        vector<vector<size_t>> combinations = GetCombinations(arrayDelemiters, arraySizeForCombinations);
        vector<vector<size_t>> summVector = GetSummVector(arraySizeForCombinations, numbersCountForDelemiter,
                                                          combinations);
        PrintVector(summVector);
    }
    for (size_t i = 0; i < numberForComposition; i++)
        cout << "1 ";
    cout << endl;
    return 0;
}

/**  
 * Возвращает все сочетания в лексикографическом порядке, для {3,5} - пары будут 123 124 125 134 etc
 * @param digitsCount - количество цифр в сочетании
 * @param maxDigit - максимальное число
 */
vector<vector<size_t>> GetCombinations(const size_t digitsCount, const size_t maxDigit)
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
        auto tempVar = combination;
        tempVar.erase(tempVar.begin());
        combinationResult.push_back(tempVar);
        //copy(combination.begin() + 1, combination.end(), std::ostream_iterator<size_t>(std::cout, " "));
        //cout << endl;
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

/**
 * Получение одной суммы числа
 */
vector<size_t> GetSumm(size_t arraySizeForCombinations, size_t numbersCountForDelemiter, vector<size_t> &combinations)
{
    vector<size_t> summ;
    //добавляем все слагаемые
    for (size_t i = 0; i < numbersCountForDelemiter; i++)
    {
        size_t tmp = 0;
        if (i + 1 == numbersCountForDelemiter) // это значит последнее значение
        {
            size_t tmptest = combinations[i - 1]; // последний элемент массива combinatoins
            tmp = arraySizeForCombinations - tmptest;
            // последнее значение = размерМассива -1 - последнее зачение в комбаниции.
        }
        else
        {
            tmp += combinations[i]; // добавляем текущее значение
            // нужно посчитать сумму элемента, обходим прредыдущие значения
            // for (size_t j = i; j > 0; j--) // вроде как не надо, мы должны вычитать предыдущийэ элемент
            // {
            //     tmp -= combinations[i - 1]; // теперь нужно вычесть предыдущие
            // }
            if (i > 0)
                tmp -= combinations[i - 1];
            
            tmp--; // вычитаем единицу у всех значений, кроме последнего            
        }
        tmp++; // добавляем по единице каждому элементу, так как мы их брали до этого
        summ.push_back(tmp);
    }
    return summ;
}

/**
 * Получение всех сумм числа с одинаковым количеством слагаемых
 */
vector<vector<size_t>> GetSummVector(size_t arraySizeForCombinations, size_t numbersCountForDelemiter,
                                     vector<vector<size_t>> &combinations)
{
    vector<vector<size_t>> summVector;
    vector<size_t> tmpSum;
    for (size_t i = 0; i < combinations.size(); i++) // ищем всем варианты суммы 
    {
        tmpSum = GetSumm(arraySizeForCombinations, numbersCountForDelemiter, combinations.at(i));
        summVector.push_back(tmpSum);
    }
    return summVector;
}

void PrintVector(vector<vector<size_t>> &summVector)
{
    for (size_t i = 0; i < summVector.size(); i++)
    {
        copy(summVector[i].begin(), summVector[i].end(), std::ostream_iterator<size_t>(std::cout, " "));
        cout << endl;
    }
}
