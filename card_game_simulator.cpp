#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <random>

// ī�� �ʱ�ȭ, 0���� 12����
void init(std::vector<int>& cards)
{
	for (int i = 0; i <= 12; i++)
	{
		cards.push_back(i);
	}
}

// ���� �÷��̾ ������ �ִ� ī�� ���
void printall(std::vector<int>& cards)
{
	for (auto ele : cards)
		std::cout << ele << " ";
	std::cout << std::endl;
}

// ī�� ����, �������� �̿�
void shuffle(std::vector<int>& cards)
{
	std::random_shuffle(cards.begin(), cards.end());
}

//1���� 13���� ������ �������� �����ϴ� �Լ� ex) getRandomNumber(1, 13)
int getRandomNumber(int min, int max)
{
	std::random_device rd;
	std::mt19937 mersenne(rd());

	std::uniform_int_distribution<> die(min, max);

	return die(mersenne);
}

//��Ī �Լ�
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

	std::cout << "player1 pick " << pl1pick+1 << "��° ī���� " << t1 << std::endl;
	std::cout << "player2 pick " << pl2pick+1 << "��° ī���� " << t2 << std::endl;
	std::cout << "player3 pick " << pl3pick+1 << "��° ī���� " << t3 << std::endl;
	std::cout << "player4 pick " << pl4pick+1 << "��° ī���� " << t4 << std::endl;


	if ((t1 == t2) && (t1 == t3) && (t1 == t4) && (t2 == t3) && (t2 == t4) && (t3 == t4))
	{
		std::cout << "�÷��̾� 4���� ī�尡 ��� ��ġ�մϴ�. ����." << std::endl;
		pl1.erase(pl1.begin() + pl1pick);
		pl2.erase(pl2.begin() + pl2pick);
		pl3.erase(pl3.begin() + pl3pick);
		pl4.erase(pl4.begin() + pl4pick);
	}

	// (1,2,3)
	else if ((t1 == t2) && (t1 == t3) && (t2 == t3))
	{
		std::cout << "�÷��̾� 3���� ī�尡 ��� ��ġ�մϴ�. �̰͵� ���� ��������.." << std::endl;

		pl1.erase(pl1.begin() + pl1pick);
		pl2.erase(pl2.begin() + pl2pick);
		pl3.erase(pl3.begin() + pl3pick);
	}
	// (1,2,4)
	else if ((t1 == t2) && (t1 == t4) && (t2 == t4))
	{
		std::cout << "�÷��̾� 3���� ī�尡 ��� ��ġ�մϴ�. �̰͵� ���� ��������.." << std::endl;

		pl1.erase(pl1.begin() + pl1pick);
		pl2.erase(pl2.begin() + pl2pick);
		pl4.erase(pl4.begin() + pl4pick);
	}
	// (2,3,4)
	else if ((t2 == t3) && (t2 == t4) && (t3 == t4))
	{
		std::cout << "�÷��̾� 3���� ī�尡 ��� ��ġ�մϴ�. �̰͵� ���� ��������.." << std::endl;
		
		pl4.erase(pl4.begin() + pl4pick);
		pl2.erase(pl2.begin() + pl2pick);
		pl3.erase(pl3.begin() + pl3pick);
	}
	// (1,3,4)
	else if ((t1 == t3) && (t3 == t4) && (t1 == t4))
	{
		std::cout << "�÷��̾� 3���� ī�尡 ��� ��ġ�մϴ�. �̰͵� ���� ��������.." << std::endl;

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
		std::cout << "�÷��̾�1�� �̰���ϴ�!" << std::endl;
	}

	else if (pl2.size() == 1)
	{
		std::cout << "�÷��̾�2�� �̰���ϴ�!" << std::endl;

	}

	else if (pl3.size() == 1)
	{
		std::cout << "�÷��̾�3�� �̰���ϴ�!" << std::endl;

	}

	else if (pl4.size() == 1)
	{
		std::cout << "�÷��̾�4�� �̰���ϴ�!" << std::endl;

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

	std::cout << "���� ���" << std::endl;
	
	std::cout << "�÷��̾� 1�� ���� ī�� : "; printall(player1);
	std::cout << "�÷��̾� 2�� ���� ī�� : "; printall(player2);
	std::cout << "�÷��̾� 3�� ���� ī�� : "; printall(player3);
	std::cout << "�÷��̾� 4�� ���� ī�� : "; printall(player4);

	finalwinner(player1, player2, player3, player4);

	return 0;
}

// �����̳� ���� �� 4���� �����̳� ��ü ����
// �����̳� �ʱ�ȭ �� ���� �Լ�
// �������� ī�带 �����ϴ� �Լ�
// ��Ī �Լ� -> �÷��̾� ī�� pick �� 4�� ī�� ��, ��ġ�ϴ� ī�� ����
// ���ڰ� �ִ��� �˻��ϴ� �Լ�
// ���ڰ� ��Ÿ�� �� ���� ��Ī �۾� �ݺ�

