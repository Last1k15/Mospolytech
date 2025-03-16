#include "iconeditorplugin.h"
#include "iconeditor.h"
#include <QtDesigner/QtDesigner>

Q_INTERFACES(IconEditorPlugin)

IconEditorPlugin::IconEditorPlugin(QObject* parent)
    :   QObject{parent}
{
    initialized = false;
}

QString IconEditorPlugin::name() const
{
    return "IconEditor";
}

QString IconEditorPlugin::includeFile() const
{
    return "iconeditor.h";
}

QString IconEditorPlugin::group() const
{
    return tr("Image Manipulation Widgets");
}

QIcon IconEditorPlugin::icon() const
{
    return QIcon(":/ico/iconeditor.png");
}

QString IconEditorPlugin::toolTip() const
{
    return tr("An icon editor widget");
}

QString IconEditorPlugin::whatsThis() const
{
    return tr("This widget is presented in Chapter 5 of <i>C++ GUI "
              "Programming with Qt 4</i> as an example of a custom Qt "
              "widget.");
}

bool IconEditorPlugin::isContainer() const
{
    return false;
}

bool IconEditorPlugin::isInitialized() const
{
    return initialized;
}

QWidget* IconEditorPlugin::createWidget(QWidget *parent)
{
    return new IconEditor(parent);
}

void IconEditorPlugin::initialize(QDesignerFormEditorInterface*)
{
    if (initialized)
        return;
    initialized = true;
}
