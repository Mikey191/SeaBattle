//морской бой
//		алгоритм решения морского боя
// определяем тип игрока
// печетаем поле
// печатаем поля с ходами обоих игроков
// расставляем корабли
// заполняем поле/можно прочитать расстановку из файла
// определяем тип игроков(человек или компьютер) и заполняем поле
// функция определения есть ли победитель
// расписываем ход игрока
// случайный ход компьютера
// процесс игры
//
#include <iostream>
using namespace std;
//воодим глобальные переменные
#define human 0
#define computer 1
const char* letters = "ABCDEFGHIJ";

int player1;
int player2;
char a1[10][10], a2[10][10], b1[10][10], b2[10][10];//поля для запонения кароблей и для стрельб по чужим кораблям
int hit1 = 0, hit2 = 0;//переменные для подсчета попаданий

int setplayer(int number)//определить тип игрока(компьютер или человек)
{
	cout << "select player number #" << number << endl;
	cout << "0 - human, 1 - computer: " << endl;
	cin >> number;
	return number;
}

void printsea(char a[10][10])//печатаем поле
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

void printsea2()//печатаем поля с ходами обоих игроков
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

void setship(char a[10][10], char begin[2], char end[2])//функция заполнения короблями(раставляем корабли)
{
	int i1, i2, j1, j2;
	i1 = int(begin[1]) - 48;//начало строки
	j1 = int(begin[0]) - 65;//начало столбца
	i2 = int(end[1]) - 48;//конец строки
	j2 = int(end[0]) - 65;//конец столбца

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

void setsea(char a[10][10], char b[10][10])//заполняем поле
{
	for (size_t i = 0; i < 10; i++)//сначало все заполняем пробелами
	{
		for (size_t j = 0; j < 10; j++)
		{
			a[i][j] = ' ';
			b[i][j] = ' ';
		}
	}

	for (size_t i = 4; i >= 1; i--)//длина коробля от 4 до 1
	{
		for (size_t j = 1; j <= 5-i; j++)//кол-во кораблей от 1 до 4
		{
			printsea(a);
			char begin[3], end[3];
			cout << "ship length: " << i << endl;
			cout << "\tbegin: ";//начало коробля
			cin >> begin;
			if (i > 1)
			{
				cout << "\tend: ";//конец корабля
				cin >> end;
			}
			else
			{
				end[0] = begin[0];
				end[1] = begin[1];
			}
			setship(a, begin, end);//запоминаем корабль
		}
	}
}

#include <fstream>
#include "Source.h"
void setsearandom(char a[10][10], char b[10][10], int p)//читаем расстановку из файла
{
	ifstream f;
	if (p == 1)
		f.open("1.txt");//открываем файл
	else
		f.open("2.txt");//либо второй открываем
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			f.get(a[i][j]);//записываем в наш массив корабли из файла
			b[i][j] = ' ';//во второй массив одного игрока записываем пробелы
		}
		char c;//для записи первой строчки, по аналогии с заполнением пооля в ручную
		f.get(c);
	}
	f.close();//закрываем файл
}

void setplayers()//определяем тип игроков и заполняем поле
{
	player1 = setplayer(1);//первый игрок человек или компьютер
	player2 = setplayer(2);//второй игрок человек или компьютер
	if (player1 == human)//если первый игрок человек
		setsea(a1, b1);//заполняем вручную
	else
		setsearandom(a1, b1, 1);//или читаем из файла если комп

	if (player2 == human)//для второго игрока тоже самое
		setsea(a2, b2);
	else
		setsearandom(a2, b2, 2);
}

int havewin()//опрелеляем победителя
{
	int win = 0;
	if (hit1 == 20) win = 1;
	if (hit2 == 20) win = 2;
	return win;
}

int getresult(char a[10][10], char b[10][10], char t[3]) //делаем ход игрока
{
	int i1, j1;
	i1 = int(t[1]) - 48;//строка зода
	j1 = int(t[0]) - 65;//столбец хода

	int result = 0;
	if (a[i1][j1] == '*')//если попал
	{
		if (b[i1][j1] == ' ')//если до жтого в эту клетку не стрелял
		{
			result = 1;//есть пробитие
			b[i1][j1] = '*';//ставим отметку о попадании в во второе поля
		}
	}
	else
	{
		b[i1][j1] = '-';//или ставик отметку о промахе
	}
	return result;
}

void setturn(char t[])//случайный ход компьютера
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
	int winner = 0;//победителя нет
	int currentplayer = 1;//игрок номер 1 ходит первым
	char turn[3];//ход
	do
	{
		printsea2();//печатаем поля с ходами игроков
		cout << "current player: " << currentplayer << endl;
		//если играет челоаек - то читаем ход с клавиатуры
		if (((currentplayer == 1) && (player1 == human)) ||
			(currentplayer == 2 && player2 == human)) {
			cout << "your turn: ";
			cin >> turn;
		}
		else setturn(turn);//иначе случайный ход

		int result = 0;//рехультат хода 
		if (currentplayer == 1)
		{
			result = getresult(a2, b1, turn);// проверяем ход первого игрока
			hit1 += result;//результат прибавляем к кол-ву попаданий
		}
		else
		{
			result = getresult(a1, b2, turn);//проверяем ход второго игрока
			hit2 += result;//результат прибавляем к кол-ву попаданий
		}
		if (result == 0)//если промах
			if (currentplayer == 1)//ход переходит к другому игроку
				currentplayer = 2;
			else
				currentplayer = 1;
		winner = havewin();//проверяем есть ои победитель
		
	} while (!winner);//играем пока победитель не будет найден
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