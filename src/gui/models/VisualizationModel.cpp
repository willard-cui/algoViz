#include "VisualizationModel.h"
#include "../algorithms/UninformedSearch.h"
#include "../algorithms/InformedSearch.h"
#include "../problems/RomaniaProblem.h"
#include <QDebug>
#include <QThread>

using namespace searching;

VisualizationModel::VisualizationModel(QObject* parent)
    : QObject(parent),
      myIsRunning(false),
      mySpeed(5),
      myCurrentAlgorithm("Select Algorithm"),
      myCurrentStepIndex(0),
      myLastAlgorithmName(""),
      myTimer(nullptr),
      myInfoPanelModel(new InfoPanelModel(this)) {
    myAlgorithms.clear();
    myAlgorithms.append("Select Algorithm");
    myAlgorithms.append("BFS");
    myAlgorithms.append("DFS");
    myAlgorithms.append("Uniform Cost");
    myAlgorithms.append("Greedy Best First");
    myAlgorithms.append("A*");
    myAlgorithms.append("Depth Limited");
    myAlgorithms.append("Iterative Deepening DFS");
    myAlgorithms.append("Iterative Deepening A*");
    myAlgorithms.append("Weighted A*");
    myProblem = std::make_unique<RomaniaProblem>();
    loadProblemData();
    
    myTimer = new QTimer(this);
    connect(myTimer, &QTimer::timeout, this, &VisualizationModel::onTimerTimeout);

    
}

VisualizationModel::~VisualizationModel() = default;

void VisualizationModel::loadProblemData() {
    myCities.clear();
    myRoads.clear();
    
    auto coords = myProblem->getAllCoordinates();
    for (const auto& city : coords) {
        QVariantMap map;
        map["name"] = QString::fromStdString(city.name);
        map["x"] = city.x;
        map["y"] = city.y;
        myCities.append(map);
    }
    emit citiesChanged();
    
    auto roads = myProblem->getAllRoads();
    for (const auto& road : roads) {
        QVariantMap map;
        map["from"] = QString::fromStdString(road.from);
        map["to"] = QString::fromStdString(road.to);
        map["distance"] = road.distance;
        myRoads.append(map);
    }
    emit roadsChanged();
    
    qDebug() << "Loaded" << myCities.count() << "cities and" << myRoads.count() << "roads";
}

InfoPanelModel* VisualizationModel::infoPanelModel() const {
    return myInfoPanelModel;
}

bool VisualizationModel::isRunning() const {
    return myIsRunning;
}

int VisualizationModel::speed() const {
    return mySpeed;
}

void VisualizationModel::setSpeed(int speed) {
    if (mySpeed == speed)
        return;

    mySpeed = speed;
    emit speedChanged();
    
    if (myIsRunning) {
        int interval = 1000 - (mySpeed - 1) * 100;
        if (interval < 50) interval = 50;
        myTimer->setInterval(interval);
    }
}

QVariantList VisualizationModel::cities() const { return myCities; }
QVariantList VisualizationModel::roads() const { return myRoads; }
QVariantList VisualizationModel::visitedNodes() const { return myVisitedNodes; }
QVariantList VisualizationModel::pathNodes() const { return myPathNodes; }
QString VisualizationModel::currentNode() const { return myCurrentNode; }

QString VisualizationModel::startNode() const {
    if (myProblem) return QString::fromStdString(myProblem->getStartCity());
    return "Arad";
}

void VisualizationModel::setStartNode(const QString& node) {
    if (startNode() == node) 
        return;
    myProblem->setStartCity(node.toStdString());
    emit startNodeChanged();
    reset();
}

QString VisualizationModel::goalNode() const {
    if (myProblem) 
        return QString::fromStdString(myProblem->getGoalCity());
    return "Bucharest";
}

void VisualizationModel::setGoalNode(const QString& node) {
    if (goalNode() == node) 
        return;
    myProblem->setGoalCity(node.toStdString());
    emit goalNodeChanged();
    reset();
}

QString VisualizationModel::currentAlgorithm() const {
    return myCurrentAlgorithm;
}

void VisualizationModel::setCurrentAlgorithm(const QString& name) {
    if (myCurrentAlgorithm == name) 
        return;
    myCurrentAlgorithm = name;
    emit currentAlgorithmChanged();
}

QVariantList VisualizationModel::algorithms() const {
    return myAlgorithms;
}

void VisualizationModel::startAlgorithm(const QString& algorithmName) {
    if (myIsRunning) 
        return;

    if (myAllVisitedStates.empty() || algorithmName != myLastAlgorithmName) {
        reset();
        executeAlgorithm(algorithmName);
    }
    
    if (myAllVisitedStates.empty()) {
        myInfoPanelModel->logInfo("No algorithm executed or empty result.");
        return;
    }

    myIsRunning = true;
    emit isRunningChanged();
    
    int interval = 1000 - (mySpeed - 1) * 100;
    if (interval < 50) interval = 50;
    myTimer->start(interval);
    myInfoPanelModel->logInfo("Algorithm started: " + algorithmName);
    myInfoPanelModel->logInfo(QString("Algorithm calculated. Steps: %1, Cost: %2").arg(myAllVisitedStates.size()).arg(myResult.totalCost));
}

