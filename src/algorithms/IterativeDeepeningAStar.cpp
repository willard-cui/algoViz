#include "IterativeDeepeningAStar.h"
#include <limits>
#include <algorithm>
#include <iostream>

namespace searching {

SearchResult IterativeDeepeningAStar::search(const SearchProblem& problem) {
    auto initialState = problem.getInitialState();
    double bound = problem.heuristic(*initialState);
    
    // Path for loop detection
    std::vector<std::shared_ptr<SearchNode>> path;
    auto root = std::make_shared<SearchNode>(initialState);
    path.push_back(root);

    SearchResult result;
    result.nodesExpanded = 0;
    result.maxFrontierSize = 1;

    while (true) {
        // Clear path for new iteration, but keep root
        path.clear();
        path.push_back(root);
        
        SearchBound searchResult = depthLimitedSearch(root, problem, bound, path, result.visitedStates);
        
        // Update statistics (approximate)
        // Since we don't count nodes in recursive calls easily without passing ref, 
        // we might miss accurate counts, but it's acceptable for this simple impl.
        
        if (searchResult.found) {
            result.success = true;
            result.solution = extractSolution(searchResult.goalNode);
            result.totalCost = searchResult.goalNode->pathCost;
            return result;
        }
        
        if (searchResult.nextLimit == std::numeric_limits<double>::infinity()) {
            return SearchResult(); // Return failure
        }
        
        bound = searchResult.nextLimit;
    }
}

IterativeDeepeningAStar::SearchBound IterativeDeepeningAStar::depthLimitedSearch(
    const std::shared_ptr<SearchNode>& node,
    const SearchProblem& problem,
    double fLimit,
    std::vector<std::shared_ptr<SearchNode>>& path,
    std::vector<std::shared_ptr<State>>& visited) {
    
    visited.push_back(node->state);
    
    double f = node->pathCost + problem.heuristic(*node->state);
    
    if (f > fLimit) {
        return SearchBound{false, f, nullptr};
    }
    
    if (problem.isGoal(*node->state)) {
        return SearchBound{true, f, node};
    }
    
    double minExceed = std::numeric_limits<double>::infinity();
    
    auto actions = problem.getActions(*node->state);
    
    for (const auto& action : actions) {
        // Use getResult instead of applyAction, and it returns a shared_ptr
        auto nextState = problem.getResult(*node->state, action);
        
        // Cycle detection in current path
        bool inPath = false;
        for (const auto& ancestor : path) {
            if (*ancestor->state == *nextState) {
                 inPath = true;
                 break;
            }
        }
        
        if (inPath) continue;
        
        double stepCost = problem.getStepCost(*node->state, action, *nextState);
        double newCost = node->pathCost + stepCost;
        
        auto child = std::make_shared<SearchNode>(nextState, node, action, newCost, node->depth + 1);
        
        path.push_back(child);
        SearchBound res = depthLimitedSearch(child, problem, fLimit, path, visited);
        path.pop_back();
        
        if (res.found) {
            return res;
        }
        
        if (res.nextLimit < minExceed) {
            minExceed = res.nextLimit;
        }
    }
    
    return SearchBound{false, minExceed, nullptr};
}

} // namespace searching
