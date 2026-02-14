#include "UninformedSearch.h"
#include <unordered_map>
#include <iostream>

namespace searching {

SearchResult UniformCostSearch::search(const SearchProblem& problem) {
    SearchResult result;
    std::unordered_map<std::shared_ptr<State>, double> reached; // state -> best cost so far

    auto initialState = problem.getInitialState();
    auto rootNode = std::make_shared<SearchNode>(initialState);

    frontier.push(rootNode);
    reached[initialState] = 0.0;
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

        // Check if this node is still the best path to its state
        auto it = reached.find(node->state);
        if (it != reached.end() && node->pathCost > it->second + 1e-9) {
            // Found a better path to this state already, skip
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

            double stepCost = problem.getStepCost(*node->state, action, *childState);
            double newCost = node->pathCost + stepCost;

            // Check if we found a better path to this state
            auto childIt = reached.find(childState);
            if (childIt != reached.end() && newCost >= childIt->second - 1e-9) {
                continue; // Not better
            }

            auto childNode = std::make_shared<SearchNode>(
                childState, node, action, newCost, node->depth + 1);

            frontier.push(childNode);
            reached[childState] = newCost;
            result.visitedStates.push_back(childState);
        }
    }

    // No solution found
    result.success = false;
    return result;
}

} // namespace searching
