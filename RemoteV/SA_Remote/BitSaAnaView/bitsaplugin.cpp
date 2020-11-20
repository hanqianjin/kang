#include "bitsa.h"
#include "bitsaplugin.h"

#include <QtPlugin>

BitSAPlugin::BitSAPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void BitSAPlugin::initialize()//(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool BitSAPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *BitSAPlugin::createWidget(QWidget *parent)
{
    return new BitSA(parent);
}

QString BitSAPlugin::name() const
{
    return QLatin1String("BitSA");
}

QString BitSAPlugin::group() const
{
    return QLatin1String("");
}

QIcon BitSAPlugin::icon() const
{
    return QIcon();
}

QString BitSAPlugin::toolTip() const
{
    return QLatin1String("");
}

QString BitSAPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool BitSAPlugin::isContainer() const
{
    return false;
}

QString BitSAPlugin::domXml() const
{
    return QLatin1String("<widget class=\"BitSA\" name=\"bitSA\">\n</widget>\n");
}

QString BitSAPlugin::includeFile() const
{
    return QLatin1String("bitsa.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(bitsaplugin, BitSAPlugin)
#endif // QT_VERSION < 0x050000
