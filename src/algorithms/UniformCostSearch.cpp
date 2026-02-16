#include "UniformCostSearch.h"
#include <unordered_map>
#include <iostream>

namespace searching {

SearchResult UniformCostSearch::search(const SearchProblem& problem) {
    SearchResult result;
    std::unordered_map<std::shared_ptr<State>, double, StatePtrHash, StatePtrEqual> reached; // state -> best cost so far

    auto initialState = problem.getInitialState();
    auto rootNode = std::make_shared<SearchNode>(initialState);

    // For UCS, we put initial node in frontier
    myFrontier.push(rootNode);
    reached[initialState] = 0.0;
    
    result.nodesExpanded = 0;
    result.maxFrontierSize = 1;

    while (!myFrontier.empty()) {
        // Update max frontier size
        if (myFrontier.size() > result.maxFrontierSize) {
            result.maxFrontierSize = myFrontier.size();
        }

        auto node = myFrontier.top();
        myFrontier.pop();
        result.nodesExpanded++;
        result.visitedStates.push_back(node->state);
        
        // Check if this node is still the best path to its state
        // If the current node's cost is greater than the cost recorded in 'reached', it means this is not the optimal path.
        // Since nodes are processed in increasing order of cost, we can skip this node to avoid revisiting states.
        auto it = reached.find(node->state);
        if (it != reached.end() && node->pathCost > it->second + 1e-9) {
            continue;
        }

        // Check if goal
        // Do not check on first visit to allow finding a better solution
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
            // If we found a better path to this state, we will add it to the frontier
            // This allows us to explore multiple paths to the same state with different costs
            // Priority queue removal is inefficient, so we do not remove old nodes
            auto childIt = reached.find(childState);
            if (childIt != reached.end() && newCost >= childIt->second - 1e-9) {
                continue;
            }

            auto childNode = std::make_shared<SearchNode>(
                childState, node, action, newCost, node->depth + 1);

            myFrontier.push(childNode);
            reached[childState] = newCost;
        }
    }

    // No solution found
    result.success = false;
    return result;
}

} // namespace searching
