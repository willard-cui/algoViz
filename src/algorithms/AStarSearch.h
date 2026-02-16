#pragma once
#include "SearchAlgorithm.h"
#include <memory>

namespace searching {

class AStarSearch : public SearchAlgorithm {
public:
    SearchResult search(const SearchProblem& problem) override;

private:
    struct NodeComparator {
        const SearchProblem* problem;
        NodeComparator(const SearchProblem* p) : problem(p) {}
        bool operator()(const std::shared_ptr<SearchNode>& a,
                        const std::shared_ptr<SearchNode>& b) const {
            double fScoreA = a->pathCost + problem->heuristic(*a->state);
            double fScoreB = b->pathCost + problem->heuristic(*b->state);
            return fScoreA > fScoreB;
        }
    };
};

} // namespace searching
