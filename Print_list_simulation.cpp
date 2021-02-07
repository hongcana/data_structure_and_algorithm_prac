//사무실 공유 프린터의 인쇄 대기 목록 시뮬레이션

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
	//생성자 : 인쇄할 파일의 정보
	job(std::string name = NULL, int page = 0)
		:work_ID(++count), m_name(name), pages(page)
	{}


	friend std::ostream& operator<< (std::ostream& os, const job& j)
	{
		std::cout << "인쇄물 정보" << std::endl;
		os << "번호 : " << j.work_ID << std::endl << j.m_name << std::endl << "페이지 수 : " << j.pages << "페이지" << std::endl << std::endl;
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

	//새 인쇄 작업 추가 함수
	bool addnewjob(const job& j)
	{
		if (todo.size() == N)
		{
			std::cout << "인쇄 대기열에 추가 실패: " << j << std::endl;
			return false;
		}

		std::cout << "인쇄 대기열에 추가: " << std::endl << j;
		todo.push(j);
		return true;
	}

	//현재까지 추가된 모든 인쇄 작업을 처리하는 함수
	void print()
	{
		while (!todo.empty())
		{
			std::cout << "인쇄 중 : " << todo.front() << std::endl;
			todo.pop();
		}
	}
};

int main()
{
	printer<5> samsung_print;

	job j1("프로그래밍 언어론", 390);
	job j2("알고리즘 분석", 500);
	job j3("IT와 경영", 220);
	job j4("컴퓨터 네트워크", 660);
	job j5("대학물리(1)", 444);
	job j6("컴퓨터구조", 550);

	samsung_print.addnewjob(j1);
	samsung_print.addnewjob(j2);
	samsung_print.addnewjob(j3);
	samsung_print.addnewjob(j4);
	samsung_print.addnewjob(j5);
	samsung_print.addnewjob(j6); // 인쇄 대기열이 가득차 인쇄 불가
	samsung_print.print();

	samsung_print.addnewjob(j6); // 이제 가능
	samsung_print.print();

	return 0;
}