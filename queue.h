#ifndef QUEUE_H
#define QUEUE_H

#define block_size 64 //размер блока устанавливаем 64 элемента оно и первоначальное их число

#include <stddef.h>
#include <stdlib.h>

#include <QDebug>


template <class T> class queue
{
    private:
        struct block_list
        {
            T m[block_size];
            int empty;
            int counter_begin;//счетчик в блоке начало
            int counter_end;//счетчик в блоке конец
        };
        block_list *L;
        int block_number_head;//номер блока начало
        int block_number_end;//номер блока конец
        int number_of_blocks;//хранит число блоков
        int reallocation();//перераспределение памяти
    public:
        queue();
        ~queue();
        T &up();// поднять
        int down(T &elem);//опустить
        int IsEmpty();//проверка на пустоту
};


template<class T> queue<T>::queue()
{
    L =  (block_list*) malloc(block_size * sizeof(block_list));
    for(int i = 0;i < block_size;i++) //инициализируем блоки пустыми
    {
        L[i].empty = 1;
        L[i].counter_begin = 0;
        L[i].counter_end = 0;
    }
    block_number_head = 0;
    block_number_end = 0;
    number_of_blocks = block_size;
}

template<class T> queue<T>::~queue()
{
    free(L);
}

template<class T> int queue<T>::reallocation()
{
    if((block_number_head == 0) && (block_number_end == (block_size - 1)))//когда все блоки полные
    {
        L = (block_list *)realloc(L,((block_number_end + 1 + block_size) * sizeof(block_list)));
        number_of_blocks = block_number_end + 1 + block_size;
        for(int i = block_number_end + 1;i < block_number_end + 1 + block_size;i++)//доинициализируем новые блоки
        {
            L[i].empty = 1;
            L[i].counter_begin = 0;
            L[i].counter_end = 0;
        }
        return 1;
    }

    int size = 0;//переменная, содержащая количество занятых блоков
    block_list *Staff;
    if((block_number_head > 0))//если начальные блоки или блок свободны
    {
        size = block_number_end - block_number_head;
        int i = 0;
        if(size <= block_size)//меньше стандартного количества блоков
        {
            Staff = (block_list *)realloc(L,((block_number_end + 1 + block_size) * sizeof(block_list)));
            number_of_blocks = block_number_end + 1 + block_size;//число задействованных блоков
            memcpy(L,Staff,(block_number_end + 1 + block_size * sizeof(block_list)));
            for(i = 0;i < (block_number_end + 1 + block_size);i++)
            {
                L[i].empty = 1;
                L[i].counter_begin = 0;
                L[i].counter_end = 0;
            }
            free(Staff);
            return 2;
        }

        if(size > block_size)//больше стандартного количества блоков
        {
            Staff = (block_list *)realloc(L,((block_number_end + 1 + 2 * block_size) * sizeof(block_list)));
            number_of_blocks = block_number_end + 1 + 2 * block_size;//число задействованных блоков
            memcpy(L,Staff,((block_number_end + 1 + 2 * block_size) * sizeof(block_list)));
            for(i = 0;i < (block_number_end + 1 + 2 * block_size);i++)
            {
                L[i].empty = 1;
                L[i].counter_begin = 0;
                L[i].counter_end = 0;
            }
            free(Staff);
            return 3;
        }
    }
}

template<class T> int queue<T>::IsEmpty()
{
    if((block_number_end == 0) && (block_number_head == 0) && (L[0].empty == 1))//вообще пусто
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


template<class T> int queue<T>::down(T &elem)
{
    int allocation_controller;
    qDebug()<<"nB";
    if((L[block_number_end].counter_end) == block_size)//в блоке закончились значения
    {
        qDebug()<<"nB1";
        qDebug()<<block_number_end;
        qDebug()<<number_of_blocks;
        if((block_number_end + 1) == number_of_blocks)//если количество блоков не хватает
        {
            allocation_controller = reallocation();//вызов перераспределения памяти
            block_number_end++;//переходим на следующий блок
            qDebug()<<"next Block";
            L[block_number_end].counter_begin = 0;
            L[block_number_end].m[L[block_number_end].counter_end] = elem;
            L[block_number_end].counter_end++;//прибавляем счетчик
        }
        else
        {
            qDebug()<<"nB2";
            block_number_end++;//переходим на следующий блок
            L[block_number_end].counter_begin = 0;
            L[block_number_end].m[L[block_number_end].counter_end] = elem;
            L[block_number_end].counter_end++;//прибавляем счетчик
        }
    }
    else//блок не кончился
    {
        if(L[block_number_end].counter_end == 0)
        {
            L[block_number_end].empty = 0;
        }
        L[block_number_end].m[L[block_number_end].counter_end] = elem;
        L[block_number_end].counter_end++;//прибавляем счетчик
    }

    qDebug()<<L[0].m[0]<<" "<<L[0].m[1]<<" "<<L[0].m[2];
    //qDebug()<<L[0].empty<< " "<<L[1].empty;
}

template<class T> T& queue<T>::up()
{
    T r;
    if(IsEmpty() != 1)//если не пусто
    {
        r = L[block_number_head].m[L[block_number_head].counter_begin];
        L[block_number_head].counter_begin++;//сдвигаем начало
        //qDebug()<<L[block_number_head].counter_begin<< " "<<L[block_number_head].counter_end;
        if(L[block_number_head].counter_begin == block_size)
        {
            block_number_head++;
            L[block_number_head].empty = 1;
        }

        return r;
    }
}

#endif // QUEUE_H
