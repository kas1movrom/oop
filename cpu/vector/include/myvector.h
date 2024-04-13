//
// Created by romka on 12.12.2023.
//

#ifndef CPU_FINAL_MYVECTOR_H
#define CPU_FINAL_MYVECTOR_H

#include <iostream>

namespace kas {

    /**
     * @brief шаблонный класс вектор
     * @detailed шаблонный класс содержит указатель на шаблонный массив, текущий размер,
     * а также размер выделенной памяти
     * */
    template<class T>
    class vector {

    private:


        T *array_ = nullptr;

        size_t size_;
        size_t capacity_;

        static const size_t kMultiplyFactor = 2;

        /**
         * @brief ф-ция очищения массива, для каждого объекта в векторе вызывает деструктор
         * и удаляет выделенную под массив память
         * @param index количество эл-тов, которые надо удалить в векторе
         * */
        void free(size_t index) {
            for (size_t i = 0; i < index; ++i) {
                (array_ + i)->~T();
            }
            operator delete(array_);
        }

        /**
         * @brief ф-ция перераспределения памяти, выделяет память под новый массив
         * и копирует старый в новый, старая память удаляется, по умолчанию размер
         * памяти увеличивается вдвое
         * @throw std::exception кидает исключение если перемещающий конструктор кидает исключение
         * */
        void reallocation() {
            if (capacity_ == 0) {
                ++capacity_;
            }
            size_t index = 0;
            capacity_ *= kMultiplyFactor;
            auto tmp = static_cast<Pointer>(operator new(sizeof(T) * capacity_));
            try {
                for (size_t i = 0; i < size_; ++i) {
                    new (tmp + i) T(std::move(array_[i]));
                    index = i;
                }
            }
            catch (...) {
                for (size_t i = 0; i < index + 1; ++i) {
                    (tmp + i)->~T();
                }
                operator delete(tmp);
                capacity_ /= kMultiplyFactor;
                throw;
            }
            free(size_);
            array_ = tmp;
        }

        /**
         * @brief ф-ция перераспределения памяти, выделяет новую память под массив
         * выделяет столько памяти, сколько указал пользователь
         * @param size новый размер выделенной памяти
         * @throw std::exception если перемещающий конструктор данного типа кидает
         * исключение
         * */
        void reallocation(size_t size) {
            if (size == 0) {
                capacity_ = 0;
                size_ = 0;
                array_ = nullptr;
                return;
            }
            size_t index = 0;
            auto tmp = static_cast<Pointer>(operator new(sizeof(T) * size));
            try {
                for (size_t i = 0; i < size_; ++i) {
                    new (tmp + i) T(std::move(array_[i]));
                    index = i;
                }
            }
            catch (...) {
                for (size_t i = 0; i < index + 1; i++) {
                    (tmp + i)->~T();
                }
                operator delete(tmp);
                throw;
            }
            free(size_);
            capacity_ = size;
            std::swap(array_, tmp);
        }

        /**
         * @brief ф-ция перераспределения памяти, увеличивает размер памяти вдвое
         * заполняет новый элемент переданным, с помощью std::forward получаем rvalue
         * @param value передаётся lvalue/rvalue ссылка
         * @throw std::exception если перемещающий конструктор кинул исключение
         * */
        template <typename P>
        void reallocation(P&& value) {
            if (capacity_ == 0) {
                ++capacity_;
            }
            size_t index = 0;
            capacity_ *= kMultiplyFactor;
            auto tmp = static_cast<Pointer>(operator new(sizeof(T) * capacity_));
            try {
                for (size_t i = 0; i < size_; ++i) {
                    new (tmp + i) T(std::move(array_[i]));
                    index = i;
                }
                new (tmp + size_) T(std::forward<P>(value));
            }
            catch (...) {
                for (size_t i = 0; i < index + 1; ++i) {
                    (tmp + i)->~T();
                }
                operator delete(tmp);
                capacity_ /= kMultiplyFactor;
                throw;
            }
            free(size_);
            std::swap(array_, tmp);
        }



    public:

