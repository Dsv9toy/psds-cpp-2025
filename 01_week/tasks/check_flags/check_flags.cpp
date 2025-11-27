#include <cstdint>
#include <stdexcept>
#include <iostream>
/* В stdexcept есть
Класс domain_error	Этот класс служит базовым классом для всех исключений, создаваемых для сообщения об ошибке в домене.
Класс invalid_argument	Этот класс служит базовым классом для всех исключений, создаваемых для сообщения о недопустимом аргументе.
Класс length_error	Этот класс служит базовым для всех исключений, создаваемых для сообщения о попытке создания слишком длинного объекта.
Класс logic_error	Этот класс служит базовым для всех исключений, создаваемых для сообщения об ошибках, которые можно обнаружить до выполнения программы, таких как нарушение логических предварительных условий.
Класс out_of_range	Этот класс служит базовым для всех исключений, создаваемых для сообщения о том, что аргумент выходит за допустимый диапазон.
Класс overflow_error	Этот класс служит базовым для всех исключений, создаваемых для сообщения об арифметическом переполнении.
Класс range_error	Этот класс служит базовым для всех исключений, создаваемых для сообщения об ошибке в диапазоне.
Класс runtime_error	Этот класс служит базовым для всех исключений, создаваемых для сообщения об ошибках, которые можно обнаружить только при выполнении программы.
Класс underflow_error	Этот класс служит базовым для всех исключений, создаваемых для сообщения об арифметической неточности.
*/
enum class CheckFlags : uint8_t {
    NONE = 0,                                      // 0 0000000 
    TIME = (1 << 0),                               // 1 0000001
    DATE = (1 << 1),                               // 2 0000010
    USER = (1 << 2),                               // 3 0000100 
    CERT = (1 << 3),                               // 4 0001000
    KEYS = (1 << 4),                               // 5 0010000
    DEST = (1 << 5),                               // 6 0100000
    ALL = TIME | DATE | USER | CERT | KEYS | DEST  // 7 1000000
};

//        7    6  5   4  3  2  1   0     номера бит
//        128 64 32  16  8  4  2   1     степени дваойки , а вообще будет такт 127 макс число, тк 0 еще есть 
/* 
Берется битовая маска. напирмер 01010010. это значит что есть TIME, CERT, DEST

// Сначала надо сделать преобразование в число
// Если число вдруг больше - выйти из проги
// Если равно нулю - вывести пустые скобки (флаг none)
// Проверяем каждый класс, если есть совпадение - выводим его
*/
void PrintCheckFlags(CheckFlags flags) {
    
    int flagValue = static_cast<uint8_t>(flags) ; 
    bool isFirst = true; //Проверять первый элемент или нет будем так

    
    if (flagValue > static_cast<uint8_t>(CheckFlags::ALL)) return;

    if (flagValue == 0) {
        std::cout << "[]";
        return;
    }

//Прошла жесткая проверка
    std::cout << "[";

    if (flagValue & static_cast<uint8_t>(CheckFlags::TIME)) {
        if (!isFirst) {std::cout << ",";}
        std::cout << "TIME";
        isFirst = false;
    }

    
    if (flagValue & static_cast<uint8_t>(CheckFlags::DATE)) {
        if (!isFirst) {std::cout << ",";}
        std::cout << "DATE";
        isFirst = false;
    }

    
    if (flagValue & static_cast<uint8_t>(CheckFlags::USER)) {
        if (!isFirst) {std::cout << ",";}
        std::cout << "USER";
        isFirst = false;
    }

    
    if (flagValue & static_cast<uint8_t>(CheckFlags::CERT)) {
        if (!isFirst) {std::cout << ",";}
        std::cout << "CERT";
        isFirst = false;
    }

    
    if (flagValue & static_cast<uint8_t>(CheckFlags::KEYS)) {
        if (!isFirst) {std::cout << ",";}
        std::cout << "KEYS";
        isFirst = false;
    }

    if (flagValue & static_cast<uint8_t>(CheckFlags::DEST)) {
        if (!isFirst) {std::cout << ",";}
        std::cout << "DEST";
        isFirst = false; 
    }



    std::cout << "]";

}
