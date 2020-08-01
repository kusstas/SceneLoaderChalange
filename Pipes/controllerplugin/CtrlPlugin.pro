# Ant copirate!

TEMPLATE = lib
TARGET = CtrlPlugin
QT += qml quick
CONFIG += plugin c++14

TARGET = $$qtLibraryTarget($$TARGET)
uri = tooling.Pipes


include(CtrlPlugin.pri)
DISTFILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) "$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)" "$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir

unix:!android: {
    installPath    =$$[QT_INSTALL_QML]/$$replace(uri, \., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    pluginfiles.path = $$installPath
    INSTALLS += target qmldir pluginfiles
}

unix:android: {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir pluginfiles
    message($$installPath)
    #DESTDIR = "./build"
}
