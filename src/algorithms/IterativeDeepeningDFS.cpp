#include "UninformedSearch.h"
#include <iostream>

namespace searching {

SearchResult IterativeDeepeningDFS::search(const SearchProblem& problem) {
    SearchResult result;
    result.maxFrontierSize = 0;
    result.nodesExpanded = 0;

    // Keep increasing depth limit until solution found
    for (int depth = 0; depth <= 1000; depth++) { // Practical depth limit
        DepthLimitedSearch dls(depth);
        SearchResult depthResult = dls.search(problem);

        result.nodesExpanded += depthResult.nodesExpanded;
        result.maxFrontierSize = std::max(result.maxFrontierSize, depthResult.maxFrontierSize);
        result.visitedStates.insert(result.visitedStates.end(),
                                   depthResult.visitedStates.begin(),
                                   depthResult.visitedStates.end());

        if (depthResult.success) {
            result.success = true;
            result.solution = depthResult.solution;
            result.totalCost = depthResult.totalCost;
            return result;
        }

        // If no cutoff occurred at this depth (i.e., fully explored finite space),
        // then no solution exists
        if (depthResult.maxFrontierSize <= 1 && depth > 0) {
            // This suggests the entire finite space was explored
            break;
        }
    }

    // No solution found within depth limit
    result.success = false;
    return result;
}

} // namespace searching
