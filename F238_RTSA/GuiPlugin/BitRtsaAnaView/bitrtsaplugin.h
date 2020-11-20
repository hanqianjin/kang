#ifndef BITRTSAPLUGIN_H
#define BITRTSAPLUGIN_H

#include <QObject>
#include <qicon.h>

//#include <QDesignerCustomWidgetInterface>

class BitRtSaPlugin : public QObject//, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
//    Q_INTERFACES(QDesignerCustomWidgetInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface")
#endif // QT_VERSION >= 0x050000

public:
    BitRtSaPlugin(QObject *parent = 0);

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