void VisualizationModel::resume() {
    if (myIsRunning) 
        return;
    if (myAllVisitedStates.empty()) 
        return;

    myIsRunning = true;
    emit isRunningChanged();
    myTimer->start(); 
    myInfoPanelModel->logInfo("Algorithm resumed");
}

void VisualizationModel::pause() {
    if (!myIsRunning) 
        return;

    myIsRunning = false;
    emit isRunningChanged();
    myTimer->stop();
    
    myInfoPanelModel->logInfo("Algorithm paused");
}

void VisualizationModel::reset() {
    pause();
    
    myVisitedNodes.clear();
    myPathNodes.clear();
    myAllVisitedStates.clear();
    myCurrentStepIndex = 0;
    myCurrentNode = "";
    
    myResult = SearchResult(); // Reset result
    
    emit visitedNodesChanged();
    emit pathNodesChanged();
    emit currentNodeChanged();
    
    
    myInfoPanelModel->logInfo("Visualization reset");
}

void VisualizationModel::executeAlgorithm(const QString& algorithmName) {
    if (algorithmName == "Select Algorithm") 
        return;
    
    myLastAlgorithmName = algorithmName;
    
    if (algorithmName == "BFS") {
        myAlgorithm = std::make_unique<BreadthFirstSearch>();
    } else if (algorithmName == "DFS") {
        myAlgorithm = std::make_unique<DepthFirstSearch>();
    } else if (algorithmName == "Uniform Cost") {
        myAlgorithm = std::make_unique<UniformCostSearch>();
    } else if (algorithmName == "Greedy Best First") {
        myAlgorithm = std::make_unique<GreedyBestFirstSearch>();
    } else if (algorithmName == "A*") {
        myAlgorithm = std::make_unique<AStarSearch>();
    } else if (algorithmName == "Depth Limited") {
        myAlgorithm = std::make_unique<DepthLimitedSearch>(5); 
    } else if (algorithmName == "Iterative Deepening DFS") {
        myAlgorithm = std::make_unique<IterativeDeepeningDFS>();
    } else if (algorithmName == "Iterative Deepening A*") {
        myAlgorithm = std::make_unique<IterativeDeepeningAStar>();
    } else if (algorithmName == "Weighted A*") {
        myAlgorithm = std::make_unique<WeightedAStarSearch>(1.5);
    } else {
        myInfoPanelModel->logInfo("Unknown algorithm: " + algorithmName);
        return;
    }
    
    myInfoPanelModel->logInfo("Running algorithm..." + algorithmName);
    myResult = myAlgorithm->search(*myProblem);
    
    myAllVisitedStates = myResult.visitedStates;   
    
    myCurrentStepIndex = 0;
}

void VisualizationModel::stepForward() {
    if (myAllVisitedStates.empty()) 
        return;
    
    if (myCurrentStepIndex < myAllVisitedStates.size()) {
        auto state = myAllVisitedStates[myCurrentStepIndex];
        auto cityState = std::dynamic_pointer_cast<RomaniaCityState>(state);
        
        if (cityState) {
            QString cityName = QString::fromStdString(cityState->city);
            myCurrentNode = cityName;
            emit currentNodeChanged();
            
            bool alreadyVisited = false;
            for (const auto& v : myVisitedNodes) {
                if(v.toString() == cityName) {
                    alreadyVisited = true;
                    break;
                }
            }
            if (!alreadyVisited) {
                myVisitedNodes.append(cityName);
                emit visitedNodesChanged();
            }
        }
        
        myCurrentStepIndex++;
    } else {
        if (myPathNodes.isEmpty() && !myResult.solution.empty()) {
            auto currentState = myProblem->getInitialState();
            auto cityState = std::dynamic_pointer_cast<RomaniaCityState>(currentState);
            if (cityState) myPathNodes.append(QString::fromStdString(cityState->city));
            
            for (const auto& action : myResult.solution) {
                currentState = myProblem->getResult(*currentState, action);
                cityState = std::dynamic_pointer_cast<RomaniaCityState>(currentState);
                if (cityState) myPathNodes.append(QString::fromStdString(cityState->city));
            }
            emit pathNodesChanged();
            const QString statusText = myResult.success ? "Success" : "Failed";
            myInfoPanelModel->logInfo(QString("Algorithm finished. Status: %1, Nodes Expanded: %2, Total Cost: %3")
                .arg(statusText)
                .arg(myResult.nodesExpanded)
                .arg(myResult.totalCost, 0, 'f', 2));
            
            pause();
        }
    }
}

void VisualizationModel::onTimerTimeout() {
    stepForward();
    
    if (myCurrentStepIndex >= myAllVisitedStates.size() && !myPathNodes.isEmpty()) {
        pause();
    }
}
