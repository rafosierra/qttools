#-------------------------------------------------
#
# Project created by QtCreator 2016-10-12T14:46:30
#
#-------------------------------------------------

QT       += widgets

TARGET = qtpropertybrowser
TEMPLATE = lib

DEFINES += QTPROPERTYBROWSER_LIBRARY

INCLUDEPATH += $$PWD
SOURCES += $$PWD/qtpropertybrowser.cpp \
            $$PWD/qtpropertymanager.cpp \
            $$PWD/qteditorfactory.cpp \
            $$PWD/qtvariantproperty.cpp \
            $$PWD/qttreepropertybrowser.cpp \
            $$PWD/qtbuttonpropertybrowser.cpp \
            $$PWD/qtgroupboxpropertybrowser.cpp \
            $$PWD/qtpropertybrowserutils.cpp \
            $$PWD/filepatheditor.cpp \
            $$PWD/filepathfactory.cpp \
            $$PWD/filepathmanager.cpp \
    filepathlisteditor.cpp \
    filepathlistfactory.cpp

HEADERS += $$PWD/qtpropertybrowser.h \
            $$PWD/qtpropertymanager.h \
            $$PWD/qteditorfactory.h \
            $$PWD/qtvariantproperty.h \
            $$PWD/qttreepropertybrowser.h \
            $$PWD/qtbuttonpropertybrowser.h \
            $$PWD/qtgroupboxpropertybrowser.h \
            $$PWD/qtpropertybrowserutils_p.h \
            $$PWD/filepatheditor.h \
            $$PWD/filepathfactory.h \
            $$PWD/filepathmanager.h \
    filepathlisteditor.h \
    filepathlistfactory.h

RESOURCES += $$PWD/qtpropertybrowser.qrc

unix {
    header_files.files = $$HEADERS
    header_files.path = /usr/local/include/$$TARGET
    INSTALLS += header_files
    target.path = /usr/local/lib
    INSTALLS += target
}
