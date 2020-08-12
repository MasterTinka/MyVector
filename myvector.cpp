#include "myvector.h"
#include <iostream>

template<class typeOf>
MyVector<typeOf>::MyVector() //Конструктор по умолчанию
{

}

template<class typeOf>
MyVector<typeOf>::MyVector(const MyVector &vector)              // Конструктор копирования
{
    this->memory = vector.memory;                               // Копируется память
    this->vectorContains = vector.vectorContains;               // Копируется содержимое массива
}

template<class typeOf>
MyVector<typeOf>::MyVector(typeOf fillElement, int repeat)      // Конструктор заполнения
{
    this->push_back(fillElement, repeat);                       // Вызывается функция, кладущая в конец элемент, n-ое колличество раз
}

template<class typeOf>
MyVector<typeOf>::MyVector(typeOf pushElement)                  // Конструктор, кладущий одиночный элемент
{
    this->push_back(pushElement);                               // Вызывается функция, кладущая в конец элемент
}

template<class typeOf>
MyVector<typeOf>::~MyVector()                                   // Деструктор по умолчанию
{
    delete[] vectorContains;
}

template<class typeOf>
unsigned int MyVector<typeOf>::size() const noexcept
{
    return this->memory.total; //Вернуть сколько всего элементов в массиве
}

template<class typeOf>
unsigned int MyVector<typeOf>::capacity() const noexcept
{
    return sizeof (typeOf) * memory.total; //Вернуть количество занятой памяти
}

template<class typeOf>
bool MyVector<typeOf>::empty() const noexcept
{
    return !memory.used; // Если не занято ничего, вернётся false, если есть хоть один элемент вернётся true
}

template<class typeOf>
void MyVector<typeOf>::resize(int size)
{
    memory.total = size; // Всего занятой памяти становится size
    updateMemory(0);  // Обновляется free память
    updateVector();      // Обновляется вектор
}

template<class typeOf>
void MyVector<typeOf>::upscale(int size)
{
     this->resize(memory.total + (size - memory.free));           // Увеличивает массив на size, но при этом учитывает свободную память
}

template <class typeOf>
void MyVector<typeOf>::shrink_to_fit() const noexcept
{
    if(memory.free)                                               // Если память свободна
    {
        this->resize(memory.total - memory.free);                 // Изменить размер вектора, чтобы памяти свободной не оставалось
    }
}

template<class typeOf>
void MyVector<typeOf>::push_back(typeOf pushedBack)             // Положить элемент в конец вектора
{
    if(memory.free)                                 // Если память свободна
    {
        vectorContains[memory.used] = pushedBack;   // Положить элемент на memory.used место, т.е. на последнее доступное
        memory.used++;
        memory.lastIndex++;
        updateMemory(0);                            // Обновление memory.free
    }
    else
    {
        updateVector();                             // Обновление вектора
        vectorContains[memory.used] = pushedBack;   // На последнее место ложится элемент
        memory.lastIndex++;
        updateMemory(1);                            // Увеличение memory.total и memory.used на 1;
    }
}

template<class typeOf>
void MyVector<typeOf>::push_back(typeOf pushed_back, int repeat)    // Положить элемент в конец n-ое колличество раз
{
    this->upscale(repeat);            // Вектор увеличивается в размере, что-бы вместетить repeat колличество элементов
    for(int i = 0; i < repeat; i++)
        this->push_back(pushed_back); // Вызывается метод push_back, с определённым элементом
}

template<class typeOf>
void MyVector<typeOf>::insert(typeOf element, int position)
{
    if(position == memory.used)                         // Если вставляется на последнее место
    {
        push_back(element);                             // Просто вызывается метод push_back
    }
    else if (position == memory.used - 1)
    {
        typeOf tempElement = vectorContains[memory.lastIndex];
        this->pop_back();                               // Удалить последний элемент
        this->push_back(element);                       // Положить туда вставляемый элемент
        this->push_back(tempElement);                   // Положить убранный элемент обратно
    }
    else                                                // В любом другом случае
    {
        updateMemory(1);                                // Увеличить память на 1, и сразу её занять
        for(int i = position - 1; i < memory.used; i++) // Начиная с position элемента массива, до его конца
        {
            typeOf tempElement1, tempElement2;          // Создаётся два временных элемета
            if(i == position - 1)                       // Если это первый проход цикла
            {
                tempElement1 = vectorContains[i];       // Первый временный элемент копирует значения массива, на месте вставки
                vectorContains[i] = element;            // И заменяет его вставляемым element`ом
            }
            else
            {
                tempElement2 = vectorContains[i];       // Второй временный элемент копирует значение массива на следующем месте
                vectorContains[i] = tempElement1;       // В массив записывается элемент, стоявший на месте i-1
                tempElement1 = tempElement2;            // Первый временный элемент перенимает значение второго
            }
        }
        memory.lastIndex++;
    }
}

