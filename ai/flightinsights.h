#ifndef FLIGHTINSIGHTS_H
#define FLIGHTINSIGHTS_H

#include <QObject>
#include <QString>

QT_FORWARD_DECLARE_CLASS(QNetworkAccessManager)
QT_FORWARD_DECLARE_CLASS(QNetworkReply)

// Opt-in "flight insights" helper.
//
// Sends a compact, anonymized summary of the VOYAGES table to the Anthropic
// Messages API and emits a short natural-language analysis. This is strictly
// opt-in: it does nothing unless the user supplies their own API key (via the
// ANTHROPIC_API_KEY environment variable, QSettings "ai/anthropic_api_key",
// or the apiKey argument). With no key it fails gracefully and emits a clear
// message instead of calling the network.
//
// No data leaves the machine unless the user has explicitly provided a key.
class FlightInsights : public QObject
{
    Q_OBJECT
public:
    explicit FlightInsights(QObject *parent = nullptr);

    // Returns true if an API key is configured from any source.
    static bool hasApiKey();

    // Resolves the API key: argument > env var > QSettings > empty.
    static QString resolveApiKey(const QString &explicitKey = QString());

    // Requests insights for the given summary text (e.g. aggregated route /
    // cost / profit figures). If no key is available, emits failed() with a
    // friendly message and never touches the network.
    void requestInsights(const QString &voyageSummary,
                         const QString &apiKey = QString());

signals:
    void insightsReady(const QString &text);
    void failed(const QString &reason);

private:
    QNetworkAccessManager *m_manager;
    QString buildPrompt(const QString &voyageSummary) const;
};

#endif // FLIGHTINSIGHTS_H
