#include "SidebarModel.h"

SidebarModel::SidebarModel(QObject *parent)
    : QObject(parent)
    , m_currentAlgorithm("Select Algorithm")
    , m_speed(5)
{
}

QString SidebarModel::currentAlgorithm() const
{
    return m_currentAlgorithm;
}

void SidebarModel::setCurrentAlgorithm(const QString &algorithm)
{
    if (m_currentAlgorithm == algorithm)
        return;

    m_currentAlgorithm = algorithm;
    emit currentAlgorithmChanged();
    qDebug() << "Algorithm selected:" << m_currentAlgorithm;
}

int SidebarModel::speed() const
{
    return m_speed;
}

void SidebarModel::setSpeed(int speed)
{
    if (m_speed == speed)
        return;

    m_speed = speed;
    emit speedChanged();
    
    qDebug() << "Speed changed to:" << m_speed;
}
