#include <graphics.h>			  //图形库头文件
#include <mmsystem.h>			  //多媒体设备头文件
#include <math.h>				  //判断落点要用到
#pragma comment(lib, "winmm.lib") //播放音乐需要使用的库文件

int flag = 0;			 //表示下棋次数
int board[20][20] = {0}; //防止重叠下棋

void initGame() //初始化游戏
{
	initgraph(600, 500); //绘制窗口

	loadimage(NULL, "背景2.jpg"); //加载背景图片

	mciSendString("open Mysoul.mp3", 0, 0, 0); //多媒体控制接口
	//暂时关掉音乐mciSendString("play Mysoul.mp3", 0, 0, 0);

	//设置线条颜色
	setlinecolor(BLACK);

	//绘制棋盘
	for (int i = 25; i <= 500; i += 25)
	{
		line(i, 0, i, 500);
		line(0, i, 500, i);
	}
	line(501, 0, 501, 500);

	//输出文字
	outtextxy(505, 100, "周庆钊：白棋");
	outtextxy(505, 300, "曹瑞珂：黑棋");
}

//下棋
//判断输赢的函数
int Judge(int, int);

void Playchess()
{
	//鼠标
	MOUSEMSG mouse; //保存鼠标消息的结构体

	int x, y;
	int a, b;

	while (1)
	{

		mouse = GetMouseMsg(); //获取鼠标消息

		for (int i = 1; i < 20; i++)
		{
			for (int j = 1; j < 20; j++)
			{
				if (abs(mouse.x - i * 25) < 12 && abs(mouse.y - j * 25) < 12)
				{
					x = i * 25;
					y = j * 25;
					a = i;
					b = j;
				}
			}
		}
		if (mouse.uMsg == WM_LBUTTONDOWN)
		{

			if (board[a][b] != 0) //检查防止重叠下棋
			{
				MessageBox(NULL, "这里已经有棋子了，请重新选择", "提示", MB_OK); //给出提示

				continue; //推出循环重新进入
			}

			if (flag % 2 == 0) //偶数的情况
			{
				setfillcolor(BLACK);
				solidcircle(x, y, 10);
				board[a][b] = 1;
			}
			else
			{
				setfillcolor(WHITE);
				solidcircle(x, y, 10);
				board[a][b] = 2;
			}

			flag++;
		}

		if (Judge(a, b))
		{
			if (flag % 2 == 0)
			{
				MessageBox(NULL, "曹瑞珂胜利", "游戏结束", MB_OK);
				exit(0);
			}
			else
			{
				MessageBox(NULL, "周庆钊胜利", "游戏结束", MB_OK);
				exit(0);
			}
		}
	}
}

int Judge(int a, int b)
{
	int i, j;
	int t = 2 - flag % 2;
	for (i = a - 4, j = b; i <= a; i++)
	{
		if (i >= 0 && i < 16 && t == board[i][j] && t == board[i + 1][j] && t == board[i + 2][j] && t == board[i + 3][j] && t == board[i + 4][j])
			return 1;
	}
	for (i = a, j = b - 4; j <= b; j++)
	{
		if (j >= 0 && j < 16 && t == board[i][j] && t == board[i][j + 1] && t == board[i][j + 2] && t == board[i][j + 3] && t == board[i][j + 4])
			return 1;
	}
	for (i = a - 4, j = b - 4; i <= a, j <= b; i++, j++)
	{
		if (j >= 0 && j < 16 && t == board[i][j] && t == board[i + 1][j + 1] && t == board[i + 2][j + 2] && t == board[i + 3][j + 3] && t == board[i + 4][j + 4])
			return 1;
	}
	for (i = a - 4, j = b + 4; i <= a, j >= 1; i++, j--)
	{
		if (j >= 0 && j < 16 && t == board[i][j] && t == board[i + 1][j - 1] && t == board[i + 2][j - 2] && t == board[i + 3][j - 3] && t == board[i + 4][j - 4])
			return 1;
	}
	return 0;
}

int main()
{
	initGame();
	Playchess();

	while (1)
		;
	return 0;
}