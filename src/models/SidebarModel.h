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

public:
    explicit SidebarModel(QObject *parent = nullptr);

    QString currentAlgorithm() const;
    void setCurrentAlgorithm(const QString &algorithm);

    int speed() const;
    void setSpeed(int speed);

signals:
    void currentAlgorithmChanged();
    void speedChanged();

private:
    QString m_currentAlgorithm;
    int m_speed;
};

#endif // SIDEBARMODEL_H
