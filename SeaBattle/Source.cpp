//������� ���
//		�������� ������� �������� ���
// ���������� ��� ������
// �������� ����
// �������� ���� � ������ ����� �������
// ����������� �������
// ��������� ����/����� ��������� ����������� �� �����
// ���������� ��� �������(������� ��� ���������) � ��������� ����
// ������� ����������� ���� �� ����������
// ����������� ��� ������
// ��������� ��� ����������
// ������� ����
//
#include <iostream>
using namespace std;
//������ ���������� ����������
#define human 0
#define computer 1
const char* letters = "ABCDEFGHIJ";

int player1;
int player2;
char a1[10][10], a2[10][10], b1[10][10], b2[10][10];//���� ��� ��������� �������� � ��� ������� �� ����� ��������
int hit1 = 0, hit2 = 0;//���������� ��� �������� ���������

int setplayer(int number)//���������� ��� ������(��������� ��� �������)
{
	cout << "select player number #" << number << endl;
	cout << "0 - human, 1 - computer: " << endl;
	cin >> number;
	return number;
}

void printsea(char a[10][10])//�������� ����
{
	system("CLS");
	cout << " " << letters << endl;
	for (size_t i = 0; i < 10; i++)
	{
		cout << i << " ";
		for (size_t j = 0; j < 10; j++)
		{
			cout << a[i][j];
		}cout << endl;
	}
}

void printsea2()//�������� ���� � ������ ����� �������
{
	system("CLS");
	cout << " " << letters << endl;
	for (size_t i = 0; i < 10; i++)
	{
		cout << i << " ";
		for (size_t j = 0; j < 10; j++)
		{
			cout << b1[i][j];
		}cout << endl;
	}

	cout << " " << letters << endl;
	for (size_t i = 0; i < 10; i++)
	{
		cout << i << " ";
		for (size_t j = 0; j < 10; j++)
		{
			cout << b2[i][j];
		}cout << endl;
	}
}

void setship(char a[10][10], char begin[2], char end[2])//������� ���������� ���������(���������� �������)
{
	int i1, i2, j1, j2;
	i1 = int(begin[1]) - 48;//������ ������
	j1 = int(begin[0]) - 65;//������ �������
	i2 = int(end[1]) - 48;//����� ������
	j2 = int(end[0]) - 65;//����� �������

	if (i1 == i2) 
	{
		for (size_t j = j1; j <= j2; j++)
		{
			a[i1][j] = '*';
		}
	}
	else
	{
		for (size_t i = i1; i <= i2; i++)
		{
			a[i][j1] = '*';
		}
	}
}

void setsea(char a[10][10], char b[10][10])//��������� ����
{
	for (size_t i = 0; i < 10; i++)//������� ��� ��������� ���������
	{
		for (size_t j = 0; j < 10; j++)
		{
			a[i][j] = ' ';
			b[i][j] = ' ';
		}
	}

	for (size_t i = 4; i >= 1; i--)//����� ������� �� 4 �� 1
	{
		for (size_t j = 1; j <= 5-i; j++)//���-�� �������� �� 1 �� 4
		{
			printsea(a);
			char begin[3], end[3];
			cout << "ship length: " << i << endl;
			cout << "\tbegin: ";//������ �������
			cin >> begin;
			if (i > 1)
			{
				cout << "\tend: ";//����� �������
				cin >> end;
			}
			else
			{
				end[0] = begin[0];
				end[1] = begin[1];
			}
			setship(a, begin, end);//���������� �������
		}
	}
}

#include <fstream>
#include "Source.h"
void setsearandom(char a[10][10], char b[10][10], int p)//������ ����������� �� �����
{
	ifstream f;
	if (p == 1)
		f.open("1.txt");//��������� ����
	else
		f.open("2.txt");//���� ������ ���������
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			f.get(a[i][j]);//���������� � ��� ������ ������� �� �����
			b[i][j] = ' ';//�� ������ ������ ������ ������ ���������� �������
		}
		char c;//��� ������ ������ �������, �� �������� � ����������� ����� � ������
		f.get(c);
	}
	f.close();//��������� ����
}

void setplayers()//���������� ��� ������� � ��������� ����
{
	player1 = setplayer(1);//������ ����� ������� ��� ���������
	player2 = setplayer(2);//������ ����� ������� ��� ���������
	if (player1 == human)//���� ������ ����� �������
		setsea(a1, b1);//��������� �������
	else
		setsearandom(a1, b1, 1);//��� ������ �� ����� ���� ����

	if (player2 == human)//��� ������� ������ ���� �����
		setsea(a2, b2);
	else
		setsearandom(a2, b2, 2);
}

int havewin()//���������� ����������
{
	int win = 0;
	if (hit1 == 20) win = 1;
	if (hit2 == 20) win = 2;
	return win;
}

int getresult(char a[10][10], char b[10][10], char t[3]) //������ ��� ������
{
	int i1, j1;
	i1 = int(t[1]) - 48;//������ ����
	j1 = int(t[0]) - 65;//������� ����

	int result = 0;
	if (a[i1][j1] == '*')//���� �����
	{
		if (b[i1][j1] == ' ')//���� �� ����� � ��� ������ �� �������
		{
			result = 1;//���� ��������
			b[i1][j1] = '*';//������ ������� � ��������� � �� ������ ����
		}
	}
	else
	{
		b[i1][j1] = '-';//��� ������ ������� � �������
	}
	return result;
}

void setturn(char t[])//��������� ��� ����������
{
	char dig[] = "0123456789";
	int i = rand() % 10;
	int j = rand() % 10;
	t[0] = letters[i];
	t[1] = dig[j];
	t[2] = '\0';
}

void game()
{
	int winner = 0;//���������� ���
	int currentplayer = 1;//����� ����� 1 ����� ������
	char turn[3];//���
	do
	{
		printsea2();//�������� ���� � ������ �������
		cout << "current player: " << currentplayer << endl;
		//���� ������ ������� - �� ������ ��� � ����������
		if (((currentplayer == 1) && (player1 == human)) ||
			(currentplayer == 2 && player2 == human)) {
			cout << "your turn: ";
			cin >> turn;
		}
		else setturn(turn);//����� ��������� ���

		int result = 0;//��������� ���� 
		if (currentplayer == 1)
		{
			result = getresult(a2, b1, turn);// ��������� ��� ������� ������
			hit1 += result;//��������� ���������� � ���-�� ���������
		}
		else
		{
			result = getresult(a1, b2, turn);//��������� ��� ������� ������
			hit2 += result;//��������� ���������� � ���-�� ���������
		}
		if (result == 0)//���� ������
			if (currentplayer == 1)//��� ��������� � ������� ������
				currentplayer = 2;
			else
				currentplayer = 1;
		winner = havewin();//��������� ���� �� ����������
		
	} while (!winner);//������ ���� ���������� �� ����� ������
	cout << hit1 << " " << hit2 << endl;
	if (winner == 1)
		cout << "player 1 - win" << endl;
	else
		cout << "player 2 - win" << endl;

}

int main()
{
	srand(time(NULL));
	setplayers();
	game();

	return 0;
}