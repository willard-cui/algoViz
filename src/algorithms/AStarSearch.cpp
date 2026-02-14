#include "InformedSearch.h"
#include <unordered_map>
#include <queue>
#include <iostream>

namespace searching {

SearchResult AStarSearch::search(const SearchProblem& problem) {
    SearchResult result;
    std::unordered_map<std::shared_ptr<State>, double> reached; // state -> best f-cost so far

    NodeComparator comparator(&problem);
    std::priority_queue<std::shared_ptr<SearchNode>,
                       std::vector<std::shared_ptr<SearchNode>>,
                       NodeComparator> frontier(comparator);

    auto initialState = problem.getInitialState();
    auto rootNode = std::make_shared<SearchNode>(initialState);

    frontier.push(rootNode);
    reached[initialState] = problem.heuristic(*initialState); // f = g + h, g=0 initially
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

        // Check if this is still the best path to this state
        double fValue = node->pathCost + problem.heuristic(*node->state);
        auto it = reached.find(node->state);
        if (it != reached.end() && fValue > it->second + 1e-9) {
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
            double newPathCost = node->pathCost + stepCost;
            double newFValue = newPathCost + problem.heuristic(*childState);

            // Check if we found a better path to this state
            auto childIt = reached.find(childState);
            if (childIt != reached.end() && newFValue >= childIt->second - 1e-9) {
                continue; // Not better
            }

            auto childNode = std::make_shared<SearchNode>(
                childState, node, action, newPathCost, node->depth + 1);

            frontier.push(childNode);
            reached[childState] = newFValue;
            result.visitedStates.push_back(childState);
        }
    }

    // No solution found
    result.success = false;
    return result;
}

} // namespace searching
