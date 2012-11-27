DESTDIR = $$QT.designer.bins
QT += core-private widgets xml network designer-private designercomponents
!isEmpty(QT.printsupport.name): QT += printsupport
!build_pass:contains(QT_CONFIG, build_all): CONFIG += release

INCLUDEPATH += \
    ../lib/sdk \
    ../lib/extension \
    ../lib/shared \
    extra

RESOURCES += designer.qrc

contains(QT_CONFIG, static) {
    DEFINES += QT_DESIGNER_STATIC
}

TARGET = designer

include(../../../shared/fontpanel/fontpanel.pri)
include(../../../shared/qttoolbardialog/qttoolbardialog.pri)

QMAKE_DOCS = $$PWD/doc/designer.qdocconf

HEADERS += \
    qdesigner.h \
    qdesigner_toolwindow.h \
    qdesigner_formwindow.h \
    qdesigner_workbench.h \
    qdesigner_settings.h \
    qdesigner_actions.h \
    qdesigner_server.h \
    qdesigner_appearanceoptions.h \
    saveformastemplate.h \
    newform.h \
    versiondialog.h \
    designer_enums.h \
    appfontdialog.h \
    preferencesdialog.h \
    assistantclient.h \
    mainwindow.h

SOURCES += main.cpp \
    qdesigner.cpp \
    qdesigner_toolwindow.cpp \
    qdesigner_formwindow.cpp \
    qdesigner_workbench.cpp \
    qdesigner_settings.cpp \
    qdesigner_server.cpp \
    qdesigner_actions.cpp \
    qdesigner_appearanceoptions.cpp \
    saveformastemplate.cpp \
    newform.cpp \
    versiondialog.cpp \
    appfontdialog.cpp \
    preferencesdialog.cpp \
    assistantclient.cpp \
    mainwindow.cpp

PRECOMPILED_HEADER=qdesigner_pch.h

FORMS += saveformastemplate.ui \
    preferencesdialog.ui \
    qdesigner_appearanceoptions.ui

win32 {
   RC_FILE      = designer.rc
}

mac {
    ICON = designer.icns
    QMAKE_INFO_PLIST = Info_mac.plist
    TARGET = Designer
    FILETYPES.files = uifile.icns
    FILETYPES.path = Contents/Resources
    QMAKE_BUNDLE_DATA += FILETYPES
}

target.path=$$[QT_INSTALL_BINS]
INSTALLS += target

include(../sharedcomponents.pri)

unix:!mac:LIBS += -lm
