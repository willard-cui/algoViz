#pragma once

#include "SearchAlgorithm.h"
#include "GreedyBestFirstSearch.h"
#include "AStarSearch.h"
#include "WeightedAStarSearch.h"
#include "IterativeDeepeningAStar.h"

namespace searching {

class BidirectionalSearch : public SearchAlgorithm {
public:
    SearchResult search(const SearchProblem& problem) override;
};

class RecursiveBestFirstSearch : public SearchAlgorithm {
public:
    SearchResult search(const SearchProblem& problem) override;

private:
    struct RBFSResult {
        double fValue;
        SearchResult result;
    };

    RBFSResult rbfs(const std::shared_ptr<SearchNode>& node,
                    const SearchProblem& problem,
                    double fLimit,
                    double& bestAlternative);
};

} // namespace searching
