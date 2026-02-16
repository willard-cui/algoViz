#include "GreedyBestFirstSearch.h"
#include <unordered_map>
#include <queue>
#include <iostream>

namespace searching {

SearchResult GreedyBestFirstSearch::search(const SearchProblem& problem) {
    SearchResult result;
    std::unordered_map<std::shared_ptr<State>, double, StatePtrHash, StatePtrEqual> reached; // state -> best h-value so far

    NodeComparator comparator(&problem);
    std::priority_queue<std::shared_ptr<SearchNode>,
                       std::vector<std::shared_ptr<SearchNode>>,
                       NodeComparator> frontier(comparator);

    auto initialState = problem.getInitialState();
    auto rootNode = std::make_shared<SearchNode>(initialState);

    frontier.push(rootNode);
    reached[initialState] = problem.heuristic(*initialState);
    result.nodesExpanded = 0;
    result.maxFrontierSize = 1;

    while (!frontier.empty()) {
        // Update max frontier size
        if (frontier.size() > result.maxFrontierSize) {
            result.maxFrontierSize = frontier.size();
        }

        auto node = frontier.top();
        frontier.pop();
        result.nodesExpanded++;
        result.visitedStates.push_back(node->state);
        // Check if this is still the best path to this state
        // (For greedy search, we might not need this check strictly,
        // but it helps avoid redundant work)
        double hValue = problem.heuristic(*node->state);
        auto it = reached.find(node->state);
        if (it != reached.end() && hValue > it->second + 1e-9) {
            // Found a path with same or better h-value already, skip
            continue;
        }

        // Check if goal
        if (problem.isGoal(*node->state)) {
            result.success = true;
            result.solution = extractSolution(node);
            result.totalCost = node->pathCost;
            return result;
        }

        // Expand node
        auto actions = problem.getActions(*node->state);
        for (const auto& action : actions) {
            auto childState = problem.getResult(*node->state, action);
            if (!childState) continue;

            double childHValue = problem.heuristic(*childState);

            // Check if we already have a path to this state with same or better h-value
            auto childIt = reached.find(childState);
            if (childIt != reached.end() && childHValue >= childIt->second - 1e-9) {
                continue; // Not better
            }

            double stepCost = problem.getStepCost(*node->state, action, *childState);
            auto childNode = std::make_shared<SearchNode>(
                childState, node, action, node->pathCost + stepCost, node->depth + 1);

            frontier.push(childNode);
            reached[childState] = childHValue;
            
        }
    }

    // No solution found
    result.success = false;
    return result;
}

} // namespace searching
