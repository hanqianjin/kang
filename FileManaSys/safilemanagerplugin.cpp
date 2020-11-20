#include "safilemanager.h"
#include "safilemanagerplugin.h"

#include <QtPlugin>

SAFileManagerPlugin::SAFileManagerPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void SAFileManagerPlugin::initialize(/*QDesignerFormEditorInterface **/ /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool SAFileManagerPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *SAFileManagerPlugin::createWidget(QWidget *parent)
{
    return new SAFileManager(parent);
}

QString SAFileManagerPlugin::name() const
{
    return QLatin1String("SAFileManager");
}

QString SAFileManagerPlugin::group() const
{
    return QLatin1String("");
}

QIcon SAFileManagerPlugin::icon() const
{
    return QIcon();
}

QString SAFileManagerPlugin::toolTip() const
{
    return QLatin1String("");
}

QString SAFileManagerPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool SAFileManagerPlugin::isContainer() const
{
    return false;
}

QString SAFileManagerPlugin::domXml() const
{
    return QLatin1String("<widget class=\"SAFileManager\" name=\"sAFileManager\">\n</widget>\n");
}

QString SAFileManagerPlugin::includeFile() const
{
    return QLatin1String("safilemanager.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(safilemanagerplugin, SAFileManagerPlugin)
#endif // QT_VERSION < 0x050000
