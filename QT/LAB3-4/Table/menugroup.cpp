#include "menugroup.h"


QAction* MenuGroup::makeAction(QMenu* parent, const QString&& label, const QString&& tooltip, const QKeySequence&& shortcut, const QIcon&& ico)
{
    QAction* newAction = new QAction{label};

    if (!tooltip.isEmpty())
        newAction->setToolTip(tooltip);

    if (!shortcut.isEmpty())
        newAction->setShortcut(shortcut);

    if (!ico.isNull())
        newAction->setIcon(ico);
    if (parent)
        parent->addAction(newAction);

    return newAction;
}

MenuGroup::MenuGroup(Table* _parent)
    :   parent{_parent}
{
////////////////////////////////////////////////////
/// FILE
///
    parent->menuBar()->setAutoFillBackground(true);

    fileMenu = parent->menuBar()->addMenu("File");

    action_new = makeAction
    (
        fileMenu,
        "New",
        "Create a new file",
        QKeySequence{Qt::CTRL | Qt::Key_N},
        QIcon{":/visual/ico/new.png"}
    );

    action_open = makeAction
    (
        fileMenu,
        "Open",
        "Open file",
        QKeySequence{Qt::CTRL | Qt::Key_O},
        QIcon{":/visual/ico/open.png"}
    );



    action_save = makeAction
    (
        fileMenu,
        "Save",
        "Save file",
        QKeySequence{Qt::CTRL | Qt::Key_S},
        QIcon{":/visual/ico/save.png"}
    );

    action_saveAs = makeAction
    (
        fileMenu,
        "Save as...",
        "Save file as...",
        QKeySequence{Qt::CTRL | Qt::SHIFT | Qt::Key_S},
        QIcon{":/visual/ico/save.png"}
    );

    fileMenu->addSeparator();

    action_close = makeAction
    (
        fileMenu,
        "Close",
        "close current file",
        QKeySequence{Qt::CTRL | Qt::Key_W},
        QIcon{":/visual/ico/close.png"}
    );

    action_exit = makeAction
    (
        fileMenu,
        "Exit",
        "Create a new file",
        QKeySequence{Qt::CTRL | Qt::Key_Q},
        QIcon{":/visual/ico/exit.png"}
    );


////////////////////////////////////////////////////
/// EDIT
///
    editMenu = parent->menuBar()->addMenu("Edit");

    action_cut = makeAction
    (
        editMenu,
        "Cut",
        "Cut selected data",
        QKeySequence{Qt::CTRL | Qt::Key_X},
        QIcon{":/visual/ico/cut.png"}
    );

    action_copy = makeAction
    (
        editMenu,
        "Copy",
        "Copy to",
        QKeySequence{Qt::CTRL | Qt::Key_C},
        QIcon{":/visual/ico/copy.png"}
    );

    action_paste = makeAction
    (
        editMenu,
        "Paste",
        "Paste from buffer",
        QKeySequence{Qt::CTRL | Qt::Key_V},
        QIcon{":/visual/ico/paste.png"}
    );

    action_delete = makeAction
    (
        editMenu,
        "Delete",
        "Delete",
        QKeySequence{Qt::Key_Delete},
        QIcon{":/visual/ico/delete.png"}
    );

    action_find = makeAction
    (
        editMenu,
        "Find",
        "Find",
        QKeySequence{Qt::CTRL | Qt::Key_F},
        QIcon{":/visual/ico/find.png"}
    );

    action_select = makeAction
    (
        editMenu,
        "Select...",
        "Select",
        QKeySequence{Qt::Key_F5},
        QIcon{":/visual/ico/select.png"}
    );

    selectMenu = new QMenu;
    action_select->setMenu(selectMenu);

    action_row = makeAction
    (
        selectMenu,
        "Row"
    );

    action_col = makeAction
    (
        selectMenu,
        "Column"
    );

    action_all = makeAction
    (
        selectMenu,
        "All",
        "",
        QKeySequence{Qt::CTRL | Qt::Key_A}
    );


////////////////////////////////////////////////////
/// TOOLS
///
    toolsMenu = parent->menuBar()->addMenu("Tools");

    action_recalc = makeAction
    (
        toolsMenu,
        "Recalculate",
        "",
        QKeySequence{Qt::Key_F9},
        QIcon{":/visual/ico/recalc.png"}
    );

    action_sort = makeAction
    (
        toolsMenu,
        "Sort",
        "Sort range",
        QKeySequence{Qt::CTRL | Qt::Key_Y},
        QIcon{":/visual/ico/sort.png"}
    );


////////////////////////////////////////////////////
/// OPTIONS
///
    optionsMenu = parent->menuBar()->addMenu("Options");

    action_showGrid = makeAction
    (
        optionsMenu,
        "Show Grid",
        "Show row and coloumn lines",
        {},
        QIcon{":visual/ico/grid.png"}
    );
    action_showGrid->setCheckable(true);
    action_showGrid->setChecked(true);

    action_recalc_auto = makeAction
    (
        optionsMenu,
        "Auto-recalculate",
        "",
        {},
        QIcon{":/visual/ico/recalc.png"}
    );
    action_recalc_auto->setCheckable(true);


////////////////////////////////////////////////////
/// HELP
///
    helpMenu = parent->menuBar()->addMenu("Help");

    action_about = makeAction
    (
        helpMenu,
        "About",
        "",
        {},
        QIcon{":visual/ico/info.png"}
    );

    action_aboutQt = makeAction
    (
        helpMenu,
        "About Qt",
        "",
        {},
        QIcon{":visual/ico/info.png"}
    );

////////////////////////////////////////////////////
/// RECENT FILES
///
}

void MenuGroup::updateRecentFilesMenu()
{
    if (!parent->recentFilesActions[0] || !fileMenu)
        return;

    fileMenu->insertSeparator(action_save);
    fileMenu->insertActions(action_save, parent->recentFilesActions);
    fileMenu->insertSeparator(action_save);
}
