#include "bitrtsa.h"
#include "bitrtsaplugin.h"

#include <QtPlugin>

BitRtSaPlugin::BitRtSaPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void BitRtSaPlugin::initialize()//(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool BitRtSaPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *BitRtSaPlugin::createWidget(QWidget *parent)
{
    return new BitRtSa(parent);
}

QString BitRtSaPlugin::name() const
{
    return QLatin1String("BitRtSa");
}

QString BitRtSaPlugin::group() const
{
    return QLatin1String("");
}

QIcon BitRtSaPlugin::icon() const
{
    return QIcon();
}

QString BitRtSaPlugin::toolTip() const
{
    return QLatin1String("");
}

QString BitRtSaPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool BitRtSaPlugin::isContainer() const
{
    return false;
}

QString BitRtSaPlugin::domXml() const
{
    return QLatin1String("<widget class=\"BitRtSa\" name=\"bitRtSa\">\n</widget>\n");
}

QString BitRtSaPlugin::includeFile() const
{
    return QLatin1String("bitrtsa.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(bitrtsaplugin, BitRtSaPlugin)
#endif // QT_VERSION < 0x050000
