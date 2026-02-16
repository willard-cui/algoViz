#pragma once
#include "SearchAlgorithm.h"
#include <queue>
#include <vector>
#include <memory>

namespace searching {

class UniformCostSearch : public SearchAlgorithm {
public:
    SearchResult search(const SearchProblem& problem) override;

private:
    struct NodeComparator {
        bool operator()(const std::shared_ptr<SearchNode>& a,
                       const std::shared_ptr<SearchNode>& b) const {
            return a->pathCost > b->pathCost;
        }
    };

    std::priority_queue<std::shared_ptr<SearchNode>,
                       std::vector<std::shared_ptr<SearchNode>>,
                       NodeComparator> myFrontier;
};

} // namespace searching
