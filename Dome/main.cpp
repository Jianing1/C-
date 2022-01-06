#include <iostream>
#include <easyx.h>			// 引用图形库头文件
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
// 定义常量、枚举量、结构体、全局变量、用于控制飞机和读取暂停界面时的按键
/////////////////////////////////////////////
#define	CMD_UP			1
#define	CMD_DOWN		2
#define	CMD_LEFT		4
#define	CMD_RIGHT		8
#define	CMD_RETURN	    	16
#define	CMD_QUIT		64
#define CMD_SPACE       		128
const int PLANE_NORMAL = 1;       //飞机的正常状态
const int PLANE_ATTACK = 40;       //飞机攻击状态
const int PLANE_HITTED = -40;       //飞机被击中的状态
const int bulletLength = 10000;    ///子弹数量
const int enemyLength = 1000;     //敌人数量
const int planelive = 10;     //敌人数量


/*
	构造飞机
*/
struct Plane                
{
	int positionX;
	int positionY;
	int Life;
	int type;
};

/*
	构造子弹
*/
struct Bullet				
{
	POINT position;
	int is_active;			//判断是否被激活
};

/*
	构造敌人
*/
struct Enemy
{
	POINT position;
	int is_active;			//判断是否被激活
	int is_aive;
};

Plane plane;    //定义一架飞机
Enemy enemy[enemyLength];
Bullet bullet[bulletLength];      //设计1w个子弹

/////////////////////////////////////////////
//需要使用到变量
/////////////////////////////////////////////
int planeX = 0;  //飞机X
int planeY = 0;  //飞机Y
int informationEnemyLength = 0;    //数据显示区域的敌人数量
int informationBulletLength = 0;   //数据显示区域的剩余子弹数量
int informationEnemyAttacked =0;   //被集中敌机的数量
int bulletnum = 0;			//发射的数量
int enemynum = 0;         //子弹的中间变量



/////////////////////////////////////////////
//方法用于调用其他方法
/////////////////////////////////////////////
void init();               			 //大方法初始化
void userInput();			//大方法用户输入
void clear();			//大方法清屏幕
void draw();			//大方法重画
void playmusic();			//播放音乐
void shootmusic();


/////////////////////////////////////////////
//函数声明
/////////////////////////////////////////////
void initBackground();
void initPlane();
void initBullet();
void initEnemy();
void initLoginInterface();
void initInformation();

/////////////////////////////////////////////
//游戏数据操作
/////////////////////////////////////////////
void Quit();						// 退出
int  GetCommand();					// 获取控制命令
void DispatchCommand(int _cmd);				// 分发控制命令
void OnUp();						// 上移
void OnDown();						// 下移
void OnLeft();						// 左移
void OnRight();						// 右移
void OnSpace();
void getKey();                      // 取消该功能，暂且先留着，且编注为B单发
void ToUpdate();					//实时更新数据
int GetCommand();					//获取控制指令
void DispatchCommand(int _cmd);     //发布指令



/////////////////////////////////////////////
//绘制图像的操作
/////////////////////////////////////////////
void drawBackground();
void drawPlane();
void drawBullet();
void drawEnemy();
void drawInformation();

/////////////////////////////////////////////
//游戏主体
/////////////////////////////////////////////
int main()
{
	menus();     //TODO:在这个地方加上一个上下选择的界面
restart:       //重新开始跳转到这里，不过需要重置子弹数和击中的敌人数量
	playmusic();
	init();

	int c;
loop:        //继续游戏跳转到这儿
	playmusic();

	do                     //循环读取按键状态控制飞机
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

	Quit();          // 暂停界面；
	Sleep(300);

	while (true)                 
	{
		char d;
		d = getch();
		c = GetCommand();
		if (c & CMD_QUIT)                  //退出游戏
			break;
		if (d == char('r') || d==char('R'))// 重新开始
			goto restart;
		if (c & CMD_RETURN)                //继续游戏
			goto loop;

	}


	return 0;
}

/*初始化方法调用
	initBackground();
	initPlane();
	initBullet();
	对整easyx界面初始化
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
	getKey();对用户数据进行截取---》该方法不再使用
	截取数据放到公共部分
	使用ToUpdate();将截取的数据放回结构体变量中，完成对数据的更新
*/
void userInput()
{
	getKey();       //---》该方法不再使用，编注为B为单发
	ToUpdate();
}

/*
	清除上一个循环的残余图案
*/
void clear()
{
	clearrectangle(0,0,700,700);
	clearrectangle(722,22,878,678);
}

/*
	从结构体变量中取出数据
	重绘制
*/
void draw()
{
	drawPlane();
	drawBullet();
	drawEnemy();
	drawInformation();
}

