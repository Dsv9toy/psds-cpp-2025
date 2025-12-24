#include <vector>

/*
Необходимо реализовать класс стек то есть обертку над вектором итнов
- Метод `Push` - добавляет элемент на верхушку стека
- Метод `Pop` - убирает элемент с верхушки стека
- Метод `Top` - обеспечивает доступ к элементу на верхушке стека 
- Метод `Empty` - возвращает результат проверки стека на отсутствие элементов  
- Метод `Size` - возвращает количество элементов в стеке
- Метод `Clear` - очищает стек
- Метод `Swap` - меняется элементами с другим стеком (без копирования)
- Оператор `==` - сравнение стека на равенство
- Оператор `!=` - сравнение стека на неравенство

Вызов метода `Pop` от пустого стека является корректной операцией. Метод должен 
возвращать `true` или `false` в зависимости от того выполнялась операция или нет.
//Значения стека должны находится в закрытой части класса
// Рекомендуется определять методы вне класса
//Некоторые методы могут потребовать перегрузки
//Обратите внимание, что при использовании в качестве полей контейнеров стандартной
//библиотеки нет необходимости писать собственные конструкторы

//Перегрузка операторов
Синтаксис: `<return_type> operator<op_symbol>(<arguments>...);`

- `<op_symbol>` - символьное обозначение оператора (`+`, `<<`, `==`, ...)
- `<arguments>...` - один или два аргумента (для унарного и бинарного операторов)
- `<return_type>` - тип возвращаемого значения

// Методы в классе это функции.
*/
//реализации методов делаются с префиксом Stack::

class Stack {
    public:
        void Push(int value);
        void Clear();
        void Swap(Stack& otherStack);
        bool Pop();
        bool Empty() const;
        int& Top();                    // Для неконстантного стека
        const int& Top() const;        // Для константного стека
        size_t Size() const;

    bool operator==(const Stack& otherStack) const;
    bool operator!=(const Stack& otherStack) const;


    private:
        std::vector<int> data; 

};

//push метод
void Stack::Push(int value) {
    data.push_back(value);
}  

//CLear метод
void Stack::Clear() {
    data.clear();

}

//Swap метод
void Stack::Swap(Stack& otherStack) {
    data.swap(otherStack.data);

}

//Pop метод
bool Stack::Pop() {
    if (Empty()) return false;

    data.pop_back();
    return true;

}

//Top меттод
int& Stack::Top() {
    static int throwMes = 0;
    if(Empty()) return throwMes;
    return data.back();
}

const int& Stack::Top() const {
    static const int throwMes = 0;
    if(Empty()) return throwMes;

    return data.back();
}

//Empty метод
bool Stack::Empty() const{
    return data.empty();

}

size_t Stack::Size() const {
    return data.size();
}

/////////////////////Перегрузка в 10G///////////////
bool Stack::operator==(const Stack& otherStack) const {
    return data == otherStack.data;
}

bool Stack::operator!=(const Stack& otherStack) const {
    return !(*this == otherStack);  // используем == тк выше уже определили его
}