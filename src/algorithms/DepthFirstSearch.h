#pragma once
#include "SearchAlgorithm.h"
#include <stack>
#include <memory>

namespace searching {

class DepthFirstSearch : public SearchAlgorithm {
public:
    SearchResult search(const SearchProblem& problem) override;

private:
    std::stack<std::shared_ptr<SearchNode>> myFrontier;
};

} // namespace searching
