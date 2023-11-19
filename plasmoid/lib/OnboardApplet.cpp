#include "./OnboardApplet.h"

#include "resources/config.h"
#include "resources/qtconfig.h"

#include "Utils.h"

#include <qtutilities/resources/resources.h>

#include <Plasma/Theme>
#include <plasma/plasma_export.h>
#include <plasma_version.h>

#include <libonboard/Log.h>

#include <QGuiApplication>
#include <QIcon>
#include <QPalette>
#include <QQmlEngine>
#include <QTimer>

using namespace std;
using namespace Plasma;

__attribute__((constructor)) void init(void) {
    Onboard::setup();
}

namespace Plasmoid {

OnboardApplet::OnboardApplet(QObject *parent, const QVariantList &data)
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    : Applet(parent, KPluginMetaData(), data)
#else
    : Applet(parent, data)
#endif
    , _initialized(false)
    , _tooltipIcon(QIcon::fromTheme("clock"))
    , _onboard(new Onboard(this))
{
    connect(_onboard, &Onboard::hasDataChanged, this, &OnboardApplet::onHasDataStateChanged);
    connect(_onboard, &Onboard::statusChanged, this, &OnboardApplet::onTrainStatusUpdated);
    connect(_onboard, &Onboard::currentTripChanged, this, &OnboardApplet::onTrainStatusUpdated);
}

void OnboardApplet::init()
{
    LOAD_QT_TRANSLATIONS;

// ensure FONTCONFIG_PATH is set (mainly required for static GNU/Linux builds)
#ifdef QT_FEATURE_fontdialog
    if (!qEnvironmentVariableIsSet("FONTCONFIG_PATH") && QDir(QStringLiteral("/etc/fonts")).exists()) {
        qputenv("FONTCONFIG_PATH", "/etc/fonts");
    }
#endif

// enable settings for High-DPI scaling
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    if (!QCoreApplication::instance()) {
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    }
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
#endif

    Applet::init();
    _initialized = true;
}

void OnboardApplet::initEngine(QObject *object)
{
    const auto engine = qmlEngine(object);
    if (!engine) {
        return;
    }

    Log::debug("QML engine initialized");
}

void OnboardApplet::onHasDataStateChanged(bool state)
{
    if(!state) {
        //setStatusIcon(QIcon::fromTheme("network-offline-symbolic"));
        setStatusIcon(QIcon());
        setStatusText("");
        setSecondaryStatusText("");
        setTooltipText("Onboard tracking");
        setSecondaryTooltipText("No supported WIFI connection");
    }
}

void OnboardApplet::onTrainStatusUpdated()
{
    QString distanceToNext = "?";
    QString platform = "?";
    QString nextStation = "?";
    QString arrivingInMin = "?";
    QString departingInMin = "?";
    bool hasArrived = false;

    QString destination = "?";
    QString trainNumber = "?";
    QString delayInformation = "Derzeit pünktlich";

    auto* currentTrip = _onboard->currentTrip();
    if(currentTrip->trip() != nullptr && currentTrip->trip()->stopInfo() != nullptr) {
        auto* trip = currentTrip->trip();
        auto* stopInfo = currentTrip->trip()->stopInfo();

        trainNumber = trip->trainType() + " " + trip->vzn();
        destination = stopInfo->finalStationName();

        for(int i = 0; i < currentTrip->trip()->stopsCount(); i++) {
            auto* stop = currentTrip->trip()->stopsAt(i);
            if(stop == nullptr || stop->station() == nullptr || stop->track() == nullptr ||
                stop->timetable() == nullptr || stop->info() == nullptr)
                continue;
            if(stopInfo->actualNext() != stop->station()->evaNr())
                continue;

            StopTimetable* time = stop->timetable();
            QDateTime now = QDateTime::currentDateTime();

            distanceToNext = QString::number(stop->info()->distance()/1000.0, 'f', 1);
            hasArrived = stop->info()->positionStatus() == "arrived";
            nextStation = stop->station()->name();
            platform = stop->track()->actual();

            arrivingInMin = QString::number(now.secsTo(QDateTime::fromMSecsSinceEpoch(time->actualArrivalTime())) / 60);
            departingInMin = QString::number(now.secsTo(QDateTime::fromMSecsSinceEpoch(time->actualDepartureTime())) / 60);

            int delay = utils::parseDelayTime(hasArrived ? time->departureDelay() : time->arrivalDelay());
            if(delay > 1) {
                QString format = hasArrived ? "Abfahrt in %1 um %2 Minuten verzögert." : "Ankunft in %1 um %2 Minuten verzögert.";
                delayInformation = QString(format).arg(nextStation).arg(delay);
            }

            for(int j = 0; j < stop->delayReasonsCount(); j++) {
                delayInformation += "\nHinweis: " + stop->delayReasonsAt(j)->text();
            }
            break;
        }
    }

    auto* status = _onboard->status();
    if(hasArrived) {
        setStatusIcon(QIcon::fromTheme("go-right"));
        setStatusText(QString("Auf Gleis %2 in %1").arg(nextStation).arg(platform));
        setSecondaryStatusText(QString("%1 km/h | Abfahrt in %2 Minuten").arg(status->speed()).arg(departingInMin));
    }
    else {
        setStatusIcon(QIcon::fromTheme("up"));
        setStatusText(QString("%1 in %2 Minuten").arg(nextStation).arg(arrivingInMin));
        setSecondaryStatusText(QString("%1 km/h | noch %2 km | Gleis %3").arg(status->speed()).arg(distanceToNext).arg(platform));
    }

    setTooltipText(QString("%1 nach %2").arg(trainNumber).arg(destination));
    setSecondaryTooltipText(delayInformation);
}

QIcon OnboardApplet::statusIcon() const
{
    return _statusIcon;
}

void OnboardApplet::setStatusIcon(const QIcon &newStatusIcon)
{
    _statusIcon = newStatusIcon;
    emit statusIconChanged();
}

QIcon OnboardApplet::tooltipIcon() const
{
    return _tooltipIcon;
}

void OnboardApplet::setTooltipIcon(const QIcon &newTooltipIcon)
{
    _tooltipIcon = newTooltipIcon;
    emit tooltipIconChanged();
}

QString OnboardApplet::statusText() const
{
    return _statusText;
}

void OnboardApplet::setStatusText(const QString &newStatusText)
{
    if (_statusText == newStatusText)
        return;
    _statusText = newStatusText;
    emit statusTextChanged();
}

QString OnboardApplet::secondaryStatusText() const
{
    return _secondaryStatusText;
}

void OnboardApplet::setSecondaryStatusText(const QString &newSecondaryStatusText)
{
    if (_secondaryStatusText == newSecondaryStatusText)
        return;
    _secondaryStatusText = newSecondaryStatusText;
    emit secondaryStatusTextChanged();
}

QString OnboardApplet::tooltipText() const
{
    return _tooltipText;
}

void OnboardApplet::setTooltipText(const QString &newTooltipText)
{
    if (_tooltipText == newTooltipText)
        return;
    _tooltipText = newTooltipText;
    emit tooltipTextChanged();
}

QString OnboardApplet::secondaryTooltipText() const
{
    return _secondaryTooltipText;
}

void OnboardApplet::setSecondaryTooltipText(const QString &newSecondaryTooltipText)
{
    if (_secondaryTooltipText == newSecondaryTooltipText)
        return;
    _secondaryTooltipText = newSecondaryTooltipText;
    emit secondaryTooltipTextChanged();
}

} // namespace Plasmoid

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
namespace Plasmoid {
K_PLUGIN_CLASS(OnboardApplet)
}
#else
K_EXPORT_PLASMA_APPLET_WITH_JSON(onboard, Plasmoid::OnboardApplet, "metadata.json")
#endif

#include "OnboardApplet.moc"
