#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <random>

// 카드 초기화, 0부터 12까지
void init(std::vector<int>& cards)
{
	for (int i = 0; i <= 12; i++)
	{
		cards.push_back(i);
	}
}

// 현재 플레이어가 가지고 있는 카드 목록
void printall(std::vector<int>& cards)
{
	for (auto ele : cards)
		std::cout << ele << " ";
	std::cout << std::endl;
}

// 카드 섞기, 랜덤셔플 이용
void shuffle(std::vector<int>& cards)
{
	std::random_shuffle(cards.begin(), cards.end());
}

//1부터 13까지 난수를 무작위로 선택하는 함수 ex) getRandomNumber(1, 13)
int getRandomNumber(int min, int max)
{
	std::random_device rd;
	std::mt19937 mersenne(rd());

	std::uniform_int_distribution<> die(min, max);

	return die(mersenne);
}

//매칭 함수
void pick(std::vector<int>& pl1, std::vector<int>& pl2, std::vector<int>& pl3, std::vector<int>& pl4)
{
	//ex pl1 = 12, 0, 3 ,2 1, 11, 6, 8 7, 9 ,10,4 ,5

	int pl1pick = getRandomNumber(0, pl1.size() - 1); // tmp = 5,
	int pl2pick = getRandomNumber(0, pl2.size() - 1);
	int pl3pick = getRandomNumber(0, pl3.size() - 1);
	int pl4pick = getRandomNumber(0, pl4.size() - 1);

	int t1 = pl1[getRandomNumber(0, pl1.size()-1)]; // plpick == 11.
	int t2 = pl2[getRandomNumber(0, pl2.size()-1)];
	int t3 = pl3[getRandomNumber(0, pl3.size()-1)];
	int t4 = pl4[getRandomNumber(0, pl4.size()-1)];

	std::cout << "player1 pick " << pl1pick+1 << "번째 카드인 " << t1 << std::endl;
	std::cout << "player2 pick " << pl2pick+1 << "번째 카드인 " << t2 << std::endl;
	std::cout << "player3 pick " << pl3pick+1 << "번째 카드인 " << t3 << std::endl;
	std::cout << "player4 pick " << pl4pick+1 << "번째 카드인 " << t4 << std::endl;


	if ((t1 == t2) && (t1 == t3) && (t1 == t4) && (t2 == t3) && (t2 == t4) && (t3 == t4))
	{
		std::cout << "플레이어 4명의 카드가 모두 일치합니다. 세상에." << std::endl;
		pl1.erase(pl1.begin() + pl1pick);
		pl2.erase(pl2.begin() + pl2pick);
		pl3.erase(pl3.begin() + pl3pick);
		pl4.erase(pl4.begin() + pl4pick);
	}

	// (1,2,3)
	else if ((t1 == t2) && (t1 == t3) && (t2 == t3))
	{
		std::cout << "플레이어 3명의 카드가 모두 일치합니다. 이것도 쉽지 않은데요.." << std::endl;

		pl1.erase(pl1.begin() + pl1pick);
		pl2.erase(pl2.begin() + pl2pick);
		pl3.erase(pl3.begin() + pl3pick);
	}
	// (1,2,4)
	else if ((t1 == t2) && (t1 == t4) && (t2 == t4))
	{
		std::cout << "플레이어 3명의 카드가 모두 일치합니다. 이것도 쉽지 않은데요.." << std::endl;

		pl1.erase(pl1.begin() + pl1pick);
		pl2.erase(pl2.begin() + pl2pick);
		pl4.erase(pl4.begin() + pl4pick);
	}
	// (2,3,4)
	else if ((t2 == t3) && (t2 == t4) && (t3 == t4))
	{
		std::cout << "플레이어 3명의 카드가 모두 일치합니다. 이것도 쉽지 않은데요.." << std::endl;
		
		pl4.erase(pl4.begin() + pl4pick);
		pl2.erase(pl2.begin() + pl2pick);
		pl3.erase(pl3.begin() + pl3pick);
	}
	// (1,3,4)
	else if ((t1 == t3) && (t3 == t4) && (t1 == t4))
	{
		std::cout << "플레이어 3명의 카드가 모두 일치합니다. 이것도 쉽지 않은데요.." << std::endl;

		pl1.erase(pl1.begin() + pl1pick);
		pl4.erase(pl4.begin() + pl4pick);
		pl3.erase(pl3.begin() + pl3pick);
	}
	// (1,2), (1,3), (1,4), (2,3), (2,4), (3,4)
	else if (t1 == t2)
	{
		pl1.erase(pl1.begin() + pl1pick);
		pl2.erase(pl2.begin() + pl2pick);
	}

	else if (t1 == t3)
	{
		pl1.erase(pl1.begin() + pl1pick);
		pl3.erase(pl3.begin() + pl3pick);
	}

	else if (t1 == t4)
	{
		pl1.erase(pl1.begin() + pl1pick);
		pl4.erase(pl4.begin() + pl4pick);
	}

	else if (t2 == t3)
	{
		pl3.erase(pl3.begin() + pl3pick);
		pl2.erase(pl2.begin() + pl2pick);
	}

	else if (t2 == t4)
	{
		pl4.erase(pl4.begin() + pl4pick);
		pl2.erase(pl2.begin() + pl2pick);
	}

	else if (t4 == t3)
	{
		pl3.erase(pl3.begin() + pl3pick);
		pl4.erase(pl4.begin() + pl4pick);
	}

	// not matched
	else
	{
		std::cout << "Not matched in this turn" << std::endl;
		shuffle(pl1);
		shuffle(pl2);
		shuffle(pl3);
		shuffle(pl4);
	}
}

