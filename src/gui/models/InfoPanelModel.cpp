#include "InfoPanelModel.h"

InfoPanelModel::InfoPanelModel(QObject* parent) : QObject(parent) {
}

void InfoPanelModel::logInfo(const QString& message) {
    emit messageLogged(message);
}

void InfoPanelModel::logMessage(const QString& message) {
    logInfo(message);
}

void InfoPanelModel::clearLog() {
    emit logClearRequested();
}
