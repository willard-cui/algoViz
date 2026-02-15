#include "UninformedSearch.h"
#include <unordered_set>
#include <iostream>

namespace searching {

SearchResult BreadthFirstSearch::search(const SearchProblem& problem) {
    SearchResult result;
    std::unordered_set<std::shared_ptr<State>, StatePtrHash, StatePtrEqual> reached;

    auto initialState = problem.getInitialState();
    auto rootNode = std::make_shared<SearchNode>(initialState);

    frontier.push(rootNode);
    reached.insert(initialState);
    result.nodesExpanded = 0;
    result.maxFrontierSize = 1;

    while (!frontier.empty()) {
        // Update max frontier size
        if (frontier.size() > result.maxFrontierSize) {
            result.maxFrontierSize = frontier.size();
        }

        auto node = frontier.front();
        frontier.pop();
        result.nodesExpanded++;

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

            // Check if already reached
            if (reached.find(childState) != reached.end()) {
                continue;
            }

            double stepCost = problem.getStepCost(*node->state, action, *childState);
            auto childNode = std::make_shared<SearchNode>(
                childState, node, action, node->pathCost + stepCost, node->depth + 1);

            frontier.push(childNode);
            reached.insert(childState);
            result.visitedStates.push_back(childState);
        }
    }

    // No solution found
    result.success = false;
    return result;
}

} // namespace searching
