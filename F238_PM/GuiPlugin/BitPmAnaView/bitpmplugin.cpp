#include "bitpm.h"
#include "bitpmplugin.h"

#include <QtPlugin>

BitPmPlugin::BitPmPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void BitPmPlugin::initialize()//(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool BitPmPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *BitPmPlugin::createWidget(QWidget *parent)
{
    return new BitPm(parent);
}

QString BitPmPlugin::name() const
{
    return QLatin1String("BitPm");
}

QString BitPmPlugin::group() const
{
    return QLatin1String("");
}

QIcon BitPmPlugin::icon() const
{
    return QIcon();
}

QString BitPmPlugin::toolTip() const
{
    return QLatin1String("");
}

QString BitPmPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool BitPmPlugin::isContainer() const
{
    return false;
}

QString BitPmPlugin::domXml() const
{
    return QLatin1String("<widget class=\"BitPm\" name=\"bitPm\">\n</widget>\n");
}

QString BitPmPlugin::includeFile() const
{
    return QLatin1String("bitpm.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(bitpmplugin, BitPmPlugin)
#endif // QT_VERSION < 0x050000
