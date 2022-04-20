#pragma once

#include "Quickset.h"
#include "Words.h"

#include <vector>
#include <concurrent_priority_queue.h>

namespace kilordle
{
	class Solver
	{
	public:
		Solver();
		virtual unsigned short Solve() = 0;
		unsigned char CalculatePerformance(const std::vector<Quickset> &FullCoverage, const std::vector<const char*> &CurrentGuesses);
		void PrintGuesses(const std::vector<const char*> &GuessList);

		std::vector<Quickset> FullCoverage;
		unsigned int FullCoveragePerformance;
		std::vector<const char*> RedditOptimalGuesses;
		bool PrintFlag;
	};

	struct Node
	{
		std::vector<const char*> Guesses;
		unsigned int Performance;
		Quickset Coverage[WORD_LENGTH];

		unsigned char GetCoverageBits(const std::vector<Quickset> &FullCoverage) const;

		Node();
		friend bool operator<(const Node &Left, const Node &Right);
	};

	class BestFirstSolver : public Solver
	{
	public:
		BestFirstSolver();
		virtual unsigned short Solve() override;
		void FindNextGuess(const std::vector<Quickset>& FullCoverage, std::vector<const char*>& CurrentGuesses);

		std::vector<const char*> CurrentGuesses;
	};

	class ExhuastiveSolver : public Solver
	{
	public:
		ExhuastiveSolver();
		virtual unsigned short Solve() override;

		void MakeNextGuess(const Node& Parent);

		concurrency::concurrent_priority_queue<Node> SearchTree;
	};
}
