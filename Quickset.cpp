#include "Quickset.h"

Quickset::Quickset()
{
	this->Bitmask = 0;
}

Quickset::Quickset(unsigned int mask)
{
	this->Bitmask = mask;
}

short Quickset::count(char x)
{
	int MaskedBit = x - 'a';

	int Mask = 1 << MaskedBit;

	if ((this->Bitmask & Mask) > 0) return 1;
	return 0;
}

void Quickset::insert(char x)
{
	int MaskedBit = x - 'a';

	int Mask = 1 << MaskedBit;

	this->Bitmask |= Mask;
}

short Quickset::BitCount()
{
	unsigned int uCount;

	uCount = this->Bitmask - ((this->Bitmask >> 1) & 033333333333) - ((this->Bitmask >> 2) & 011111111111);
	return (short)(((uCount + (uCount >> 3)) & 030707070707) % 63);
}
