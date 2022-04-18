#pragma once

#include "Quickset.h"

#include <vector>

namespace kilordle
{
	int main();
	short CalculatePerformanceOfGuess(const std::vector<Quickset> &FullCoverage, const std::vector<const char*>& CurrentGuesses, const char* Word);
	void FindNextGuess(const std::vector<Quickset> &FullCoverage, std::vector<const char*>& CurrentGuesses);
	const char* FindWord(const char*);
}