        using ValueType = T;
        using Pointer = T *;
        using ConstPointer = const T *;
        using Reference = T &;
        using ConstReference = const T &;
        using SizeType = std::size_t;
        using Iterator = T *;
        using ConstIterator = const T *;
        using ReverseIterator = std::reverse_iterator<Iterator>;
        using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

        /**
         * @brief конструктор по умолчанию, генерирует пустой вектор
         * */
        vector() : array_(nullptr), size_(0), capacity_(0) {}

        /**
         * @brief конструктор от размера, создает вектор заданного размера, заполненный
         * значениями по умолчанию для типа
         * @param size размер вектора
         * @throw std::exception если конструктор по умолчанию кидает исключение
         * */
        explicit vector(SizeType size) : size_(size), capacity_(size) {
            if (size != 0) {
                size_t index = 0;
                array_ = static_cast<Pointer>(operator new(sizeof(ValueType) * size));
                try {
                    for (size_t i = 0; i < size; ++i) {
                        new(array_ + i) ValueType();
                        index = i;
                    }
                }
                catch (...) {
                    free(index + 1);
                    throw;
                }
            }
        }

        /**
         * @brief конструктор от размера и const lvalue ссылки, создаёт вектор заданного размера
         * и вызывает для каждого эл-0та копирующий конструктор от значения
         * @param size размер вектора
         * @param value значение типа
         * @throw std::exception в случае, если копирующий конструктор кинул исключение
         * */
        vector(SizeType size, ConstReference value) : size_(size), capacity_(size) {
            if (size != 0) {
                size_t index = 0;
                array_ = static_cast<Pointer>(operator new(sizeof(ValueType) * size));
                try {
                    for (size_t i = 0; i < size; ++i) {
                        new(array_ + i) ValueType(value);
                        index = i;
                    }
                }
                catch (...) {
                    free(index + 1);
                    throw;
                }
            }
        }

        /**
         * @brief копирующий конструктор, копирует все значения из одного вектора во
         * второй
         * @param other вектор, который надо скопировать
         * @throw std::exception в случае если копирующий конструктор для типа
         * кинул исключение
         * */
        vector(const vector &other) : size_(other.size_), capacity_(other.capacity_) {
            if (size_ != 0) {
                size_t index = 0;
                array_ = static_cast<Pointer>(operator new(sizeof(ValueType) * size_));
                try {
                    for (size_t i = 0; i < size_; ++i) {
                        new(array_ + i) ValueType(other.array_[i]);
                        index = i;
                    }
                }
                catch (...) {
                    free(index + 1);
                    throw;
                }
            }
        }

        /**
         * @brief перемещающий конструктор, перемещает указатели
         * @param other rvalue ссылка на другой вектор
         * */
        vector(vector &&other) noexcept: size_(other.size_), capacity_(other.capacity_) {
            if (size_ != 0) {
                array_ = other.array_;
            }
            other.array_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }

        /**
         * @brief оператор копирования, вызывает копирующий конструктор для
         * временного объекта и меняет их местами с вызывающим
         * @param other константный вектор, который надо скопировать
         * */
        vector &operator=(const vector &other) {
            if (this == &other) {
                return *this;
            }
            vector tmp = other;
            swap(tmp);
            return *this;
        }

        /**
         * @brief оператор перемещения, вызывает перемещающий конструктор для
         * временного объекта и меняет их местами с вызывающим
         * @param other rvalue ссылка на другой вектор
         * */
        vector& operator=(vector&& other) noexcept {
            if (this == &other) {
                return *this;
            }
            vector tmp = std::move(other);
            swap(tmp);
            return *this;
        }


        /**
         * @brief деструктор по умолчанию, для каждого объекта вызывает деструктор
         * и очищает выделенную под массив память
         * */
        ~vector() {
            for (size_t i = 0; i < size_; ++i) {
                (array_ + i)->~T();
            }
            operator delete(array_);
        }


        /**
         * @brief стандартный метод swap, меняет местами два вектора
         * @param other другой вектор, с которым нужно поменять вызывающий
         * */
        void swap(vector& other) {
            std::swap(array_, other.array_);
            std::swap(size_, other.size_);
            std::swap(capacity_, other.capacity_);
        }


