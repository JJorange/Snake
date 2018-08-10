```c+
#include "EatSnake.h"

void SetPos(int x, int y)//设置光标位置
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 0 };
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void DrawMap()//画地图
{
	int i = 0;
	for (i = 0; i < 58; i += 2) //打印上边界
	{
		SetPos(i, 0);
		printf(FOOD);
	}
	for (i = 0; i < 58; i += 2) //打印下边界
	{
		SetPos(i, 26);
		printf(FOOD);
	}
	for (i = 0; i <= 26; i++) //打印左边界
	{
		SetPos(0, i);
		printf(FOOD);
	}
	for (i = 0; i <= 26; i++) //打印右边界
	{
		SetPos(58, i);
		printf(FOOD);
	}
}

void InitSnake(pSnake ps) //初始化蛇
{
	pSnakeNode cur = NULL;
	int i = 0;

	cur = (SnakeNode*)malloc(sizeof(SnakeNode));
	memset(cur, 0, sizeof(SnakeNode));

	cur->x = INIT_X;
	cur->y = INIT_Y;
	cur->next = NULL;

	for (i = 1; i <= 4; i++)
	{
		ps->_pSnake = malloc(sizeof(SnakeNode));
		ps->_pSnake->next = cur;
		ps->_pSnake->x = INIT_X + i * 2;
		ps->_pSnake->y = INIT_Y;
		cur = ps->_pSnake;
	}

	while (cur != NULL)
	{
		SetPos(cur->x, cur->y);
		printf(FOOD);
		cur = cur->next;
	}
	ps->_SleepTime = INIT_SPEECH;
	ps->_Status = OK;
	ps->_Dir = RIGHT;
	ps->lenth = INIT_LENTH;
}

void CreatFood(pSnake ps)//设置食物
{
	pSnakeNode cur = NULL;
	pSnakeNode food = NULL;

	food = (SnakeNode*)malloc(sizeof(SnakeNode));

again:
	memset(food, 0, sizeof(SnakeNode));
	do
	{
		food->x = rand() % 56 + 2;
	} while (food->x % 2 != 0);

	food->y = rand() % 25 + 1;

	cur = ps->_pSnake;
	while (cur != NULL)
	{
		if (cur->x == food->x && cur->y == food->y)//食物不能出现在蛇身子里
		{
			goto again;
		}
		cur = cur->next;
	}
	ps->_food = food;
	SetPos(food->x, food->y);
	printf(FOOD);
}

int NextHasFood(pSnake ps, pSnakeNode nNode) //判断有木有食物
{
	return ps->_food->x == nNode->x && ps->_food->y == nNode->y;
}

void EatFood(pSnake ps, pSnakeNode nNode) //吃食物
{
	pSnakeNode cur = ps->_pSnake;
	nNode->next = cur;
	ps->_pSnake = nNode;

	cur = ps->_pSnake;

	while (cur != NULL)
	{
		SetPos(cur->x, cur->y);
		printf(FOOD);
		cur = cur->next;
	}
	ps->lenth++;
	SetPos(74, 13);
	printf("%d", ps->lenth - INIT_LENTH);//每次吃到食物，就显示最新分数

	if (ps->_SleepTime > MAX_SPEECH) //每次吃到食物后，就加速一次
	{
		ps->_SleepTime -= 50;
	}
	CreatFood(ps);
}

void NoFood(pSnake ps, pSnakeNode nNode)//没食物
{
	pSnakeNode cur = ps->_pSnake;
	nNode->next = cur;
	ps->_pSnake = nNode;

	cur = ps->_pSnake;

	while (cur->next->next != NULL)
	{
		SetPos(cur->x, cur->y);
		printf(FOOD);
		cur = cur->next;
	}

	SetPos(cur->next->x, cur->next->y);
	printf("  ");
	free(cur->next);
	cur->next = NULL;
}

void SnakeMove(pSnake ps) //蛇移动
{
	pSnakeNode nNode = (SnakeNode*)malloc(sizeof(SnakeNode));
	memset(nNode, 0, sizeof(SnakeNode));

	nNode->x = ps->_pSnake->x;
	nNode->y = ps->_pSnake->y;

	switch (ps->_Dir)
	{
	case UP:
		nNode->y--;
		break;
	case DOWN:
		nNode->y++;
		break;
	case LEFT:
		nNode->x -= 2;
		break;
	case RIGHT:
		nNode->x += 2;
		break;
	default:
		break;
	}

	if (1 == NextHasFood(ps, nNode))//有食物
	{
		EatFood(ps, nNode);
	}
	else
	{
		NoFood(ps, nNode);
	}
}

int KillByWall(pSnake ps)
{
	if (ps->_pSnake->x == 0 || ps->_pSnake->x == 58
		|| ps->_pSnake->y == 0 || ps->_pSnake->y == 26)
	{
		return 1;
	}
	return 0;
}

int KillBySelf(pSnake ps) //判断是否死在自己手上
{
	pSnakeNode cur = ps->_pSnake->next;
	while (cur != NULL)
	{
		if (ps->_pSnake->x == cur->x && ps->_pSnake->y == cur->y)
		{
			return 1;
		}
		cur = cur->next;
	}
	return 0;
}

int SnakeLenth(pSnake ps)  //判断死亡时蛇的长度
{
	return ps->lenth - INIT_LENTH;
}


void SnakeRun(pSnake ps) //控制蛇的方向
{
	do
	{
		if (GetAsyncKeyState(VK_DOWN) && ps->_Dir != UP)
		{
			ps->_Dir = DOWN;
		}
		else if (GetAsyncKeyState(VK_UP) && ps->_Dir != DOWN)
		{
			ps->_Dir = UP;
		}
		else if (GetAsyncKeyState(VK_LEFT) && ps->_Dir != RIGHT)
		{
			ps->_Dir = LEFT;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && ps->_Dir != LEFT)
		{
			ps->_Dir = RIGHT;
		}
		else if (GetAsyncKeyState(VK_F1) && ps->_SleepTime > MAX_SPEECH) //加速
		{
			ps->_SleepTime -= 50;
		}
		else if (GetAsyncKeyState(VK_F2) && ps->_SleepTime < (INIT_SPEECH - (ps->lenth) * 50)) // 减速
		{
			ps->_SleepTime += 50;
		}
		else if (GetAsyncKeyState(VK_SPACE)) //暂停
		{
			while (1)
			{
				Sleep(300);
				if (GetAsyncKeyState(VK_SPACE)) //再按一次空格继续
				{
					break;
				}
				else if (GetAsyncKeyState(VK_ESCAPE)) //按ESC退出游戏
				{
					exit(0);
				}
			}

		}
		SnakeMove(ps);

		if (1 == KillBySelf(ps)) //蛇头碰到蛇身
		{
			ps->_Status = KILL_BY_SELF;
		}

		if (1 == KillByWall(ps)) //撞墙
		{
			ps->_Status = KILL_BY_WALL;
		}
		Sleep(ps->_SleepTime);

	} while (ps->_Status == OK);

}
```
