#include "Solver.h"
#include "Words.h"

#include <iostream>
#include <algorithm>

namespace kilordle
{
	void ComputeFullCoverage(std::vector<Quickset>& FullCoverage)
	{
		for (const char* Wordle : WORDLES)
		{
			for (char Index = 0; Index < 5; Index++)
			{
				FullCoverage[Index].insert(Wordle[Index]);
			}
		}
	}
}

int main()
{
	return kilordle::main();
}

short kilordle::CalculatePerformanceOfGuess(const std::vector<Quickset> &FullCoverage, const std::vector<const char*>& CurrentGuesses, const char* Word)
{
	short Result = 0;
	Quickset ActiveChars[5];

	for (const char* Guess : CurrentGuesses)
	{
		for (short Index = 0; Index < 5; Index++)
		{
			ActiveChars[Index].insert(Guess[Index]);
		}
	}

	for (short Index = 0; Index < 5; Index++)
	{
		ActiveChars[Index].insert(Word[Index]);

		unsigned int UsedChars = ActiveChars[Index].Bitmask & FullCoverage[Index].Bitmask;
		Result += Quickset(UsedChars).BitCount();
	}

	return Result;
}

void kilordle::FindNextGuess(const std::vector<Quickset>& FullCoverage, std::vector<const char*> &CurrentGuesses)
{
	const char* BestGuess = WORDS[0];
	short BestGuessHitCount = 0;

	for (const char* Word : WORDS)
	{
		short HitCount = CalculatePerformanceOfGuess(FullCoverage, CurrentGuesses, Word);

		if (HitCount > BestGuessHitCount)
		{
			BestGuess = Word;
			BestGuessHitCount = HitCount;
		}
	}

	for (const char* Word : WORDLES)
	{
		short HitCount = CalculatePerformanceOfGuess(FullCoverage, CurrentGuesses, Word);

		if (HitCount > BestGuessHitCount)
		{
			BestGuess = Word;
			BestGuessHitCount = HitCount;
		}
	}

	CurrentGuesses.push_back(BestGuess);
}

const char* kilordle::FindWord(const char* x)
{
	for (const char* Word : WORDS)
	{
		if (strncmp(Word, x, 5) == 0)
		{
			return Word;
		}
	}

	for (const char* Word : WORDLES)
	{
		if (strncmp(Word, x, 5) == 0)
		{
			return Word;
		}
	}
}

int kilordle::main()
{
	std::cout << "Welcome to kilordle solver" << std::endl;

	constexpr double ProbilbilityWordChosen = 1.0 - ((NUM_WORDLES - 1000.0) / NUM_WORDLES);
	constexpr char GUESS_LIMIT = 38;

	std::vector<Quickset> FullCoverage(5);

	ComputeFullCoverage(FullCoverage);

	std::cout << "best-first optimized guesses are" << std::endl;

	std::vector<const char*> CurrentGuesses;

	for (char Index = 0; Index < GUESS_LIMIT; Index++)
	{
		FindNextGuess(FullCoverage, CurrentGuesses);
	}

	for (auto X : CurrentGuesses)
	{
		for (short Index = 0; Index < 5; Index++)
		{
			std::cout << X[Index];
		}

		std::cout << std::endl;
	}

	std::cout << std::endl << "list performance: " << CalculatePerformanceOfGuess(FullCoverage, CurrentGuesses, CurrentGuesses[0]) << std::endl;

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

	std::cout << std::endl << "reddit optimized list performance: " << CalculatePerformanceOfGuess(FullCoverage, RedditOptimalGuesses, RedditOptimalGuesses[0]) << std::endl;

	unsigned int MaxHull = 0;

	for (auto x : FullCoverage)
	{
		MaxHull += x.BitCount();
	}

	std::cout << std::endl << "max possible performance: " << MaxHull << std::endl;

	return 0;
}