        /**
         * @brief возвращает текущий размер вектора
         * @return текущий размер
         * */
        [[nodiscard]] SizeType size() const {
            return size_;
        }

        /**
         * @brief возвращает размер выделенной под массив память
         * @return размер выделенной памяти
         * */
        [[nodiscard]] SizeType capacity() const {
            return capacity_;
        }

        /**
         * @brief метод проверят вектор на пустоту
         * @return true если вектор пуст
         * */
        [[nodiscard]] bool empty() const {
            return size_ == 0;
        }


        /**
         * @brief оператор индексирования, возвращает ссылку на элемент в векторе
         * по данному индексу
         * @param index заданный индекс
         * @return reference на заданный элемент массива
         * */
        Reference operator[](SizeType index) {
            return array_[index];
        }

        /**
         * @brief оператор индексирования для константного вектора, возвращает
         * константную ссылку
         * @param index заданный индекс
         * @return const_reference на заданный элемент массива
         * */
        ConstReference operator[](SizeType index) const {
            return array_[index];
        }

        /**
         * @brief метод возвращающий ссылку на элемент по заданному индексу
         * @param index индекс запрашиваемого элемента
         * @throw std::exception кидает исключение в случае выходы за границы массива
         * @return reference на заданный элемент массива
         * */
        Reference at(SizeType index) {
            if (index >= size_) {
                throw std::out_of_range("VectorOutOfRange");
            }
            return array_[index];
        }

        /**
         * @brief метод возвращающий константную ссылку на элемент по заданному индексу
         * @param index индекс запрашиваемого элемента
         * @throw std::exception кидает исключение в случае выходы за границы массива
         * @return const_reference на заданный элемент массива
         * */
        ConstReference at(SizeType index) const {
            if (index >= size_) {
                throw std::out_of_range("VectorOutOfRange");
            }
            return array_[index];
        }

        /**
         * @brief метод возвращающий ссылку на последний элемент вектора
         * @return reference на последний элемент массива
         * */
        Reference back() {
            return array_[size_ - 1];
        }

        /**
         * @brief метод возвращающий константную ссылку на последний элемент вектора
         * @return const_reference на последний элемент вектора
         * */
        ConstReference back() const {
            return array_[size_ - 1];
        }

        /**
         * @brief метод возвращающий ссылку на первый элемент вектора
         * @return reference на первый элемент вектора
         * */
        Reference front() {
            return array_[0];
        }

        /**
         * @brief метод возвращающий константную ссылку на первый элемент вектора
         * @return const_reference на первый элемент вектора
         * */
        ConstReference front() const {
            return array_[0];
        }

        /**
         * @brief метод возвращает указатель на память под элементы
         * @return pointer на начало массива
         * */
        Pointer data() {
            return array_;
        }

        /**
         * @brief метод возвращает константный указатель на память под элементы
         * @return const_pointer на начало массива
         * */
        ConstPointer data() const {
            return array_;
        }


        /**
         * @brief метод возвращает итератор на начало вектора
         * @return iterator на начало
         * */
        Iterator begin() {
            return array_;
        }

        /**
         * @brief метод возвращает константный итератор на начало вектора
         * @return const_iteator на начало
         * */
        ConstIterator cbegin() const {
            return array_;
        }

        /**
         * @brief метод возвращает итератор на конец вектора
         * @return iterator на конец
         * */
        Iterator end() {
            return array_ + size_;
        }

        /**
         * @brief метод возвращает константный итератор на конец вектора
         * @return const_iterator на конец
         * */
        ConstIterator cend() const {
            return array_ + size_;
        }

        /**
         * @brief метод возвращает константный итератор на начало вектора, это перегрузка
         * begin() для константного вектора
         * @return const_iterator на начало
         * */
        ConstIterator begin() const {
            return cbegin();
        }

        /**
         * @brief метод возвращает константный итератор на конец вектора, это перегрузка
         * end() для константного вектора
         * @return const_iterator на конец
         * */
        ConstIterator end() const {
            return cend();
        }

