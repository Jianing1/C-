#include <iostream>
#include <easyx.h>			// ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include<stdio.h>
#include <string>
#include <windows.h>
#include <graphics.h>
#include "Tool.h"
#include "ExtraPart.h"
#pragma comment(lib,"Winmm.lib")
using namespace std;


/////////////////////////////////////////////
// ���峣����ö�������ṹ�塢ȫ�ֱ��������ڿ��Ʒɻ��Ͷ�ȡ��ͣ����ʱ�İ���
/////////////////////////////////////////////
#define	CMD_UP			1
#define	CMD_DOWN		2
#define	CMD_LEFT		4
#define	CMD_RIGHT		8
#define	CMD_RETURN	    	16
#define	CMD_QUIT		64
#define CMD_SPACE       		128
const int PLANE_NORMAL = 1;       //�ɻ�������״̬
const int PLANE_ATTACK = 40;       //�ɻ�����״̬
const int PLANE_HITTED = -40;       //�ɻ������е�״̬
const int bulletLength = 10000;    ///�ӵ�����
const int enemyLength = 1000;     //��������
const int planelive = 10;     //��������


/*
	����ɻ�
*/
struct Plane                
{
	int positionX;
	int positionY;
	int Life;
	int type;
};

/*
	�����ӵ�
*/
struct Bullet				
{
	POINT position;
	int is_active;			//�ж��Ƿ񱻼���
};

/*
	�������
*/
struct Enemy
{
	POINT position;
	int is_active;			//�ж��Ƿ񱻼���
	int is_aive;
};

Plane plane;    //����һ�ܷɻ�
Enemy enemy[enemyLength];
Bullet bullet[bulletLength];      //���1w���ӵ�

/////////////////////////////////////////////
//��Ҫʹ�õ�����
/////////////////////////////////////////////
int planeX = 0;  //�ɻ�X
int planeY = 0;  //�ɻ�Y
int informationEnemyLength = 0;    //������ʾ����ĵ�������
int informationBulletLength = 0;   //������ʾ�����ʣ���ӵ�����
int informationEnemyAttacked =0;   //�����ел�������
int bulletnum = 0;			//���������
int enemynum = 0;         //�ӵ����м����



/////////////////////////////////////////////
//�������ڵ�����������
/////////////////////////////////////////////
void init();               			 //�󷽷���ʼ��
void userInput();			//�󷽷��û�����
void clear();			//�󷽷�����Ļ
void draw();			//�󷽷��ػ�
void playmusic();			//��������
void shootmusic();


/////////////////////////////////////////////
//��������
/////////////////////////////////////////////
void initBackground();
void initPlane();
void initBullet();
void initEnemy();
void initLoginInterface();
void initInformation();

/////////////////////////////////////////////
//��Ϸ���ݲ���
/////////////////////////////////////////////
void Quit();						// �˳�
int  GetCommand();					// ��ȡ��������
void DispatchCommand(int _cmd);				// �ַ���������
void OnUp();						// ����
void OnDown();						// ����
void OnLeft();						// ����
void OnRight();						// ����
void OnSpace();
void getKey();                      // ȡ���ù��ܣ����������ţ��ұ�עΪB����
void ToUpdate();					//ʵʱ��������
int GetCommand();					//��ȡ����ָ��
void DispatchCommand(int _cmd);     //����ָ��



/////////////////////////////////////////////
//����ͼ��Ĳ���
/////////////////////////////////////////////
void drawBackground();
void drawPlane();
void drawBullet();
void drawEnemy();
void drawInformation();

