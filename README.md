This is an in-progress port to Qt 5. At the moment, it requires Qt 5.5.1. It has
only been tested on OS X.

This is because:

1. The webkit module is needed and is not available in Qt 5.6.

2. Legacy QuickTime APIs are needed on OS X, necessitating a 32-bit build.
   The last version of chromium that still compiles in 32-bit mode
   is bundled with webengine release with Qt 5.5.1.
   
Of course the plan is to drop the use of QuickTime APIs, and use webengine
from a 64-bit build.

OS X
====

You'll need a 32-bit install of Qt 5.5.1 with Chromium and Phonon. MacPorts
doesn't provide one so you'll have to roll your own.

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
 
    ../qt-everywhere-opensource-src-5.6.1/configure \
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
  
3. Phonon build

 a) Download and untar
    https://github.com/KDE/phonon/archive/v4.9.0.tar.gz
    
 b) This will be a shadow build that will install into the Qt installation from
    above. Create a build folder.
 
 c) Setup the build: In the build folder:
 
    cmake ../phonon-4.9.0 -G Ninja \
      -DPHONON_BUILD_PHONON4QT5=ON \
      -DPHONON_INSTALL_QT_EXTENSIONS_INTO_SYSTEM_QT=ON \
      -DCMAKE_PREFIX_PATH=(qt install folder) \
      -DPHONON_NO_DBUS=ON \
      -DCMAKE_CXX_FLAGS="-arch i386"
 
 d) Build and install
 
    ninja install
 
 e) Make the <phonon> include prefix work:
	 
    ln -s /usr/local/include/phonon4qt5/phonon /usr/local/include/
 
Ubuntu Linux
============
Fonts
	- If you want to use the web compatible fonts, you need to install the package ttf-mscorefonts-installer.
