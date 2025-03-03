#include "menugroup.h"

QAction* makeAction(const QString label, QMenu* parent = nullptr, const QString tooltip = "", const QKeySequence shortcut = QKeySequence{})
{
    QAction* newAction = new QAction{label};

    if (!tooltip.isEmpty())
        newAction->setToolTip(tooltip);

    if (!shortcut.isEmpty())
        newAction->setShortcut(shortcut);

    if (parent)
        parent->addAction(newAction);

    return newAction;
}

MenuGroup::MenuGroup(QMainWindow* _parent)
    :   parent{_parent}
{
////////////////////////////////////////////////////
/// FILE
///
    fileMenu = parent->menuBar()->addMenu("File");

    action_new = makeAction(           "New",                  fileMenu,       "Create a new file",    {Qt::CTRL | Qt::Key_N}              );
    action_open = makeAction(          "Open",                 fileMenu,       "Open file",            {Qt::CTRL | Qt::Key_O}              );
    action_save = makeAction(          "Save",                 fileMenu,       "Save file",            {Qt::CTRL | Qt::Key_S}              );
    action_saveAs = makeAction(        "Save as...",           fileMenu,       "Save file as...",      {Qt::CTRL | Qt::SHIFT | Qt::Key_S}  );
    action_exit = makeAction(          "Exit",                 fileMenu,       "Create a new file",    {Qt::CTRL | Qt::Key_Q}              );


////////////////////////////////////////////////////
/// EDIT
///
    editMenu = parent->menuBar()->addMenu("Edit");

    action_cut = makeAction(           "Cut",                  editMenu,       "Cut",                  {Qt::CTRL | Qt::Key_X}              );
    action_copy = makeAction(          "Copy",                 editMenu,       "Copy",                 {Qt::CTRL | Qt::Key_C}              );
    action_paste = makeAction(         "Paste",                editMenu,       "Paste",                {Qt::CTRL | Qt::Key_V}              );
    action_delete = makeAction(        "Delete",               editMenu,       "Delete",               {Qt::Key_Delete}                    );
    action_find = makeAction(          "Find",                 editMenu,       "Find",                 {Qt::CTRL | Qt::Key_F}              );
    action_select = makeAction(        "Select...",            editMenu,       "Select",               {Qt::Key_F5}                        );

    selectMenu = new QMenu;
    action_select->setMenu(selectMenu);

    action_row = makeAction(           "Row",                  selectMenu);
    action_col = makeAction(           "Column",               selectMenu);
    action_all = makeAction(           "All",                  selectMenu,     "",                     {Qt::CTRL | Qt::Key_A}              );


////////////////////////////////////////////////////
/// TOOLS
///
    toolsMenu = parent->menuBar()->addMenu("Tools");

    action_recalc = makeAction(        "Recalculate",          toolsMenu,      "",                     {Qt::Key_F9});
    action_sort = makeAction(          "Sort",                 toolsMenu);
////////////////////////////////////////////////////
/// OPTIONS
///
    optionsMenu = parent->menuBar()->addMenu("Options");

    action_showGrid = makeAction(      "Show Grid",            optionsMenu);
    action_showGrid->setCheckable(true);

    action_recalc_auto = makeAction(   "Auto-recalculate",     optionsMenu);
    action_recalc_auto->setCheckable(true);
////////////////////////////////////////////////////
/// HELP
///
    helpMenu = parent->menuBar()->addMenu("Help");

    action_about = makeAction(         "About",                helpMenu);
    action_aboutQt = makeAction(       "About Qt",             helpMenu);

    parent->menuBar()->setAutoFillBackground(true);
}