/////////////////////////////////////////////
//��Ϸ����
/////////////////////////////////////////////
int main()
{
	menus();     //TODO:������ط�����һ������ѡ��Ľ���
restart:       //���¿�ʼ��ת�����������Ҫ�����ӵ����ͻ��еĵ�������
	playmusic();
	init();

	int c;
loop:        //������Ϸ��ת�����
	playmusic();

	do                     //ѭ����ȡ����״̬���Ʒɻ�
	{
		clear();
		userInput();
		draw();
		FlushBatchDraw();
		c = GetCommand();
		DispatchCommand(c);
		if (plane.Life <= 0)
		{
			Death();
			Sleep(5000);
			return 0;
		}
		Sleep(5);
	} while (!(c & CMD_QUIT));

	Quit();          // ��ͣ���棻
	Sleep(300);

	while (true)                 
	{
		char d;
		d = getch();
		c = GetCommand();
		if (c & CMD_QUIT)                  //�˳���Ϸ
			break;
		if (d == char('r') || d==char('R'))// ���¿�ʼ
			goto restart;
		if (c & CMD_RETURN)                //������Ϸ
			goto loop;

	}


	return 0;
}

/*��ʼ����������
	initBackground();
	initPlane();
	initBullet();
	����easyx�����ʼ��
*/
void init()
{
	plane.Life = 3;
	plane.type = 0;
	initBackground();
	initPlane();
	initBullet();
	initEnemy();
	initLoginInterface();
	initInformation();
}

/*
	getKey();���û����ݽ��н�ȡ---���÷�������ʹ��
	��ȡ���ݷŵ���������
	ʹ��ToUpdate();����ȡ�����ݷŻؽṹ������У���ɶ����ݵĸ���
*/
void userInput()
{
	getKey();       //---���÷�������ʹ�ã���עΪBΪ����
	ToUpdate();
}

/*
	�����һ��ѭ���Ĳ���ͼ��
*/
void clear()
{
	clearrectangle(0,0,700,700);
	clearrectangle(722,22,878,678);
}

/*
	�ӽṹ�������ȡ������
	�ػ���
*/
void draw()
{
	drawPlane();
	drawBullet();
	drawEnemy();
	drawInformation();
}

/*���Ʋ��ű�������*/
void playmusic()
{
	// ������
	mciSendString("open background.mp3 alias mymusic", NULL, 0, NULL);

	// ��������
	mciSendString("play mymusic repeat", NULL, 0, NULL);

}
void shootmusic()
{
	// ������
	mciSendString("open shoot.mp3 alias mymusic", NULL, 0, NULL);
	// ��������
	mciSendString("play shoot.mp3", NULL, 0, NULL);
}
/*
	��ʼ����������
*/
void initBackground()
{
	initgraph(900, 700);	// ������ͼ���ڣ���СΪ 640x480 ����
	
}
void initPlane()
{
	plane.Life = planelive;
	planeX = 200;
	planeY = 200;
	plane.positionX = planeX;
	plane.positionY = planeY;
		//����
	
	fillrectangle(plane.positionX,plane.positionY,10+plane.positionX,10+plane.positionY);
	fillrectangle(plane.positionX,10+plane.positionY,10+plane.positionX,20+plane.positionY);
	fillrectangle(plane.positionX,20+plane.positionY,10+plane.positionX,30+plane.positionY);
	fillrectangle(plane.positionX,30+plane.positionY,10+plane.positionX,40+plane.positionY);
	fillrectangle(plane.positionX,40+plane.positionY,10+plane.positionX,50+plane.positionY);
	//�����
	fillrectangle(plane.positionX-10,40+plane.positionY,plane.positionX,50+plane.positionY);
	fillrectangle(plane.positionX-20,40+plane.positionY,plane.positionX-10,50+plane.positionY);
	fillrectangle(plane.positionX-30,40+plane.positionY,plane.positionX-20,50+plane.positionY);
	fillrectangle(plane.positionX-40,30+plane.positionY,plane.positionX-30,40+plane.positionY);
	//�һ���
	fillrectangle(plane.positionX+10,40+plane.positionY,plane.positionX+20,50+plane.positionY);
	fillrectangle(plane.positionX+20,40+plane.positionY,plane.positionX+30,50+plane.positionY);
	fillrectangle(plane.positionX+30,40+plane.positionY,plane.positionX+40,50+plane.positionY);
	fillrectangle(plane.positionX+40,30+plane.positionY,plane.positionX+50,40+plane.positionY);
}
void initBullet()
{	
	bulletnum = 0;
	for(int i=0;i<bulletLength;i++){
		bullet[i].is_active = 0;
	}
}
void initEnemy()
{
	for(int i=0;i<enemyLength;i++)
	{
		enemy[i].position.x =  getRandInt(0,640);
		enemy[i].position.y =  0;
		enemy[i].is_active = 0;
		enemy[i].is_aive = 1;
	}
}
void initLoginInterface()
{
	for(int i=0;i<20;i++)
	{
		rectangle(701+i*20,0,700+i*20+20,20);
	}
	for(int i=0;i<20;i++)
	{
		rectangle(701+i*20,680,700+i*20+20,700);
	}
	for(int i=0;i<35;i++)
	{
		rectangle(701,i*20,720,i*20+20);
	}
	for(int i=0;i<35;i++)
	{
		rectangle(880,i*20,900,i*20+20);
	}
}
void initInformation()
{
	informationEnemyLength = enemyLength;
	informationBulletLength = bulletLength;
	informationEnemyAttacked = 0;

	outtextxy(750,80,"�л�����");
	char num[20];
	sprintf(num, "%d", informationEnemyLength);
	outtextxy(750,100,num);



	outtextxy(750,120,"�ӵ�����");
	char num2[20];
	sprintf(num2, "%d", informationBulletLength);
	outtextxy(750,140,num2);


	outtextxy(750,160,"���е�������");
	char num3[20];
	sprintf(num3, "%d", informationEnemyAttacked);
	outtextxy(750,180,num3);
}

