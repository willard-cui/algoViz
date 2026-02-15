#include "SearchAlgorithm.h"
#include <algorithm>

namespace searching {

std::vector<Action> SearchAlgorithm::extractSolution(const std::shared_ptr<SearchNode>& goalNode) const {
    std::vector<Action> solution;
    auto node = goalNode;

    // Trace back from goal to initial state
    while (node && node->parent) {
        solution.push_back(node->action);
        node = node->parent;
    }

    // Reverse to get actions from start to goal
    std::reverse(solution.begin(), solution.end());
    return solution;
}

} // namespace searching
