#pragma once

#include "InfoPanelModel.h"
#include "../algorithms/SearchAlgorithm.h"
#include <QObject>
#include <QString>
#include <QVariantList>
#include <QVariantMap>
#include <QTimer>
#include <memory>
#include <vector>

namespace searching {
class RomaniaProblem;
class SearchAlgorithm;
class State;
struct SearchResult;
}

class VisualizationModel : public QObject {
    Q_OBJECT

    bool myIsRunning;
    int mySpeed;
    
    // Info Panel Model
    InfoPanelModel* myInfoPanelModel;

    // Problem and Algorithm
    std::unique_ptr<searching::RomaniaProblem> myProblem;
    std::unique_ptr<searching::SearchAlgorithm> myAlgorithm;
    searching::SearchResult myResult;
    
    // Visualization State
    QVariantList myCities;
    QVariantList myRoads;
    QVariantList myVisitedNodes;
    QVariantList myPathNodes;
    QString myCurrentNode;
    
    // Execution State
    std::vector<std::shared_ptr<searching::State>> myAllVisitedStates;
    size_t myCurrentStepIndex;
    QTimer* myTimer;
    QString myLastAlgorithmName;
    QString myCurrentAlgorithm;
    QVariantList myAlgorithms;

public:
    explicit VisualizationModel(QObject* parent = nullptr);
    ~VisualizationModel();

    Q_PROPERTY(bool isRunning READ isRunning NOTIFY isRunningChanged)
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    
    // Visualization Data
    Q_PROPERTY(QVariantList cities READ cities NOTIFY citiesChanged)
    Q_PROPERTY(QVariantList roads READ roads NOTIFY roadsChanged)
    Q_PROPERTY(QVariantList visitedNodes READ visitedNodes NOTIFY visitedNodesChanged)
    Q_PROPERTY(QVariantList pathNodes READ pathNodes NOTIFY pathNodesChanged)
    Q_PROPERTY(QString currentNode READ currentNode NOTIFY currentNodeChanged)
    Q_PROPERTY(QString startNode READ startNode WRITE setStartNode NOTIFY startNodeChanged)
    Q_PROPERTY(QString goalNode READ goalNode WRITE setGoalNode NOTIFY goalNodeChanged)
    Q_PROPERTY(QString currentAlgorithm READ currentAlgorithm WRITE setCurrentAlgorithm NOTIFY currentAlgorithmChanged)
    Q_PROPERTY(QVariantList algorithms READ algorithms CONSTANT)
    Q_PROPERTY(InfoPanelModel* infoPanelModel READ infoPanelModel CONSTANT)

    InfoPanelModel* infoPanelModel() const;
    
    bool isRunning() const;
    int speed() const;
    void setSpeed(int speed);

    QVariantList cities() const;
    QVariantList roads() const;
    QVariantList visitedNodes() const;
    QVariantList pathNodes() const;
    QString currentNode() const;
    QString startNode() const;
    void setStartNode(const QString& node);
    QString goalNode() const;
    void setGoalNode(const QString& node);
    QString currentAlgorithm() const;
    void setCurrentAlgorithm(const QString& name);
    QVariantList algorithms() const;

    Q_INVOKABLE void startAlgorithm(const QString& algorithmName);
    Q_INVOKABLE void pause();
    Q_INVOKABLE void resume();
    Q_INVOKABLE void reset();
    Q_INVOKABLE void stepForward();


private:
    void loadProblemData();
    void executeAlgorithm(const QString& algorithmName);


signals:
    void isRunningChanged();
    void speedChanged();
    void citiesChanged();
    void roadsChanged();
    void visitedNodesChanged();
    void pathNodesChanged();
    void currentNodeChanged();
    void startNodeChanged();
    void goalNodeChanged();
    void currentAlgorithmChanged();

private slots:
    void onTimerTimeout();
};

#endif // VISUALIZATIONMODEL_H
