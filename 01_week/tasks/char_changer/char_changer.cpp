#include <cstddef>
#include <stdexcept>
#include <cctype>   // для is функций из https://en.cppreference.com/w/cpp/string/byte.html
#include <string>
#include <iostream>

// Пересчёт символов с выводом их кол-ва - есть  . C>10 = C0  
// Замена непонятных символов (а не букв) на '_' - есть
// замена цифр на звездочки - есть 
//22 заменились на звездочки и посчитались, вывелось *2 - есть
// Пробел заменился на ',' если передать в функцию чем заменяем - есть
//err: Проблема раннего перевода в верхний регистр. мб сделать поднятие в верхний регистр после того как повторяющиеся буквы заменились на букву+цифру повторения - есть

size_t CharChanger(char array[], size_t size, char delimiter = ' ') {
    if (size == 0) return 0;

    size_t outputArray = 0;
    size_t i = 0;

    while (i < size && array[i] != '\0') {
        char currentSymb = array[i];
        
        //Смотрим пробелы
        if (currentSymb == ' ') {
            size_t spaceCounter = 1;
            while (i + spaceCounter < size && array[i + spaceCounter] == ' ') {
                spaceCounter++;
            }
            if (outputArray < size) {
                array[outputArray++] = delimiter;
            }
            i += spaceCounter;
            continue;
        }

        //Для остальных символов
        size_t sameSymbCounter = 1;
        size_t nextSymb = i + 1;
        
        while (nextSymb < size && array[nextSymb] != '\0') {
            if (array[nextSymb] == currentSymb) {
                sameSymbCounter++;
                nextSymb++;
            } else {
                break;
            }
        }

        //Преобразование символов
        char transformed = '0';
        if (std::isdigit(currentSymb)) {
            transformed = '*';
        } else if (std::islower(currentSymb)) {
            transformed = std::toupper(currentSymb);
        } else if (std::isupper(currentSymb)) {
            transformed = currentSymb;
        } else {
            transformed = '_';
        }

        //Перепись великого пассажа 
        if (outputArray < size) {
            array[outputArray++] = transformed;
        }
        
        if (sameSymbCounter > 1) {
            if (sameSymbCounter >= 10) {
                if (outputArray < size) {
                    array[outputArray++] = '0';
                }
            } else {
                if (outputArray < size) {
                    array[outputArray++] = '0' + sameSymbCounter;
                }
            }
        }

        i = nextSymb; // Для перехода к след итерации.
    }

    if (outputArray < size) {
        array[outputArray] = '\0';
    } else if (size > 0) {
        array[size - 1] = '\0';
        outputArray = size - 1;
    }

    return outputArray;
}
// //Для отладки. И проверки своих выводов
// int main() {

//     char array[] = "aAaAaA_234_ssssDdd*$$   3333a";
//     size_t size = 28;

//     CharChanger(array, size, ',');
//     std::cout << array << std::endl;
// }
