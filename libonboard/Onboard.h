#ifndef ONBOARD_H
#define ONBOARD_H

#include <QObject>
#include <QTimer>

#include "global.h"

#include "model/CurrentTrip.h"
#include "model/Status.h"

class OnboardApiClient;

class LIB_ONBOARD_EXPORT Onboard : public QObject
{
    Q_OBJECT
public:
    explicit Onboard(QObject *parent = nullptr);
    ~Onboard();

    static void setup();

    bool isConnected() const;

    Status *status() const;
    CurrentTrip *currentTrip() const;

    bool hasData() const;
    void setHasData(bool newHasData);

signals:
    void onConnectionStateChanged(bool isConnected);
    void hasDataChanged(bool hasData);

    void statusChanged();
    void currentTripChanged();

private slots:
    void checkConnectionState();
    void toggleBackgroundService(bool enable);
    void pollData();

private:
    static bool _ready;
    static QStringList _ssids;

    bool _hasData = false;
    bool _isConnected = false;

    QTimer _pollTimer;

    OnboardApiClient* _apiClient = nullptr;

    Status* _status = new Status(this);
    CurrentTrip* _currentTrip = new CurrentTrip(this);

    Q_PROPERTY(bool isConnected READ isConnected NOTIFY onConnectionStateChanged FINAL)
    Q_PROPERTY(bool hasData READ hasData WRITE setHasData NOTIFY hasDataChanged FINAL)

    Q_PROPERTY(Status *status READ status MEMBER _status NOTIFY statusChanged FINAL)
    Q_PROPERTY(CurrentTrip *currentTrip READ currentTrip MEMBER _currentTrip NOTIFY currentTripChanged FINAL)
};

#endif // ONBOARD_H
