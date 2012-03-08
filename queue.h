#ifndef QUEUE_H
#define QUEUE_H

#define block_size 64 //������ ����� ������������� 64 �������� ��� � �������������� �� �����

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
            int counter_begin;//������� � ����� ������
            int counter_end;//������� � ����� �����
        };
        block_list *L;
        int block_number_head;//����� ����� ������
        int block_number_end;//����� ����� �����
        int number_of_blocks;//������ ����� ������
        int reallocation();//����������������� ������
    public:
        queue();
        ~queue();
        T &up();// �������
        int down(T &elem);//��������
        int IsEmpty();//�������� �� �������
};


template<class T> queue<T>::queue()
{
    L =  (block_list*) malloc(block_size * sizeof(block_list));
    for(int i = 0;i < block_size;i++) //�������������� ����� �������
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
    if((block_number_head == 0) && (block_number_end == (block_size - 1)))//����� ��� ����� ������
    {
        L = (block_list *)realloc(L,((block_number_end + 1 + block_size) * sizeof(block_list)));
        number_of_blocks = block_number_end + 1 + block_size;
        for(int i = block_number_end + 1;i < block_number_end + 1 + block_size;i++)//���������������� ����� �����
        {
            L[i].empty = 1;
            L[i].counter_begin = 0;
            L[i].counter_end = 0;
        }
        return 1;
    }

    int size = 0;//����������, ���������� ���������� ������� ������
    block_list *Staff;
    if((block_number_head > 0))//���� ��������� ����� ��� ���� ��������
    {
        size = block_number_end - block_number_head;
        int i = 0;
        if(size <= block_size)//������ ������������ ���������� ������
        {
            Staff = (block_list *)realloc(L,((block_number_end + 1 + block_size) * sizeof(block_list)));
            number_of_blocks = block_number_end + 1 + block_size;//����� ��������������� ������
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

        if(size > block_size)//������ ������������ ���������� ������
        {
            Staff = (block_list *)realloc(L,((block_number_end + 1 + 2 * block_size) * sizeof(block_list)));
            number_of_blocks = block_number_end + 1 + 2 * block_size;//����� ��������������� ������
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
    if((block_number_end == 0) && (block_number_head == 0) && (L[0].empty == 1))//������ �����
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
    if((L[block_number_end].counter_end) == block_size)//� ����� ����������� ��������
    {
        qDebug()<<"nB1";
        qDebug()<<block_number_end;
        qDebug()<<number_of_blocks;
        if((block_number_end + 1) == number_of_blocks)//���� ���������� ������ �� �������
        {
            allocation_controller = reallocation();//����� ����������������� ������
            block_number_end++;//��������� �� ��������� ����
            qDebug()<<"next Block";
            L[block_number_end].counter_begin = 0;
            L[block_number_end].m[L[block_number_end].counter_end] = elem;
            L[block_number_end].counter_end++;//���������� �������
        }
        else
        {
            qDebug()<<"nB2";
            block_number_end++;//��������� �� ��������� ����
            L[block_number_end].counter_begin = 0;
            L[block_number_end].m[L[block_number_end].counter_end] = elem;
            L[block_number_end].counter_end++;//���������� �������
        }
    }
    else//���� �� ��������
    {
        if(L[block_number_end].counter_end == 0)
        {
            L[block_number_end].empty = 0;
        }
        L[block_number_end].m[L[block_number_end].counter_end] = elem;
        L[block_number_end].counter_end++;//���������� �������
    }

    qDebug()<<L[0].m[0]<<" "<<L[0].m[1]<<" "<<L[0].m[2];
    //qDebug()<<L[0].empty<< " "<<L[1].empty;
}

template<class T> T& queue<T>::up()
{
    T r;
    if(IsEmpty() != 1)//���� �� �����
    {
        r = L[block_number_head].m[L[block_number_head].counter_begin];
        L[block_number_head].counter_begin++;//�������� ������
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
