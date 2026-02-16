#pragma once
#include "SearchAlgorithm.h"
#include <memory>

namespace searching {

class DepthLimitedSearch : public SearchAlgorithm {
public:
    explicit DepthLimitedSearch(int depthLimit) : myDepthLimit(depthLimit) {}
    SearchResult search(const SearchProblem& problem) override;

private:
    int myDepthLimit;
    SearchResult recursiveDLS(const std::shared_ptr<SearchNode>& node,
                             const SearchProblem& problem,
                             int depth);
};

} // namespace searching
