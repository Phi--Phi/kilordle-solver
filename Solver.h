#pragma once

#include "Quickset.h"

#include <vector>

namespace kilordle
{
	class Solver
	{
	public:
		virtual void Solve() = 0;
		unsigned char CalculatePerformance(const std::vector<Quickset> &FullCoverage, const std::vector<const char*> &CurrentGuesses);
		void PrintGuesses(const std::vector<const char*> &GuessList);
	};

	class BestFirstSolver : public Solver
	{
	public:
		virtual void Solve() override;
	private:
		void FindNextGuess(const std::vector<Quickset> &FullCoverage, std::vector<const char*> &CurrentGuesses);
	};
	
}
