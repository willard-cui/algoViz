#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <string>

namespace searching {

struct State {
    virtual ~State() = default;
    virtual bool operator==(const State& other) const = 0;
    virtual size_t hash() const = 0;
};

struct Action {
    std::string name;
    double cost = 1.0;
};

class SearchProblem {
public:
    virtual ~SearchProblem() = default;
    virtual std::shared_ptr<State> getInitialState() const = 0;
    virtual bool isGoal(const State& state) const = 0;
    virtual std::vector<Action> getActions(const State& state) const = 0;
    virtual std::shared_ptr<State> getResult(const State& state, const Action& action) const = 0;
    virtual double getStepCost(const State& state, const Action& action,
                               const State& successor) const = 0;
    virtual double heuristic(const State& state) const { return 0.0; }
};

struct SearchNode {
    std::shared_ptr<State> state;
    std::shared_ptr<SearchNode> parent;
    Action action;
    double pathCost = 0.0;
    int depth = 0;

    SearchNode(std::shared_ptr<State> s, std::shared_ptr<SearchNode> p = nullptr,
               Action a = {}, double cost = 0.0, int d = 0)
        : state(s), parent(p), action(a), pathCost(cost), depth(d) {}
};

struct SearchResult {
    bool success = false;
    std::vector<Action> solution;
    double totalCost = 0.0;
    int nodesExpanded = 0;
    int maxFrontierSize = 0;
    std::vector<std::shared_ptr<State>> visitedStates;
};

class SearchAlgorithm {
public:
    virtual ~SearchAlgorithm() = default;
    virtual SearchResult search(const SearchProblem& problem) = 0;

protected:
    std::vector<Action> extractSolution(std::shared_ptr<SearchNode> goalNode) const;
};

} // namespace searching
