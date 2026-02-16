#pragma once
#include "SearchAlgorithm.h"
#include <queue>
#include <memory>

namespace searching {

class BreadthFirstSearch : public SearchAlgorithm {
public:
    SearchResult search(const SearchProblem& problem) override;

private:
    std::queue<std::shared_ptr<SearchNode>> myFrontier;
};

} // namespace searching
