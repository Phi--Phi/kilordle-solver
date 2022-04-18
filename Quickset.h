#pragma once

class Quickset
{

public:
	Quickset();
	Quickset(unsigned int mask);
	void insert(char x);
	short count(char x);
	short BitCount();
	unsigned int Bitmask;
};
