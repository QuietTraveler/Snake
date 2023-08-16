#define _CRT_SECURE_NO_WARNINGS  1
#include"snake.h"
#include"TimerClock.h"

struct message {
	char dir;                  //方向
	int length;                //长度
	int speed;               //速度
	struct position coord[MAX];         //身体坐标
}snake;

struct foods {
	bool exist;
	int x;
	int y;
}food;
int map[Y][X];

void InitSnake()
{
		snake.coord[0].x = 13;
		snake.coord[0].y = 13;
		snake.coord[1].x = 13;
		snake.coord[1].y = 14;
		snake.speed = 1;
		snake.length = 2;
		snake.dir = 'w';
}

void InitFood()
{
		food.x = 7;
		food.y = 8;
		food.exist = true;
}

void InitMap()
{
	for (int i = 0; i < Y; i++)
	{
		for (int j = 0; j < X; j++)
		{
			if (i == 0 || j == 0 || i == Y - 1 || j == X - 1)
			{
				map[i][j] = 1;
			}
			else
			{
				map[i][j] = 0;
			}
		}
	}
}

void ProduceFood()
{
	int i = 0;
	while (!food.exist)
	{
		food.x = rand() % 23 + 1;
		food.y = rand() % 20 + 1;
		for (i = 0; i < snake.length; i++)
		{
			if (snake.coord[i].x == food.x && snake.coord[i].y == food.y)
				break;
		}
		if (i == snake.length)
		{
			food.exist = true;
			break;
		}
	}
}

void Draw()
{
	BeginBatchDraw();
	cleardevice();
	for (int i = 0; i < Y; i++)
	{
		for (int j = 0; j < X; j++)
		{
			if (map[i][j] == 1)
			{
				setlinecolor(WHITE);
				rectangle(j * SIZE, i * SIZE, (j + 1) * SIZE, (i + 1) * SIZE);
			}
		}
	}

	for (int j = 0; j < snake.length; j++)
	{
		setfillcolor(LIGHTRED);
		solidrectangle(snake.coord[j].x * SIZE, snake.coord[j].y * SIZE, (snake.coord[j].x + 1) * SIZE, (snake.coord[j].y + 1) * SIZE);
	}
	setfillcolor(LIGHTBLUE);
	solidrectangle(food.x * SIZE, food.y * SIZE, (food.x + 1) * SIZE, (food.y + 1) * SIZE);
	settextcolor(WHITE);
	settextstyle(55, 25, "隶书");
	char s[] = "存档";
	outtextxy(900, 380, s);
	EndBatchDraw();
}

void Input()
{
	if ((GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState(VK_UP) & 0x8000) && snake.dir != 's')
	{
		snake.dir = 'w';
	}
	if ((GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000) && snake.dir != 'w')
	{
		snake.dir = 's';
	}
	if ((GetAsyncKeyState('A') & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8000) && snake.dir != 'd')
	{
		snake.dir = 'a';
	}
	if ((GetAsyncKeyState('D') & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8000) && snake.dir != 'a')
	{
		snake.dir = 'd';
	}

}


void Enlongate()
{
	int count = snake.length;
	while (count > 0)
	{
		snake.coord[count] = snake.coord[count - 1];
		count--;
	}
	snake.coord[0].x = food.x;
	snake.coord[0].y = food.y;
	snake.length++;
	food.exist = false;
}

bool Crash(int headx, int heady)
{
	for (int i = 0; i < snake.length; i++)
	{
		if (snake.coord[i].x == headx && snake.coord[i].y == heady)
		{
			return true;
		}
	}
	return false;
}

int Move()
{
		struct position temp;
		temp.x = snake.coord[0].x;
		temp.y = snake.coord[0].y;
		int count = snake.length - 1;
		bool ret = false;
		switch (snake.dir)
		{
		case 'd':
			if (map[temp.y][temp.x + snake.speed] == 1 || (ret = Crash(temp.x + snake.speed, temp.y)))
				return DEAD;
			if (temp.x + snake.speed == food.x && temp.y == food.y)
			{
				Enlongate();
				return ENLONG;
			}
			temp.x += snake.speed;
			break;
		case 'w':
			if (map[temp.y - snake.speed][temp.x] == 1 || (ret = Crash(temp.x, temp.y - snake.speed)))
				return DEAD;
			if (temp.x == food.x && temp.y - snake.speed == food.y)
			{
				Enlongate();
				return ENLONG;
			}
			temp.y -= snake.speed;
			break;
		case 's':
			if (map[temp.y + snake.speed][temp.x] == 1 || (ret = Crash(temp.x, temp.y + snake.speed)))
				return DEAD;
			if (temp.y + snake.speed == food.y && temp.x == food.x)
			{
				Enlongate();
				return ENLONG;
			}
			temp.y += snake.speed;
			break;
		case 'a':
			if (map[temp.y][temp.x - snake.speed] == 1 || (ret = Crash(temp.x - snake.speed, temp.y)))
				return DEAD;
			if (temp.x - snake.speed == food.x && temp.y == food.y)
			{
				Enlongate();
				return ENLONG;
			}
			temp.x -= snake.speed;
			break;
		}
		while (count > 0)
		{
			snake.coord[count].x = snake.coord[count - 1].x;
			snake.coord[count].y = snake.coord[count - 1].y;
			count--;
		}
		snake.coord[0].x = temp.x;
		snake.coord[0].y = temp.y;
	return ALIVE;
}

int IsStates(int ret)
{
	ExMessage msg;
	if (peekmessage(&msg, EX_MOUSE)) {
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (msg.x >= 880 && msg.y >= 380 && msg.x <= 935 && msg.y <= 405)
			{
				printf("已存档\n");
				return EXIT;
			}
		}
	}
	if (ret == ALIVE || ret == ENLONG)
	{
		return CONTINUE;
	}
	else
	{
		printf("你输了!\n");
		return EXIT;
	}
}
