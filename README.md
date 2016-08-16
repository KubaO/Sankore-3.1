This is an in-progress port to Qt 5.

It builds successfully on OS X 10.10 and starts up and brings up the GUI. All the dependencies
are internal. The extent to which it functions hasn't been investigated yet.

It should also build on Windows with MSVC 2015. Only a 32-bit build is being attempted at this
time.

The legacy Qt requirement will be dropped as soon as ICU and WebKit find their way into
the third party repository.

The following third-party prerequisites are built along with the project:

- phonon
- quazip
- xpdf
- zlib    (on Windows)
- icu     (on Windows)
- openssl (on Windows)

The plan is to add the following to the third-party repository to enable a successful
and functional build under newest Qt:

- webkit from Qt 5.5.1

There's not much point in adding a phonon backend; the port to Qt Multimedia shouldn't
be too hard.

General Prerequisites
=====================

1. Qt 5.5.1 (exact version required)

  The webkit module is needed and is not available in Qt 5.6.

  This Qt bundles the last version of chromium that still compiles in 32-bit mode
  on OS X.

2. OS X 10.10 or Windows+MSVC 2015

  No other platforms have been tested. After the legacy QuickTime and Phonon
  dependencies are dropped, builds on other platforms will be investigated as
  well.

Preparation & Building
======================

1. Check out the Sankore-ThirdParty repository. Both repositories should be
   in the same folder:

   |
   +- Sankore              (this can have arbitrary name)
   +- Sankore-Thirdparty   (this is a default, if you change it edit config.pri to match)

2. After installing the prerequisites, build the Sankore_top.pro project.

OS X Prerequisites
==================

You'll need a 32-bit install of Qt 5.5.1 with WebKit. MacPorts
doesn't provide one so you'll have to roll your own.

The 64-bit Qt won't work as all the code must be built in 32 bits since
legacy QuickTime APIs are needed on OS X, necessitating a 32-bit build.

1. Prep:

 a) Install MacPorts.
 b) Install necessary development tool ports:

    port install python-27 cmake ninja gmake

2. Qt 5.5.1 32-bit build

 a) Download and untar
    https://download.qt.io/archive/qt/5.5/5.5.1/single/qt-everywhere-opensource-src-5.5.1.tar.xz

 b) Edit qtwebengine/tools/qmake/mkspecs/features/functions.prf to allow a 32 bit
    build of Chromium.

    Change linux-g++*|win32-msvc2013|macx-clang: return(true)
    to:    linux-g++*|win32-msvc2013|macx-clang*: return(true)

 c) This will be a shadow build. Create a build and install folder.

 d) Setup the build: In the build folder:

    ../qt-everywhere-opensource-src-5.5.1/configure \
      -prefix (qt install folder) \
      -nomake examples -platform macx-clang-32 -debug-and-release \
      -opensource -confirm-license

 e) Build stage 1:
    gmake -j8

 f) Build stage 2: Edit qtwebengine/src/core/qmake_extras.gypi
  Remove junk after the closing brace on line 20.

 g) Build stage 3:
    gmake -j8

 h) Install
    gmake install

Ubuntu Linux Prerequisites
==========================
Fonts
	- If you want to use the web compatible fonts, you need to install the package ttf-mscorefonts-installer.
