#include<graphics.h>//ͼ�ο�ͷ�ļ�
#include<mmsystem.h>//��ý���豸ͷ�ļ�
#include<math.h>//�ж����Ҫ�õ�
#pragma comment(lib,"winmm.lib")//����������Ҫʹ�õĿ��ļ�


void initGame()//��ʼ����Ϸ
{
	initgraph(600, 500); //���ƴ���

	loadimage(NULL, "����2.jpg");  //���ر���ͼƬ

	mciSendString("open Mysoul.mp3", 0, 0, 0);//��ý����ƽӿ�
	//��ʱ�ص�����mciSendString("play Mysoul.mp3", 0, 0, 0);

	//����������ɫ
	setlinecolor(BLACK);

	//��������
	for (int i = 25; i<=500;i+=25)
	{ 
		line(i, 0, i, 500);
		line(0, i,500,i);
	}
	line(501, 0, 501, 500);

	//�������
	outtextxy(505, 100, "�����ȣ�����");
	outtextxy(505, 300, "�����棺����");
}

//����
void Playchess()
{
	//���
	MOUSEMSG mouse;//���������Ϣ�Ľṹ��

	int x, y;
	int a, b;

	while (1)
	{
		

		mouse = GetMouseMsg();//��ȡ�����Ϣ


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
			//Ϊ��ȷ���ڽ������
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