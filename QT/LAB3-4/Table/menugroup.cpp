#include "menugroup.h"
#include "table.h"

QAction* makeAction(QMenu* parent, const QString&& label, const QString&& tooltip = "", const QKeySequence&& shortcut = QKeySequence{}, const QIcon&& ico = QIcon{})
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

    // if (parent->recentFilesActions[0] != nullptr) // !
    // {
    //     QMenu* recentFileMenu = new QMenu;
    //     recentFileMenu->addSeparator();

    //     for (int i = 0; i < parent->maxRecentFiles; i++)
    //     {
    //         QAction* currentRecentFile {parent->recentFilesActions[i]};

    //         if (currentRecentFile)
    //             recentFileMenu->addAction(parent->recentFilesActions[i]);
    //     }

    //     recentFileMenu->addSeparator();
    //     action_open->setMenu(recentFileMenu);
    // }

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
        QKeySequence{Qt::Key_F9}
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
        "Show Grid"
    );
    action_showGrid->setCheckable(true);

    action_recalc_auto = makeAction
    (
        optionsMenu,
        "Auto-recalculate"
    );
    action_recalc_auto->setCheckable(true);


////////////////////////////////////////////////////
/// HELP
///
    helpMenu = parent->menuBar()->addMenu("Help");

    action_about = makeAction
    (
        helpMenu,
        "About"
    );

    action_aboutQt = makeAction
    (
        helpMenu,
        "About Qt"
    );
}

