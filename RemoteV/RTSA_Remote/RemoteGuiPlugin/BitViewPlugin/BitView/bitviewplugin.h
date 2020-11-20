#ifndef BITVIEWPLUGIN_H
#define BITVIEWPLUGIN_H

//#include <QtUiPlugin/QDesignerCustomWidgetInterface>
#include <QObject>
#include <qicon.h>


//#if defined(BITVIEW_BUILD)
//#  define WIDGET_API Q_DECL_EXPORT
//#else
//#  define WIDGET_API Q_DECL_IMPORT
//#endif


class BitViewPlugin : public QObject//, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
//  //Q_INTERFACES(QDesignerCustomWidgetInterface)
//#if QT_VERSION >= 0x050000
//  Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface")
//#endif // QT_VERSION >= 0x050000

public:
  BitViewPlugin(QObject *parent = 0);

  bool isContainer() const;
  bool isInitialized() const;
  QIcon icon() const;
  QString domXml() const;
  QString group() const;
  QString includeFile() const;
  QString name() const;
  QString toolTip() const;
  QString whatsThis() const;
  QWidget *createWidget(QWidget *parent);
  void initialize();//(QDesignerFormEditorInterface *core);

private:
  bool m_initialized;
};

#endif