        /**
         * @brief метод возвращает reverse итератор на начало вектора
         * @return reverse_iterator на начало
         * */
        ReverseIterator rbegin() {
            return static_cast<ReverseIterator>(array_ + size_);
        }

        /**
         * @brief метод возвращает reverse итератор на конец вектора
         * @return reverse_iterator на конец
         * */
        ReverseIterator rend() {
            return static_cast<ReverseIterator>(array_);
        }

        /**
         * @brief метод возвращает константный reverse итератор на начало вектора, это перегрузка
         * rbegin() для константного вектора
         * @return const_reverse_iterator на начало
         * */
        ConstReverseIterator rbegin() const {
            return static_cast<ConstReverseIterator>(cend());
        };

        /**
         * @brief метод возвращает константный reverse итератор на конец вектора, это перегрузка
         * rend() для константного вектора
         * @return const_reverse_iterator на конец
         * */
        ConstReverseIterator rend() const {
            return static_cast<ConstReverseIterator>(cbegin());
        }

        /**
         * @brief метод возвращает константный reverse итератор на начало вектора
         * @return const_reverse_iterator на начало
         * */
        ConstReverseIterator crbegin() const {
            return rbegin();
        }

        /**
         * @brief метод возвращает константный reverse итератор на конец вектора
         * @return const_reverse_iterator на конец
         * */
        ConstReverseIterator crend() const {
            return rend();
        }


        /**
         * @brief оператор сравнения меньше, лексикографическое сравнение с другим вектором
         * @param other сравниваемый константный вектор
         * @return результат сравнения
         * */
        bool operator<(const vector& other) const {
            for (size_t i = 0; i < std::min(size_, other.size_); ++i) {
                if (array_[i] != other.array_[i]) {
                    return array_[i] < other.array_[i];
                }
            }
            return size_ < other.size_;
        }

        /**
         * @brief метод изменения текущего размера массива заданным значением
         * @param new_size новый размер вектора
         * @throw std::exception в случае если конструктор по умолчанию
         * кидает исключение
         * */
        void resize(SizeType new_size) {
            if (size_ >= new_size) {
                for (size_t i = new_size; i < size_; ++i) {
                    (array_ + i)->~T();
                }
                size_ = new_size;
                return;
            }
            if (capacity_ >= new_size) {
                for (size_t i = size_; i < new_size; ++i) {
                    new (array_ + i) T();
                }
                size_ = new_size;
                return;
            }
            auto tmp = static_cast<Pointer>(operator new(sizeof(ValueType) * new_size));
            for (size_t i = 0; i < size_; ++i) {
                new (tmp + i) ValueType(std::move(array_[i]));
            }
            try {
                for (size_t i = size_; i < new_size; ++i) {
                    new (tmp + i) ValueType();
                }
            }
            catch (...) {
                operator delete(tmp);
                throw;
            }
            free(size_);
            capacity_ = new_size;
            size_ = new_size;
            std::swap(tmp, array_);
        }

        /**
         * @brief метод, изменяющий размер вектора и заполняемый ячейки переданным
         * значением
         * @param new_size новый размер вектора
         * @param value значение, которым вектор будет заполняться
         * @throw std::exception если перемещающий конструктор кидает исключение
         * */
        void resize(SizeType new_size, ConstReference value) {
            if (size_ >= new_size) {
                for (size_t i = new_size; i < size_; ++i) {
                    (array_ + i)->~T();
                }
                size_ = new_size;
                return;
            }
            if (capacity_ >= new_size) {
                for (size_t i = size_; i < new_size; ++i) {
                    new (array_ + i) T(std::move(value));
                }
                size_ = new_size;
                return;
            }
            auto tmp = static_cast<Pointer>(operator new(sizeof(ValueType) * new_size));
            for (size_t i = 0; i < size_; ++i) {
                new (tmp + i) T(std::move(array_[i]));
            }
            size_t mark = 0;
            try {
                for (size_t i = size_; i < new_size; ++i) {
                    new (tmp + i) T(std::move(value));
                    mark = i;
                }
            }
            catch (...) {
                for (size_t i = 0; i < mark; ++i) {
                    (tmp + i)->~T();
                }
                operator delete(tmp);
                throw;
            }
            free(size_);
            capacity_ = new_size;
            size_ = new_size;
            std::swap(tmp, array_);
        }


