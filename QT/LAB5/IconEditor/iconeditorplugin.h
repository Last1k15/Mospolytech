#ifndef ICONEDITORPLUGIN_H
#define ICONEDITORPLUGIN_H

#include <QObject>
#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class IconEditorPlugin
    : public QObject,
      public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "iconEditorPluginInterface")
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    IconEditorPlugin(QObject* parent = nullptr);
    QString name() const override;
    QString group() const override;
    QString toolTip() const override;
    QString whatsThis() const override;
    QString includeFile() const override;
    QIcon icon() const override;
    bool isContainer() const override;
    bool isInitialized() const override;
    QWidget *createWidget(QWidget *parent) override;
    void initialize(QDesignerFormEditorInterface*) override;
private:
    bool initialized = false;
};

Q_DECLARE_INTERFACE(IconEditorPlugin, "iconEditorPluginInterface")

#endif // ICONEDITORPLUGIN_H
