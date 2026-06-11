#include "flightinsights.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include <QProcessEnvironment>
#include <QUrl>

namespace {
// Anthropic Messages API. The model id is intentionally a recent, widely
// available default; users can override it via QSettings "ai/model".
const char *kAnthropicEndpoint = "https://api.anthropic.com/v1/messages";
const char *kAnthropicVersion = "2023-06-01";
// Current, valid model id (see Anthropic model catalog). Users may override
// via QSettings "ai/model".
const char *kDefaultModel = "claude-haiku-4-5";
}

FlightInsights::FlightInsights(QObject *parent)
    : QObject(parent), m_manager(new QNetworkAccessManager(this))
{
}

QString FlightInsights::resolveApiKey(const QString &explicitKey)
{
    if (!explicitKey.isEmpty())
        return explicitKey;

    const QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    if (env.contains("ANTHROPIC_API_KEY"))
        return env.value("ANTHROPIC_API_KEY");

    QSettings settings("QtVoyager", "QtVoyager");
    return settings.value("ai/anthropic_api_key").toString();
}

bool FlightInsights::hasApiKey()
{
    return !resolveApiKey().isEmpty();
}

QString FlightInsights::buildPrompt(const QString &voyageSummary) const
{
    return QStringLiteral(
               "You are a travel-operations analyst. Given the following "
               "aggregated, anonymized flight booking data from a travel "
               "agency, provide 3-5 concise, actionable insights about routes, "
               "pricing, and profitability. Be specific and brief.\n\n"
               "Data:\n") + voyageSummary;
}

void FlightInsights::requestInsights(const QString &voyageSummary,
                                     const QString &apiKey)
{
    const QString key = resolveApiKey(apiKey);
    if (key.isEmpty())
    {
        emit failed(tr("Flight insights are disabled: no Anthropic API key "
                       "configured. Set the ANTHROPIC_API_KEY environment "
                       "variable or the 'ai/anthropic_api_key' QSettings key "
                       "to enable this opt-in feature."));
        return;
    }

    QSettings settings("QtVoyager", "QtVoyager");
    const QString model = settings.value("ai/model", QString::fromLatin1(kDefaultModel)).toString();

    QJsonObject message;
    message.insert("role", "user");
    message.insert("content", buildPrompt(voyageSummary));

    QJsonArray messages;
    messages.append(message);

    QJsonObject body;
    body.insert("model", model);
    body.insert("max_tokens", 512);
    body.insert("messages", messages);

    QNetworkRequest request{QUrl(QString::fromLatin1(kAnthropicEndpoint))};
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("x-api-key", key.toUtf8());
    request.setRawHeader("anthropic-version", kAnthropicVersion);

    QNetworkReply *reply = m_manager->post(request, QJsonDocument(body).toJson());
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        if (reply->error() != QNetworkReply::NoError)
        {
            emit failed(tr("Anthropic request failed: %1").arg(reply->errorString()));
            return;
        }

        const QByteArray raw = reply->readAll();
        QJsonParseError parseError;
        const QJsonDocument doc = QJsonDocument::fromJson(raw, &parseError);
        if (parseError.error != QJsonParseError::NoError || !doc.isObject())
        {
            emit failed(tr("Could not parse Anthropic response."));
            return;
        }

        // Response shape: { "content": [ { "type": "text", "text": "..." } ] }
        const QJsonArray content = doc.object().value("content").toArray();
        QString text;
        for (const QJsonValue &block : content)
        {
            if (block.toObject().value("type").toString() == "text")
                text += block.toObject().value("text").toString();
        }

        if (text.isEmpty())
        {
            emit failed(tr("Anthropic returned an empty response."));
            return;
        }

        emit insightsReady(text);
    });
}
