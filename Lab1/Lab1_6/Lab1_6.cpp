#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct Command
{
    size_t numberOfThings; // кол-во вещей
    size_t countOfThings; // вес предметов (вместимость рюкзака)
    size_t priceOfThings; // стоимость предметов
};

struct Thing
{
    size_t weight; // вес
    size_t price; // цена 
};

void ParseCommandFile(Command &command, vector<Thing> &thing);
void GetResultItems(vector<vector<size_t>>& array, size_t k, size_t s, vector<Thing>& w, vector<Thing>& resultArray);
/* 1.6. [# 35] Задача об укладке рюкзака.
	Есть 𝑛 различных предметов. Каждый предмет с номером 𝑖, где 𝑖=1,…,𝑛, имеет заданный положительный вес 𝑤_𝑖 и стоимость 𝑐_𝑖.
	Нужно уложить рюкзак так, чтобы общая стоимость предметов в нем была не менее 𝑆, а вес не превышал заданного 𝑇.
	Вход. В первой строке три числа
	    𝑛 - кол-во вещей,
	    𝑇 - вместимость рюкзака предметов,
	    𝑆 - стоимость предметов,
	    в следующих 𝑛 строчках – по два числа (вес 𝑤_𝑖 и стоимость 𝑐_𝑖)
	Выход. В первой строке – вес получившегося рюкзака,
	во второй строчке строка из 0 и 1 поясняющих какие предметы берутся, а какие – не берутся.
 */
int main(int argc, char *argv[])
{
    Command command;
    vector<Thing> thingVector;
    ParseCommandFile(command, thingVector);

    // добавляем единицу, так как для 0 предметов стоимость везде будет 0
    vector<vector<size_t>> A(command.numberOfThings + 1, vector<size_t>(command.countOfThings + 1, 0));

    for (size_t i = 0; i < command.countOfThings; i++) // Заполняем нулевую строчку
        A[0][i] = 0;
    // заполняем таблицу
    for (size_t s = 1; s < command.numberOfThings + 1; s++) // кол-во вещей
    {
        //заполняем один ряд таблицы
        for (size_t n = 0; n < command.countOfThings + 1; n++) // размер рюкзака
        {
            A[s][n] = A[s - 1][n]; // записываем предыдущий элемент из этой же строки
            size_t currentThingWeight = thingVector[s].weight;
            size_t currentThingPrice =  thingVector[s].price;

            bool first = n >= currentThingWeight; // размер рюказа в этой итерации больше чем вес выбранной вещи
            bool second = false;
            
            if (first) 
            {
                size_t firstArgument = A[s - 1][n - currentThingWeight]; // 
                size_t secondArgument = A[s][n];  // текущее состояние элемента таблицы
                second = (firstArgument + currentThingPrice > secondArgument); 
            }   
            if (first && second)
            {
                A[s][n] = A[s - 1][n - currentThingWeight] + currentThingPrice;
            }
        }
    }
    // Восстанавливаем элементы рюкзака
    vector<Thing> resultArray;
    GetResultItems(A,command.numberOfThings,command.countOfThings,thingVector ,resultArray  );
    cout << "Result backback in size = " << command.countOfThings << " is: " << endl;
    for(size_t i = 0; i < resultArray.size(); i++)
    {
        cout << "weight: " << resultArray[i].weight << " , price: " << resultArray[i].price << endl;
    }
    return 0;
}

void ParseCommandFile(Command &command, vector<Thing> &thingVector)
{
    ifstream in("config.txt");
    if (in.is_open())
    {
        in >> command.numberOfThings >> command.countOfThings >> command.priceOfThings;
        Thing thing;
        thingVector.push_back({0,0}); // КОСТЫЛЬ побороть чтение с 1 элемента
        while (!in.eof())
        {
            in >> thing.weight >> thing.price;
            thingVector.push_back(thing);
        }
    }
}

void GetResultItems(vector<vector<size_t>>& array, size_t k, size_t s, vector<Thing>& w, vector<Thing>& resultArray)
{
    if (array[k][s] == 0)
        return;
    if (array[k - 1][s] == array[k][s])
        GetResultItems(array, k - 1, s, w, resultArray);
    else
    {
        GetResultItems(array, k - 1, s - w[k].weight, w, resultArray);
        resultArray.push_back({w[k].weight,w[k].price});     
    }         
}