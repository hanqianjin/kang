#include "bitrtsaremote.h"
#include "rtsaremoteplugin.h"

#include <QtPlugin>

RtSaRemotePlugin::RtSaRemotePlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void RtSaRemotePlugin::initialize()//(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool RtSaRemotePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *RtSaRemotePlugin::createWidget(QWidget *parent)
{
    return new BitRtSaRemote(parent);
}

QString RtSaRemotePlugin::name() const
{
    return QLatin1String("BitRtSaRemote");
}

QString RtSaRemotePlugin::group() const
{
    return QLatin1String("");
}

QIcon RtSaRemotePlugin::icon() const
{
    return QIcon();
}

QString RtSaRemotePlugin::toolTip() const
{
    return QLatin1String("");
}

QString RtSaRemotePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool RtSaRemotePlugin::isContainer() const
{
    return false;
}

QString RtSaRemotePlugin::domXml() const
{
    return QLatin1String("<widget class=\"BitRtSaRemote\" name=\"bitRtSa\">\n</widget>\n");
}

QString RtSaRemotePlugin::includeFile() const
{
    return QLatin1String("bitrtsa.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(bitrtsaplugin, RtSaRemotePlugin)
#endif // QT_VERSION < 0x050000
