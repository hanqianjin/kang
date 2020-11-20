#include "bitview.h"
#include "bitviewplugin.h"

#include <QtPlugin>

BitViewPlugin::BitViewPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}


void BitViewPlugin::initialize()//(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool BitViewPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *BitViewPlugin::createWidget(QWidget *parent)
{
  return new BitView(parent);
}

QString BitViewPlugin::name() const
{
  return QLatin1String("BitView");
}

QString BitViewPlugin::group() const
{
  return QLatin1String("");
}

QIcon BitViewPlugin::icon() const
{
  return QIcon();
}

QString BitViewPlugin::toolTip() const
{
  return QLatin1String("");
}

QString BitViewPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool BitViewPlugin::isContainer() const
{
  return false;
}

QString BitViewPlugin::domXml() const
{
  return QLatin1String("<widget class=\"BitView\" name=\"bitView\">\n</widget>\n");
}

QString BitViewPlugin::includeFile() const
{
  return QLatin1String("bitview.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(bitviewplugin, BitViewPlugin)
#endif // QT_VERSION < 0x050000
