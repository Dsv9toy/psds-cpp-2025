#include <stdexcept>
#include <iostream>
/*
//Две функции: 
Одна для интов
Другая для дабл
//Принимает число возвращает число в шестрадцатиричной форме в формтате 0xYYYY;
//Нельзя использовать Сstyle Cast и контейнеры
В функцию передается вторым аргументом флаг который по запросу перевернет представление числа. Слева направо или справа налево (BE или LE). По умолчанию не инвертируем
// Для преобразования цифры в число сделаем массив всех чисел и букв для 16-ричной системы счисления
// Затем сделаем цифры символами чтобы вывести их на экран
*/
void PrintMemory(int number, bool reverseFlag = false) 
{
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&number);
    const char hexChars[] = "0123456789ABCDEF";
    
    std::cout << "0x";
    
    if (!reverseFlag) {
        for (int i = 0; i < sizeof(number); ++i) {  
            unsigned char currentByte = bytes[i];
            std::cout << hexChars[currentByte >> 4];
            std::cout << hexChars[currentByte & 0x0F];
        }
    } else {
        // С реверсом (BE)
        for (int i = sizeof(number) - 1; i >= 0; --i) {  
            unsigned char currentByte = bytes[i];
            std::cout << hexChars[currentByte >> 4];
            std::cout << hexChars[currentByte & 0x0F];
        }
    }
    std::cout << std::endl;
}


void PrintMemory(double number, bool reverseFlag = false) 
{
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&number);
    const char hexChars[] = "0123456789ABCDEF";
    
    std::cout << "0x";
    const int total_bytes = sizeof(double);
    
    if (!reverseFlag) {
        for (int i = 0; i < total_bytes; ++i) {  
            unsigned char currentByte = bytes[i];
            std::cout << hexChars[currentByte >> 4];
            std::cout << hexChars[currentByte & 0x0F];
        }
    } else {
        for (int i = total_bytes - 1; i >= 0; --i) {  
            unsigned char currentByte = bytes[i];
            std::cout << hexChars[currentByte >> 4];
            std::cout << hexChars[currentByte & 0x0F];
        }
    }
    std::cout << std::endl;
}