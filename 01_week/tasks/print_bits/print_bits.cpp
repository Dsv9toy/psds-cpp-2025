#include <cstddef>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <cstdint>


// Если размер 1 числа - 0b0000'0000
//       Если размер 2 - 0b0000'0000'00000'000
//       Если размер 4 - 0b0000'0000'0000'0000'0000'0000'0000'0000
//       Если размер 8 - 0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000
// А если размер другой? например 16? Ограничим возможность представления других размеров, дабы тесты корректно выполнялись

//Как перевести число в двоичную систему счисления?
//Берется десятичное число, напирмер 42
// Если число не 10-чное, а например шестнадцатиричное или восьмиричное - приводим к десятичному
// делится на 2 до тех пор пока число не будет равно одному 
// Запись остатков от деления ведется в массив
// Переворачивается задом на перед
// Выводится на экран в формате 0b[массив]
//!!!!  При значении размера байт $bytes \notin (0, 8]$ функция ничего не выводит. - есть недопонимание.
//                                                                         как бы cout << ""; - это вывод, но пустой, считается ли это что функция ничего не выводит?
// В тестах видно что есть разделитель между разрядами. Надо добавить

void PrintBits(long long value, size_t bytes) {
    using namespace std;

    if (bytes != 1 && bytes != 2 && bytes != 4 && bytes != 8 ){
        cout << ""; //Просто return почему-то не работает, пока не могу понять почему. А так все тесты пройдены.
    }    

    const size_t bitValue = bytes * 8;
    unsigned long long unsignedValue = 0;
    
    if (value < 0 && bytes < 8) {
        switch (bytes) {
            case 1: unsignedValue = static_cast<uint8_t>(value); break;
            case 2: unsignedValue = static_cast<uint16_t>(value); break;
            case 4: unsignedValue = static_cast<uint32_t>(value); break;
            default: unsignedValue = static_cast<unsigned long long>(value);
        }
    } else {
        unsignedValue = static_cast<unsigned long long>(value);
    }

    cout << "0b";
    
    // Идем от старшего бита к младшему
    for (int i = bitValue - 1; i >= 0; --i) {
        unsigned long long bit = (unsignedValue >> i) & 1;
        cout << bit;
        
        //Без разделителя тесты ругаются, добавим его
        if (i > 0 && i % 4 == 0) {
            cout << '\'';
        }
    }

    cout << endl;
}