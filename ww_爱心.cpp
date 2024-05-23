#include<iostream>
#include<easyx.h>
#include<cmath>
#include<ctime>
#include<string>
using namespace std;
const double R = 100;
const int ONCE = 50;
const int SUM = ONCE * ONCE;
const int Window_Width = 800;
const int Window_Height = 600;
const int Exc_x = 380;
const int Exc_y = 170;
typedef struct heart
{
	int height;//心形的高度
	double angle;//与原点之间的夹角
	double r;//心形自身边缘的点距离自身原点的距离 即极半径rou
	int curR;//放大倍数
	int x;
	int y;
}heart;
//使用粒子发射器原理
//每次喷射ONCE个，使用粒子池ONCE*ONCE=SUM
heart myHeart[SUM];

void init()
{
	//创建窗口
	initgraph(Window_Width, Window_Height);
	memset(myHeart, 0, sizeof(heart) * SUM);
	//配置随机种子
	srand(time(NULL));
}
void getRandAngles(int buf[], int n)
{
	//严格：要保证这20个随机数不相同
	//随机数只能取整数
	int M = 314 * 2 * 2;
	for (int i = 0; i < n; i++)
	{
		int randTemp = 0;
		int j = 0;
		while (1)
		{
			randTemp = rand() % M;
			for (j = 0; j < i && buf[j] != randTemp; j++);
			if (j >= i)
				break;
		}
		buf[i] = randTemp;
	}
}
void addNewHeart()
{
	//从心形池中取出20个没有使用过的心
	int k = 0;
	for (k = 0; k < SUM && myHeart[k].curR>0; k++);//过滤已经使用过的心
	//生成20个不相同的随机角度
	int angles[ONCE];
	getRandAngles(angles, ONCE);
	for (int i = k; i < k + ONCE && i <= SUM; i++)//连续创建20个爱心
	{
		myHeart[i].angle = angles[i - k] * 0.01;
		myHeart[i].r = (sin(myHeart[i].angle) * sqrt(fabs(cos(myHeart[i].angle)))) /
			(sin(myHeart[i].angle) + 1.4142) - 2 * sin(myHeart[i].angle) + 2;
		myHeart[i].curR = R;
		myHeart[i].height = 0;
		myHeart[i].x = myHeart[i].curR * myHeart[i].r * cos(myHeart[i].angle) + Exc_x;
		myHeart[i].y = -myHeart[i].curR * myHeart[i].r * sin(myHeart[i].angle) + Exc_y;
	}
}
void updateWindow()
{
	BeginBatchDraw();
	cleardevice();
	settextcolor(RGB(255, 153, 255));
	for (int i = 0; i < SUM; i++)
	{
		if (myHeart[i].curR == 0)
			continue;
		//设置字体
		//settextstyle(myHeart[i].height + 15, 0, "Webdings");
		settextstyle(myHeart[i].height + 15, 0, "楷体");
		//设置背景透明
		setbkmode(TRANSPARENT);
		//输出字体
		//outtextxy(myHeart[i].x + 10, myHeart[i].y - 80, "Y");
		outtextxy(myHeart[i].x + 10, myHeart[i].y - 80, ".");
	}
	string str = "520";
	settextstyle(150, 0, str.c_str());
	int tx = (Window_Width - textwidth(str.c_str())) / 2;
	int ty = (Window_Height - textheight(str.c_str())) / 2 - 100;
	outtextxy(tx, ty, str.c_str());
	EndBatchDraw();
}
void modifyData()
{
	for (int i = 0; i < SUM; i++)
	{
		if (myHeart[i].curR == 0)
			continue;
		myHeart[i].curR++;
		if (myHeart[i].curR > (R + 35))
		{
			memset(&myHeart[i], 0, sizeof(heart));
		}
		myHeart[i].height++;
		myHeart[i].x = myHeart[i].curR * myHeart[i].r * cos(myHeart[i].angle) + Exc_x;
		myHeart[i].y = -myHeart[i].curR * myHeart[i].r * sin(myHeart[i].angle) + Exc_y;
	}
}
int main()
{
	init();
	while (1)//注释：myheart的400个心形都被使用后就满掉了
	{
		addNewHeart();
		//刷新画面
		updateWindow();
		//修改数据
		modifyData();
		//暂停
		Sleep(20);
	}
	system("pause");
	return 0;
}