/*
	�û����뼯��  
*/

// ��ȡ��������
int GetCommand()
{
	int c = 0;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)		c |= CMD_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)	c |= CMD_RIGHT;
	if (GetAsyncKeyState(VK_UP) & 0x8000)		c |= CMD_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)		c |= CMD_DOWN;
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)	c |= CMD_QUIT;
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)	c |= CMD_RETURN;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)     c |= CMD_SPACE;

	return c;
}
void DispatchCommand(int _cmd)
{
	if (_cmd & CMD_UP)		OnUp();
	if (_cmd & CMD_DOWN)		OnDown();
	if (_cmd & CMD_LEFT)		OnLeft();
	if (_cmd & CMD_RIGHT)		OnRight();
	if (_cmd & CMD_SPACE)       		OnSpace();
}
void getKey()
{
	if(_kbhit()){
	char val  = _getch();
	switch(val)
	{
	//b�ǵ���
	case 'b':
		plane.type=40;
		bulletnum++;
		informationBulletLength--;
		bullet[bulletnum].is_active = 1;
		bullet[bulletnum].position.x = plane.positionX;
		bullet[bulletnum].position.y = plane.positionY-10;
		break;
	}
	}
}
void OnUp()
{
	if (planeY <= 0) planeY = 0; else planeY -= 3;
}
void OnDown()
{
	if (planeY >= 630) planeY = 630; else planeY += 3;
}
void OnLeft()
{
	if (planeX <= 30) planeX = 30; else planeX -= 3;
}
void OnRight()
{
	if (planeX >= 648) planeX = 648; else planeX += 3;
}
void OnSpace()
{
	plane.type = 40;
	bulletnum++;
	informationBulletLength--;
	bullet[bulletnum].is_active = 1;
	bullet[bulletnum].position.x = plane.positionX;
	bullet[bulletnum].position.y = plane.positionY - 10;
}
//��ײ���
void ToUpdate()
{
	plane.positionX = planeX;
	plane.positionY = planeY;

	//���µ���λ�ã���������������ˢ�µ��ˣ��ж��Ƿ�����ҷɻ�������ײ
	enemynum =  timeApperNums(1000);
		if(enemynum != -1)
		{
			enemy[enemynum].is_active=1;
		}
		for(int i=0;i<enemyLength;i++)
		{
			if(enemy[i].position.y>700)
			{
				enemy[i].is_active = 0;
			}
			if(enemy[i].is_active)
			{
				enemy[i].position.y  = enemy[i].position.y + 3;  //���µ���λ��
				//�ж��Ƿ�����ײ
				//��߷�����ײ
				/*
				if (plane.positionX - 40 > enemy[i].position.x && plane.positionX - 40 < enemy[i].position.x + 30 && enemy[i].position.y + 30 > plane.positionY)
				{
					plane.Life--;
					plane.type = PLANE_HITTED;
					enemy[i].is_active = 0;
				}
				else if (plane.positionX + 50 > enemy[i].position.x && plane.positionX + 50 < enemy[i].position.x + 30 && enemy[i].position.y + 30 > plane.positionY)
				{
					plane.Life--;
					plane.type = PLANE_HITTED;
					enemy[i].is_active = 0;
				}
				else if (plane.positionX+50  > enemy[i].position.x && plane.positionX-40  < enemy[i].position.x + 30 && enemy[i].position.y + 30 > plane.positionY && plane.positionY)
				{
					plane.Life--;
					plane.type = PLANE_HITTED;
					enemy[i].is_active = 0;
				}
				*/
				bool flag = test_collision(plane.positionX-40, plane.positionY, plane.positionX + 50, plane.positionY+50,enemy[i].position .x, enemy[i].position.y, enemy[i].position.x+30, enemy[i].position.y+30);
				if (flag == true)
				{
					plane.Life--;
					plane.type = PLANE_HITTED;
					enemy[i].is_active = 0;
				}
			}
		}

	//�����ӵ�λ�ã�ͬʱ�ж��Ƿ��ӵ��������ײ
	for(int i=0;i<10000;i++){
		if(bullet[i].is_active){
			if(bullet[i].position.y<0){bullet[i].is_active=0;}
			else{
			bullet[i].position.y = bullet[i].position.y - 8;
			}
			//��ײ���
			for(int j=0;j<1000;j++){
				if(enemy[j].is_active)
				{
					/*
					if(bullet[i].position.x>=enemy[j].position.x&&bullet[i].position.x+10<enemy[j].position.x+30&&bullet[i].position.y>=enemy[j].position.y&&bullet[i].position.y<=enemy[j].position.y+30)
					{
						bullet[i].is_active = 0;
						enemy[j].is_active = 0;
						informationEnemyAttacked ++;
						
					}
					if(bullet[i].position.x<=enemy[j].position.x&&bullet[i].position.x+10>enemy[j].position.x&&bullet[i].position.y>=enemy[j].position.y&&bullet[i].position.y<=enemy[j].position.y+30)
					{
						bullet[i].is_active = 0;
						enemy[j].is_active = 0;
						informationEnemyAttacked ++;
						
					}
					if(bullet[i].position.x>=enemy[j].position.x&&bullet[i].position.x+10<enemy[j].position.x+30&&bullet[i].position.y>=enemy[j].position.y&&bullet[i].position.y<=enemy[j].position.y+30)
					{
						bullet[i].is_active = 0;
						enemy[j].is_active = 0;
					}
					*/
					bool flag = test_collision(bullet[i].position.x, bullet[i].position.y, bullet[i].position.x+10, bullet[i].position.y+10, enemy[j].position.x, enemy[j].position.y, enemy[j].position.x+30, enemy[j].position.y+30);
					if (flag == true)
					{
						bullet[i].is_active = 0;
						enemy[j].is_active = 0;
						informationEnemyAttacked++;
						shootmusic();
					}
				}
			}
		}
	}

}                

