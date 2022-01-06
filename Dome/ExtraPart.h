#include <iostream>
#include <easyx.h>			// 引用图形库头文件
#include <conio.h>
#include<stdio.h >
#include <fstream>
#include <cassert>
#include <string>
#include <windows.h>
#include <conio.h>
#include <graphics.h>

using namespace std;
//读取开始菜单所需文件

void readTxt(string file)
{
	ifstream infile;
	infile.open(file.data());   //将文件流对象与文件连接起来
	assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行

	string s;
	while (getline(infile, s))
	{
		cout << s << endl;
	}
	infile.close();             //关闭文件输入流
}
void stopmusic();			//暂停音乐
void stopmusic()
{
	// 打开音乐
	mciSendString("open background.mp3 alias mymusic", NULL, 0, NULL);
	mciSendString("stop mymusic", NULL, 0, NULL);
	mciSendString("close mymusic", NULL, 0, NULL);
}
//开始菜单
int menus()
{
	//readTxt("4.txt");
	while (true)
	{
		char begintitle[] = "           press any key to start...          ";
		cout << begintitle;

		Sleep(500);

		for (int i = 0; i < strlen(begintitle); i++)
			cout << "\b \b";

		Sleep(25);

		if (_kbhit())
			break;
	}

	system("cls");   //清屏，进入加载界面
	readTxt("5.txt");
	for (int i = 0; i <= 80; i++)
	{
		cout << '>';
		Sleep(25);
	}
	system("cls");  //加载完成清屏
	return 0;

}

// 暂停菜单
void Quit()
{
	stopmusic();
	setfillcolor(0x55FF55);
	for (int i = 0; i < 20; i++)                                                 //绘制框架
	{
		fillrectangle(200 + i * 20, 200, 200 + i * 20 + 20, 220);
	}
	for (int i = 0; i < 20; i++)
	{
		fillrectangle(200 + i * 20, 400, 200 + i * 20 + 20, 420);
	}
	for (int i = 0; i < 10; i++)
	{
		fillrectangle(200, 200 + i * 20, 220, 220 + i * 20 + 20);
	}
	for (int i = 0; i < 10; i++)
	{
		fillrectangle(200 + 19 * 20, 200 + i * 20, 220 + 19 * 20, 220 + i * 20 + 20);
	}
	outtextxy(350, 250, "ENTER 回到游戏");
	outtextxy(350, 280, "  R   重新开始");
	outtextxy(350, 310, " ESC  退出游戏");

}

//死亡画面
void Death()
{
	setfillcolor(RED);
	for (int i = 0; i < 20; i++)                                                 //绘制框架
	{
		fillrectangle(200 + i * 20, 200, 200 + i * 20 + 20, 220);
	}
	for (int i = 0; i < 20; i++)
	{
		fillrectangle(200 + i * 20, 400, 200 + i * 20 + 20, 420);
	}
	for (int i = 0; i < 10; i++)
	{
		fillrectangle(200, 200 + i * 20, 220, 220 + i * 20 + 20);
	}
	for (int i = 0; i < 10; i++)
	{
		fillrectangle(200 + 19 * 20, 200 + i * 20, 220 + 19 * 20, 220 + i * 20 + 20);
	}
	outtextxy(350, 250, "你死了");
	

}