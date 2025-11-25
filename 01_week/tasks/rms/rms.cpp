#include <cstddef>
#include <stdexcept>
#include <math.h>
#include <numbers>

//RMS - среднеквадратическое отклонение. 
// Берем массив. Возводим текущее значение в квадрат, суммируем все значения, делим на кол-во элементов и всё под корень. 

double CalculateRMS(double values[], size_t size) {

    if (size == 0) return 0.0; //Если вдруг массив нулевой.
    if (values == nullptr || size == 0) {
        return 0.0; // доп проверка на nullptr.
    }

    double RMS = 0.0;
    for (size_t i = 0; i < size; ++i) {
        RMS += values[i] * values[i] ;

    }
    return sqrt(RMS / size);
}

