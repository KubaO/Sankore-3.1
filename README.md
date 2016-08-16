This mac-avfoundation branch is for porting from legacy Carbon QuickTime APIs to AVFoundation.
It is a prerequisite to 64-bit builds.

This is a WORK IN PROGRESS. If you see this message, the code isn't suppoed to build yet, no matter
what statements to the contrary you might read below.

It builds successfully on OS X 10.10 and starts up and brings up the GUI. All the dependencies
are internal. The extent to which it functions hasn't been investigated yet.

It should also build on Windows with MSVC 2015.

The legacy Qt requirement will be dropped as soon as ICU and WebKit find their way into
the third party repository.

The following third-party prerequisites are built along with the project:

- phonon
- quazip
- xpdf
- zlib    (on Windows)
- icu     (on Windows)
- openssl (on Windows)

General Prerequisites
=====================

OS X 10.10 or Windows+MSVC 2015. Other platforms will be investigated eventually.

Preparation & Building
======================

1. Check out the Sankore-ThirdParty repository. Both repositories should be
   in the same folder:

   |
   +- Sankore              (this can have arbitrary name)
   +- Sankore-Thirdparty   (this is a default, if you change it edit config.pri to match)

2. After installing the prerequisites, build the Sankore_top.pro project.

Windows Prerequisites
=====================

Qt 5.5.1 with Webkit. You'll need to build and install ICU prior to building Qt.

OS X Prerequisites
==================

Qt 5.6.1 from Macports on OS X. It includes the webkit module.

1. Install MacPorts.
2. Install Qt:

    port install qt5-mac

Ubuntu Linux Prerequisites
==========================
Fonts
	- If you want to use the web compatible fonts, you need to install the package ttf-mscorefonts-installer.
