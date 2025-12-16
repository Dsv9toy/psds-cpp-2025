#include <stdexcept>
#include <vector>
#include <math.h>
/*
Функция принимает на вход контейнер int, а возвращает структуру DataStats, в которой есть среднее отклонение average и стандарт отклонение standard deviation
Нельзя алгоритмы
Лучше решить в один проход
//Под корнем среднего отклонения не должно быть отрицательных чисел. Есть такая штука как std::max. Он сравнивает два аргумента и выдает наибольшой.
*/

struct DataStats { 
    double avg = 0.0;
    double sd = 0.0;
};

DataStats CalculateDataStats(const std::vector<int>& Nums) {
    DataStats resultOfMeasure;
    size_t sizeNum = Nums.size();

    if (sizeNum == 0) return DataStats{};

    double sum = 0.0;
    double sumSquares = 0.0;

    for (size_t i = 0; i < sizeNum; ++i) {
        sum += Nums[i];
        sumSquares += static_cast<double>(Nums[i]) * Nums[i];
    }
    
    resultOfMeasure.avg = sum / sizeNum;
    double deviation = (sumSquares / sizeNum) - (resultOfMeasure.avg * resultOfMeasure.avg);
    resultOfMeasure.sd = sqrt(std::max(deviation, 0.0));

    return resultOfMeasure;

}
