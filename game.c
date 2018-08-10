```c
#include "EatSnake.h"

void Welcome()
{
	system("COLOR f0");//设置背景颜色
	system("mode con cols=100 lines=30");//设置显示框大小

	SetPos(33, 10);
	printf("******************************");
	SetPos(33, 12);
	printf("   欢迎来到贪吃蛇游戏！");
	SetPos(33, 14);
	printf("******************************");

	SetPos(33, 18);
	system("pause");
	system("cls");

	SetPos(65, 5);
	printf("   请选择<1开始 2退出>：");
	SetPos(65, 7);
	printf("   使用↑ ↓ ← →控制方向");
	SetPos(65, 9);
	printf("   F1加速，F2减速");
	SetPos(65, 11);
	printf("   按空格暂停/继续，ESC退出");
	SetPos(65, 13);
	printf("   得分：");
}


void SnakeStart(pSnake s)
{
	DrawMap();
	InitSnake(s);
	CreatFood(s);
}

void game()
{
	Snake s = { 0 };
	SnakeStart(&s);
	while (s._Status == OK)
	{
		SnakeMove(&s);
		SnakeRun(&s);
	}

	int mark = SnakeLenth(&s);

	if (s._Status == KILL_BY_WALL)
	{
		SetPos(24, 12);
		printf("装墙而死,得分：%d", mark);
	}
	else if (s._Status == KILL_BY_SELF)
	{
		SetPos(24, 12);
		printf("碰蛇而死,得分：%d", mark);
	}

	SetPos(24, 14);
	system("pause");
}

void test()
{
	srand((unsigned int)time(NULL));
	while (1)
	{
		Welcome();
		SetPos(90, 5);
		int input = 0;
		scanf_s("%d", &input);

		if (1 == input)
		{
			game();
		}
		else if (2 == input)
		{
			exit(0);
		}

	}
}

int main()
{
	test();
	return 0;
}
```
