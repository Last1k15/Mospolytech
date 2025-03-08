#ifndef MENUGROUP_H
#define MENUGROUP_H

#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QMainWindow>
#include "table.h"

struct MenuGroup
{
    Table* parent;

    explicit MenuGroup(Table* parent = nullptr);
    QMenu* fileMenu;
        QAction* action_new;
        QAction* action_open;
        QAction* action_save;
        QAction* action_saveAs;
        QAction* action_close;
        QAction* action_exit;

    QMenu* editMenu;
        QAction* action_cut;
        QAction* action_copy;
        QAction* action_paste;
        QAction* action_delete;
        QAction* action_find;
        QAction* action_select;

    QMenu* selectMenu;
        QAction* action_row;
        QAction* action_col;
        QAction* action_all;

    QMenu* toolsMenu;
        QAction* action_recalc;
        QAction* action_sort;

    QMenu* optionsMenu;
        QAction* action_showGrid;
        QAction* action_recalc_auto;

    QMenu* helpMenu;
        QAction* action_about;
        QAction* action_aboutQt;

    static QAction* makeAction(QMenu* parent, const QString&& label = "", const QString&& tooltip = "", const QKeySequence&& shortcut = QKeySequence{}, const QIcon&& ico = QIcon{});

    void updateRecentFilesMenu();
};

#endif // MENUGROUP_H
