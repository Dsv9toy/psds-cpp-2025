#include <stdexcept>
#include <vector>
/*
Функция принимает отсортированный вектор std::vector<int> и возвращает уникальные элементы в порядке их встречи (то есть массив тоже будет, из тестов вижу целочисленный)
Нельзя алгоритмы
Не надо частых аллокаций
Вместимость сделать соответствующей кол-ву элементов
//Вообще можно использовать std::unique и тогда можно сделать код в раазыыы короче, но я не понимаю насколько это оправданно. Насколько этот std:unique эффективен
Написал без него, мне кажется моя версия должна быть эффективнее по памяти так как unique более тяжелая и мощная вещь. 
*/

std::vector<int> Unique(const std::vector<int>& inputArray) {
    size_t size = inputArray.size();
    if (size == 0) return {};
    
    size_t uniqueCount = 1;
    for (size_t i = 1; i < size; ++i) {
        if (inputArray[i] != inputArray[i-1]) {
            ++uniqueCount;
        }
    }

    std::vector<int> outputArray;
    outputArray.reserve(uniqueCount);
    
    outputArray.push_back(inputArray[0]);
    for (size_t i = 1; i < size; ++i) {
        if (inputArray[i] != inputArray[i-1]) {
            outputArray.push_back(inputArray[i]);
        }
    }
    
    return outputArray;
}
