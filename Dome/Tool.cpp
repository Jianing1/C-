#include<stdio.h>
#include"Tool.h"
#include <conio.h>
#include<stdlib.h>
//ÿ��time�����һ��1
int timeApperActive(int time)
{
    static int s = 0;
    int times = time/5;
    if(s == times)
    {
        s=0;
        return 1;
    }
    else
    {
        s++;
        return 0;
    }
}
//ÿ��time����һ�����ִ�1��ʼ�����ϼ�1
int timeApperNums(int time)
{
    static int s = 0;
    static int Nums = 0;
    int times = time/5;
    if(s == times)
    {
        Nums++;
        s=0;
        return Nums-1;
    }
    else
    {
        s++;
        return -1;
    }
}

//��ȡ�������
int getRandInt(int start, int end)
{
    int dis = end - start;
    return rand() % dis + start;
}

//�жϾ����Ƿ��ཻ
 bool test_collision(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
 {
     //x1 y1 x2 y2 Ϊ��һ�����������Ͻǣ������½�
     //x3 y3 x4 y4 Ϊ��һ�����������Ͻǣ������½�
    return (((x1 >= x3 && x1 < x4) || (x3 >= x1 && x3 <= x2)) &&
     ((y1 >= y3 && y1 < y4) || (y3 >= y1 && y3 <= y2))) ? true : false;
  }

