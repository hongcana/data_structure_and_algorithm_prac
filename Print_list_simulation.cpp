//�繫�� ���� �������� �μ� ��� ��� �ùķ��̼�

#include <iostream>
#include <queue>

class job
{
private:
	int work_ID;
	std::string m_name;
	int pages;

	static int count;
public:
	//������ : �μ��� ������ ����
	job(std::string name = NULL, int page = 0)
		:work_ID(++count), m_name(name), pages(page)
	{}


	friend std::ostream& operator<< (std::ostream& os, const job& j)
	{
		std::cout << "�μ⹰ ����" << std::endl;
		os << "��ȣ : " << j.work_ID << std::endl << j.m_name << std::endl << "������ �� : " << j.pages << "������" << std::endl << std::endl;
		return os;
	}
};
int job::count = 0;

template <size_t N>
class printer
{
private:
	std::queue<job> todo;

public:

	//�� �μ� �۾� �߰� �Լ�
	bool addnewjob(const job& j)
	{
		if (todo.size() == N)
		{
			std::cout << "�μ� ��⿭�� �߰� ����: " << j << std::endl;
			return false;
		}

		std::cout << "�μ� ��⿭�� �߰�: " << std::endl << j;
		todo.push(j);
		return true;
	}

	//������� �߰��� ��� �μ� �۾��� ó���ϴ� �Լ�
	void print()
	{
		while (!todo.empty())
		{
			std::cout << "�μ� �� : " << todo.front() << std::endl;
			todo.pop();
		}
	}
};

int main()
{
	printer<5> samsung_print;

	job j1("���α׷��� ����", 390);
	job j2("�˰��� �м�", 500);
	job j3("IT�� �濵", 220);
	job j4("��ǻ�� ��Ʈ��ũ", 660);
	job j5("���й���(1)", 444);
	job j6("��ǻ�ͱ���", 550);

	samsung_print.addnewjob(j1);
	samsung_print.addnewjob(j2);
	samsung_print.addnewjob(j3);
	samsung_print.addnewjob(j4);
	samsung_print.addnewjob(j5);
	samsung_print.addnewjob(j6); // �μ� ��⿭�� ������ �μ� �Ұ�
	samsung_print.print();

	samsung_print.addnewjob(j6); // ���� ����
	samsung_print.print();

	return 0;
}