#include <iostream>
//#include "stack.h"
#include "queue.h"

using namespace std;

int main()
{
    //cout << "Hello World!" << endl;
    queue<long int> q;
    long int i = 0;
    /*q.down(i);
    i++;
    q.down(i);
    i++;
    q.down(i);*/
    long int j = 0;
    for(j = 0;j<11929349;j++)
    {
        q.down(j);
    }

   /* int k = 0;
    for(j = 0;j<60;j++)
    {
        k = q.up();
        qDebug()<<k;
    }
    for(j = 0;j<75;j++)
    {
        q.down(j);
    }

    for(j = 0;j<90;j++)
    {
        k = q.up();
        qDebug()<<k;
    }*/

    /*j = q.up();
    j = q.up();
    j = q.up();
    j = q.IsEmpty();
    qDebug()<<j;*/
    return 0;
}

