#include "connection.h"

#include <QSettings>
#include <QProcessEnvironment>

QString Connection::resolveSetting(const QString &envVar,
                                   const QString &settingsKey,
                                   const QString &defaultValue)
{
    const QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    if (env.contains(envVar))
        return env.value(envVar);

    QSettings settings("QtVoyager", "QtVoyager");
    if (settings.contains(settingsKey))
        return settings.value(settingsKey).toString();

    return defaultValue;
}

bool Connection::createconnection()
{
    bool test = false;

    // Credentials are externalized: environment variables take priority,
    // then QSettings, then an empty/default fallback. No secrets are hardcoded.
    // See .env.example and docs for the supported configuration keys.
    const QString driver   = resolveSetting("QTVOYAGER_DB_DRIVER", "db/driver", "QODBC");
    const QString dbName   = resolveSetting("QTVOYAGER_DB_NAME",   "db/name",   QString());
    const QString userName = resolveSetting("QTVOYAGER_DB_USER",   "db/user",   QString());
    const QString password = resolveSetting("QTVOYAGER_DB_PASSWORD", "db/password", QString());

    db = QSqlDatabase::addDatabase(driver);
    db.setDatabaseName(dbName);
    if (!userName.isEmpty())
        db.setUserName(userName);
    if (!password.isEmpty())
        db.setPassword(password);

    if (db.open())
        test = true;
    return test;
}

void Connection::closeConnection()
{
    db.close();
}
