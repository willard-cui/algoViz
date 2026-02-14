#include "SidebarModel.h"

SidebarModel::SidebarModel(QObject *parent)
    : QObject(parent)
    , m_currentAlgorithm("Select Algorithm")
    , m_speed(5)
    , m_isRunning(false)
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

bool SidebarModel::isRunning() const
{
    return m_isRunning;
}

void SidebarModel::initialize()
{
    qDebug() << "Initializing algorithm:" << m_currentAlgorithm;
    emit algorithmInitialized(m_currentAlgorithm);
}

void SidebarModel::stepForward()
{
    qDebug() << "Step forward";
    emit algorithmStepped();
}

void SidebarModel::run()
{
    if (m_isRunning)
        return;

    m_isRunning = true;
    emit isRunningChanged();
    qDebug() << "Algorithm started";
}

void SidebarModel::pause()
{
    if (!m_isRunning)
        return;

    m_isRunning = false;
    emit isRunningChanged();
    qDebug() << "Algorithm paused";
}

void SidebarModel::reset()
{
    m_isRunning = false;
    emit isRunningChanged();
    qDebug() << "Algorithm reset";
    emit algorithmReset();
}
