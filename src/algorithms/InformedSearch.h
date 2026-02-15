#pragma once

#include "SearchAlgorithm.h"
#include <queue>
#include <functional>
#include <limits>

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

class AStarSearch : public SearchAlgorithm {
public:
    SearchResult search(const SearchProblem& problem) override;

private:
    struct NodeComparator {
        const SearchProblem* problem;
        NodeComparator(const SearchProblem* p) : problem(p) {}
        bool operator()(const std::shared_ptr<SearchNode>& a,
                        const std::shared_ptr<SearchNode>& b) const {
            double f_a = a->pathCost + problem->heuristic(*a->state);
            double f_b = b->pathCost + problem->heuristic(*b->state);
            return f_a > f_b;
        }
    };
};

class WeightedAStarSearch : public SearchAlgorithm {
public:
    explicit WeightedAStarSearch(double weight = 2.0) : weight(weight) {}
    SearchResult search(const SearchProblem& problem) override;

private:
    double weight;
    struct NodeComparator {
        const SearchProblem* problem;
        double weight;
        NodeComparator(const SearchProblem* p, double w) : problem(p), weight(w) {}
        bool operator()(const std::shared_ptr<SearchNode>& a,
                        const std::shared_ptr<SearchNode>& b) const {
            double f_a = a->pathCost + weight * problem->heuristic(*a->state);
            double f_b = b->pathCost + weight * problem->heuristic(*b->state);
            return f_a > f_b;
        }
    };
};

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
