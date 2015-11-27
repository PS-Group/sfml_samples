
defineReplace(inferTargetDir) {
    buildSubdir = release-x64
    debug {
        equals(QT_ARCH, x86_64) {
            buildSubdir = debug-x64
        } else {
            buildSubdir = debug-x32
        }
    } else {
        !contains($$QT_ARCH, x86_64) {
            buildSubdir = release-x32
        }
    }
    buildDir=$$PWD/~build/$$buildSubdir
    return($$buildDir)
}

defineReplace(inferTarget) {
    buildTargetPath=$$inferTargetDir()/$$1
    return($$buildTargetPath)
}

CONFIG += c++11

LIBS += -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

TARGET = $$inferTarget($$TARGET)

SOURCES += \
    main.cpp \
    application.cpp \
    button.cpp \
    assets.cpp

HEADERS += \
    application.h \
    button.h \
    assets.h