bool ifwinner(std::vector<int>& pl1, std::vector<int>& pl2, std::vector<int>& pl3, std::vector<int>& pl4)
{
	if (pl1.size() == 1)
	{
		return false;
	}

	else if (pl2.size() == 1)
	{
		return false;
	}

	else if (pl3.size() == 1)
	{
		return false;
	}

	else if (pl4.size() == 1)
	{
		return false;
	}

	else return true;
}

void finalwinner(std::vector<int>& pl1, std::vector<int>& pl2, std::vector<int>& pl3, std::vector<int>& pl4)
{
	if (pl1.size() == 1)
	{
		std::cout << "플레이어1이 이겼습니다!" << std::endl;
	}

	else if (pl2.size() == 1)
	{
		std::cout << "플레이어2가 이겼습니다!" << std::endl;

	}

	else if (pl3.size() == 1)
	{
		std::cout << "플레이어3이 이겼습니다!" << std::endl;

	}

	else if (pl4.size() == 1)
	{
		std::cout << "플레이어4가 이겼습니다!" << std::endl;

	}
}

int main()
{
	std::vector<int> player1;
	std::vector<int> player2;
	std::vector<int> player3;
	std::vector<int> player4;

	init(player1);
	init(player2);
	init(player3);
	init(player4);
	shuffle(player1);
	shuffle(player2);
	shuffle(player3);
	shuffle(player4);

	while (ifwinner(player1, player2, player3, player4))
	{
		pick(player1, player2, player3, player4);
	}

	std::cout << "게임 결과" << std::endl;
	
	std::cout << "플레이어 1의 남은 카드 : "; printall(player1);
	std::cout << "플레이어 2의 남은 카드 : "; printall(player2);
	std::cout << "플레이어 3의 남은 카드 : "; printall(player3);
	std::cout << "플레이어 4의 남은 카드 : "; printall(player4);

	finalwinner(player1, player2, player3, player4);

	return 0;
}

// 컨테이너 결정 및 4개의 컨테이너 객체 생성
// 컨테이너 초기화 및 섞는 함수
// 무작위로 카드를 선택하는 함수
// 매칭 함수 -> 플레이어 카드 pick 및 4장 카드 비교, 일치하는 카드 제거
// 승자가 있는지 검사하는 함수
// 승자가 나타날 때 까지 매칭 작업 반복

