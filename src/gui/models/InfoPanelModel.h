#ifndef INFOPANELMODEL_H
#define INFOPANELMODEL_H

#include <QObject>
#include <QString>

class InfoPanelModel : public QObject {
    Q_OBJECT

public:
    explicit InfoPanelModel(QObject* parent = nullptr);

    Q_INVOKABLE void logInfo(const QString& message);
    Q_INVOKABLE void logMessage(const QString& message);
    Q_INVOKABLE void clearLog();

signals:
    void messageLogged(const QString& message);
    void logClearRequested();
};

#endif // INFOPANELMODEL_H
