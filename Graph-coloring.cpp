#include "stdafx.h"
#include <iostream>
#include <conio.h>
#define TRUE 1
#define FALSE 0
typedef int Boolean;
typedef struct L *Lref; // Тип: указатель на заголовочный узел.
typedef struct T *Tref; // Тип: указатель на дуговой узел.

//Описание типа заголовочного узла.
typedef struct L
{
	int Key; //Имя заголовочного узла.
	int Color; //Цвет раскраски.
	int Count; //Количество предшественников.
	Boolean Flag; //Флаг посещения узла при обходе.
	Tref Trail; //Указатель на список смежности.
	Lref Next; //Указатель на следующий узел в списке заголовочных узлов.
};

//Описание типа дугового узла.
typedef struct T
{
	Lref Id;
	Tref Next;
};

class Spisok
{
private:
	Lref Head; //Указатель на голову списка заголовочных узлов.
	Lref Tail; //Указатель на фиктивный элемент 
	// в конце списка заголовочных узлов.
	int MSet[256]; //Вспомогательное множество, содер- 
	//жащее 0,1,2...,n.
	void SearchGraph(int, Lref *);
public:
	Spisok() {//Инициализация списка заголовочных узлов.
		Head = Tail = new (L);
	}
	Lref GetHead() { return Head; }
	Lref GetTail() { return Tail; }
	void MakeGraph();
	void PrintGraph();
	void Color(Lref, int);
	void Postr(int);
};

void main()
{
	setlocale(LC_ALL, "rus");
	Spisok A;
	Lref t; //Рабочий указатель для перемещения 
	// по списку заголовочных звеньев.
	int n = 0; //Количество вершин в графе.

	std::cout << "\n              ++++++++++++++++++++++++++++++++\n              ++++++++++++++++++++++++++++++++\n              +++ Алгоритм Раскраски Графа +++\n              ++++++++++++++++++++++++++++++++\n              ++++++++++  Дияр З. Х. +++++++++\n\n";

	//Построение графа и вывод его структуры Вирта.
	A.MakeGraph();
	A.PrintGraph(); std::cout << std::endl;
	//Раскраска с помощью рекурсивного обхода графа в глубину.
	//Инициализация.
	t = A.GetHead(); //Установлен рабочий указатель.
	while (t != A.GetTail())
	{
		t->Flag = TRUE; t->Color = 0;
		n++; t = (*t).Next;
	}
	// ------------------------------------ 
	//Построение вспомогательного множества MSet.
	A.Postr(n);
	std::cout << "\n Результат раскраски: \n ";
	A.Color(A.GetHead(), n);
	std::cout << " \n++++++++++++++++++++++++\n++ 1 для Красный цвет ++\n++ 2 для Зеленый цвет ++\n++ 3 для Желтый цвет  ++\n++++++++++++++++++++++++\n\n              ++++++++++++++++++++++++++++++++\n              ++++++++++++  2017  ++++++++++++\n              ++++++++++++++++++++++++++++++++" << std::endl;
	_getch();
}

void Spisok::Postr(int n)
//Построение вспомогательного множества MSet.
{
	for (int i = 0; i<256; i++)
		MSet[i] = (i <= n) ? 1 : 0;
}

void Spisok::SearchGraph(int w, Lref *h)
//Функция возвращает указатель на заголовочный узел 
//с ключом w в графе, заданном структурой Вирта с указателем Head. 
{
	*h = Head; (*Tail).Key = w;
	while ((**h).Key != w) *h = (**h).Next;
	if (*h == Tail)
		//В списке заголовочных узлов нет узла с ключом w.
		//Поместим его в конец списка Head.
	{
		Tail = new (L); (**h).Count = 0;
		(**h).Trail = NULL; (**h).Next = Tail;
	}
}

void Spisok::MakeGraph()
//Функция возвращает указатель Head на структуру 
//Вирта, соответствующую ориентированному графу.
{
	int x, y;
	Lref p, q; //Рабочие указатели.
	Tref t, r; //Рабочие указатели.
	Boolean Res; //Флаг наличия дуги.
	std::cout << "  Вводите начальную вершину дуги: ";
	std::cin >> x;
	while (x != 0)
	{
		std::cout << "  Вводите конечную вершину дуги: "; std::cin >> y;  std::cout << "\n";
		//Определим, существует ли в графе дуга (x,y)?
		SearchGraph(x, &p); SearchGraph(y, &q);
		r = (*p).Trail; Res = FALSE;
		while ((r != NULL) && (!Res))
		if ((*r).Id == q) Res = TRUE;
		else r = (*r).Next;
		if (!Res) //Если дуга отсутствует, то поместим её в граф.
		{
			t = new (T); (*t).Id = q;
			(*t).Next = (*p).Trail; (*p).Trail = t; (*q).Count++;
		}
		std::cout << "Вводите начальную вершину дуги: "; std::cin >> x;
	}
}

void Spisok::PrintGraph()
//Вывод структуры Вирта, заданной указателем 
//Head и соответствующей ориентированному графу.
{
	Lref p; //Рабочий указатель.
	Tref q; //Рабочий указатель.

	p = Head;
	while (p != Tail)
	{
		std::cout << (*p).Key << "("; q = (*p).Trail;
		while (q != NULL)
		{
			std::cout << (*(*q).Id).Key; q = (*q).Next;
		}
		std::cout << ")"; p = (*p).Next; std::cout << " ";
	}
}

void Spisok::Color(Lref r, int n)
//Последовательная раскраска графа при помощи
//рекурсивного обхода графа в глубину.
//r - указатель на структуру Вирта.
//MSet - глобальное множество.
//n    - количество вершин в графе.
{
	Tref t, t1;
	int i;         //Параметр цикла.
	Boolean Fl;

	t = r->Trail; r->Flag = FALSE;
	//Сейчас мы находимся в вершине r->Key.
	//Исключим цвета всех вершин, смежных вершине
	//r->Key, из множества MSet.
	t1 = t;
	while (t1 != NULL)
	{
		MSet[t1->Id->Color] = 0; t1 = t1->Next;
	}
	//Выбор цвета вершины: это "первый" элемент множества MSet.
	Fl = TRUE; i = 1;
	while (Fl)
	if (MSet[i]) Fl = FALSE; else  i++;
	r->Color = i;   //Цвет присвоен!
	std::cout << "(" << r->Key << "," << r->Color << ") ";
	//Восстановление вспомогательного множества MSet.
	for (i = 0; i<256; MSet[i++] = 0);
	for (i = 0; i <= n; MSet[i++] = 1);
	// ------------- 
	while (t != NULL)
	{
		if (t->Id->Flag) Color(t->Id, n);
		t = t->Next;
	}
}
