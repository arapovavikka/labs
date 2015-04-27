#include <iostream>
#include <fstream>

using namespace std;

struct Elem
{
	Elem* next;
	int info;
};

struct List
{
	Elem *fir, *last;
};

struct Form
{
	Elem *fir, *prev, *cur, *last;
};

void add_info(Elem *a, int num)
{
	a->info = num;
}

void add_next(Elem *a, Elem *a2)
{
	a->next = a2;
}

Elem* init_elem()
{
	Elem* a = new Elem;
	add_next(a, NULL);
	add_info(a, 0);
	return a;
}

List init_list()
{
	List b;
	b.fir = NULL;
	b.last = NULL;

	return b;
}

List init_list(Form b)
{
	List l;
	l.fir = b.fir;
	l.last = b.last;

	return l;
}

Form init_form()
{
	Form f;
	f.fir = NULL;
	f.last = NULL;
	f.cur = NULL;
	f.prev = NULL;

	return f;
}

Form init_form(List l)
{
	Form f;
	f.fir = l.fir;
	f.last = l.last;
	f.cur = l.fir;
	f.prev = NULL;

	return f;
}

bool list_empty(List &b)
{
	return b.last == NULL;
}

void add_fir_elem(Elem *a, Form &b)
{
	b.fir = a;
}

void add_elem(Elem *a, Form &b)
{
	b.prev = b.cur;
	b.cur = b.last = a;
	b.cur->next = NULL;
	
	if (b.prev) {
		b.prev->next = a;
	}

	if (!b.fir)
	{
		add_fir_elem(a, b);
	}
}

void go_next(Form &b)
{
	if (b.cur != NULL)
	{
		b.prev = b.cur;
		b.cur = b.cur->next;
	}
}

void print_list(List &l)
{
	Form b = init_form(l);
	for (int i = 0; b.cur != NULL; i++)
	{
		cout /*<< i + 1 << ") "*/ << b.cur->info << " => ";
		go_next(b);
	}
	cout << "X" << endl;
}

List read_list(char* filename)
{
	fstream in;
	in.open(filename, ios::in);
	Form b = init_form();

	while(!in.eof())
	{	
		int num;
		in >> num;
		Elem* a = init_elem();
		add_info(a, num);
		add_elem(a, b);
	}

	in.close();
	List l = init_list(b);

	if(list_empty(l))
	{
		cout << "No list inputed/n";
		exit(1);
	}
	
	print_list(l);
	return l;
}

List read_list()
{
	cout << "Input size of second list: \n";
	int len;
	cin >> len;
	Form b = init_form();
	for (int i = 0; i < len; i++)
	{
//		cout << i + 1 <<") x = ";
		int num;
		cin >> num;
		Elem *a = init_elem();
		add_info(a, num);
		add_elem(a, b);
	}
	List l = init_list(b);

	if(list_empty(l))
	{
		cout << "No list inputed/n";
		exit(2);
	}
	print_list(l);
	return l;
}

List unite(List &b, List &b2)
{
	b.last->next = b2.fir;
	b.last = b2.last;

	return b;
}

void remove_twin(Form &b) 
{
	if (b.prev != NULL)
	{
		b.prev->next = b.cur->next;
	}
	else
	{
		b.fir = b.cur->next;
	}

	if (b.prev->next == NULL) 
	{
		b.last = b.prev;
	}

	delete b.cur;

	b.cur = b.prev; // compatible with go_next(b)
}

void delete_twins(List &l) 
{
	Form b1 = init_form(l);

	for (; b1.cur != NULL; go_next(b1)) {
		Form b2 = b1;
		go_next(b2);

		for (; b2.cur != NULL; go_next(b2)) {
			if (b1.cur->info == b2.cur->info) 
			{
				remove_twin(b2);
			}
		}
	}

	l = init_list(b1);
}

int main()
{
	List l1 = read_list("input.txt");
	List l2 = read_list();

	delete_twins(l2);

	List l = unite(l1, l2);
	print_list(l);

	fstream out;
	out.open("output.txt", ios::out);
	out.close(); 

	system("pause");
	return 0; 
}