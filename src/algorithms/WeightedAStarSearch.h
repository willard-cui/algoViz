#pragma once
#include "SearchAlgorithm.h"
#include <memory>

namespace searching {

class WeightedAStarSearch : public SearchAlgorithm {
public:
    explicit WeightedAStarSearch(double weight = 2.0) : myWeight(weight) {}
    SearchResult search(const SearchProblem& problem) override;

private:
    double myWeight;
    struct NodeComparator {
        const SearchProblem* problem;
        double weight;
        NodeComparator(const SearchProblem* p, double w) : problem(p), weight(w) {}
        bool operator()(const std::shared_ptr<SearchNode>& a,
                        const std::shared_ptr<SearchNode>& b) const {
            double fScoreA = a->pathCost + weight * problem->heuristic(*a->state);
            double fScoreB = b->pathCost + weight * problem->heuristic(*b->state);
            return fScoreA > fScoreB;
        }
    };
};

} // namespace searching
