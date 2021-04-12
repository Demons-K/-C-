#include<graphics.h>//图形库头文件
#include<mmsystem.h>//多媒体设备头文件
#include<math.h>//判断落点要用到
#pragma comment(lib,"winmm.lib")//播放音乐需要使用的库文件


void initGame()//初始化游戏
{
	initgraph(600, 500); //绘制窗口

	loadimage(NULL, "背景2.jpg");  //加载背景图片

	mciSendString("open Mysoul.mp3", 0, 0, 0);//多媒体控制接口
	//暂时关掉音乐mciSendString("play Mysoul.mp3", 0, 0, 0);

	//设置线条颜色
	setlinecolor(BLACK);

	//绘制棋盘
	for (int i = 25; i<=500;i+=25)
	{ 
		line(i, 0, i, 500);
		line(0, i,500,i);
	}
	line(501, 0, 501, 500);

	//输出文字
	outtextxy(505, 100, "周庆钊：白棋");
	outtextxy(505, 300, "曹瑞珂：黑棋");
}

//下棋
void Playchess()
{
	//鼠标
	MOUSEMSG mouse;//保存鼠标消息的结构体

	int x, y;
	int a, b;

	while (1)
	{
		

		mouse = GetMouseMsg();//获取鼠标消息


		for (int i = 1; i < 20; i++)
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
			solidcircle(x, y, 10);
			//为了确保在交叉点上
		}
	}
}


int main()
{
	initGame();
	Playchess();


	while (1);
	return 0;

}