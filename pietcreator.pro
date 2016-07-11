QMAKE_CXXFLAGS += -Wall -Wextra  -Werror -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += svg sql printsupport

cross_compile {
  # Crosscompile only
  message("Desktop application, built for cross-compiling from Linux to Windows")
  QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra -Weffc++
}


QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets svg

TEMPLATE = app

CONFIG(debug, debug|release) {
  message(Debug mode)
}

CONFIG(release, debug|release) {
  message(Release mode)
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}


greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

SOURCES += \
    Command.cpp \
    CommandDelegate.cpp \
    CommandImpl.cpp \
    CommandsModel.cpp \
    CommandWidget.cpp \
    DebugWidget.cpp \
    FlowCompass.cpp \
    ImageModel.cpp \
    KColorCells.cpp \
    KColorMimeData.cpp \
    KColorPatch.cpp \
    main.cpp \
    MainWindow.cpp \
    NPietObserver.cpp \
    PixelDelegate.cpp \
    ResizeDialog.cpp \
    RunController.cpp \
    UndoCommands.cpp \
    UndoHandler.cpp \
    ViewMonitor.cpp

RESOURCES += \
    pietcreator.qrc

HEADERS += \
    ColorUtils.h \
    Command.h \
    CommandDelegate.h \
    CommandImpl.h \
    CommandsModel.h \
    CommandWidget.h \
    DebugWidget.h \
    FlowCompass.h \
    ImageModel.h \
    KColorCells.h \
    KColorMimeData.h \
    KColorPatch.h \
    MainWindow.h \
    NPietObserver.h \
    PixelDelegate.h \
    ResizeDialog.h \
    RunController.h \
    UndoCommands.h \
    UndoHandler.h \
    ViewMonitor.h

FORMS += \
    DebugWidget.ui \
    MainWindow.ui