        /**
         * @brief метод, сбрасывающий массив, вызывает деструкторы для всех объектов
         * устанавливает значение размера на ноль
         * */
        void clear() {
            for (size_t i = 0; i < size_; ++i) {
                (array_ + i)->~T();
            }
            size_ = 0;
        }


        /**
         * @brief метод, изменяющий размер выделенной памяти на текущий размер массива
         * */
        void shrink_to_fit() {
            if (size_ == 0) {
                operator delete(array_);
                array_ = nullptr;
            }
            reallocation(size_);
            capacity_ = size_;
        }


        /**
         * @brief метод, выделяющий под вектор заданное количество памяти
         * @param new_cap новый размер памяти вектора
         * */
        void reserve(size_t new_cap) {
            if (new_cap > capacity_) {
                reallocation(new_cap);
            }
        }


        /**
         * @brief метод, извлекающий из вектора последний элемент
         * */
        void pop_back() {
            (array_ + (size_--) - 1)->~T();
        }

        /**
         * @brief метод, добавляющий в вектор элемент, составленный из заданных аргументов
         * @param args пакет аргументов, из которых конструируется объект данного типа
         * */
        template <typename... Args>
        void emplace_back(Args&&... args) {
            if (size_ >= capacity_) {
                reallocation();
            }
            new (array_ + (size_++)) T(std::forward<Args>(args)...);
        }

        /**
         * @brief метод, добавляющий элемент в конец вектора
         * @param value объект данного типа, который будем добавлять
         * @throw std::exception если копирующий конструктор кинул исключение
         * */
        void push_back(ConstReference value) {
            if (size_ >= capacity_) {
                reallocation(value);
                ++size_;
                return;
            }
            try {
                new (array_ + size_) T(value);
                ++size_;
            }
            catch (...) {
                (array_ + size_)->~T();
                throw;
            }
        }

        /**
         * @brief добавляет элемент в конец вектора, получает rvalue ссылку
         * @param value rvalue ссылка на объект данного типа
         * @throw std::exception если перемещающий конструктор кинул исключение
         * */
        void push_back(T&& value) {
            if (size_ >= capacity_) {
                reallocation(std::move(value));
                ++size_;
                return;
            }
            try {
                new (array_ + size_) T(std::move(value));
                ++size_;
            }
            catch (...) {
                (array_ + size_)->~T();
                throw;
            }
        }
    };

    /**
     * @brief шаблонный оператор сравнения двух векторов
     * @param first первый вектор
     * @param second второй вектор
     * @return результат сравнения
     * */
    template <typename T>
    bool operator==(const vector<T>& first, const vector<T>& second) {
        return (first <= second) && (first >= second);
    }

    /**
     * @brief шаблонный оператор сравнения > двух векторов
     * @param first первый вектор
     * @param second второй вектор
     * @return результат сравнения
     * */
    template <typename T>
    bool operator>(const vector<T>& first, const vector<T>& second) {
        return second < first;
    }

    /**
     * @brief шаблонный оператор сравнения <= двух векторов
     * @param first первый вектор
     * @param second второй вектор
     * @return результат сравнения
     * */
    template <typename T>
    bool operator<=(const vector<T>& first, const vector<T>& second){
        return !(first > second);
    }

    /**
     * @brief шаблонный оператор сравнения >= двух векторов
     * @param first первый вектор
     * @param second второй вектор
     * @return результат сравнения
     * */
    template <typename T>
    bool operator>=(const vector<T>& first, const vector<T>& second) {
        return !(first < second);
    }

    /**
     * @brief шаблонный оператор сравнения двух векторов (!=)
     * @param first первый вектор
     * @param second второй вектор
     * @return результат сравнения
     * */
    template <typename T>
    bool operator!=(const vector<T>& first, const vector<T>& second) {
        return !(first == second);
    }
}

#endif //CPU_FINAL_MYVECTOR_H
