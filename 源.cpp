#include<graphics.h>//ͼ�ο�ͷ�ļ�
#include<mmsystem.h>//��ý���豸ͷ�ļ�
#include<math.h>//�ж����Ҫ�õ�
#pragma comment(lib,"winmm.lib")//����������Ҫʹ�õĿ��ļ�

int flag = 0;//��ʾ�������
int board[30][20] = { 0 };//��ֹ�ص�����
int m = 0;
int n = 0;





void initGame()//��ʼ����Ϸ
{
	initgraph(600, 500); //���ƴ���

	loadimage(NULL, "����.jpg");  //���ر���ͼƬ

	mciSendString("open Mysoul.mp3", 0, 0, 0);//��ý����ƽӿ�
	mciSendString("play Mysoul.mp3", 0, 0, 0);

	//����������ɫ
	setlinecolor(BLACK);

	//��������
	for (int i = 25; i<=475;i+=25)
	{ 
		line(i, 25, i, 475);
		line(25, i,475,i);
	}
	line(501, 0, 501, 500);

	//�������
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(116, 138, 152));
	solidcircle(550, 90, 25);
	solidcircle(550, 190, 25);
	solidcircle(550, 280, 25);
	solidcircle(555, 370, 25);
	solidcircle(555, 460, 25);

	outtextxy(537, 80, "����");
	outtextxy(537, 180, "�ؿ�");
	outtextxy(537, 270, "����");
	outtextxy(540, 360, "����");
	outtextxy(540, 450, "����");
}

//����
//�ж���Ӯ�ĺ���
int Judge(int, int);

void Remake(void)//�ؿ�һ��
{
	cleardevice();
	initGame();
	for (int i = 0; i < 30; i++)
		for (int j = 0; j < 20; j++)
			board[i][j] = 0;
}

void Huiqi(void)//����
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
	MessageBox(NULL, "����Ϸ�ɲ������д", "����", MB_OK);
}

void Playchess()
{
	//���
	MOUSEMSG mouse;//���������Ϣ�Ľṹ��

	int x = 0;
	int y = 0;
	int a = 0;
	int b = 0;


	while (1)
	{
		

		mouse = GetMouseMsg();//��ȡ�����Ϣ

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
				if (board[a][b] != 0)//����ֹ�ص�����
				{
					MessageBox(NULL, "�����Ѿ��������ˣ�������ѡ��", "��ʾ", MB_OK);//������ʾ

					continue;//�Ƴ�ѭ�����½���
				}


				if (flag % 2 == 0)//ż�������
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
				MessageBox(NULL, "����ʤ��", "��Ϸ����", MB_OK);
				exit(0);
			}
			else
			{
				MessageBox(NULL, "����ʤ��", "��Ϸ����", MB_OK);
				exit(0);	
			
			}

		}

	}
}

	int Judge(int a, int b)//�ж���Ϸ�Ƿ����
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