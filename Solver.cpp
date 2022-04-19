#include "Solver.h"
#include "Words.h"

#include <iostream>
#include <algorithm>

int main()
{
	kilordle::BestFirstSolver BFS;

	BFS.Solve();

	return 0;
}

kilordle::Solver::Solver()
{
	FullCoverage.resize(WORD_LENGTH);
	FullCoverage.shrink_to_fit();
	ComputeFullCoverage(FullCoverage);

	FullCoveragePerformance = 0;

	for (auto X : FullCoverage)
	{
		FullCoveragePerformance += X.BitCount();
	}

	RedditOptimalGuesses.reserve(30);
	RedditOptimalGuesses.push_back(FindWord("fixer"));
	RedditOptimalGuesses.push_back(FindWord("rowdy"));
	RedditOptimalGuesses.push_back(FindWord("crump"));
	RedditOptimalGuesses.push_back(FindWord("aback"));
	RedditOptimalGuesses.push_back(FindWord("twixt"));
	RedditOptimalGuesses.push_back(FindWord("banjo"));
	RedditOptimalGuesses.push_back(FindWord("usque"));
	RedditOptimalGuesses.push_back(FindWord("glyph"));
	RedditOptimalGuesses.push_back(FindWord("kvell"));
	RedditOptimalGuesses.push_back(FindWord("schwa"));
	RedditOptimalGuesses.push_back(FindWord("nkosi"));
	RedditOptimalGuesses.push_back(FindWord("ydrad"));
	RedditOptimalGuesses.push_back(FindWord("zesty"));
	RedditOptimalGuesses.push_back(FindWord("djinn"));
	RedditOptimalGuesses.push_back(FindWord("vuggs"));
	RedditOptimalGuesses.push_back(FindWord("optic"));
	RedditOptimalGuesses.push_back(FindWord("hydro"));
	RedditOptimalGuesses.push_back(FindWord("whiff"));
	RedditOptimalGuesses.push_back(FindWord("aglow"));
	RedditOptimalGuesses.push_back(FindWord("enzym"));
	RedditOptimalGuesses.push_back(FindWord("itchy"));
	RedditOptimalGuesses.push_back(FindWord("luvvy"));
	RedditOptimalGuesses.push_back(FindWord("mekka"));
	RedditOptimalGuesses.push_back(FindWord("pzazz"));
	RedditOptimalGuesses.push_back(FindWord("embog"));
	RedditOptimalGuesses.push_back(FindWord("jambu"));
	RedditOptimalGuesses.push_back(FindWord("expel"));
	RedditOptimalGuesses.push_back(FindWord("affix"));
	RedditOptimalGuesses.push_back(FindWord("qajaq"));
	RedditOptimalGuesses.push_back(FindWord("squib"));
}

unsigned char kilordle::Solver::CalculatePerformance(const std::vector<Quickset> &FullCoverage, const std::vector<const char*> &CurrentGuesses)
{
	unsigned char Result = 0;
	Quickset ActiveChars[WORD_LENGTH];

	for (const char* Guess : CurrentGuesses)
	{
		for (short Index = 0; Index < WORD_LENGTH; Index++)
		{
			ActiveChars[Index].insert(Guess[Index]);
		}
	}

	for (short Index = 0; Index < WORD_LENGTH; Index++)
	{
		unsigned int UsedChars = ActiveChars[Index].Bitmask & FullCoverage[Index].Bitmask;
		Result += Quickset(UsedChars).BitCount();
	}

	return Result;
}

void kilordle::Solver::PrintGuesses(const std::vector<const char*> &GuessList)
{
	for (auto X : GuessList)
	{
		for (short Index = 0; Index < WORD_LENGTH; Index++)
		{
			std::cout << X[Index];
		}

		std::cout << std::endl;
	}
}

void kilordle::BestFirstSolver::FindNextGuess(const std::vector<Quickset> &FullCoverage, std::vector<const char*> &CurrentGuesses)
{
	const char* BestGuess = WORDS[0];
	short BestGuessHitCount = 0;

	for (const char* Word : WORDS)
	{
		CurrentGuesses.push_back(Word);
		short HitCount = CalculatePerformance(FullCoverage, CurrentGuesses);
		CurrentGuesses.pop_back();

		if (HitCount > BestGuessHitCount)
		{
			BestGuess = Word;
			BestGuessHitCount = HitCount;
		}
	}

	for (const char* Word : WORDLES)
	{
		CurrentGuesses.push_back(Word);
		short HitCount = CalculatePerformance(FullCoverage, CurrentGuesses);
		CurrentGuesses.pop_back();

		if (HitCount > BestGuessHitCount)
		{
			BestGuess = Word;
			BestGuessHitCount = HitCount;
		}
	}

	CurrentGuesses.push_back(BestGuess);
}

kilordle::BestFirstSolver::BestFirstSolver() : Solver()
{
}

unsigned short kilordle::BestFirstSolver::Solve()
{
	std::cout << "best-first optimized guesses are: " << std::endl;

	while (CalculatePerformance(FullCoverage, CurrentGuesses) < FullCoveragePerformance)
	{
		FindNextGuess(FullCoverage, CurrentGuesses);
	}

	PrintGuesses(CurrentGuesses);

	std::cout << std::endl << "we did it in " << CurrentGuesses.size() << " guesses" << std::endl;

	return CurrentGuesses.size();
}

kilordle::ExhuastiveSolver::ExhuastiveSolver() : Solver()
{
}

unsigned short kilordle::ExhuastiveSolver::Solve()
{

	return 100U;
}
