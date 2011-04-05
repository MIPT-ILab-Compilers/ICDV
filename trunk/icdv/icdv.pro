TARGET = icdv
TEMPLATE = app
SOURCES += main.cpp \
    Graph/Edge.cpp \
    Graph/Graph.cpp \
    Graph/Node.cpp \
    Layout/LEdge.cpp \
    Layout/Ordering.cpp \
    Layout/Layout.cpp \
    Layout/LNode.cpp \
    Layout/LGraph.cpp \
    Deriv.cpp \
    Gui/mainscene.cpp
HEADERS += Deriv.h \
    Graph/Edge.h \
    Graph/Graph.h \
    Graph/predecls.h \
    Graph/Node.h \
    Layout/Ordering.h \
    Layout/LNode.h \
    Layout/LGraph.h \
    Layout/LEdge.h \
    Layout/Layout.h \
    Gui/mainscene.h

CONFIG( debug, debug|release ) {
    OBJECTS_DIR=Debug
    DEFINES += DEBUG\
            NDEBUG\
            _DEBUG
} else {
    OBJECTS_DIR=Release
    DEFINES += RELEASE
}

FORMS += \
    Gui/mainscene.ui