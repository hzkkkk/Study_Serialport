TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.C


INCLUDEPATH += /usr/local/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2

LIBS += /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_core.so    \
        /usr/local/lib/libopencv_imgproc.so  \
        /usr/local/lib/libopencv_shape.so \
        /usr/local/lib/libopencv_videoio.so \
      /usr/local/lib/libopencv_imgcodecs.so.3.4\
        /usr/local/lib/libopencv_imgcodecs.so.3.4\
        /opt/Qt5.3.0/5.3/gcc_64/lib/libicui18n.so.52\
        /opt/Qt5.3.0/5.3/gcc_64/lib/libicuuc.so.52\
        /opt/Qt5.3.0/5.3/gcc_64/lib/libicudata.so.52

HEADERS += \
    config.h
