#include "DepthFirstSearch.h"
#include <unordered_set>
#include <iostream>

namespace searching {

SearchResult DepthFirstSearch::search(const SearchProblem& problem) {
    SearchResult result;
    // Use explored set for Graph Search to avoid infinite loops in cycles
    std::unordered_set<std::shared_ptr<State>, StatePtrHash, StatePtrEqual> explored;

    auto initialState = problem.getInitialState();
    auto rootNode = std::make_shared<SearchNode>(initialState);

    myFrontier.push(rootNode);
    explored.insert(initialState);
    result.nodesExpanded = 0;
    result.maxFrontierSize = 1;

    while (!myFrontier.empty()) {
        // Update max frontier size
        if (myFrontier.size() > result.maxFrontierSize) {
            result.maxFrontierSize = myFrontier.size();
        }

        auto node = myFrontier.top();
        myFrontier.pop();
        result.visitedStates.push_back(node->state);
        result.nodesExpanded++;

        // Expand node
        auto actions = problem.getActions(*node->state);
        
        // Note: Standard DFS often pushes neighbors in reverse order so the first neighbor 
        // is popped first, but here we stick to the provided order or simple iteration.
        
        for (const auto& action : actions) {
            auto childState = problem.getResult(*node->state, action);
            if (!childState) continue;

            // Cycle detection using value-based comparison
            if (explored.find(childState) != explored.end()) {
                continue;
            }

            double stepCost = problem.getStepCost(*node->state, action, *childState);
            auto childNode = std::make_shared<SearchNode>(
                childState, node, action, node->pathCost + stepCost, node->depth + 1);

            myFrontier.push(childNode);
            explored.insert(childState);
            if (problem.isGoal(*childNode->state)) {
                result.success = true;
                result.solution = extractSolution(childNode);
                result.totalCost = childNode->pathCost;
                return result;
            }
        }
    }

    // No solution found
    result.success = false;
    return result;
}

} // namespace searching
