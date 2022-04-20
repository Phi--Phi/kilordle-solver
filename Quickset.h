#pragma once

class Quickset
{

public:
	Quickset();
	Quickset(unsigned int mask);
	void insert(char x);
	short count(char x);
	short BitCount(); // TODO: replace with std::popcount() in c++ 20
	unsigned int Bitmask;
};
