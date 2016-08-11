This is an in-progress port to Qt 5. At the moment, it requires Qt 5.5.1.

This is because:

1. The webkit module is needed and is not available in Qt 5.6.

2. Legacy QuickTime APIs are needed on OS X, necessitating a 32-bit build.
   The last version of chromium that still compiles in 32-bit mode
   is bundled with webengine release with Qt 5.5.1.
   
Of course the plan is to drop the use of QuickTime APIs, and use webengine
from a 64-bit build.

[Ubuntu Linux]
Fonts
	- If you want to use the web compatible fonts, you need to install the package ttf-mscorefonts-installer.
