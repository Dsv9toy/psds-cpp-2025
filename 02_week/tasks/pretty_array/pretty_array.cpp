#include <stdexcept>
#include <iostream>
#include <vector>
/*
Функция выводит целочисленный массив.
Принимает указатель на начало, конец массива ; также принимает ограничитель. 0 - нет ограничения, n - значит есть ограничение. 
Причем задается кол-во элементов, если установлен ограничитель на n элементов, то а массив имеет n+m, то после n элементов
Будет через запятую троеточие, а в новой строке отступив пробел будет выводиться продолжение.
// Массив выводится в таком виде [, , , , ]
// Также из прошлого задания little big будет реализован разворот массива, однако здесь это задается не флагом, а условием:
указатель на end < указателя begin
// немного пробегусь по реализации:
1- Нужна проверка что указатели есть и массив вообще не нулевой. Проверяем nullptr
2- Проверка указателей. Как будет строиться массив, задом наперед или в прямом направлении
3- цикл for, который принимает элементы массива, и выкидывает их в cout в красивой форме [1, 2, 3, 4]
4- Условие цикла. Нужен счётчик при котором если наш элемент по счёту > чем ограничитель, мы печатаем ... 
а затем в новой строке продолжаем перечисление элементов
5- вывод запятой не должен быть педед ]
//Было много недопонимания при продолжении печати после переноса, было принято добавить еще один аргумент в функию
некий флаг, который бы помог отличить функцию начальную, от функции которая вызвана рекурсивно. Так как тесты требуют что если задан ограничитель
то он будет всегда ограничивать одно и то же ко-во элементов, а массив может быть большим и переносов строк может быть не один. 
// Будем пользоваться вкусными методами от vector. Так проще для восприятия.
*/
void PrintArray(const int* begin, const int* end, size_t Limiter = 0, bool firstCall = true) 
{
    if (begin == nullptr || end == nullptr) { 
        std::cout << "[]" << std::endl; 
        return; 
    }
    // обратный порядок
    if (begin > end) {
        std::vector<int> reversedArray = {};
        for (const int* currentItemPtr = begin; currentItemPtr != end; --currentItemPtr) {
            reversedArray.push_back(*currentItemPtr);
        }
        
//Теперь вызываем для вектора (прямой порядок)
        if (reversedArray.empty()) {
            if (firstCall) std::cout << "[]" << std::endl;
            else std::cout << "]" << std::endl;
        } else {
            PrintArray(reversedArray.data(), reversedArray.data() + reversedArray.size(), Limiter, firstCall);
        }
        return;
    }
    
    // Прямой порядок (begin <= end)
    if (begin == end) { 
        if (firstCall) std::cout << "[]" << std::endl;
        else std::cout << "]" << std::endl;
        return; 
    }
    
    if (firstCall) std::cout << "[";
    
    size_t remaining = end - begin;
    
    if (Limiter == 0 || Limiter >= remaining) {
    // Без ограничения
        for (const int* currentItemPtr = begin; currentItemPtr != end; ++currentItemPtr) {
            if (currentItemPtr != begin) std::cout << ", ";
            std::cout << *currentItemPtr;
        }
        std::cout << "]" << std::endl;
    } else {
        // с ограничителем
        for (size_t i = 0; i < Limiter; ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << begin[i];
        }
        
        if (begin + Limiter != end) {
            std::cout << ", ...\n ";
            PrintArray(begin + Limiter, end, Limiter, false);
        } else {
            std::cout << "]" << std::endl;
        }
    }
}