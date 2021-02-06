#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

struct node {
	std::string name;
	node* prev;
	node* next;
};

class music_list {
private:
	node* m_current;
	node* m_head;
	node* m_last;
	node* play_now;

public:
	music_list(node* cur = NULL, node* head = NULL, node* last = NULL, node* now = NULL)
		:m_current(cur), m_head(head), m_last(last), play_now(now)
	{}

	~music_list()
	{
		delete m_current;
		delete m_head;
		delete m_last;
	}

	struct list_iterator
	{
	private:
		node* ptr;

	public:
		list_iterator(node* p) : ptr(p) {}

		std::string& operator*() { return ptr->name; }

		node* get() { return ptr; }

		list_iterator& operator++()
		{
			ptr = ptr->next;
			return *this;
		}

		list_iterator operator++(int)
		{
			list_iterator result = *this;
			++(*this);
			return result;
		}
	};

	list_iterator begin() { return list_iterator(m_head); }
	list_iterator end() { return list_iterator(m_last); }
	list_iterator begin() const { return list_iterator(m_head); }
	list_iterator end() const { return list_iterator(m_last); }

	void insert(std::string name)
	{
		node* new_music = new node;
		new_music->name = name;

		if (!m_head)
		{
			m_head = new_music;
			m_last = new_music;
			m_current = new_music;
			new_music->next = new_music;
			new_music->prev = new_music;
		}

		else
		{
			m_last = new_music;
			m_head->prev = new_music;

			new_music->prev = m_current;
			new_music->next = m_head;
			m_current->next = new_music;
			m_current = new_music;
		}
	}

	void next()
	{
		if (play_now)
		{
			std::cout << "다음 곡을 재생합니다... " << std::endl;
			play_now = play_now->next;
			std::cout << "현재 곡 : " << play_now->name << std::endl;
		}

		// NULL일때
		else
		{
			// 음악이 1도 없을 때
			if (!m_head)
			{
				std::cout << "먼저 음악을 추가해주세요. 명령어 : insert " << std::endl;
			}
			else
			{
				play_now = m_current;
				std::cout << "현재 곡 : " << play_now->name << std::endl;
			}
		}
	}

	void previous()
	{
		if (play_now)
		{
			std::cout << "이전 곡을 재생합니다... " << std::endl;
			play_now = play_now->prev;
			std::cout << "현재 곡 : " << play_now->name << std::endl;
		}

		// NULL일때
		else
		{
			// 음악이 1도 없을 때
			if (!m_head)
			{
				std::cout << "먼저 음악을 추가해주세요. 명령어 : insert " << std::endl;
			}
			else
			{
				play_now = m_current->prev;
				std::cout << "현재 곡 : " << play_now->name << std::endl;
			}
		}
	}

	void printall()
	{
		using namespace std;

		cout << "현재 당신의 갬-성 뮤직 리스트는... " << endl;

		if (!m_head)
		{
			cout << "현재 재생 목록이 비어있습니다. " << endl;
		}
		
		else
		{
			for (auto it = list_iterator(m_head); it.get() != m_last;it++)
			{
				cout << *it << endl;
			}
			// 음악이 1가지만 있지 않다면,
			if (m_head != m_last)
			{
				cout << m_last->name << " 입니다." << endl;
			}
			// 음악이 1가지만 있다면,
			else
			{
				cout << m_head->name << " 입니다." << endl;
			}
		}
	}

	void remove(const std::string& music)
	{
		using namespace std;

		//재생 목록이 비어 있다면,

		if (!m_head)
		{
			cout << "현재 재생 목록이 비어있어, 음악을 제거할 수 없습니다." << endl;
		}

		else
		{
			auto it = list_iterator(m_head);

			// 입력한 이름의 음악이 첫번째 음악인 경우
			while (1)
			{
				if (it.get()->name == music)
				{
					// 음악 삭제후 재생 목록이 empty일 경우
					if (m_head == m_last)
					{
						node* tmp = m_head;
						m_head = nullptr;
						m_last = nullptr;
						m_current = nullptr;
						play_now = nullptr;
						delete tmp;

						cout << music << "을 지웠습니다. " << endl;
						break;
					}
					else
					{
						node* tmp = it.get();
						tmp->next->prev = tmp->prev;
						tmp->prev->next = tmp->next;
						m_current = m_head;
						play_now = m_current;
						delete tmp;

						cout << music << "을 지웠습니다. " << endl;
						break;
					}
				}
				else if(it.get() == m_last)
				{
					//마지막 곡과 일치할 경우
					if (it.get()->name == music)
					{
						node* tmp = it.get();
						tmp->next->prev = tmp->prev;
						tmp->prev->next = tmp->next;
						m_current = m_head;
						play_now = m_current;
						m_last = m_last->prev;
						m_last->next = m_head;
						delete tmp;

						cout << music << "을 지웠습니다. " << endl;
						break;
					}
					//마지막 곡까지 다 돌려봤는데 일치하는 음악이 없을 경우
					else
					{
						cout << music << "과 일치하는 음악이 없습니다... " << endl;
						break;
					}
				}
				else
				{
					it++;
				}
			}
		}
	}

};

int main()
{
	std::cout << "당신의 취향 리스트, URmusic. " << std::endl;

	music_list URmusic;

	std::string command;
	while (1)
	{
		std::cout << "명령어를 입력해주세요. 도움을 받고 싶다면, -help를 입력하세요. " << std::endl;
		std::cin >> command;
		if (command == "-help")
		{
			std::cout << "여러 명령어를 입력해보세요." << std::endl << std::endl;
			std::cout << "0. 다시 도움을 받으려면...? -help " << std::endl;
			std::cout << "1. 재생 목록에 음악을 추가하고 싶다면...? -insert " << std::endl;
			std::cout << "2. 재생 목록에 음악을 제거하고 싶다면...? -remove " << std::endl;
			std::cout << "3. 전체 재생 목록을 보고 싶다면...? -printall " << std::endl;
			std::cout << "그리고 -next, -prev, -exit가 있어요! " << std::endl;
		}
		else if (command == "-exit")
		{
			std::cout << "종료..." << std::endl;
			break;
		}

		else if (command == "-remove")
		{
			std::cout << "어떤 음악을 지울까요?" << std::endl;
			std::string musicname;
			std::cin.ignore(); // erase buffer
			std::getline(std::cin, musicname);
			URmusic.remove(musicname);
		}

		else if (command == "-insert")
		{
			std::cout << "어떤 음악을 추가할까요?" << std::endl;
			std::string musicname;
			std::cin.ignore(); // erase buffer
			std::getline(std::cin, musicname);
			URmusic.insert(musicname);
			std::cout << musicname << "을 추가했습니다. " << std::endl;
		}

		else if (command == "-printall")
		{
			URmusic.printall();
		}

		else if (command == "-next")
		{
			URmusic.next();
		}
		else if (command == "-prev")
		{
			URmusic.previous();
		}
	}
	return 0;
}
// 원형 데이터 표현을 지원하는 기본 구조 설계
// 앞에서 만든 구조에 데이터 삽입 및 삭제 기능 구현
// 사용자 정의 반복자(iterator) 구현

// 구현기능 : -help, -insert, -remove, -printall, -next, -prev, -exit
