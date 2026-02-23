#include <string>
#include <utility>  // для std::move

/*
Необходимо реализовать класс `SimpleList`, представляющий упрощенную реализацию
двусвязного списка `std::list` для строк `std::string` в динамической памяти. 
Методы вставки должны работать как с константными значениями, так и с временными.
Вставка и удаление элемента из списка при наличии указателя на элемент работает
за O(1).
--Нельзя контейнеры list string
*/
//ADL (также известный как Koenig lookup) - это правило C++, согласно которому при вызове функции компилятор ищет её не только в текущих пространствах имен, 
//но и в пространствах имен, связанных с типами аргументов.
//для пользовательских типов часто эффективнее реализовать свою версию swap (обмен указателями, а не поэлементное копирование).

class SimpleList {
private:
    struct Node {
        std::string value;
        Node* next;
        Node* prev;

        Node(const std::string& val) : value(val), next(nullptr), prev(nullptr) {}
        Node(std::string&& val) : value(std::move(val)), next(nullptr), prev(nullptr) {}
    };

    Node* based_; //это будет указатель на спец элемент, который не будет использоваться.Он служит отправной точкой для навигации по списку  Это нужно чтоб не писать потом проверки на nullptr 
    size_t size_; 
    
//метод для вставки узла перед заданным
    void Link(Node* newNode, Node* beforeThis) {
        newNode->next = beforeThis;
        newNode->prev = beforeThis->prev;
        beforeThis->prev->next = newNode;
        beforeThis->prev = newNode;
        ++size_;
    }
    
//метод для удаления узла из списка
    void Unlink(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        --size_;
        delete node;
    }
    
public:
    SimpleList() : size_(0) {
        based_ = new Node("");  //какой-то элемент
        based_->next = based_;  
        based_->prev = based_;   
    }
    
//конс-р копир-я
    SimpleList(const SimpleList& other) : SimpleList() {
        Node* current = other.based_->next;
        while (current != other.based_) {
            PushBack(current->value);
            current = current->next;
        }
    }
    
//конс-р перемещнения
    SimpleList(SimpleList&& other) noexcept 
        : based_(other.based_), size_(other.size_) {
        other.based_ = new Node("");
        other.based_->next = other.based_;
        other.based_->prev = other.based_;
        other.size_ = 0;
    }
    
//опер коп. присва-я
    SimpleList& operator=(const SimpleList& other) {
        if (this != &other) {
            SimpleList temp(other);
            Swap(temp);
        }
        return *this;
    }
    
//опер перемещ. присваивания
    SimpleList& operator=(SimpleList&& other) noexcept {
        if (this != &other) {
            Clear(); 
            delete based_;
            
            based_ = other.based_;
            size_ = other.size_;
            
            other.based_ = new Node("");
            other.based_->next = other.based_;
            other.based_->prev = other.based_;
            other.size_ = 0;
        }
        return *this;
    }

    ~SimpleList() {
        Clear();
        delete based_;
    }

    
    void Swap(SimpleList& other) noexcept {
        std::swap(based_, other.based_);
        std::swap(size_, other.size_);
    }
    
    size_t Size() const {
        return size_;
    }
    
    bool Empty() const {
        return size_ == 0;
    }
    
    void PushBack(const std::string& value) {
        Node* newNode = new Node(value);
        Link(newNode, based_); 
    }
    
    void PushBack(std::string&& value) {
        Node* newNode = new Node(std::move(value));
        Link(newNode, based_);
    }

    void PushFront(const std::string& value) {
        Node* newNode = new Node(value);
        Link(newNode, based_->next); 
    }
    
    void PushFront(std::string&& value) {
        Node* newNode = new Node(std::move(value));
        Link(newNode, based_->next);
    }

    void PopBack() {
        if (!Empty()) {
            Unlink(based_->prev);
        }
    }
    
    void PopFront() {
        if (!Empty()) {
            Unlink(based_->next);
        }
    }
    
    std::string& Front() {
        return based_->next->value;
    }
    
    const std::string& Front() const {
        return based_->next->value;
    }
    
    std::string& Back() {
        return based_->prev->value;
    }
    
    const std::string& Back() const {
        return based_->prev->value;
    }
    
    void Clear() {
        while (!Empty()) {
            PopFront();
        }
    }
};

// Внешняя функция swap для ADL
void Swap(SimpleList& lhs, SimpleList& rhs) noexcept {
    lhs.Swap(rhs);
}