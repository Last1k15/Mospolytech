QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=   \
    main.cpp  \
    grid.cpp   \
    table.cpp   \
    menugroup.cpp\
    cell.cpp      \
    spreadsheet.cpp\
    findDialog.cpp

HEADERS +=  \
    grid.h   \
    table.h   \
    menugroup.h\
    cell.h      \
    spreadsheet.h\
    finddialog.h

FORMS +=      \
    grid.ui    \
    table.ui    \
    cell.ui      \
    spreadsheet.ui\
    finddialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