/*
	�ػ�����
*/
void drawBullet()
{
	for(int i=0;i<bulletLength;i++){
		if(bullet[i].is_active){   //������ӵ����ڼ���״̬
			setlinecolor(BLACK);
			setfillcolor(WHITE);
			fillrectangle(bullet[i].position.x,bullet[i].position.y,bullet[i].position.x+10,bullet[i].position.y+10); //�����ӵ�
		}
	}
}
void drawPlane()
{
	//����
	plane.positionX = planeX;
	plane.positionY = planeY;
	//X��Y��һ����ͷ�ķ���
	setlinecolor(BLACK);
	//���ü���״̬������
	if(plane.type==0){setfillcolor(WHITE);}
	else if(1<=plane.type&&plane.type<=40){setfillcolor(GREEN);plane.type -= 5 ;}
	else if (1>= plane.type && plane.type >= -40) { setfillcolor(RED); plane.type += 2; }
	//else if(plane.type==80){setfillcolor(RED);}
	fillrectangle(plane.positionX,plane.positionY,10+plane.positionX,10+plane.positionY);
	fillrectangle(plane.positionX,10+plane.positionY,10+plane.positionX,20+plane.positionY);
	fillrectangle(plane.positionX,20+plane.positionY,10+plane.positionX,30+plane.positionY);
	fillrectangle(plane.positionX,30+plane.positionY,10+plane.positionX,40+plane.positionY);
	fillrectangle(plane.positionX,40+plane.positionY,10+plane.positionX,50+plane.positionY);
	//�����
	fillrectangle(plane.positionX-10,40+plane.positionY,plane.positionX,50+plane.positionY);
	fillrectangle(plane.positionX-20,40+plane.positionY,plane.positionX-10,50+plane.positionY);
	fillrectangle(plane.positionX-20,50+plane.positionY,plane.positionX-10,60+plane.positionY);
	fillrectangle(plane.positionX-30,40+plane.positionY,plane.positionX-20,50+plane.positionY);
	fillrectangle(plane.positionX-40,30+plane.positionY,plane.positionX-30,40+plane.positionY);
	//�һ���
	fillrectangle(plane.positionX+10,40+plane.positionY,plane.positionX+20,50+plane.positionY);
	fillrectangle(plane.positionX+20,40+plane.positionY,plane.positionX+30,50+plane.positionY);
	fillrectangle(plane.positionX+20,50+plane.positionY,plane.positionX+30,60+plane.positionY);
	fillrectangle(plane.positionX+30,40+plane.positionY,plane.positionX+40,50+plane.positionY);
	fillrectangle(plane.positionX+40,30+plane.positionY,plane.positionX+50,40+plane.positionY);
}
void drawEnemy()
{
	for(int i=0;i<enemyLength;i++)
		{
			if(enemy[i].is_active)
			{
				setfillcolor(RED);
				fillrectangle(enemy[i].position.x,enemy[i].position.y,enemy[i].position.x+30,enemy[i].position.y+30);
			}
		}
}
void drawInformation()
{
	
	outtextxy(750,80,"�л�����");
	char num[20];
	sprintf(num, "%d", informationEnemyLength);
	outtextxy(750,100,num);


	outtextxy(750,120,"�ӵ�����");
	char num2[20];
	sprintf(num2, "%d", informationBulletLength);
	outtextxy(750,140,num2);

	outtextxy(750,160,"���е�������");
	char num3[20];
	sprintf(num3, "%d", informationEnemyAttacked);
	outtextxy(750, 180, num3);


	outtextxy(750, 200, "ʣ������");
	char num4[20];
	sprintf(num4, "%d", plane.Life);
	outtextxy(750,220,num4);

	outtextxy(750, 560, "���ƣ�");
	outtextxy(750, 580, "��������");
	outtextxy(750, 600, "���������� b");
	outtextxy(750, 620, "���������� �ո�");
	outtextxy(750, 640, "��ͣ��ESC");
}
