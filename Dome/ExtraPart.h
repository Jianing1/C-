#include <iostream>
#include <easyx.h>			// ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include<stdio.h >
#include <fstream>
#include <cassert>
#include <string>
#include <windows.h>
#include <conio.h>
#include <graphics.h>

using namespace std;
//��ȡ��ʼ�˵������ļ�

void readTxt(string file)
{
	ifstream infile;
	infile.open(file.data());   //���ļ����������ļ���������
	assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ��������

	string s;
	while (getline(infile, s))
	{
		cout << s << endl;
	}
	infile.close();             //�ر��ļ�������
}
void stopmusic();			//��ͣ����
void stopmusic()
{
	// ������
	mciSendString("open background.mp3 alias mymusic", NULL, 0, NULL);
	mciSendString("stop mymusic", NULL, 0, NULL);
	mciSendString("close mymusic", NULL, 0, NULL);
}
//��ʼ�˵�
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

	system("cls");   //������������ؽ���
	readTxt("5.txt");
	for (int i = 0; i <= 80; i++)
	{
		cout << '>';
		Sleep(25);
	}
	system("cls");  //�����������
	return 0;

}

// ��ͣ�˵�
void Quit()
{
	stopmusic();
	setfillcolor(0x55FF55);
	for (int i = 0; i < 20; i++)                                                 //���ƿ��
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
	outtextxy(350, 250, "ENTER �ص���Ϸ");
	outtextxy(350, 280, "  R   ���¿�ʼ");
	outtextxy(350, 310, " ESC  �˳���Ϸ");

}

//��������
void Death()
{
	setfillcolor(RED);
	for (int i = 0; i < 20; i++)                                                 //���ƿ��
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
	outtextxy(350, 250, "������");
	

}