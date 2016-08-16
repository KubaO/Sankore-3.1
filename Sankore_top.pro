# This is the project that builds all the dependencies and the Sankore application itself.
# Open this project in Qt Creator to do development work.
TEMPLATE = subdirs

include(config.pri)

SUBDIRS = \
    sub_app \
    sub_phonon \
    sub_quazip \
    sub_xpdf

sub_app.file = Sankore.pro
sub_app.depends = sub_phonon sub_quazip sub_xpdf

sub_phonon.subdir = thirdparty/phonon
sub_quazip.subdir = thirdparty/quazip
sub_xpdf.subdir = thirdparty/xpdf

win32 {
    SUBDIRS += sub_icu sub_zlib sub_openssl
    sub_app.depends += sub_icu sub_zlib sub_openssl

    sub_icu.subdir = thirdparty/icu
    sub_zlib.subdir = thirdparty/zlib
    sub_openssl.subdir = thirdparty/openssl
}

OTHER_FILES += README.md
