This archive contains the source code of VeraCrypt with integrated 
keyword spotting system Mycroft Precise for volume dismount 
on detection of personalized spoken keyword.

Original repositories
=====================

This project is derived from the original VeraCrypt source code located 
at https://github.com/veracrypt/VeraCrypt. The original code of the integrated 
KWS system can be found at https://github.com/MycroftAI/mycroft-precise.

Bulding on Linux 
================

Requirements for Building the application on Linux
--------------------------------------------------

- GNU Make
- GNU C++ Compiler 4.0 or compatible
- Apple Xcode (Mac OS X only)
- YASM 1.3.0 or newer (Linux only, x86/x64 architecture only)
- pkg-config
- wxWidgets 3.0 shared library and header files installed or
  wxWidgets 3.0 library source code (available at https://www.wxwidgets.org)
- FUSE library and header files (available at https://github.com/libfuse/libfuse
  and https://osxfuse.github.io/)


Instructions for Building VeraCrypt on Linux:
---------------------------------------------

1) Change the current directory to the root of the VeraCrypt source code.

2) If you have no wxWidgets shared library installed, run the following
   command to configure the wxWidgets static library for VeraCrypt and to
   build it:

   $ make WXSTATIC=1 WX_ROOT=/usr/src/wxWidgets wxbuild

   The variable WX_ROOT must point to the location of the source code of the
   wxWidgets library. Output files will be placed in the './wxrelease/'
   directory.

3) To build VeraCrypt, run the following command:

   $ make

   or if you have no wxWidgets shared library installed:

   $ make WXSTATIC=1

4) If successful, the VeraCrypt executable should be located in the directory
   'Main'.

By default, a universal executable supporting both graphical and text user
interface (through the switch --text) is built.
On Linux, a console-only executable, which requires no GUI library, can be
built using the 'NOGUI' parameter:

   $ make NOGUI=1 WXSTATIC=1 WX_ROOT=/usr/src/wxWidgets wxbuild
   $ make NOGUI=1 WXSTATIC=1
   
The KWS system dependencies:
----------------------------

 - python3-pip
 - libopenblas-dev
 - python3-scipy
 - cython
 - libhdf5-dev
 - python3-h5py
 - portaudio19-dev


