Introduction:
=============
PureMVC is an excellent framework for Action Script which uses MVC design pattern inside.
It is a porting version with all APIs are the same to PureMVC in Action Script 3 version. 
PureMVC also supports thread-safe, singleton/multiton versions and all API base on standard STL library. 

Supporting compilers:
=====================
 + Microsoft Visual C++ 6.0 7.0 8.0 9.0 10.0
 + Minimalist GNU for Windows G++ 3.4.5, 4.x.x (MinGW32)
 + GCC for Linux, MacOS: 3.4.5, 4.x.x
 + Embarcadero C++ Builder 6.21 (Borland C++ Builder in old-name)
 + Digital Mars C++ 8.42n

Supporting operation systems:
=============================
 + Microsoft Windows XP SP3, Micorosoft Windows 7
 + Linux (Fedora 7, CentOS 5.2 64 bit & 32 bit)
 + Macintosh (Tiger X 10.4, Leopard 10.5)

Terminology:
============
bcc: Borland C++ Compiler / Embarcadero C++ Compiler
vc: Visual C++ Compiler
dmc: Digital Marcs C++ Compiler
ic: Intel C++ Compiler
mgw: Minimalist GNU for Windows (MinGW32)
gcc: GNU C++ Compiler

PureMVC source code & binary structure:
=======================================
 + bin                          <-- Contain the shared library after build soure code of PureMVC (*.dll on Windows & *.so on Linux/MacOS)
      \bcc                        <-- *Shared libary for Embarcadero C++ (Windows)
          \PureMVC.dll              <-- Release mode (Depending on C runtime library)  ==> make -f makekfile.bcc
          \PureMVCd.dll             <-- Debug mode   (Depending on C runtime library)  ==> make -f makekfile.bcc DEBUG=1
      \dmc                        <-- *Shared libary for Digital Mars C++ (Windows)
          \PureMVC.dll              <-- Release mode (Depending on C runtime library)  ==> make -f makekfile.dmc / smake -f makefile.dmc_smake
          \PureMVCd.dll             <-- Debug mode   (Depending on C runtime library)  ==> make -f makekfile.dmc / smake -f makefile.dmc_smake DEBUG=1
      \mingw                      <-- *Shared library for Minimalist GNU for Windows (Windows)
            \PureMVC.dll            <-- Release mode (Depending on C runtime library)  ==> mingw32-make -f makekfile.mgw
            \PureMVCd.dll           <-- Debug mode   (Depending on C runtime library)  ==> mingw32-make -f makekfile.mgw DEBUG=1
      \gcc                        <-- *Shared ligrary for GCC (MSYS/Linux only)
          \libPureMVCd.so           <-- Release mode                                   ==> make -f makekfile.gcc
          \libPureMVCd.so           <-- Debug mode                                     ==> make -f makekfile.gcc DEBUG=1
      \ic                         <-- *Shared libary for Intel C++ (Windows/Linux)
         \PureMVC.dll               <-- Release mode (Depending on C runtime library)
         \PureMVCd.dll              <-- Debug mode   (Depending on C runtime library)
      \vc                         <-- *Shared libary for Visual C++ (Windows)
         \PureMVC.dll               <-- Release mode (Depending on C runtime library)  ==> make -f makekfile.vc
         \PureMVCd.dll              <-- Debug mode   (Depending on C runtime library)  ==> make -f makekfile.vc DEBUG=1
 + lib                          <-- Contain the static linking library and static linking for shared library (*.a. *.lib on Windows & *.a on Linux/MacOS)
      \bcc                        <-- *Static libary for Embarcadero C++ (Windows)
          \PureMVC.lib              <-- Release mode (Static linking library, included C runtime library)  ==> make -f makekfile.bcc
          \PureMVCd.lib             <-- Debug mode   (Static linking library, included C runtime library)  ==> make -f makekfile.bcc DEBUG=1
          \PureMVCdll.lib           <-- Release mode (Import linking to shared library)                    ==> make -f makekfile.bcc
          \PureMVCddll.lib          <-- Debug mode   (Import linking to shared library)                    ==> make -f makekfile.bcc DEBUG=1
      \dmc                        <-- *Static libary for Digital Mars C++ (Windows)
          \PureMVC.lib              <-- Release mode (Static linking library, included C runtime library)  ==> make -f makekfile.dmc / smake -f makefile.dmc_smake
          \PureMVCd.lib             <-- Debug mode   (Static linking library, included C runtime library)  ==> make -f makekfile.dmc / smake -f makefile.dmc_smake DEBUG=1
          \PureMVCdll.lib           <-- Release mode (Import linking to shared library)                    ==> make -f makekfile.dmc / smake -f makefile.dmc_smake
          \PureMVCddll.lib          <-- Debug mode   (Import linking to shared library)                    ==> make -f makekfile.dmc / smake -f makefile.dmc_smake DEBUG=1
      \mingw                      <-- *Static library for Minimalist GNU for Windows (Windows)
            \libPureMVC.a           <-- Release mode (Static linking library, included C runtime library)  ==> mingw32-make -f makekfile.mgw
            \libPureMVCd.a          <-- Debug mode   (Static linking library, included C runtime library)  ==> mingw32-make -f makekfile.mgw DEBUG=1
            \libPureMVCdll.a        <-- Release mode (Import linking to shared library)                    ==> mingw32-make -f makekfile.mgw
            \libPureMVCddll.a       <-- Debug mode   (Import linking to shared library)                    ==> mingw32-make -f makekfile.mgw DEBUG=1
      \gcc                        <-- *Static ligrary for GCC (MSYS/Linux only)                            
          \libPureMVC.a             <-- Release mode (Static linking library)                              ==> make -f makekfile.gcc
          \libPureMVCd.a            <-- Debug mode   (Static linking library)                              ==> make -f makekfile.gcc DEBUG=1
      \ic                         <-- *Static libary for Intel C++ (Windows/Linux)                         
         \PureMVC.lib               <-- Release mode (Static linking library, included C runtime library)  
         \PureMVCd.lib              <-- Debug mode   (Static linking library, included C runtime library)  
         \PureMVCdll.lib            <-- Release mode (Import linking to shared library)                    
         \PureMVCddll.lib           <-- Debug mode   (Import linking to shared library)                    
      \vc                         <-- *Static libary for Visual C++ (Windows)                              
         \PureMVC.lib               <-- Release mode (Static linking library, included C runtime library)  ==> nmake -f makekfile.vc
         \PureMVCd.lib              <-- Debug mode   (Static linking library, included C runtime library)  ==> nmake -f makekfile.vc DEBUG=1
         \PureMVCdll.lib            <-- Release mode (Import linking to shared library)                    ==> nmake -f makekfile.vc
         \PureMVCddll.lib           <-- Debug mode   (Import linking to shared library)                    ==> nmake -f makekfile.vc DEBUG=1
 + include                      <-- Contain only header files of PureMVC C++
 + src                          <-- Contain the source code of PureMVC C++ which need to build on your host/target machine.
 + testsuite                    <-- Contain the test suilte of PureMVC++ which developed base on Template Unit Test (http://tut-framework.sourceforge.net/)       
 + configure                    <-- Configure file for building PureMVC on Linux
 + makefile.bcc                 <-- Makefile for Embarcadero C++ Compiler
 + makefile.bkl                 <-- Bakefile script to generate makefile base on Bakefile (http://www.bakefile.org/index.html)
 + makefile.dmc                 <-- Makefile for Digital Mars C++ Compiler (using with make.exe from Digital Mars)
 + makefile.dmc_smake           <-- Makefile for Digital Mars C++ Compiler (using with smake.exe from Digital Mars)
 + makefile.gcc                 <-- Makefile for GCC (Linux only)
 + makefile.icw                 <-- Makefile for Intel C++ (Windows only)
 + makefile.mgw                 <-- Makefile for MinGW32
 + makefile.vc                  <-- Makefile for Visual C++ Compiler
 + puremvc.pc.in               <-- pkg-config file for PureMVC on Linux/MacOS
 + puremvc-static.pc.in        <-- pkg-config file for PureMVC static linking library on Linux/MacOS
 + PureMVC.Doxyfile             <-- Doxygen documentation
 + PureMVC.sln                  <-- Visual Studio solution file which I used to port PureMVC, you can use this to build source code.
 + ...

*) This directory will be generated after building PureMVC source code.

Building PureMVC source code:
=============================
PureMVC was delivered with source code only (without binary libary). So that before using PureMVC. End user must
build source code again suitable for OS platform and compilers. Please read instruction below carefully to build
soure code successfully on your host/target platform and compilers. 

Microsoft Windows variant (Windows XP, Windows Vista, Windows 7):
----------------------------------------------------------------
    @ Build with Microsoft Visual C++ (in Microsoft Visual Studio 2005/2008/2010): (Makefile & IDE)
    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        1) Please download and install Visual Studio on your computer, please select C++ Language to build PureMVC late. (http://www.microsoft.com/visualstudio)
        # With Makefile:
        ################
        2) Supposing that you install Microsoft Visual Studio 20xx in C:\Program Files\. On desktop screen please click:
            Start --> All Program --> Microsoft Visual Studio 20xx --> Visual Studio Tools --> Visual Studio 2008 Command Prompt
        or you can run program directly like that in command line:
            "C:\Program Files\Microsoft Visual Studio xx.0\VC\vcvarsall.bat"
        3) In "Visual Studio Command Prompt" please jump to source code of PureMVC by command:
           cd /d "<the directory path of PureMVC source code - Ex: D:\PureMVC\>"
        4) Typing command below to build PureMVC with Visual C++
           nmake -f makefile.vc                                 <-- Build PureMVC in release mode (recommend)
           nmake -f makefile.vc DEBUG=1                         <-- Build PureMVC in debug mode (for bug tracking only)
        # Or with Visual Studio:
        ########################
        2) Open PureMVC.sln, in Visual Studio there are four mode to build.
            Debug Share     (Build shared library in debug mode)
            Debug Static    (Build static library in debug mode)
            Release Shared  (Build shared library in release mode)
            Release Static  (Build static library in release mode)
        3) Select all mode and build.
        (note: xx is version of Visual Studio)

    @ Build with Borland / Embarcadero C++: (Makefile only)
    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        1) Please download and install Embarcadero C++ Builder XE/Starter or C++ Builder compiler at least. (http://www.embarcadero.com/products/cbuilder)
        2) Supposing that you install in C:\Program Files\
        3) Please start up command line: Start --> Run --> typing: cmd
        4) In command line please typing:
            set PATH="C:\Program Files\Embarcadero\RAD Studio\x.x\bin"
           to set path of make.exe
        5) Jump to soure code of PureMVC:
           cd /d "<the directory path of PureMVC source code - Ex: D:\PureMVC\>"
        6) Typing command below to build PureMVC with Embarcadero C++
           make -f makefile.bcc                                 <-- Build PureMVC in release mode (recommend)
           make -f makefile.bcc DEBUG=1                         <-- Build PureMVC in debug mode (for bug tracking only)
        7) Support C++0x feature:
           make -f makefile.bcc CPP0X=1                          <-- Build PureMVC in release mode & C++0x features
           make -f makefile.bcc DEBUG=1 CPP0X=1                  <-- Build PureMVC in debug mode & C++0x features
        (note: xx is version of Embarcadero tool)
 
    @ Build with Minimalist GNU for Windows G++ - MinGW: (Makefile only)
    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        1) Please download and install MinGW. (http://tdm-gcc.tdragon.net/)
        2) Supposing that you install in C:\MinGW\
        3) Please start up command line: Start --> Run --> typing: cmd
        4) In command line please typing:
            set PATH="C:\MinGW\bin"
           to set path of mingw32-make.exe
        5) Jump to soure code of PureMVC:
           cd /d "<the directory path of PureMVC source code - Ex: D:\PureMVC\>"
        6) Typing command below to build PureMVC with MinGW
           mingw32-make -f makefile.mingw                                 <-- Build PureMVC in release mode (recommend)
           mingw32-make -f makefile.mingw DEBUG=1                         <-- Build PureMVC in debug mode (for bug tracking only)
        7) Support C++0x feature:
           mingw32-make -f makefile.mingw CPP0X=1                         <-- Build PureMVC in release mode & C++0x features
           mingw32-make -f makefile.mingw DEBUG=1 CPP0X=1                 <-- Build PureMVC in debug mode & C++0x features

    @ Build witn Digital Marc C++: (Makefile only)
    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        1) Please download and install Digital Mars C++ & tool. (http://www.digitalmars.com)
        2) Supposing that you install in C:\dm\
        3) Please start up command line: Start --> Run --> typing: cmd
        4) In command line please typing:
            set PATH="C:\dm\bin"
           to set path of make.exe of smake.exe
        5) Jump to soure code of PureMVC:
           cd /d "<the directory path of PureMVC source code - Ex: D:\PureMVC\>"
        6) Typing command below to build PureMVC with MinGW
           For make:
               make -f makefile.dmc
           For smake:
               smake -f makefile.dmc_smake                                 <-- Build PureMVC in release mode (recommend)
               smake -f makefile.dmc_smake DEBUG=1                         <-- Build PureMVC in debug mode (for bug tracking only)

    @ Build with Intel C++ for Windows: (Makefile only)
    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        1) Please download and install Intel C++ on Windows. (http://software.intel.com/en-us/articles/intel-compilers/)
        2) Supposing that you install in C:\Program Files\
        3) Please start up command line: Start --> Run --> typing: cmd
        4) In command line please typing:
            "D:\Program Files\Intel\Compiler\xx.x\054\bin\iclvars.bat" ia32
        5) Jump to soure code of PureMVC:
           cd /d "<the directory path of PureMVC source code - Ex: D:\PureMVC\>"
        6) Typing command below to build PureMVC with Intel C++ on Windows
           nmake -f makefile.icw                                 <-- Build PureMVC in release mode (recommend)
           nmake -f makefile.icw DEBUG=1                         <-- Build PureMVC in debug mode (for bug tracking only)
           
