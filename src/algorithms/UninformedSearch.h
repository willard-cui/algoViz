#pragma once

#include "SearchAlgorithm.h"
#include <queue>
#include <stack>

namespace searching {

class BreadthFirstSearch : public SearchAlgorithm {
public:
    SearchResult search(const SearchProblem& problem) override;

private:
    std::queue<std::shared_ptr<SearchNode>> frontier;
};

class DepthFirstSearch : public SearchAlgorithm {
public:
    SearchResult search(const SearchProblem& problem) override;

private:
    std::stack<std::shared_ptr<SearchNode>> frontier;
};

class DepthLimitedSearch : public SearchAlgorithm {
public:
    explicit DepthLimitedSearch(int depthLimit) : depthLimit(depthLimit) {}
    SearchResult search(const SearchProblem& problem) override;

private:
    int depthLimit;
    SearchResult recursiveDLS(const std::shared_ptr<SearchNode>& node,
                             const SearchProblem& problem,
                             int depth);
};

class IterativeDeepeningDFS : public SearchAlgorithm {
public:
    SearchResult search(const SearchProblem& problem) override;
};

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
                       NodeComparator> frontier;
};

} // namespace searching
