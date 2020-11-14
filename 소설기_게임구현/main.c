#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "map1.h"
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
#define DOWN 80
#define REVERSE_RIGHT 75
#define REVERSE_LEFT 77
#define REVERSE_DOWN 72
//GameBoard
#define GBOARD_HEIGHT 40
#define GBOARD_WIDTH  32
#define GBOARD_ORIGIN_X 8
#define GBOARD_ORIGIN_Y 10

COORD PC;
int PC_map1;
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

int speed = 10;

void RemoveCursor(void)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
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
	SetCurrentCursorPos(GBOARD_ORIGIN_X + 2, GBOARD_ORIGIN_Y);
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
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorOfPC);
				PC = GetCurrentCursorPos();

				printf("♨");

			}
			else if (map1[y][x] == 7)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
				printf("■");
			}
		}
	}

	//SetCurrentCursorPos(curPos.X, curPos.Y);
}

void DrawGameBlock_init()
{
	int y, x;
	SetCurrentCursorPos(GBOARD_ORIGIN_X + 2, GBOARD_ORIGIN_Y);
	curPos = GetCurrentCursorPos();
	for (y = 0; y < 40; y++)
	{
		for (x = 0; x < 30; x++)
		{
			SetCurrentCursorPos(curPos.X + x * 2, curPos.Y + y);
			if (map1_init[y][x] == 0)
			{
				printf("  ");
			}
			else if (map1_init[y][x] == 1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
				printf("■");
			}
			else if (map1_init[y][x] == 2)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
				printf("■");
			}
			else if (map1_init[y][x] == 3)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
				printf("■");
			}
			else if (map1_init[y][x] == 4)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
				printf("■");
			}
			else if (map1_init[y][x] == 5)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				printf("§");
			}
			else if (map1_init[y][x] == 6)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				printf("♨");
			}
			else if (map1_init[y][x] == 7)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
				printf("■");
			}
		}
	}

	//SetCurrentCursorPos(curPos.X, curPos.Y);
}

void element1Print()
{
	int x, y;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	SetCurrentCursorPos(GBOARD_ORIGIN_X + 2, GBOARD_ORIGIN_Y);
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

void element1Print_init()//initialize 알파벳배열 출력
{
	int x, y;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	SetCurrentCursorPos(GBOARD_ORIGIN_X + 2, GBOARD_ORIGIN_Y);
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
		SetCurrentCursorPos(GBOARD_ORIGIN_X + 2, GBOARD_ORIGIN_Y + y);
		if (y == GBOARD_HEIGHT)
			printf("└");
		else
			printf("│");
	}
	for (x = 1; x < GBOARD_WIDTH - 2; x++)
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
			printf("│");
	}

	SetCurrentCursorPos(GBOARD_WIDTH, 0);
	DrawGameBlock(map1);
}

void StoryTelling()
{
	printf("옛날옛적에 윙가드리오마을 숲속에 동물친구들이 옹기종기 살고 있었어요~ \n하지만 어느날...\n악랄한 수라고동사이정이 나타나\n동물 친구들의 이름을 빼앗아 가버렸어요\n이제 우리는 친구들을 부를 수 가 없어요ㅠㅠ\n여러분이 제 친구들의 이름을 찾아주세요!!!!\n");
}


void initialize()
{
	DrawGameBlock_init();
	element1Print_init();

}
void DrawStage()
{
	DrawGameBlock();
	CurrentSituationPrint();
	element1Print();
}


void ShiftRight()
{
	//move right
	if (map1[PC.Y - GBOARD_ORIGIN_Y + 1][(PC.X - GBOARD_ORIGIN_X) / 2] != 0)
	{
		map1[PC.Y - GBOARD_ORIGIN_Y][(PC.X - GBOARD_ORIGIN_X) / 2 - 1] = 0;
		PC.X += 2;
		SetCurrentCursorPos(PC.X, PC.Y);

		map1[PC.Y - GBOARD_ORIGIN_Y][(PC.X - GBOARD_ORIGIN_X) / 2 - 1] = 6;
		DrawStage();
	}
	// check color and then, if color == blockcolor -> movedown
	int arrCurX_PC = (PC.X - GBOARD_ORIGIN_X) / 2 - 1;
	int arrCurY_PC = (PC.Y - GBOARD_ORIGIN_Y);

	while (!DetectCollisionPCWithBlock())
	{
		map1[arrCurY_PC][arrCurX_PC] = 0;
		map1[arrCurY_PC + 1][arrCurX_PC] = 6;
		PC.Y += 1; arrCurY_PC++;
		DrawStage();
	}
}



//왼쪽이동
void ShiftLeft()
{

	if (map1[PC.Y - GBOARD_ORIGIN_Y + 1][(PC.X - GBOARD_ORIGIN_X) / 2 - 2] != 0)
	{
		map1[PC.Y - GBOARD_ORIGIN_Y][(PC.X - GBOARD_ORIGIN_X) / 2 - 1] = 0;
		PC.X -= 2;
		SetCurrentCursorPos(PC.X, PC.Y);

		map1[PC.Y - GBOARD_ORIGIN_Y][(PC.X - GBOARD_ORIGIN_X) / 2 - 1] = 6;
		DrawStage();
	}

	int arrCurX_PC = (PC.X - GBOARD_ORIGIN_X) / 2 - 1;
	int arrCurY_PC = (PC.Y - GBOARD_ORIGIN_Y);

	while (!DetectCollisionPCWithBlock())
	{
		map1[arrCurY_PC][arrCurX_PC] = 0;
		map1[arrCurY_PC + 1][arrCurX_PC] = 6;
		PC.Y += 1; arrCurY_PC++;
		DrawStage();
	}

}

