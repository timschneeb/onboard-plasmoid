#include <QCommandLineParser>
#include <QCoreApplication>
#include <QScopeGuard>

#include <unistd.h>
#include <stdio.h>

#include <libonboard/Onboard.h>
#include <libonboard/model/Status.h>
#include <libonboard/model/CurrentTrip.h>

QString pad(QString name, QString value, int maxPad = 25) {
    QString spacer = QString(" ").repeated(std::max(maxPad - name.length(), 1));
    return name + ":" + spacer + value + "\n";
}

int main(int argc, char *argv[])
{
    const QString resetSequence = isatty(stdout->_fileno) ? "\x1B[2J\x1B[H" : "";

    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("onboard");

    QCommandLineOption status(QStringList() << "s" << "status", "Show current train status");
    QCommandLineOption trip(QStringList() << "t" << "trip", "Show current train trip");
    QCommandLineOption rawStatus(QStringList() << "raw-status", "Dump current raw train status data");
    QCommandLineOption rawTrip(QStringList() << "raw-trip", "Dump current raw train trip data");
    QCommandLineOption once(QStringList() << "o" << "once", "Exit after printing the result");
    QCommandLineOption silent(QStringList() << "n" << "silent", "Disable logging");

    QCommandLineParser parser;
    parser.setApplicationDescription(QObject::tr("Client for onboard APIs of German ICE trains"));
    parser.addHelpOption();

    // Operations
    parser.addOptions({status, trip, rawStatus, rawTrip, once, silent});
    parser.process(app);

    Log::instance().setSilent(parser.isSet(silent));

    if(argc <= 1) {
        Log::information("Use --help to view information about usage and parameters");
    }

    Onboard::setup();

    auto* onboard = new Onboard();

    if(parser.isSet(rawStatus) || parser.isSet(status)) {
        QObject::connect(onboard, &Onboard::statusChanged, [onboard, &parser, &rawStatus, &once, resetSequence]{
            QString output;

            if(parser.isSet(rawStatus)) {
                // Dump raw data
                onboard->status()->dump(output);
            }
            else {
                // Dump as readable data
                auto* status = onboard->status();
                output += pad("Train speed", "%1 km/h").arg(status->speed());
                output += pad("Latitude", "%1").arg(status->latitude());
                output += pad("Longitude", "%1").arg(status->longitude());
                output += pad("Train type", "%1").arg(status->trainType());
                output += pad("Train series", "%1").arg(status->series());
                output += pad("Trainset number", "%1").arg(status->tzn()); /* tzn = Triebzugnummer */
                output += pad("Wagon class", "%1").arg(status->wagonClass());
                output += pad("Internet", "%1").arg(status->internet());
                output += pad("Server time", "%1").arg(QDateTime::fromMSecsSinceEpoch(status->serverTime()).toString(Qt::RFC2822Date));
            }

            Log::console(resetSequence + output);

            if(parser.isSet(once))
                QCoreApplication::quit();
        });
    }
    else if(parser.isSet(rawTrip) || parser.isSet(trip)) {
        QObject::connect(onboard, &Onboard::currentTripChanged, [onboard, &parser, &rawTrip, &once, resetSequence]{
            QString output;

            if(parser.isSet(rawTrip)) {
                // Dump raw data
                onboard->currentTrip()->dump(output);
            }
            else {
                // Dump as readable data
                auto* currentTrip = onboard->currentTrip();
                if(currentTrip != nullptr && currentTrip->trip() != nullptr && currentTrip->trip()->stopInfo() != nullptr) {
                    auto* trip = currentTrip->trip();
                    auto* stopInfo = currentTrip->trip()->stopInfo();

                    output += pad("Distance since start", "%1km").arg(trip->actualPosition()/1000.0, 0, 'f', 1);
                    output += pad("Distance since last stop", "%1km").arg(trip->distanceFromLastStop()/1000.0, 0, 'f', 1);
                    output += pad("Total distance", "%1km").arg(trip->totalDistance()/1000.0, 0, 'f', 1);
                    output += pad("Line number", "%1 %2").arg(trip->trainType()).arg(trip->vzn());
                    output += pad("Destination", "%1 (%2)").arg(stopInfo->finalStationName()).arg(stopInfo->finalStationEvaNr());
                    output += "\n";

                    for(int i = 0; i < currentTrip->trip()->stopsCount(); i++) {
                        auto* stop = currentTrip->trip()->stopsAt(i);
                        if(stop == nullptr || stop->station() == nullptr || stop->track() == nullptr ||
                            stop->timetable() == nullptr || stop->info() == nullptr)
                            continue;
                        if(stopInfo->actualNext() != stop->station()->evaNr())
                            continue;

                        if(stop->info()->positionStatus() == "arrived")
                            output += pad("Currently standing at", "%1 (%2)").arg(stop->station()->name()).arg(stop->station()->evaNr());
                        else
                            output += pad("Next station", "%1 (%2)").arg(stop->station()->name()).arg(stop->station()->evaNr());

                        output += pad("Remaining distance", "%1km").arg(stop->info()->distance() - trip->distanceFromLastStop()/1000.0, 0, 'f', 1);
                        output += pad("Arriving on platform", "%1").arg(stop->track()->actual());
                        output += pad("Scheduled arrival time", "%1").arg(QDateTime::fromMSecsSinceEpoch(stop->timetable()->scheduledArrivalTime()).toString(Qt::RFC2822Date));
                        output += pad("Actual arrival time", "%1").arg(QDateTime::fromMSecsSinceEpoch(stop->timetable()->actualArrivalTime()).toString(Qt::RFC2822Date));
                        output += pad("Scheduled departure time", "%1").arg(QDateTime::fromMSecsSinceEpoch(stop->timetable()->scheduledDepartureTime()).toString(Qt::RFC2822Date));
                        output += pad("Actual departure time", "%1").arg(QDateTime::fromMSecsSinceEpoch(stop->timetable()->actualDepartureTime()).toString(Qt::RFC2822Date));

                        for(int j = 0; j < stop->delayReasonsCount(); j++) {
                            output += pad("Delay reason", "%1").arg(stop->delayReasonsAt(j)->text());
                        }
                        break;
                    }
                }
            }

            Log::console(resetSequence + output);

            if(parser.isSet(once))
                QCoreApplication::quit();
        });
    }

    auto guard = qScopeGuard([onboard] { delete onboard; });
    return app.exec();
}
