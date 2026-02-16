#pragma once
#include "SearchAlgorithm.h"
#include <vector>
#include <memory>
#include <limits>

namespace searching {

class IterativeDeepeningAStar : public SearchAlgorithm {
public:
    SearchResult search(const SearchProblem& problem) override;

private:
    struct SearchBound {
        bool found = false;
        double nextLimit = std::numeric_limits<double>::infinity();
        std::shared_ptr<SearchNode> goalNode = nullptr;
    };

    SearchBound depthLimitedSearch(const std::shared_ptr<SearchNode>& node,
                                   const SearchProblem& problem,
                                   double fLimit,
                                   std::vector<std::shared_ptr<SearchNode>>& path,
                                   std::vector<std::shared_ptr<State>>& visited);
};

} // namespace searching
