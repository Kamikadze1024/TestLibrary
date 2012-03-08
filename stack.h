/*
  Kashitsyn Denis (c)
  2012
  */
#ifndef STACK_H
#define STACK_H

#include <stddef.h>

template <class T> class STACK
{
    struct Item//элемент линейного списка
    {
        T elem;//сам Т элемент
        Item *previous;//указатель на предыдущий
    };

    Item *base;//указатель на базу
    Item *pointer;//указатель на элемент,с которым можно работать
    Item *temproary;//указатель,используемый при создании элемента в непуском стеке
    unsigned long int size;

public:
    STACK();
    T up();
    void down(T ForDown);
    int isEmpty();//проверка на пустоту
};

template <class T> STACK <T>::STACK():size(0){
    base = NULL;//указатели обнуляются при создании стека
    pointer = NULL;
    temproary = NULL;
}

template <class T> T STACK<T>::up()//поднять
{
    T rezult;//результат, который возвратим
    if(pointer == base)//в стеке один элемент
    {
        base = NULL;//обнуляем базовый
        rezult = pointer -> elem;//сохраняем элемент
        delete pointer;//удаляем элемент списка
        pointer = NULL;//обнуляем указатель
        size--;//убавляем число элементов
        return rezult;//возвращаем элемент
    }
    else//в стеке более одного элемента
    {
        temproary = pointer;//последний становится временным
        pointer = pointer -> previous;//теперь последний элемент отвязан от списка
        rezult = temproary -> elem;//сохраняем элемент
        delete temproary;//удаляем элемент списка
        temproary = NULL;//обнуляем указатель
        size--;//убавляем число элементов
        return rezult;//возвращаем элемент
    }
}

template <class T> void STACK <T>::down(T ForDown)//опустить
{
    if(base == NULL)//если стек пуст
    {
        base = new Item;//создаем элемент списка
        base -> previous = NULL;//обнуляем указатель на предыдущий так как это начало стека
        base -> elem = ForDown;//"подвешиваем" нужную информацию к элементу
        pointer = base;//указатель на последний и базовый одинаковые так как 1 элемент в стеке
        size++;//увеличиваем количество элементов
    }
    else
    {
        temproary = new Item;//создаем элемент списка
        temproary -> elem = ForDown;//"подвешиваем" нужную информацию к элементу
        temproary -> previous = pointer;//"привязываем" этот элемент к предыдущему
        pointer = temproary;//указатель на последний элемент обновляем в соответствии с изменениями
        temproary = NULL;//обнуляем свободный указатель
        size++;//увеличиваем количество элементов
    }
}

template <class T> int STACK <T>::isEmpty()
{
    if((base == NULL) && (pointer == NULL))//проверка на пустоту
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

#endif // STACK_H
