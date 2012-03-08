/*
  Kashitsyn Denis (c)
  2012
  */
#ifndef STACK_H
#define STACK_H

#include <stddef.h>

template <class T> class STACK
{
    struct Item//������� ��������� ������
    {
        T elem;//��� � �������
        Item *previous;//��������� �� ����������
    };

    Item *base;//��������� �� ����
    Item *pointer;//��������� �� �������,� ������� ����� ��������
    Item *temproary;//���������,������������ ��� �������� �������� � �������� �����
    unsigned long int size;

public:
    STACK();
    T up();
    void down(T ForDown);
    int isEmpty();//�������� �� �������
};

template <class T> STACK <T>::STACK():size(0){
    base = NULL;//��������� ���������� ��� �������� �����
    pointer = NULL;
    temproary = NULL;
}

template <class T> T STACK<T>::up()//�������
{
    T rezult;//���������, ������� ���������
    if(pointer == base)//� ����� ���� �������
    {
        base = NULL;//�������� �������
        rezult = pointer -> elem;//��������� �������
        delete pointer;//������� ������� ������
        pointer = NULL;//�������� ���������
        size--;//�������� ����� ���������
        return rezult;//���������� �������
    }
    else//� ����� ����� ������ ��������
    {
        temproary = pointer;//��������� ���������� ���������
        pointer = pointer -> previous;//������ ��������� ������� ������� �� ������
        rezult = temproary -> elem;//��������� �������
        delete temproary;//������� ������� ������
        temproary = NULL;//�������� ���������
        size--;//�������� ����� ���������
        return rezult;//���������� �������
    }
}

template <class T> void STACK <T>::down(T ForDown)//��������
{
    if(base == NULL)//���� ���� ����
    {
        base = new Item;//������� ������� ������
        base -> previous = NULL;//�������� ��������� �� ���������� ��� ��� ��� ������ �����
        base -> elem = ForDown;//"�����������" ������ ���������� � ��������
        pointer = base;//��������� �� ��������� � ������� ���������� ��� ��� 1 ������� � �����
        size++;//����������� ���������� ���������
    }
    else
    {
        temproary = new Item;//������� ������� ������
        temproary -> elem = ForDown;//"�����������" ������ ���������� � ��������
        temproary -> previous = pointer;//"�����������" ���� ������� � �����������
        pointer = temproary;//��������� �� ��������� ������� ��������� � ������������ � �����������
        temproary = NULL;//�������� ��������� ���������
        size++;//����������� ���������� ���������
    }
}

template <class T> int STACK <T>::isEmpty()
{
    if((base == NULL) && (pointer == NULL))//�������� �� �������
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

#endif // STACK_H
