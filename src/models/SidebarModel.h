#ifndef SIDEBARMODEL_H
#define SIDEBARMODEL_H

#include <QObject>
#include <QString>
#include <QDebug>

class SidebarModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentAlgorithm READ currentAlgorithm WRITE setCurrentAlgorithm NOTIFY currentAlgorithmChanged)
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(bool isRunning READ isRunning NOTIFY isRunningChanged)

public:
    explicit SidebarModel(QObject *parent = nullptr);

    QString currentAlgorithm() const;
    void setCurrentAlgorithm(const QString &algorithm);

    int speed() const;
    void setSpeed(int speed);

    bool isRunning() const;

    Q_INVOKABLE void initialize();
    Q_INVOKABLE void stepForward();
    Q_INVOKABLE void run();
    Q_INVOKABLE void reset();
    Q_INVOKABLE void pause();

signals:
    void currentAlgorithmChanged();
    void speedChanged();
    void isRunningChanged();
    void algorithmInitialized(const QString &name);
    void algorithmStepped();
    void algorithmReset();

private:
    QString m_currentAlgorithm;
    int m_speed;
    bool m_isRunning;
};

#endif // SIDEBARMODEL_H
