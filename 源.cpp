#include<graphics.h>//图形库头文件
#include<mmsystem.h>//多媒体设备头文件
#include<math.h>//判断落点要用到
#pragma comment(lib,"winmm.lib")//播放音乐需要使用的库文件

int flag = 0;//表示下棋次数
int board[30][20] = { 0 };//防止重叠下棋
int m = 0;
int n = 0;





void initGame()//初始化游戏
{
	initgraph(600, 500); //绘制窗口

	loadimage(NULL, "背景.jpg");  //加载背景图片

	mciSendString("open Mysoul.mp3", 0, 0, 0);//多媒体控制接口
	mciSendString("play Mysoul.mp3", 0, 0, 0);

	//设置线条颜色
	setlinecolor(BLACK);

	//绘制棋盘
	for (int i = 25; i<=475;i+=25)
	{ 
		line(i, 25, i, 475);
		line(25, i,475,i);
	}
	line(501, 0, 501, 500);

	//输出文字
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(116, 138, 152));
	solidcircle(550, 90, 25);
	solidcircle(550, 190, 25);
	solidcircle(550, 280, 25);
	solidcircle(555, 370, 25);
	solidcircle(555, 460, 25);

	outtextxy(537, 80, "悔棋");
	outtextxy(537, 180, "重开");
	outtextxy(537, 270, "帮助");
	outtextxy(540, 360, "静音");
	outtextxy(540, 450, "播放");
}

//下棋
//判断输赢的函数
int Judge(int, int);

void Remake(void)//重开一局
{
	cleardevice();
	initGame();
	for (int i = 0; i < 30; i++)
		for (int j = 0; j < 20; j++)
			board[i][j] = 0;
}

void Huiqi(void)//悔棋
{
	board[m][n] = 0;
	cleardevice();
	initGame();
	for (int i = 1; i < 30; i++)
	{
		for (int j = 1; j < 20; j++)
		{
			if (board[i][j] == 1)
			{
				setfillcolor(BLACK);
				solidcircle(i * 25, j * 25, 10);
			}
			else if (board[i][j] == 2)
			{
				setfillcolor(WHITE);
				solidcircle(i * 25, j * 25, 10);
			}

		}
	}
}
void Menu(void)
{
	MessageBox(NULL, "本游戏由曹瑞珂编写", "帮助", MB_OK);
}

void Playchess()
{
	//鼠标
	MOUSEMSG mouse;//保存鼠标消息的结构体

	int x = 0;
	int y = 0;
	int a = 0;
	int b = 0;


	while (1)
	{
		

		mouse = GetMouseMsg();//获取鼠标消息

		for (int i = 1; i < 30; i++)
		{
			for (int j = 1; j < 20; j++)
			{
				if (abs(mouse.x-i*25)<12 && abs(mouse.y-j*25)<12)
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

			if (x > 500)
			{
				if (y > 55 && y < 110)
					Huiqi();
				if (y > 155 && y < 205)
					Remake();
				if (y > 245 && y < 300)
					Menu();
				if (y > 330 && y < 390)
					mciSendString("pause Mysoul.mp3", 0, 0, 0);
				if (y > 420 && y < 480)
					mciSendString("play Mysoul.mp3", 0, 0, 0);
			}
			else if(x < 500)
			{
				if (board[a][b] != 0)//检查防止重叠下棋
				{
					MessageBox(NULL, "这里已经有棋子了，请重新选择", "提示", MB_OK);//给出提示

					continue;//推出循环重新进入
				}


				if (flag % 2 == 0)//偶数的情况
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

			}
			
			
			m = a;
			n = b;
			
			flag++;
		}

		

		if (Judge(a, b))
		{
			if (flag % 2 == 0)
			{
				MessageBox(NULL, "白棋胜利", "游戏结束", MB_OK);
				exit(0);
			}
			else
			{
				MessageBox(NULL, "黑棋胜利", "游戏结束", MB_OK);
				exit(0);	
			
			}

		}

	}
}

	int Judge(int a, int b)//判断游戏是否结束
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


	while (1);
	return 0;

}