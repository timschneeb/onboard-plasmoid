#include "Onboard.h"

#include "model/Status.h"
#include "model/CurrentTrip.h"
#include "network/HttpException.h"
#include "network/OnboardApiClient.h"

#include <NetworkManagerQt/Manager>
#include <NetworkManagerQt/WirelessDevice>

bool Onboard::_ready = false;

QStringList Onboard::_ssids = QStringList(std::initializer_list<QString>({"WIFIonICE", "WIFI@DB"}));

Onboard::Onboard(QObject *parent) : _apiClient(new OnboardApiClient(this)), QObject{parent}
{
    if(!_ready) {
        Log::critical("Please call Onboard::setup once before using this library.");
        abort();
    }

    connect(NetworkManager::notifier(), &NetworkManager::Notifier::primaryConnectionChanged, this, &Onboard::checkConnectionState);
    connect(this, &Onboard::onConnectionStateChanged, this, &Onboard::toggleBackgroundService);
    connect(&_pollTimer, &QTimer::timeout, this, &Onboard::pollData);

    checkConnectionState();
}

Onboard::~Onboard()
{
    _status->deleteLater();
    _currentTrip->deleteLater();
}

void Onboard::setup()
{
    qRegisterMetaType<Connectivity*>();
    qRegisterMetaType<Status*>();
    qRegisterMetaType<CurrentTrip*>();
    qRegisterMetaType<Trip*>();
    qRegisterMetaType<TripStopInfo*>();
    qRegisterMetaType<Stop*>();
    qRegisterMetaType<Track*>();
    qRegisterMetaType<Station*>();
    qRegisterMetaType<DelayReason*>();
    qRegisterMetaType<StopInfo*>();
    qRegisterMetaType<StopTimetable*>();
    _ready = true;
}

bool Onboard::isConnected() const
{
    return _isConnected;
}

void Onboard::checkConnectionState()
{
    // We have to find some wireless device
    const NetworkManager::Device::List deviceList = NetworkManager::networkInterfaces();
    NetworkManager::WirelessDevice::Ptr wifiDevice;

    for (NetworkManager::Device::Ptr dev : deviceList) {
        if (dev->type() == NetworkManager::Device::Wifi) {
            wifiDevice = qobject_cast<NetworkManager::WirelessDevice *>(dev);
            break;
        }
    }

    // Get current SSID
    QString currentSsid = "";
    if (!wifiDevice) {
        Log::warning("No wifi device found");
    }
    else if(auto ap = wifiDevice.get()->activeAccessPoint(); ap != nullptr) {
        currentSsid = ap.get()->ssid();
    }

    // Compare SSID with list of supported train wifi networks
    bool connected = _ssids.contains(currentSsid);
    if (_isConnected != connected) {
        _isConnected = connected;

        Log::debug(QString("Connection state has changed to: %1 (%2)").arg(_isConnected ? "yes" : "no").arg(currentSsid));
        emit onConnectionStateChanged(connected);
    }
}

void Onboard::toggleBackgroundService(bool enable)
{
    setHasData(false);
    _status->reset();
    _currentTrip->reset();

    if(enable) {
        _pollTimer.setSingleShot(false);
        _pollTimer.setInterval(4000);
        _pollTimer.start();
        pollData();
    }
    else {
        _pollTimer.stop();
    }
}

void Onboard::pollData()
{
    _apiClient->getStatus()
        .then([this](QString json){
            _status->deserialize(json);
            setHasData(true);
            emit statusChanged();
        }).fail([this](const HttpException& ex){
            Log::error(QString("Failed to retrieve status information. HTTP code %1 (%2)").arg(ex.statusCode()).arg(ex.reasonPhrase()));
            setHasData(false);
        });

    _apiClient->getTripInfo()
        .then([this](QString json){
            _currentTrip->deserialize(json);
            setHasData(true);
            emit currentTripChanged();
        }).fail([this](const HttpException& ex){
            Log::error(QString("Failed to retrieve status information. HTTP code %1 (%2)").arg(ex.statusCode()).arg(ex.reasonPhrase()));
            setHasData(false);
        });
}

bool Onboard::hasData() const
{
    return _hasData;
}

void Onboard::setHasData(bool newHasData)
{
    if (_hasData == newHasData)
        return;
    _hasData = newHasData;
    emit hasDataChanged(_hasData);
}

Status *Onboard::status() const
{
    return _status;
}

CurrentTrip *Onboard::currentTrip() const
{
    return _currentTrip;
}
