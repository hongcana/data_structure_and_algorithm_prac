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
			std::cout << "���� ���� ����մϴ�... " << std::endl;
			play_now = play_now->next;
			std::cout << "���� �� : " << play_now->name << std::endl;
		}

		// NULL�϶�
		else
		{
			// ������ 1�� ���� ��
			if (!m_head)
			{
				std::cout << "���� ������ �߰����ּ���. ��ɾ� : insert " << std::endl;
			}
			else
			{
				play_now = m_current;
				std::cout << "���� �� : " << play_now->name << std::endl;
			}
		}
	}

	void previous()
	{
		if (play_now)
		{
			std::cout << "���� ���� ����մϴ�... " << std::endl;
			play_now = play_now->prev;
			std::cout << "���� �� : " << play_now->name << std::endl;
		}

		// NULL�϶�
		else
		{
			// ������ 1�� ���� ��
			if (!m_head)
			{
				std::cout << "���� ������ �߰����ּ���. ��ɾ� : insert " << std::endl;
			}
			else
			{
				play_now = m_current->prev;
				std::cout << "���� �� : " << play_now->name << std::endl;
			}
		}
	}

	void printall()
	{
		using namespace std;

		cout << "���� ����� ��-�� ���� ����Ʈ��... " << endl;

		if (!m_head)
		{
			cout << "���� ��� ����� ����ֽ��ϴ�. " << endl;
		}
		
		else
		{
			for (auto it = list_iterator(m_head); it.get() != m_last;it++)
			{
				cout << *it << endl;
			}
			// ������ 1������ ���� �ʴٸ�,
			if (m_head != m_last)
			{
				cout << m_last->name << " �Դϴ�." << endl;
			}
			// ������ 1������ �ִٸ�,
			else
			{
				cout << m_head->name << " �Դϴ�." << endl;
			}
		}
	}

	void remove(const std::string& music)
	{
		using namespace std;

		//��� ����� ��� �ִٸ�,

		if (!m_head)
		{
			cout << "���� ��� ����� ����־�, ������ ������ �� �����ϴ�." << endl;
		}

		else
		{
			auto it = list_iterator(m_head);

			// �Է��� �̸��� ������ ù��° ������ ���
			while (1)
			{
				if (it.get()->name == music)
				{
					// ���� ������ ��� ����� empty�� ���
					if (m_head == m_last)
					{
						node* tmp = m_head;
						m_head = nullptr;
						m_last = nullptr;
						m_current = nullptr;
						play_now = nullptr;
						delete tmp;

						cout << music << "�� �������ϴ�. " << endl;
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

						cout << music << "�� �������ϴ�. " << endl;
						break;
					}
				}
				else if(it.get() == m_last)
				{
					//������ ��� ��ġ�� ���
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

						cout << music << "�� �������ϴ�. " << endl;
						break;
					}
					//������ ����� �� �����ôµ� ��ġ�ϴ� ������ ���� ���
					else
					{
						cout << music << "�� ��ġ�ϴ� ������ �����ϴ�... " << endl;
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
	std::cout << "����� ���� ����Ʈ, URmusic. " << std::endl;

	music_list URmusic;

	std::string command;
	while (1)
	{
		std::cout << "��ɾ �Է����ּ���. ������ �ް� �ʹٸ�, -help�� �Է��ϼ���. " << std::endl;
		std::cin >> command;
		if (command == "-help")
		{
			std::cout << "���� ��ɾ �Է��غ�����." << std::endl << std::endl;
			std::cout << "0. �ٽ� ������ ��������...? -help " << std::endl;
			std::cout << "1. ��� ��Ͽ� ������ �߰��ϰ� �ʹٸ�...? -insert " << std::endl;
			std::cout << "2. ��� ��Ͽ� ������ �����ϰ� �ʹٸ�...? -remove " << std::endl;
			std::cout << "3. ��ü ��� ����� ���� �ʹٸ�...? -printall " << std::endl;
			std::cout << "�׸��� -next, -prev, -exit�� �־��! " << std::endl;
		}
		else if (command == "-exit")
		{
			std::cout << "����..." << std::endl;
			break;
		}

		else if (command == "-remove")
		{
			std::cout << "� ������ ������?" << std::endl;
			std::string musicname;
			std::cin.ignore(); // erase buffer
			std::getline(std::cin, musicname);
			URmusic.remove(musicname);
		}

		else if (command == "-insert")
		{
			std::cout << "� ������ �߰��ұ��?" << std::endl;
			std::string musicname;
			std::cin.ignore(); // erase buffer
			std::getline(std::cin, musicname);
			URmusic.insert(musicname);
			std::cout << musicname << "�� �߰��߽��ϴ�. " << std::endl;
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
// ���� ������ ǥ���� �����ϴ� �⺻ ���� ����
// �տ��� ���� ������ ������ ���� �� ���� ��� ����
// ����� ���� �ݺ���(iterator) ����

// ������� : -help, -insert, -remove, -printall, -next, -prev, -exit
