#include <iostream>
#include <string>
#include <conio.h>
int menu()
{
	int input;
	do
	{
		std::cout << "============================" << std::endl;
		std::cout << "오목 게임을 플레이합시다!" << std::endl;
		std::cout << "1. 2인용 플레이" << std::endl;
		std::cout << "2. 게임 방법" << std::endl;
		std::cout << "3. Credits" << std::endl;
		std::cout << "4. 종료" << std::endl;
		std::cout << "============================" << std::endl;
		std::cout << "원하는 메뉴를 입력하세요 : ";

		std::cin >> input;

		if (input <= 0 || input >= 5)
		{
			std::cout << "다시 입력하세요." << std::endl;
		}
		else
		{
			break;
		}
	} while (true);
	return input;
}
void HowToPlay()
{
	system("cls");
	std::cout << "============================" << std::endl;
	std::cout << "오목은 보드판 위에 5개의 돌을 연속으로 놓으면 승리하는 게임입니다." << std::endl;
	std::cout << "현재 2인용 게임만 구현되어 있으며, 1p가 먼저 시작합니다." << std::endl;
	std::cout << "[단축키]" << std::endl;
	std::cout << "키보드 ↑ ↓ ← → : 보드판에서 이동합니다." << std::endl;
	std::cout << "Enter : 바둑돌을 놓습니다." << std::endl;
}
void Credits() // 크레딧
{
	system("cls");
	std::cout << "Made by. FanJae." << std::endl;
}
bool IndexSafeCheck(int x, int y) // 인덱스 범위를 초과하는지 확인하는 함수
{
	if (x < 0 || x >= 15)
	{
		return false;
	}
	if (y < 0 || y >= 15)
	{
		return false;
	}
	return true;
}
void PrintBoard(int board[15][15], int cursorX, int cursorY, int turn) // 보드 출력
{
	std::string stone[2] = { "○","●" };
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (i == cursorX && j == cursorY)
			{
				std::cout << stone[turn];
			}
			else if (board[i][j] == 0)
			{
				std::cout << "□";
			}
			else if (board[i][j] == 1) // 1p의 돌은 ○
			{
				std::cout << stone[0];
			}
			else if (board[i][j] == 2) // 2p의 돌은 ●
			{
				std::cout << stone[1];
			}
		}
		std::cout << std::endl;
	}
}
bool WinCheck(int board[15][15], int turn)
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			int cnt[4] = { 0 };
			for (int k = 0; k < 5; k++)
			{

				if (IndexSafeCheck(i, j + k) == true)  // → 방향으로 해당 턴 유저가 깔아놓은 돌 개수 체크
				{
					if (board[i][j + k] == turn + 1)
					{
						cnt[0]++;
					}
				}
				if (IndexSafeCheck(i + k, j) == true)  // ↓ 방향으로 해당 턴 유저가 깔아놓은 돌 개수 체크
				{
					if (board[i + k][j] == turn + 1)
					{
						cnt[1]++;
					}
				}
				if (IndexSafeCheck(i + k, j + k) == true)  // ↘ 방향으로 해당 턴 유저가 깔아놓은 돌 개수 체크
				{
					if (board[i + k][j + k] == turn + 1)
					{
						cnt[2]++;
					}
				}
				if (IndexSafeCheck(i + k, j - k) == true)  // ↙ 방향으로 해당 턴 유저가 깔아놓은 돌 개수 체크
				{
					if (board[i + k][j - k] == turn + 1)
					{
						cnt[3]++;
					}
				}
			}
			for (int i = 0; i < 4; i++)
			{
				if (cnt[i] == 5) // 이 값이 하나라도 5가 되었다는 것은 오목이 되었음을 의미한다.
				{
					return true;
				}
			}
		}
	}
	return false;
}
void PlayGame() // 게임 플레이 함수
{
	int board[15][15] = { 0 }; // 보드판 
	int cursorX = 0, cursorY = 0; // 가상의 커서 위치
	int turn = 0;
	std::string system_message = "";
	while (1)
	{
		system("cls");
		PrintBoard(board, cursorX, cursorY, turn);
		std::cout << "Player " << turn + 1 << "P의 턴입니다." << std::endl;
		std::cout << "키보드(상,하,좌,우)키로 이동하고, Enter를 눌러 돌을 배치하여 주세요." << std::endl;
		std::cout << system_message;

		char input = _getch();

		if (input == 72) // 화살표 윗키
		{
			cursorX--;
			if (IndexSafeCheck(cursorX, cursorY) == false) cursorX++;
			system_message = "";
		}
		else if (input == 80) // 화살표 아랫키
		{
			cursorX++;
			if (IndexSafeCheck(cursorX, cursorY) == false) cursorX--;
			system_message = "";
		}
		else if (input == 75) // 화살표 왼쪽키
		{
			cursorY--;
			if (IndexSafeCheck(cursorX, cursorY) == false) cursorY++;
			system_message = "";
		}
		else if (input == 77) // 화살표 오른쪽키
		{
			cursorY++;
			if (IndexSafeCheck(cursorX, cursorY) == false) cursorY--;
			system_message = "";
		}
		else if (input == 13)
		{
			if (board[cursorX][cursorY] == 1 || board[cursorX][cursorY] == 2) // 이미 배치되어 있는 경우.
			{
				system_message = "이미 돌이 배치되어 있습니다. 다른 곳에 배치해주세요.\n";
			}
			else
			{
				board[cursorX][cursorY] = turn + 1;
				if (WinCheck(board, turn) == true) // 승부가 결정된 경우
				{
					system("cls");
					PrintBoard(board, cursorX, cursorY, turn);
					std::cout << "Player " << turn + 1 << "P의 승리로 게임을 종료합니다." << std::endl;
					std::cout << "아무 키를 입력하면 메뉴로 돌아갑니다." << std::endl;
					_getch();
					break;
				}
				else // 승부가 결정나지 않은 경우
				{
					turn = (turn + 1) % 2;
				}
			}
		}
	}
}
int main(void)
{
	int input;
	while (true)
	{
		input = menu();
		switch (input)
		{
		case 1:
			PlayGame();
			break;
		case 2:
			HowToPlay();
			break;
		case 3:
			system("cls");
			Credits();
			break;
		case 4:
			std::cout << "프로그램을 종료합니다.";
			return 0;
		default:
			std::cout << "[Error] : Program Logic Error" << std::endl;
			break;
		}
	}
}