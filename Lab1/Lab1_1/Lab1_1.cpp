#include <algorithm>

#include "iostream"
#include "vector"
#include <boost/timer.hpp>

/**
    1.1. [# 5]
        1) Сгенерировать с помощью алгоритма Нарайаны порождения всех перестановок с выводом времени работы до сотых секунд для 𝑁=10.
        2) Записать время порождения всех перестановок для 𝑁=10, 𝑁=15, 𝑁=20 без вывода полученных последовательностей.
        3) Оценить время работы программы для входа 𝑁=50 и 𝑁=100.
 */
int main(int argc, char* argv[])
{
    std::vector<size_t> v = {1,2,3,4,5,6,7,8};
    boost::timer t;
    t.restart();
    std::sort(v.begin(), v.end());
    do
    {
        copy(v.begin(), v.end(), std::ostream_iterator<size_t>(std::cout, " "));
        std::cout << std::endl;
    }
    while (std::next_permutation(v.begin(), v.end()));

    const double duration = t.elapsed();
    std::cout << duration << std::endl;
    return 0;
}
