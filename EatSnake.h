```c
#ifndef __RETROSNAKER_H__
#define __RETROSNAKER_H__

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>


/*********宏定义区**************/
#define FOOD "■"
#define INIT_X 24 //蛇出生点
#define INIT_Y 10
#define INIT_SPEECH 500
#define MAX_SPEECH 100
#define INIT_LENTH 5 //初始长度


/**********枚举常量定义区*********/
enum DIRECTION
{
	//行走方向
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
};

enum Status
{
	/*蛇的状态*/
	OK,   //活的
	KILL_BY_SELF, //被自己弄死
	KILL_BY_WALL  //被墙弄死
};


/*********结构体定义区****************/
typedef struct node
{
	/*蛇身节点*/
	int x;
	int y;
	struct node* next;

}SnakeNode, *pSnakeNode;

typedef struct Snake
{
	/*蛇本身*/
	pSnakeNode _pSnake; //蛇头指针
	pSnakeNode _food; //食物
	enum DIRECTION _Dir; //行走方向
	enum Status _Status; //蛇状态
	int _SleepTime; //每走一步停的时间
	int lenth;  //蛇长度

}Snake, *pSnake;


/**********函数声明区******************/
void SetPos(int x, int y);//设置光标位置

void DrawMap();//画地图

void InitSnake(pSnake pSnake); //初始化蛇

void CreatFood(pSnake pSnake);//初始化食物

int NextHasFood(pSnake pSnake, pSnakeNode nNode); //判断有木有食物

void EatFood(pSnake pSnake, pSnakeNode nNode); //吃食物

void NoFood(pSnake pSnake, pSnakeNode nNode);//没食物

void SnakeMove(pSnake pSnake); //蛇移动

int KillByWall(pSnake ps); //判断是否被撞墙

int KillBySelf(pSnake ps); //判断是否蛇头碰到蛇身

void SnakeRun(pSnake ps); //蛇连续跑

int SnakeLenth(pSnake ps); // 蛇长度


#endif
```
