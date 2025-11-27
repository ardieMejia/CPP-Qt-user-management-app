# Specifies the type of project: 'app' for application, 'lib' for library, etc.
TEMPLATE = app

# Specifies the name of the executable target
TARGET = hello

# Specifies the Qt modules required by the project
# For a basic GUI application, 'core', 'gui', and 'widgets' are common
QT += core gui widgets sql

# Lists the source files (.cpp) in the project
SOURCES += \
    hello.cpp \
    mainwindow.cpp \
    ## org_mainwindow.cpp \
    adminwindow.cpp \
    insertuserwindow.cpp \
    insertdeptwindow.cpp \
    database.cpp

# Lists the header files (.h) in the project
HEADERS += \
    mainwindow.h \
    ## org_mainwindow.h \
    adminwindow.h \
    insertuserwindow.h \
    insertdeptwindow.h \
    database.h

# Lists the UI files (.ui) designed with Qt Designer
FORMS += \
    mainwindow.ui \
    ## org_mainwindow.ui \
    adminwindow.ui \
    insertuserwindow.ui \
    insertdeptwindow.ui

QMAKE_CXXFLAGS += -Wno-unused-variable
    


