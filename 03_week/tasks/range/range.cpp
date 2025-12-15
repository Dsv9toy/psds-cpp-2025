#include <stdexcept>
#include <vector>

/*
Функция принимает значение начала и конца диапазона и шаг
Возвращает вектор std::vector<int> из значений с опред шагом
По умолчанию шаг = 1
[from, to)
Нельзя алгоритмы
Если выделять память, то под нужное количество элементов заранее
//Отрациательный шаг тоже шаг
*/

std::vector<int> Range(int from, int to, int step = 1) 
{
    if (step == 0) return {};
    int countSteps = 0;
    
    if (step > 0 && from < to) {
        countSteps = (to - from + step - 1) / step;
    }
    else if (step < 0 && from > to) {
        countSteps = (from - to - step - 1) / (-step);
    }
    
    if (countSteps <= 0) return {};
    
    std::vector<int> rangedArray = {};
    rangedArray.reserve(countSteps);
    
    if (step > 0) {
        for (int i = from; i < to; i += step) {
            rangedArray.push_back(i);
        }
    } else {
        for (int i = from; i > to; i += step) {
            rangedArray.push_back(i);
        }
    }
    
    return rangedArray;
}
