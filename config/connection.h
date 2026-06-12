#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QMessageBox>
#include <QString>

class Connection
{
    QSqlDatabase db;

public:
    Connection() = default;
    bool createconnection();
    void closeConnection();

private:
    // Resolves a configuration value with the following precedence:
    //   1. Environment variable (e.g. QTVOYAGER_DB_NAME)
    //   2. QSettings (organization "QtVoyager", application "QtVoyager")
    //   3. The provided default value
    static QString resolveSetting(const QString &envVar,
                                  const QString &settingsKey,
                                  const QString &defaultValue);
};

#endif // CONNECTION_H
