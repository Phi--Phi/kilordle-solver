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

unsigned char kilordle::Solver::CalculatePerformance(const std::vector<Quickset> &FullCoverage, const std::vector<const char*>& CurrentGuesses)
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

void kilordle::BestFirstSolver::FindNextGuess(const std::vector<Quickset>& FullCoverage, std::vector<const char*> &CurrentGuesses)
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

void kilordle::BestFirstSolver::Solve()
{
	constexpr char GUESS_DEPTH = 38;

	std::vector<Quickset> FullCoverage(WORD_LENGTH);

	ComputeFullCoverage(FullCoverage);

	std::cout << "best-first optimized guesses are" << std::endl;

	std::vector<const char*> CurrentGuesses;

	for (char Index = 0; Index < GUESS_DEPTH; Index++)
	{
		FindNextGuess(FullCoverage, CurrentGuesses);
	}

	for (auto X : CurrentGuesses)
	{
		for (short Index = 0; Index < WORD_LENGTH; Index++)
		{
			std::cout << X[Index];
		}

		std::cout << std::endl;
	}

	std::cout << std::endl << "list performance: " << (unsigned int)CalculatePerformance(FullCoverage, CurrentGuesses) << std::endl;

	std::vector<const char*> RedditOptimalGuesses;

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

	std::cout << std::endl << "reddit optimized list performance: " << (unsigned int)CalculatePerformance(FullCoverage, RedditOptimalGuesses) << std::endl;

	unsigned int MaxHull = 0;

	for (auto x : FullCoverage)
	{
		MaxHull += x.BitCount();
	}

	std::cout << std::endl << "max possible performance: " << MaxHull << std::endl;
}