#include<stdio.h>
#include"Tool.h"
#include <conio.h>
#include<stdlib.h>
//每隔time秒出现一个1
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
//每隔time出现一个数字从1开始，不断加1
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

//获取随机数字
int getRandInt(int start, int end)
{
    int dis = end - start;
    return rand() % dis + start;
}

//判断矩形是否相交
 bool test_collision(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
 {
     //x1 y1 x2 y2 为第一个正方形右上角，和左下角
     //x3 y3 x4 y4 为第一个正方形右上角，和左下角
    return (((x1 >= x3 && x1 < x4) || (x3 >= x1 && x3 <= x2)) &&
     ((y1 >= y3 && y1 < y4) || (y3 >= y1 && y3 <= y2))) ? true : false;
  }

