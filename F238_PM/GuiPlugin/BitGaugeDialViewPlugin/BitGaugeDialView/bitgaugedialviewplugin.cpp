#include "bitgaugedialview.h"
#include "bitgaugedialviewplugin.h"

#include <QtPlugin>

BitGaugeDialViewPlugin::BitGaugeDialViewPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}


void BitGaugeDialViewPlugin::initialize()//(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool BitGaugeDialViewPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *BitGaugeDialViewPlugin::createWidget(QWidget *parent)
{
  return new BitGaugeDialView(parent);
}

QString BitGaugeDialViewPlugin::name() const
{
  return QLatin1String("BitGaugeDialView");
}

QString BitGaugeDialViewPlugin::group() const
{
  return QLatin1String("");
}

QIcon BitGaugeDialViewPlugin::icon() const
{
  return QIcon();
}

QString BitGaugeDialViewPlugin::toolTip() const
{
  return QLatin1String("");
}

QString BitGaugeDialViewPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool BitGaugeDialViewPlugin::isContainer() const
{
  return false;
}

QString BitGaugeDialViewPlugin::domXml() const
{
  return QLatin1String("<widget class=\"BitGaugeDialView\" name=\"bitgaugedialView\">\n</widget>\n");
}

QString BitGaugeDialViewPlugin::includeFile() const
{
  return QLatin1String("bitgaugedialview.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(bitgaugedialviewplugin, BitGaugeDialViewPlugin)
#endif // QT_VERSION < 0x050000
