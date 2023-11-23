#ifndef ONBOARDAPPLET_H
#define ONBOARDAPPLET_H

// ignore Plasma deprecation warnings because I'm not sure how to fix them considering Plasma's own applets
// haven't been ported yet
#define PLASMA_NO_DEPRECATED_WARNINGS 1

#include <Plasma/Applet>
#include <Plasma/Theme>

#include <libonboard/Onboard.h>

#include <QPalette>
#include <QSize>
#include <QIcon>

namespace Plasmoid {

class OnboardApplet : public Plasma::Applet {
    Q_OBJECT
    Q_PROPERTY(QString statusText READ statusText WRITE setStatusText NOTIFY statusTextChanged FINAL)
    Q_PROPERTY(QString secondaryStatusText READ secondaryStatusText WRITE setSecondaryStatusText NOTIFY secondaryStatusTextChanged FINAL)
    Q_PROPERTY(QString tooltipText READ tooltipText WRITE setTooltipText NOTIFY tooltipTextChanged FINAL)
    Q_PROPERTY(QString secondaryTooltipText READ secondaryTooltipText WRITE setSecondaryTooltipText NOTIFY secondaryTooltipTextChanged FINAL)
    Q_PROPERTY(QIcon tooltipIcon READ tooltipIcon WRITE setTooltipIcon NOTIFY tooltipIconChanged FINAL)
    Q_PROPERTY(QIcon statusIcon READ statusIcon WRITE setStatusIcon NOTIFY statusIconChanged FINAL)
    Q_PROPERTY(bool statusIconVisible READ statusIconVisible WRITE setStatusIconVisible NOTIFY statusIconVisibleChanged FINAL)

public:
    OnboardApplet(QObject *parent, const QVariantList &data);

public:
    QString statusText() const;
    void setStatusText(const QString &newStatusText);
    QString secondaryStatusText() const;
    void setSecondaryStatusText(const QString &newSecondaryStatusText);
    QString tooltipText() const;
    void setTooltipText(const QString &newTooltipText);
    QString secondaryTooltipText() const;
    void setSecondaryTooltipText(const QString &newSecondaryTooltipText);
    QIcon statusIcon() const;
    void setStatusIcon(const QIcon &newStatusIcon);
    QIcon tooltipIcon() const;
    void setTooltipIcon(const QIcon &newTooltipIcon);

    bool statusIconVisible() const;
    void setStatusIconVisible(bool newStatusIconVisible);

public slots:
    void init() override;
    void initEngine(QObject *object);
    QString resolveFallbackIcon(const QString& primary, const QString& fallback);

protected slots:
    void configChanged() override;

private slots:
    void onHasDataStateChanged(bool state);
    void onTrainStatusUpdated();

    void updateTestModeState();
    void updateTranslator();

signals:
    void statusTextChanged();
    void secondaryStatusTextChanged();
    void tooltipTextChanged();
    void secondaryTooltipTextChanged();
    void statusIconChanged();
    void tooltipIconChanged();

    void statusIconVisibleChanged();

private:
    bool _initialized;
    Onboard* _onboard;

    QIcon _statusIcon;
    QIcon _tooltipIcon;
    QString _statusText;
    QString _secondaryStatusText;
    QString _tooltipText;
    QString _secondaryTooltipText;
    bool _statusIconVisible;
};
} // namespace Plasmoid

#endif // ONBOARDAPPLET_H
