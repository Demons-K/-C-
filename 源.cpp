#include <graphics.h>			  //ͼ�ο�ͷ�ļ�
#include <mmsystem.h>			  //��ý���豸ͷ�ļ�
#include <math.h>				  //�ж����Ҫ�õ�
#pragma comment(lib, "winmm.lib") //����������Ҫʹ�õĿ��ļ�

int flag = 0;			 //��ʾ�������
int board[20][20] = {0}; //��ֹ�ص�����

void initGame() //��ʼ����Ϸ
{
	initgraph(600, 500); //���ƴ���

	loadimage(NULL, "����2.jpg"); //���ر���ͼƬ

	mciSendString("open Mysoul.mp3", 0, 0, 0); //��ý����ƽӿ�
	//��ʱ�ص�����mciSendString("play Mysoul.mp3", 0, 0, 0);

	//����������ɫ
	setlinecolor(BLACK);

	//��������
	for (int i = 25; i <= 500; i += 25)
	{
		line(i, 0, i, 500);
		line(0, i, 500, i);
	}
	line(501, 0, 501, 500);

	//�������
	outtextxy(505, 100, "�����ȣ�����");
	outtextxy(505, 300, "�����棺����");
}

//����
//�ж���Ӯ�ĺ���
int Judge(int, int);

void Playchess()
{
	//���
	MOUSEMSG mouse; //���������Ϣ�Ľṹ��

	int x, y;
	int a, b;

	while (1)
	{

		mouse = GetMouseMsg(); //��ȡ�����Ϣ

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

			if (board[a][b] != 0) //����ֹ�ص�����
			{
				MessageBox(NULL, "�����Ѿ��������ˣ�������ѡ��", "��ʾ", MB_OK); //������ʾ

				continue; //�Ƴ�ѭ�����½���
			}

			if (flag % 2 == 0) //ż�������
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
				MessageBox(NULL, "������ʤ��", "��Ϸ����", MB_OK);
				exit(0);
			}
			else
			{
				MessageBox(NULL, "������ʤ��", "��Ϸ����", MB_OK);
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