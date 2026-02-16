#pragma once
#include "SearchAlgorithm.h"

namespace searching {

class IterativeDeepeningDFS : public SearchAlgorithm {
public:
    SearchResult search(const SearchProblem& problem) override;
};

} // namespace searching
