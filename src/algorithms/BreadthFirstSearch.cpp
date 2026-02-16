#include "BreadthFirstSearch.h"
#include <unordered_set>
#include <iostream>

namespace searching {

SearchResult BreadthFirstSearch::search(const SearchProblem& problem) {
    SearchResult result;
    std::unordered_set<std::shared_ptr<State>, StatePtrHash, StatePtrEqual> reached;

    auto initialState = problem.getInitialState();
    auto rootNode = std::make_shared<SearchNode>(initialState);

    myFrontier.push(rootNode);
    reached.insert(initialState);
    result.nodesExpanded = 0;
    result.maxFrontierSize = 1;

    while (!myFrontier.empty()) {
        // Update max frontier size
        if (myFrontier.size() > result.maxFrontierSize) {
            result.maxFrontierSize = myFrontier.size();
        }

        
        auto node = myFrontier.front();
        myFrontier.pop();
        result.nodesExpanded++;
        result.visitedStates.push_back(node->state);
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

            myFrontier.push(childNode);
            reached.insert(childState);
            
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
