QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += static

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    datastruct.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    datastruct.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    Xlsx2Xml_en_HK.ts

TARGET = FileConvertor

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(3rdparty/qtxlsx/src/xlsx/qtxlsx.pri)

win32: RC_FILE += $$PWD/res.rc

DISTFILES +=

RESOURCES += \
    resource.qrc
