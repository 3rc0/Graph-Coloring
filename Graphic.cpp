#include "stdafx.h"
#include <iostream>
#include <conio.h>
#define TRUE 1
#define FALSE 0
typedef int Boolean;
typedef struct L *Lref; // ���: ��������� �� ������������ ����.
typedef struct T *Tref; // ���: ��������� �� ������� ����.

//�������� ���� ������������� ����.
typedef struct L
{
	int Key; //��� ������������� ����.
	int Color; //���� ���������.
	int Count; //���������� ����������������.
	Boolean Flag; //���� ��������� ���� ��� ������.
	Tref Trail; //��������� �� ������ ���������.
	Lref Next; //��������� �� ��������� ���� � ������ ������������ �����.
};

//�������� ���� �������� ����.
typedef struct T
{
	Lref Id;
	Tref Next;
};

class Spisok
{
private:
	Lref Head; //��������� �� ������ ������ ������������ �����.
	Lref Tail; //��������� �� ��������� ������� 
	// � ����� ������ ������������ �����.
	int MSet[256]; //��������������� ���������, �����- 
	//����� 0,1,2...,n.
	void SearchGraph(int, Lref *);
public:
	Spisok() {//������������� ������ ������������ �����.
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
	Lref t; //������� ��������� ��� ����������� 
	// �� ������ ������������ �������.
	int n = 0; //���������� ������ � �����.

	std::cout << "\n              ++++++++++++++++++++++++++++++++\n              ++++++++++++++++++++++++++++++++\n              +++ �������� ��������� ����� +++\n              ++++++++++++++++++++++++++++++++\n              ++++++++++  ���� �. �. +++++++++\n\n";

	//���������� ����� � ����� ��� ��������� �����.
	A.MakeGraph();
	A.PrintGraph(); std::cout << std::endl;
	//��������� � ������� ������������ ������ ����� � �������.
	//�������������.
	t = A.GetHead(); //���������� ������� ���������.
	while (t != A.GetTail())
	{
		t->Flag = TRUE; t->Color = 0;
		n++; t = (*t).Next;
	}
	// ------------------------------------ 
	//���������� ���������������� ��������� MSet.
	A.Postr(n);
	std::cout << "\n ��������� ���������: \n ";
	A.Color(A.GetHead(), n);
	std::cout << " \n++++++++++++++++++++++++\n++ 1 ��� ������� ���� ++\n++ 2 ��� ������� ���� ++\n++ 3 ��� ������ ����  ++\n++++++++++++++++++++++++\n\n              ++++++++++++++++++++++++++++++++\n              ++++++++++++  2017  ++++++++++++\n              ++++++++++++++++++++++++++++++++" << std::endl;
	_getch();
}

void Spisok::Postr(int n)
//���������� ���������������� ��������� MSet.
{
	for (int i = 0; i<256; i++)
		MSet[i] = (i <= n) ? 1 : 0;
}

void Spisok::SearchGraph(int w, Lref *h)
//������� ���������� ��������� �� ������������ ���� 
//� ������ w � �����, �������� ���������� ����� � ���������� Head. 
{
	*h = Head; (*Tail).Key = w;
	while ((**h).Key != w) *h = (**h).Next;
	if (*h == Tail)
		//� ������ ������������ ����� ��� ���� � ������ w.
		//�������� ��� � ����� ������ Head.
	{
		Tail = new (L); (**h).Count = 0;
		(**h).Trail = NULL; (**h).Next = Tail;
	}
}

void Spisok::MakeGraph()
//������� ���������� ��������� Head �� ��������� 
//�����, ��������������� ���������������� �����.
{
	int x, y;
	Lref p, q; //������� ���������.
	Tref t, r; //������� ���������.
	Boolean Res; //���� ������� ����.
	std::cout << "  ������� ��������� ������� ����: ";
	std::cin >> x;
	while (x != 0)
	{
		std::cout << "  ������� �������� ������� ����: "; std::cin >> y;  std::cout << "\n";
		//���������, ���������� �� � ����� ���� (x,y)?
		SearchGraph(x, &p); SearchGraph(y, &q);
		r = (*p).Trail; Res = FALSE;
		while ((r != NULL) && (!Res))
		if ((*r).Id == q) Res = TRUE;
		else r = (*r).Next;
		if (!Res) //���� ���� �����������, �� �������� � � ����.
		{
			t = new (T); (*t).Id = q;
			(*t).Next = (*p).Trail; (*p).Trail = t; (*q).Count++;
		}
		std::cout << "������� ��������� ������� ����: "; std::cin >> x;
	}
}

void Spisok::PrintGraph()
//����� ��������� �����, �������� ���������� 
//Head � ��������������� ���������������� �����.
{
	Lref p; //������� ���������.
	Tref q; //������� ���������.

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
//���������������� ��������� ����� ��� ������
//������������ ������ ����� � �������.
//r - ��������� �� ��������� �����.
//MSet - ���������� ���������.
//n    - ���������� ������ � �����.
{
	Tref t, t1;
	int i;         //�������� �����.
	Boolean Fl;

	t = r->Trail; r->Flag = FALSE;
	//������ �� ��������� � ������� r->Key.
	//�������� ����� ���� ������, ������� �������
	//r->Key, �� ��������� MSet.
	t1 = t;
	while (t1 != NULL)
	{
		MSet[t1->Id->Color] = 0; t1 = t1->Next;
	}
	//����� ����� �������: ��� "������" ������� ��������� MSet.
	Fl = TRUE; i = 1;
	while (Fl)
	if (MSet[i]) Fl = FALSE; else  i++;
	r->Color = i;   //���� ��������!
	std::cout << "(" << r->Key << "," << r->Color << ") ";
	//�������������� ���������������� ��������� MSet.
	for (i = 0; i<256; MSet[i++] = 0);
	for (i = 0; i <= n; MSet[i++] = 1);
	// ------------- 
	while (t != NULL)
	{
		if (t->Id->Flag) Color(t->Id, n);
		t = t->Next;
	}
}
