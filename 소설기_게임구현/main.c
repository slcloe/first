#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "map1.h"
#include "map2.h"

//Color
#define RED 4
#define BLUE 1
#define GREEN 2
#define YELLOW 6
//Number Of Item
#define LIFE_ID 100
#define DIRECTION_ID 101
#define MOBSPEED_ID 102
#define BLOCKSPEED_ID 103
#define GOUP_ID 104
//Key
#define RIGHT 77
#define LEFT 75
#define DOWN 120
#define REVERSE_RIGHT 75
#define REVERSE_LEFT 77
#define REVERSE_DOWN 72
//GameBoard
#define GBOARD_HEIGHT 40
#define GBOARD_WIDTH  32
#define GBOARD_ORIGIN_X 8
#define GBOARD_ORIGIN_Y 10

int row = 40;
int col = 30;
int interval = 5;
int BlockRow_Cnt = 0;
int player_Life = 3;
char obtainAlphabet[7];	//PC가 먹은 글자
int mobSpeed = 50;
int blockSpeed = 50;
COORD curPos;
int item_ID;
int colorOfPC = 6;

void SetCurrentCursorPos(int x, int y)
{
	COORD position = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
COORD GetCurrentCursorPos(void)
{
	COORD curPoint;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curPoint.X = curInfo.dwCursorPosition.X;
	curPoint.Y = curInfo.dwCursorPosition.Y;

	return curPoint;
}
void DrawGameBlock()
{
	int y, x;
	SetCurrentCursorPos(10, 10);
	curPos = GetCurrentCursorPos();

	for (y = 0; y < 40; y++)
	{
		for (x = 0; x < 30; x++)
		{
			SetCurrentCursorPos(curPos.X + x * 2, curPos.Y + y);
			if (map1[y][x] == 0)
			{
				printf("  ");
			}
			else if (map1[y][x] == 1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
				printf("■");
			}
			else if (map1[y][x] == 2)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
				printf("■");
			}
			else if (map1[y][x] == 3)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
				printf("■");
			}
			else if (map1[y][x] == 4)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
				printf("■");
			}
			else if (map1[y][x] == 5)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				printf("§");

			}
			else if (map1[y][x] == 6)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				printf("♨");

			}
			else if (map1[y][x] == 7)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
				printf("■");
			}
		}
	}
	SetCurrentCursorPos(curPos.X, curPos.Y);
}
void ElementPrint()
{
	int x, y;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	SetCurrentCursorPos(10, 10);
	curPos = GetCurrentCursorPos();

	for (y = 0; y < 40; y++)
	{
		for (x = 0; x < 30; x++)
		{

			SetCurrentCursorPos(curPos.X + x * 2, curPos.Y + y);
			if (element1[y][x] >= 'a' && element1[y][x] <= 'z')
			{
				printf("%c", element1[y][x]);
			}
		}
	}


	SetCurrentCursorPos(curPos.X, curPos.Y);
}
void CurrentSituationPrint()
{
	int i = 30;
	SetCurrentCursorPos(80, i++);
	printf("WORD THAT MUST ACQUIRE : duck");
	SetCurrentCursorPos(80, i++);
	printf("LETTERS ACQUIRED : ");
	puts(obtainAlphabet);
	SetCurrentCursorPos(80, i++);
	printf("LIFE COUNT : %d", player_Life);
	SetCurrentCursorPos(80, i++);
	printf("--------------------------");
	SetCurrentCursorPos(80, i++);
	printf("<KEY MANUAL>");
	SetCurrentCursorPos(80, i++);
	printf("Right key : 오른쪽으로 이동");
	SetCurrentCursorPos(80, i++);
	printf("Left key : 왼쪽으로 이동");
	SetCurrentCursorPos(80, i++);
	printf("Down key : 포털 이동 및 블록 삭제");
	SetCurrentCursorPos(80, i++);
	printf("MOB : §");
	SetCurrentCursorPos(100, i++);
}
void DrawGameBoard()
{
	int  x, y;

	for (y = 0; y <= GBOARD_HEIGHT; y++)
	{
		SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);
		if (y == GBOARD_HEIGHT)
			printf("└");
		else
			printf("I");
	}

	for (x = 0; x < GBOARD_WIDTH - 2; x++)
	{
		SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2 + 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);

		printf("─");
	}


	for (y = 0; y <= GBOARD_HEIGHT; y++)
	{
		SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 - 2, GBOARD_ORIGIN_Y + y);
		if (y == GBOARD_HEIGHT)
			printf("┘");
		else
			printf("I");
	}

	SetCurrentCursorPos(GBOARD_WIDTH, 0);
}
void DrawStage()
{
	DrawGameBlock();
	CurrentSituationPrint();
	ElementPrint();
}
int main()
{
	int N = 40;

	DrawStage();

	SetCurrentCursorPos(100, 100);

	return 0;
}