template<class typeOf>
void MyVector<typeOf>::insert(typeOf element, int position, int repeat)
{
    for(int i = 0; i < repeat; i++)                 // Пока i меньше числа повторов
    {
        this->insert(element, position);            // Вызывается insert с элементом и позицием
        position++;
    }
}

template<class typeOf>
void MyVector<typeOf>::pop_back()                   // Убрать элемент из конца вектора
{
    if(memory.total > 0)
    {
        vectorContains[memory.lastIndex] = 0;       // Последний элемент равняется 0
        memory.used -= 1;                           // Использованная память уменьшается на 1
        memory.lastIndex -= 1;                      // Последний индекс уменьшается на 1
        updateMemory(0);                            // Обновляется свободная память
    }
    else
    {
        throw std::out_of_range("MyVector::pop_back(), Vector is empty");
    }
}

template<class typeOf>
void MyVector<typeOf>::clear()     // Очищает вектор
{
    this->resize(0);
}


template <class typeOf>
typeOf& MyVector<typeOf>::at(int index)
{
    if(index > this->memory.total) //если индекс больше, чем максимальный
    {
        throw std::out_of_range("MyVector::at(int index), index is out of range");       //Бросаем эксепшн
    }
    else  // иначе
    {
        return vectorContains[index - 1]; //Вернуть элемент на i-1 месте
    }
}

template<class typeOf>
typeOf& MyVector<typeOf>::front()
{
    if(memory.used)                         // Если есть занятая память
        return vectorContains[0];           // Вернуть первый элемеет
    else                                    // Если нет занятой памяти
        throw std::out_of_range("MyVector::front(), Vector is empty");                 // Бросаем эксепшн
}

template<class typeOf>
typeOf& MyVector<typeOf>::back()
{
    if(memory.used)                                         // Если есть занятая память
        return vectorContains[memory.lastIndex];            // Вернуть элемент на последнем месте
    else                                                    // Если нет занятой памяти
        throw std::out_of_range("MyVector::front(), Vector is empty");                 // Бросаем эксепшн
}

template<class typeOf>
typeOf* MyVector<typeOf>::data()
{
    return vectorContains;
}

template<class typeOf>
void MyVector<typeOf>::updateMemory(int action)
{
    if (action == 0)                                // 0 действие - обновить свободную память
    {
        memory.free = memory.total - memory.used;
        if(memory.free < 0)                         // Если оказалось, что свободной памяти меньше нуля
        {
            memory.free = 0;                        // Свободная пасять равна нулю
            updateMemory(2);                        // Вызывается обновление памяти, со 2 действием
            memory.lastIndex = memory.used - 1;     // Обновляется последний индекс
        }
    }
    else if (action == 1)                           // 1 действие - увеличить занятую память на 1
    {
        if(memory.free)                             // Если память свободна
        {
            memory.total += 1;
            updateMemory(0);                        // Обновить свободную память
        }
        else                                        // Если нет свободной памяти
        {
            memory.total += 1;
            memory.used += 1;
        }
    }
    else if (action == 2)                           // 2 действие - обновить занятую память
    {
        if(memory.used > memory.total)              // Если использованной памяти больше чем общей памяти
        {
            memory.used = memory.total;             // Использованная память уменьшается до общей
        }
    }
}

template<class typeOf>
MyVector<typeOf> MyVector<typeOf>::operator=(const MyVector<typeOf> &Vector)
{
    this->memory = Vector.memory;
    this->vectorContains = Vector.vectorContains;
}

template<class typeOf>
void MyVector<typeOf>::copyData(typeOf* mainVector, typeOf* tempVector)
{
    for(int i = 0; i < memory.used - 1; i++)
    {      
        mainVector[i] = tempVector[i];
    }
}

template<class typeOf>
void MyVector<typeOf>::updateVector()
{
    typeOf * tempVector = new typeOf[memory.used]; // Создание временного вектора

    copyData(tempVector, vectorContains);       // и запись туда старого

    delete[] vectorContains;

    vectorContains = new typeOf[memory.total + 1]; // Основной вектор создаётся по новой, но увеличивается в размере
    copyData(vectorContains, tempVector); // возвращается значение временного вектора

    delete [] tempVector;
}
