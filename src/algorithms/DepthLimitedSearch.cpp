#include "DepthLimitedSearch.h"
#include <iostream>

namespace searching {

SearchResult DepthLimitedSearch::search(const SearchProblem& problem) {
    SearchResult result;
    result = recursiveDLS(std::make_shared<SearchNode>(problem.getInitialState()),
                         problem, myDepthLimit);
    return result;
}

SearchResult DepthLimitedSearch::recursiveDLS(const std::shared_ptr<SearchNode>& node,
                                             const SearchProblem& problem,
                                             int depth) {
    SearchResult result;
    result.nodesExpanded = 1; // This node is being expanded
    result.visitedStates.push_back(node->state);

    // Check if goal
    if (problem.isGoal(*node->state)) {
        result.success = true;
        result.solution = extractSolution(node);
        result.totalCost = node->pathCost;
        result.maxFrontierSize = 1; // Recursive depth doesn't have a traditional frontier
        return result;
    }

    // Check depth limit
    if (depth <= 0) {
        result.success = false;
        result.maxFrontierSize = 1;
        return result;
    }

    bool cutoffOccurred = false;
    int maxDepthReached = 0;

    // Expand node
    auto actions = problem.getActions(*node->state);
    for (const auto& action : actions) {
        auto childState = problem.getResult(*node->state, action);
        if (!childState) continue;

        double stepCost = problem.getStepCost(*node->state, action, *childState);
        auto childNode = std::make_shared<SearchNode>(
            childState, node, action, node->pathCost + stepCost, node->depth + 1);

        SearchResult childResult = recursiveDLS(childNode, problem, depth - 1);
        result.nodesExpanded += childResult.nodesExpanded;
        
        // Accumulate visited states regardless of success
        result.visitedStates.insert(result.visitedStates.end(),
                                   childResult.visitedStates.begin(),
                                   childResult.visitedStates.end());

        if (childResult.success) {
            // Propagate success up
            result.success = true;
            result.solution = childResult.solution;
            result.totalCost = childResult.totalCost;
            result.maxFrontierSize = std::max(result.maxFrontierSize, childResult.maxFrontierSize);
            return result;
        } else if (!childResult.success && childResult.maxFrontierSize > 0) {
            // Cutoff occurred
            cutoffOccurred = true;
            maxDepthReached = std::max(maxDepthReached, childResult.maxFrontierSize);
        }
    }

    // No solution found at this depth
    result.success = false;
    result.maxFrontierSize = maxDepthReached + 1;
    return result;
}

} // namespace searching