int DetectCollisionPCWithBlock()
{
	int arrCurX, arrCurY;
	int UnderBlock_Info;
	arrCurX = (PC.X - GBOARD_ORIGIN_X) / 2 - 1;
	arrCurY = (PC.Y - GBOARD_ORIGIN_Y);
	UnderBlock_Info = map1[arrCurY + 1][arrCurX] % 10;

	if (UnderBlock_Info == 1)
		UnderBlock_Info = RED;
	else if (UnderBlock_Info == 2)
		UnderBlock_Info = BLUE;
	else if (UnderBlock_Info == 3)
		UnderBlock_Info = GREEN;
	else if (UnderBlock_Info == 4)
		UnderBlock_Info = YELLOW;

	if (colorOfPC == UnderBlock_Info || UnderBlock_Info == 0)
		return 0;
	else if (colorOfPC != UnderBlock_Info && UnderBlock_Info != 0)
		return 1;
}

void PortalBlock()
{
	int arrCurX_PC, arrCurY_PC;
	int tmp_COLOR;
	int playerdownBlock_COLOR;
	arrCurX_PC = (PC.X - GBOARD_ORIGIN_X) / 2 - 1;
	arrCurY_PC = (PC.Y - GBOARD_ORIGIN_Y);
	tmp_COLOR = map1[arrCurY_PC + 1][arrCurX_PC] % 10;
	if (tmp_COLOR == 4)
	{
		if (arrCurY_PC + 1 == 34)
		{
			map1[arrCurY_PC][arrCurX_PC] = 0;
			arrCurY_PC = 8;
			arrCurX_PC = 24;
			map1[arrCurY_PC][arrCurX_PC] = 6;

			PC.X = (arrCurX_PC + 1) * 2 + GBOARD_ORIGIN_X;
			PC.Y = arrCurY_PC + GBOARD_ORIGIN_Y;
		}

		else if (arrCurY_PC + 1 == 9)
		{
			map1[arrCurY_PC][arrCurX_PC] = 0;
			arrCurY_PC = 33;
			arrCurX_PC = 6;
			map1[arrCurY_PC][arrCurX_PC] = 6;

			PC.X = (arrCurX_PC + 1) * 2 + GBOARD_ORIGIN_X;
			PC.Y = arrCurY_PC + GBOARD_ORIGIN_Y;

		}

		DrawStage();
	}


}
//블록 하강
void PlayerDown()
{
	int arrCurX_PC, arrCurY_PC;
	int tmp_COLOR;
	int playerdownBlock_COLOR;
	arrCurX_PC = (PC.X - GBOARD_ORIGIN_X) / 2 - 1;
	arrCurY_PC = (PC.Y - GBOARD_ORIGIN_Y);
	tmp_COLOR = map1[arrCurY_PC + 1][arrCurX_PC] % 10;
	//if (tmp_COLOR) // if downblock is none
	//   return;
	if (tmp_COLOR != 0)
	{
		if (tmp_COLOR == 1)
			colorOfPC = RED;
		else if (tmp_COLOR == 2)
			colorOfPC = BLUE;
		else if (tmp_COLOR == 3)
			colorOfPC = GREEN;
		else if (tmp_COLOR == 4)
			PortalBlock();
		//colorOfPC = tmp_COLOR;
	}
	/*
	while (!DetectCollisionPCWithBlock())
	{
		map1[arrCurY_PC][arrCurX_PC] = 0;
		map1[arrCurY_PC + 1][arrCurX_PC] = 6;
		PC.Y += 1; arrCurY_PC++;
		DrawStage();
	}
	*/


	while (1)
	{
		if (DetectCollisionPCWithBlock() == 0)
		{
			map1[arrCurY_PC][arrCurX_PC] = 0;
			map1[arrCurY_PC + 1][arrCurX_PC] = 6;
			PC.Y += 1; arrCurY_PC++;
			DrawStage();
		}
		else
			break;
	}


	//printf("-end");
}



void ProcessKeyInput()
{
	for (int i = 0; i < 20; i++)
	{
		if (_kbhit() != 0)
		{
			int key = _getch();
			switch (key)
			{
			case LEFT:
				ShiftLeft();
				break;
			case RIGHT:
				ShiftRight();
				break;
			case DOWN:
				PlayerDown();
				break;

			}
		}
		Sleep(speed);//만약 더 빠르게 하고싶으면 speed를 작게한다
	}
}

int main()
{
	RemoveCursor();

	//StoryTelling();
	//Sleep(10000);
	DrawGameBoard();
	DrawStage();

	while (1)
	{
		ProcessKeyInput();
	}

}