Linux variant (Fedora, Ubuntu, Red Hat Enterprise, CentOS, Mandriva, SuSE)
--------------------------------------------------------------------------
    @ Build with default makefile.gcc (Testing only)
    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        1) Open shell terminate and jump to source code of PureMVC
        2) Typing
           make -f makefile.gcc                                 <-- Build PureMVC in release mode (recommend)
           make -f makefile.gcc DEBUG=1                         <-- Build PureMVC in debug mode (for bug tracking only)
        3) Build with C++0x features
           make -f makefile.gcc CPP0X=1                         <-- Build PureMVC in release mode & C++0x features
           make -f makefile.gcc DEBUG=1 CPP0X=1                 <-- Build PureMVC in debug mode & C++0x features

    @ Build with configure (STRONG RECOMMEND)
    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        1) Open shell terminate and jump to source code of PureMVC
        2) Typing
            #> sh configure
            #> make
            #> make install
        3) Recheck again
            #> pkg-config --libs --cflags puremvc
            #> pkg-config --libs --cflags puremvc-static
        4) Build with C++0x features
            #> sh configure --enable-c++0x
            #> make
            #> make install

Macintosh variant (Tiger X 10.4, Leopard 10.5):
---------------------------------------------
   1) Please download XCode and install on MacOS machine
   2) Download pkg-config for MacOS (http://mac.softpedia.com/get/Developer-Tools/pkg-config.shtml) and install
    @ Build with default makefile.gcc (Testing only)
    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        1) Open shell terminate and jump to source code of PureMVC
        2) Typing
           make -f makefile.gcc                                 <-- Build PureMVC in release mode (recommend)
           make -f makefile.gcc DEBUG=1                         <-- Build PureMVC in debug mode (for bug tracking only)

    @ Build with configure (STRONG RECOMMEND)
    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        1) Open shell terminate and jump to source code of PureMVC
        2) Typing
            #> sh configure
            #> make
            #> make install
        3) Recheck again
            #> pkg-config --libs --cflags puremvc
            #> pkg-config --libs --cflags puremvc-static
        4) Build with C++0x features
            #> sh configure --enable-c++0x
            #> make
            #> make install

Done!
Good luck!!!
