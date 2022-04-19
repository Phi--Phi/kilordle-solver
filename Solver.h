#pragma once

#include "Quickset.h"

#include <vector>

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
	};

	class BestFirstSolver : public Solver
	{
	public:
		BestFirstSolver();
		virtual unsigned short Solve() override;

		std::vector<const char*> CurrentGuesses;
	private:
		void FindNextGuess(const std::vector<Quickset> &FullCoverage, std::vector<const char*> &CurrentGuesses);
	};

	class ExhuastiveSolver : public Solver
	{
	public:
		ExhuastiveSolver();
		virtual unsigned short Solve() override;
	};
}
