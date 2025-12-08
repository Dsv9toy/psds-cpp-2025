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
// Тесты прошли, однако настроенный CI в гитхабе заругался на попытку сравнения знакового и беззнакового типа в цикле

*/
void PrintMemory(int number, bool reverseFlag = false) 
{
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&number);
    const char hexChars[] = "0123456789ABCDEF";
    
    std::cout << "0x";
    const int size = static_cast<int>(sizeof(number));
    
    if (!reverseFlag) {
        for (int i = 0; i < size; ++i) {  
            unsigned char currentByte = bytes[i];
            std::cout << hexChars[currentByte >> 4];
            std::cout << hexChars[currentByte & 0x0F];
        }
    } else {
        // С реверсом (BE)
        for (int i = size - 1; i >= 0; --i) {  
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
    const int size = static_cast<int>(sizeof(number));
    
    if (!reverseFlag) {
        for (int i = 0; i < size; ++i) {  
            unsigned char currentByte = bytes[i];
            std::cout << hexChars[currentByte >> 4];
            std::cout << hexChars[currentByte & 0x0F];
        }
    } else {
        for (int i = size - 1; i >= 0; --i) {  
            unsigned char currentByte = bytes[i];
            std::cout << hexChars[currentByte >> 4];
            std::cout << hexChars[currentByte & 0x0F];
        }
    }
    std::cout << std::endl;
}