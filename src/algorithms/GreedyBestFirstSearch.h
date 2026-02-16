#pragma once
#include "SearchAlgorithm.h"
#include <memory>

namespace searching {

class GreedyBestFirstSearch : public SearchAlgorithm {
public:
    SearchResult search(const SearchProblem& problem) override;

private:
    struct NodeComparator {
        const SearchProblem* problem;
        NodeComparator(const SearchProblem* p) : problem(p) {}
        bool operator()(const std::shared_ptr<SearchNode>& a,
                        const std::shared_ptr<SearchNode>& b) const {
            return problem->heuristic(*a->state) >
                   problem->heuristic(*b->state);
        }
    };
};

} // namespace searching