/*控制播放背景音乐*/
void playmusic()
{
	// 打开音乐
	mciSendString("open background.mp3 alias mymusic", NULL, 0, NULL);

	// 播放音乐
	mciSendString("play mymusic repeat", NULL, 0, NULL);

}
void shootmusic()
{
	// 打开音乐
	mciSendString("open shoot.mp3 alias mymusic", NULL, 0, NULL);
	// 播放音乐
	mciSendString("play shoot.mp3", NULL, 0, NULL);
}
/*
	初始化函数集合
*/
void initBackground()
{
	initgraph(900, 700);	// 创建绘图窗口，大小为 640x480 像素
	
}
void initPlane()
{
	plane.Life = planelive;
	planeX = 200;
	planeY = 200;
	plane.positionX = planeX;
	plane.positionY = planeY;
		//机身
	
	fillrectangle(plane.positionX,plane.positionY,10+plane.positionX,10+plane.positionY);
	fillrectangle(plane.positionX,10+plane.positionY,10+plane.positionX,20+plane.positionY);
	fillrectangle(plane.positionX,20+plane.positionY,10+plane.positionX,30+plane.positionY);
	fillrectangle(plane.positionX,30+plane.positionY,10+plane.positionX,40+plane.positionY);
	fillrectangle(plane.positionX,40+plane.positionY,10+plane.positionX,50+plane.positionY);
	//左机翼
	fillrectangle(plane.positionX-10,40+plane.positionY,plane.positionX,50+plane.positionY);
	fillrectangle(plane.positionX-20,40+plane.positionY,plane.positionX-10,50+plane.positionY);
	fillrectangle(plane.positionX-30,40+plane.positionY,plane.positionX-20,50+plane.positionY);
	fillrectangle(plane.positionX-40,30+plane.positionY,plane.positionX-30,40+plane.positionY);
	//右机翼
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

	outtextxy(750,80,"敌机数量");
	char num[20];
	sprintf(num, "%d", informationEnemyLength);
	outtextxy(750,100,num);



	outtextxy(750,120,"子弹数量");
	char num2[20];
	sprintf(num2, "%d", informationBulletLength);
	outtextxy(750,140,num2);


	outtextxy(750,160,"击中敌人数量");
	char num3[20];
	sprintf(num3, "%d", informationEnemyAttacked);
	outtextxy(750,180,num3);
}

/*
	用户输入集合  
*/

// 获取控制命令
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
	//b是单发
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
//碰撞检测
void ToUpdate()
{
	plane.positionX = planeX;
	plane.positionY = planeY;

	//更新敌人位置，利用随机数，随机刷新敌人，判断是否与玩家飞机发生碰撞
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
				enemy[i].position.y  = enemy[i].position.y + 3;  //更新敌人位置
				//判断是否发生碰撞
				//左边发生碰撞
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

	//更新子弹位置，同时判断是否子弹与敌人碰撞
	for(int i=0;i<10000;i++){
		if(bullet[i].is_active){
			if(bullet[i].position.y<0){bullet[i].is_active=0;}
			else{
			bullet[i].position.y = bullet[i].position.y - 8;
			}
			//碰撞监测
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
	重画集合
*/
void drawBullet()
{
	for(int i=0;i<bulletLength;i++){
		if(bullet[i].is_active){   //如果该子弹处于激活状态
			setlinecolor(BLACK);
			setfillcolor(WHITE);
			fillrectangle(bullet[i].position.x,bullet[i].position.y,bullet[i].position.x+10,bullet[i].position.y+10); //绘制子弹
		}
	}
}
void drawPlane()
{
	//机身
	plane.positionX = planeX;
	plane.positionY = planeY;
	//X，Y是一个机头的方块
	setlinecolor(BLACK);
	//利用激活状态来绘制
	if(plane.type==0){setfillcolor(WHITE);}
	else if(1<=plane.type&&plane.type<=40){setfillcolor(GREEN);plane.type -= 5 ;}
	else if (1>= plane.type && plane.type >= -40) { setfillcolor(RED); plane.type += 2; }
	//else if(plane.type==80){setfillcolor(RED);}
	fillrectangle(plane.positionX,plane.positionY,10+plane.positionX,10+plane.positionY);
	fillrectangle(plane.positionX,10+plane.positionY,10+plane.positionX,20+plane.positionY);
	fillrectangle(plane.positionX,20+plane.positionY,10+plane.positionX,30+plane.positionY);
	fillrectangle(plane.positionX,30+plane.positionY,10+plane.positionX,40+plane.positionY);
	fillrectangle(plane.positionX,40+plane.positionY,10+plane.positionX,50+plane.positionY);
	//左机翼
	fillrectangle(plane.positionX-10,40+plane.positionY,plane.positionX,50+plane.positionY);
	fillrectangle(plane.positionX-20,40+plane.positionY,plane.positionX-10,50+plane.positionY);
	fillrectangle(plane.positionX-20,50+plane.positionY,plane.positionX-10,60+plane.positionY);
	fillrectangle(plane.positionX-30,40+plane.positionY,plane.positionX-20,50+plane.positionY);
	fillrectangle(plane.positionX-40,30+plane.positionY,plane.positionX-30,40+plane.positionY);
	//右机翼
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
	
	outtextxy(750,80,"敌机数量");
	char num[20];
	sprintf(num, "%d", informationEnemyLength);
	outtextxy(750,100,num);


	outtextxy(750,120,"子弹数量");
	char num2[20];
	sprintf(num2, "%d", informationBulletLength);
	outtextxy(750,140,num2);

	outtextxy(750,160,"击中敌人数量");
	char num3[20];
	sprintf(num3, "%d", informationEnemyAttacked);
	outtextxy(750, 180, num3);


	outtextxy(750, 200, "剩余生命");
	char num4[20];
	sprintf(num4, "%d", plane.Life);
	outtextxy(750,220,num4);

	outtextxy(750, 560, "控制：");
	outtextxy(750, 580, "←→↑↓");
	outtextxy(750, 600, "单发攻击： b");
	outtextxy(750, 620, "连发攻击： 空格");
	outtextxy(750, 640, "暂停：ESC");
}
