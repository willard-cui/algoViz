#pragma once

#include "../algorithms/SearchAlgorithm.h"
#include <string>
#include <unordered_map>
#include <vector>

namespace searching {

class RomaniaCityState : public State {
public:
    std::string city;
    explicit RomaniaCityState(const std::string& c) : city(c) {}
    bool operator==(const State& other) const override {
        const RomaniaCityState* rhs = dynamic_cast<const RomaniaCityState*>(&other);
        return rhs && city == rhs->city;
    }
    size_t hash() const override {
        return std::hash<std::string>{}(city);
    }
};

class RomaniaProblem : public SearchProblem {
public:
    RomaniaProblem() {
        initCityCoordinates();
        initRoadNetwork();
    }
    std::shared_ptr<State> getInitialState() const override {
        return std::make_shared<RomaniaCityState>("Arad");
    }
    bool isGoal(const State& state) const override {
        const RomaniaCityState* cityState = dynamic_cast<const RomaniaCityState*>(&state);
        return cityState && cityState->city == "Bucharest";
    }
    std::vector<Action> getActions(const State& state) const override {
        const RomaniaCityState* cityState = dynamic_cast<const RomaniaCityState*>(&state);
        if (!cityState) return {};
        auto it = roadNetwork.find(cityState->city);
        if (it == roadNetwork.end()) return {};
        return it->second;
    }
    std::shared_ptr<State> getResult(const State& state, const Action& action) const override {
        std::string actionStr = action.name;
        if (actionStr.substr(0, 2) == "To") {
            std::string dest = actionStr.substr(2);
            return std::make_shared<RomaniaCityState>(dest);
        }
        return nullptr;
    }
    double getStepCost(const State& state, const Action& action,
                       const State& successor) const override {
        return action.cost;
    }
    double heuristic(const State& state) const override {
        const RomaniaCityState* cityState = dynamic_cast<const RomaniaCityState*>(&state);
        if (!cityState) return 0.0;
        static const std::unordered_map<std::string, double> sld = {
            {"Arad", 366}, {"Bucharest", 0}, {"Sibiu", 253}, {"Timisoara", 329},
            {"Zerind", 374}, {"Oradea", 380}, {"Fagaras", 176}, {"Rimnicu Vilcea", 193},
            {"Pitesti", 100}, {"Craiova", 160}, {"Lugoj", 244}, {"Mehadia", 241},
            {"Drobeta", 242}, {"Giurgiu", 77}, {"Urziceni", 80}, {"Hirsova", 151},
            {"Eforie", 161}, {"Vaslui", 199}, {"Iasi", 226}, {"Neamt", 234}
        };
        auto it = sld.find(cityState->city);
        if (it != sld.end()) return it->second;
        return 0.0;
    }

private:
    std::unordered_map<std::string, std::pair<double, double>> coordinates;
    std::unordered_map<std::string, std::vector<Action>> roadNetwork;
    void initCityCoordinates() {
        coordinates["Arad"] = {0, 0};
        coordinates["Bucharest"] = {100, 100};
        coordinates["Sibiu"] = {50, 20};
        coordinates["Timisoara"] = {-30, 10};
        coordinates["Zerind"] = {-20, -10};
        coordinates["Oradea"] = {-40, -20};
        coordinates["Fagaras"] = {80, 40};
        coordinates["Rimnicu Vilcea"] = {60, 60};
        coordinates["Pitesti"] = {80, 80};
        coordinates["Craiova"] = {70, 120};
        coordinates["Lugoj"] = {-10, 30};
        coordinates["Mehadia"] = {0, 40};
        coordinates["Drobeta"] = {10, 50};
        coordinates["Giurgiu"] = {90, 110};
        coordinates["Urziceni"] = {120, 90};
        coordinates["Hirsova"] = {150, 100};
        coordinates["Eforie"] = {170, 110};
        coordinates["Vaslui"] = {130, 70};
        coordinates["Iasi"] = {140, 60};
        coordinates["Neamt"] = {130, 40};
    }
    void initRoadNetwork() {
        addRoad("Arad", "Zerind", 75);
        addRoad("Arad", "Sibiu", 140);
        addRoad("Arad", "Timisoara", 118);
        addRoad("Zerind", "Oradea", 71);
        addRoad("Oradea", "Sibiu", 151);
        addRoad("Sibiu", "Fagaras", 99);
        addRoad("Sibiu", "Rimnicu Vilcea", 80);
        addRoad("Fagaras", "Bucharest", 211);
        addRoad("Rimnicu Vilcea", "Pitesti", 97);
        addRoad("Rimnicu Vilcea", "Craiova", 146);
        addRoad("Pitesti", "Bucharest", 101);
        addRoad("Pitesti", "Craiova", 138);
        addRoad("Bucharest", "Giurgiu", 90);
        addRoad("Bucharest", "Urziceni", 85);
        addRoad("Urziceni", "Hirsova", 98);
        addRoad("Urziceni", "Vaslui", 142);
        addRoad("Hirsova", "Eforie", 86);
        addRoad("Vaslui", "Iasi", 92);
        addRoad("Iasi", "Neamt", 87);
        addRoad("Timisoara", "Lugoj", 111);
        addRoad("Lugoj", "Mehadia", 70);
        addRoad("Mehadia", "Drobeta", 75);
        addRoad("Drobeta", "Craiova", 120);
    }
    void addRoad(const std::string& from, const std::string& to, double distance) {
        roadNetwork[from].push_back(Action{"To" + to, distance});
        roadNetwork[to].push_back(Action{"To" + from, distance});
    }
};

} // namespace searching
