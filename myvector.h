#ifndef MYVECTOR_H
#define MYVECTOR_H

template <class typeOf>
class MyVector
{
    public:
        //                        КОНСТРУКТОРЫ И ДЕСТРУКТОРЫ
        MyVector();                                             // Конструктор по умолчанию
        MyVector(const MyVector &vector);                       // Конструтор заполнения
        MyVector(typeOf fillElement, int repeat);               // Конструктор заполнения
        MyVector(typeOf pushElement);                           // Конструктор заполнения с одним элементов
        ~MyVector();                                            // Деструктор по умолчанию
        //                        ФУНКЦИИ РАЗМЕРА И ПАМЯТИ
        unsigned int size() const noexcept;                     // Возвращает колличество элементов в векторе
        unsigned int capacity() const noexcept;                 // Возвращает размер вектора
        bool empty() const noexcept;                            // Проверяет, пуст ли массив
        void resize(int size);                                  // Изменяет размер массива на size
        void upscale(int size);                                 // Увеличивает размер на size, с учётом свободной памяти
        void shrink_to_fit() const noexcept;                    // Сжимает размер, до совпадения

        //                   ФУНКЦИИ, УПРАВЛЯЮЩИЕ ЭЛЕМЕНТАМИ В МАССИВЕ
        void push_back(typeOf pushedBack);                      // Положить элемент в конец вектора
        void push_back(typeOf pushedBack, int repeat);          // Положить элемент в конец списка несколько раз
        void insert(typeOf element, int position);              // Вставить элемент на определённую позицию
        void insert(typeOf element, int position, int repeat);  // Вставить repeat колличество элементов на опеределённую позцию
        void pop_back();                                        // Удаляет элемент в конце массива
        void clear();                                           // Очищает вектор

        //                      ДОСТАВАНИЕ ЭЛЕМЕНТА ИЗ МАССИВА-
        typeOf &at(int index);                                  // Вернуть элемент на i номере
        typeOf &front();                                        // Вернуть первый элемент массива
        typeOf &back();                                         // Вернуть последний элемент
        typeOf *data();                                         // Вернуть указатель на начало динамического массива

        //                              ОПЕРАТОРЫ
        MyVector<typeOf> operator= (const MyVector<typeOf> &vector);

        private:
        //                           ДАННЫЕ
        struct sizeOfVector                                     // Структура управления памятью
        {
            int used;
            int lastIndex;
            int free;
            int total;
        };

        sizeOfVector memory = {0, -1, 0, 0};                    // Создание структуры, и установка всего на нуль

        typeOf * vectorContains = nullptr;                      // Создание массива, содержащего данные

        private:
        //                              ФУНКЦИИ
        void updateMemory(int action);                          // Функция управления памятью

        void copyData(typeOf* mainVector, typeOf* tempVector);  // Функция, копирующая один вектор в другой

        void updateVector();                                    // Функция, обновляющая размер вектора
};

#endif  // MYVECTOR_H
