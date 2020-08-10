#ifndef MYVECTOR_H
#define MYVECTOR_H

template <class typeOf>
class MyVector
{
    public:
        MyVector();
        ~MyVector();
//                        ФУНКЦИИ РАЗМЕРА И ПАМЯТИ
        unsigned int size() const noexcept;            // Возвращает колличество элементов в векторе
        unsigned int capacity() const noexcept;        // Возвращает размер вектора
        bool empty() const noexcept;
        void resize(int size); // Изменяет размер массива на size
        void shrink_to_fit();  // Сжимает размер, до совпадения

//                   ФУНКЦИИ, УПРАВЛЯЮЩИЕ ЭЛЕМЕНТАМИ В МАССИВЕ
        void push_back(typeOf pushedBack); // Положить элемент в конец вектора
        void pop_back();                   // Удаляет элемент в конце массива
        void clear();                      // Очищает вектор

//                      ДОСТАВАНИЕ ЭЛЕМЕНТА ИЗ МАССИВА-
        typeOf at(int index);   // Вернуть элемент на i номере
        typeOf front();         // Вернуть первый элемент массива
        typeOf back();          // Вернуть последний элемент

        private:
//                           ДАННЫЕ
        struct sizeOfVector // Структура управления памятью
        {
            int used;
            int lastIndex;
            int free;
            int total;
        };

        sizeOfVector memory = {0, -1, 0, 0}; // Создание структуры, и установка всего на нуль

        typeOf * vectorContains = nullptr; // Создание массива, содержащего данные

        protected:
//                              ФУНКЦИИ
        void updateMemory(int action); // Функция управления памятью

        void copyData(typeOf* mainVector, typeOf* tempVector); // Функция, копирующая один вектор в другой

        void updateVector();                                // Функция, обновляющая размер вектора
};

#endif // MYVECTOR_H
