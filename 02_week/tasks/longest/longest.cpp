#include <stdexcept>
#include <vector>

/* Функция должна находить наибольшую подпоследовательсть 
 1- функция принимает два указателя ( на начало и на конец массива символов )
 2- возвращает указатель на начало самой длинной подпоследовательности
 3- Длина подпоследовательности возвращается через третий аргумент функции. 
 4- Указатели соответствуют диапазону $[begin, end)$.
 // Если передано что-то не то, то возращается нулевой указатель nullptr
 // Если подпоследовательности наибольшие одинаковой длины - возвращается первая
*/
// .data() понадобится для указателя на начало последовательности. 
// Из тестов видно, что например СССс - это не четыре. Регистр важен.
// С цифрами тоже работаем. 
// Особенность: .append() и .push_back(). Оба добавляют что-то в конец, но .append может сразу несколько элементов добавить, а .push_back только один
// .append() в основном используется для пуша строк. по одной букве как-то долго, не так ли?)
// У нас встречаются как числа так и символы. если будем возвращать чисто int* или чисто char* то странно как-то. Надо иметь возможность и то и то.
// Тогда видимо придется перегружать функцию

const char* FindLongestSubsequence(const char* begin, const char* end, size_t& count)
    {
    if (begin == nullptr || end == nullptr || begin >= end) {
        count = 0; return nullptr;
    }
    const char* best_begin = begin;
    size_t maxLength = 1;
    const char* current_begin = begin;
    size_t currentLength = 1;

    for (const char* ptr = begin + 1; ptr != end; ++ptr) {

        if(*ptr == *(ptr - 1)) ++currentLength;
        else { // если символ сменился

            if(currentLength > maxLength){
                maxLength = currentLength;
                best_begin = current_begin;
                
            }
            current_begin = ptr;
            currentLength = 1;
        }
    }

    if(currentLength > maxLength){
    maxLength = currentLength;
    best_begin = current_begin;
    }
    count = maxLength;
    return best_begin;
}
// Вообще была идея изначально попробовать использовать template<typename SmthigType>
// Это по сути было бы приятнее, но опять же тогда появился бы вопрос. Другой разработчик если бы начал читать код, не очевидно было бы
// Функция меняет что-то или не меняет? Она принимает констатны или нет? Пришлось бы внимателньо читать код и бегло уже не пройтись по коду.
// А как я знаю уже из опыта, любая сущность должна явно отражать что она делает исходя из названия и параметров
// Перегрузка
char* FindLongestSubsequence(char* begin, char* end, size_t& count) {
    // Вызвав константную версию, приведем указатели к const
    const char* result = FindLongestSubsequence(
        static_cast<const char*>(begin),
        static_cast<const char*>(end),
        count
    );
    // А затем снимаем констатность дабы всё прошло норм
    return const_cast<char*>(result);
}
