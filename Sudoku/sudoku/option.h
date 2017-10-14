#pragma once

class option
{
public:
	int x;
	int y;
	int l[9];//choose set

	void set(int a, int b);
	bool remove(int x);
	void add(int x);
	int length();
	int choose(int b);

};

void option::set(int a, int b)//set 1 if can be choosen
{
	this->x = a;
	this->y = b;
	for (int i = 0; i < 9; i++)
	{
		l[i] = 1;
	}
}

bool option::remove(int x)			//set 0 
{
	if (l[x - 1] == 1) l[x - 1] = 0;
	else return false;
	return true;
}

void option::add(int x) {
	l[x - 1] = 1;
}

int option::length()
{
	int len = 0;
	for (int k = 0; k < 9; k++)
	{
		if (l[k] == 1) len++;
	}
	return len;
}

int option::choose(int b)
{
	for (int i = 0; i<9; i++) {
		if (l[i] == 1) b--;
		else continue;
		if (b == 0) return i + 1;
	}
}
