#include "UninformedSearch.h"
#include <unordered_set>
#include <iostream>

namespace searching {

// Helper structs for hashing shared_ptr<State> by value
struct StatePtrHash {
    size_t operator()(const std::shared_ptr<State>& s) const {
        return s ? s->hash() : 0;
    }
};

struct StatePtrEqual {
    bool operator()(const std::shared_ptr<State>& a, const std::shared_ptr<State>& b) const {
        if (!a || !b) return a == b;
        return *a == *b;
    }
};

SearchResult DepthFirstSearch::search(const SearchProblem& problem) {
    SearchResult result;
    // Use explored set for Graph Search to avoid infinite loops in cycles
    std::unordered_set<std::shared_ptr<State>, StatePtrHash, StatePtrEqual> explored;

    auto initialState = problem.getInitialState();
    auto rootNode = std::make_shared<SearchNode>(initialState);

    frontier.push(rootNode);
    explored.insert(initialState);
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

        // Check if goal
        if (problem.isGoal(*node->state)) {
            result.success = true;
            result.solution = extractSolution(node);
            result.totalCost = node->pathCost;
            return result;
        }

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

            frontier.push(childNode);
            explored.insert(childState);
            result.visitedStates.push_back(childState);
        }
    }

    // No solution found
    result.success = false;
    return result;
}

} // namespace searching
