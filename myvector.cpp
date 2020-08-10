#include "myvector.h"
#include <iostream>

template<class typeOf>
MyVector<typeOf>::MyVector() //Конструктор
{

}

template<class typeOf>
MyVector<typeOf>::~MyVector()
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
    return sizeof (memory) + sizeof (typeOf) * memory.total; //Вернуть количество занятой памяти
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

template <class typeOf>
void MyVector<typeOf>::shrink_to_fit()
{
    if(memory.free)
    {
        this->resize(memory.total - memory.free);
    }
}

template<class typeOf>
void MyVector<typeOf>::push_back(typeOf pushedBack)             // Положить элемент в конец вектора
{
    if(!memory.free)                                            // если память не свободна
    {
        updateMemory(1);                                     // увеличить на 1, и сразу её занять
    }

    else
    {
        memory.used++;
        updateMemory(0);
    }

    updateVector();                                             // Обновление размера вектора

    vectorContains[memory.lastIndex] = pushedBack;       // На последнюю позицию ложатся данные

    memory.lastIndex++;
}

template<class typeOf>
void MyVector<typeOf>::pop_back()             // Положить элемент в конец вектора
{
    if(memory.total > 0)
    {
        memory.total--;                             //Уменьшить память

        if(!memory.free)
            memory.used--;

        updateMemory(0);                            // Обновление свободной памяти
        updateVector();                             // Обновление размера вектора
        memory.lastIndex--;
    }
}

template<class typeOf>
void MyVector<typeOf>::clear()                      // Очищает вектор
{
    this->resize(0);
}


template <class typeOf>
typeOf MyVector<typeOf>::at(int index)
{
    if(index > this->memory.used) //если индекс больше, чем максимальный
    {
        return typeOf(); //ничего не возвращать
    }
    else  // иначе
    {
        return vectorContains[index - 1]; //Вернуть элемент на i-1 месте
    }

}

template<class typeOf>
typeOf MyVector<typeOf>::front()
{
    if(memory.used)                         // Если есть занятая память
        return vectorContains[0];    // Вернуть первый элемеет
    else
        return typeOf(0);
}

template<class typeOf>
typeOf MyVector<typeOf>::back()
{
    if(memory.used)                                         // Если есть занятая память
        return vectorContains[memory.lastIndex - 1];     // Вернуть элемент на последнем месте
    else
        return typeOf(0);
}

template<class typeOf>
void MyVector<typeOf>::updateMemory(int action)
{
    if (action == 0)                                // 0 действие - обновить свободную память
    {
        memory.free = memory.total - memory.used;
        if(memory.free < 0)                         //Если оказалось, что свободной памяти меньше нуля
        {
            memory.free = 0;                        // Свободная пасять равна нулю
            updateMemory(2);                     // Вызывается обновление памяти, со 2 действием
            memory.lastIndex = memory.used - 1;     // Обновляется последний индекс
        }
    }
    else if (action == 1)                           //добавить память, и сразу её занять
    {
        memory.total += 1;
        memory.used += 1;
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

    vectorContains = new typeOf[memory.used]; // Основной вектор создаётся по новой, но увеличивается в размере
    copyData(vectorContains, tempVector); // возвращается значение временного вектора

    delete [] tempVector;
}
