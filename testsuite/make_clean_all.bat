set OLD_PATH=%PATH%
IF NOT EXIST "%VS100COMNTOOLS%vsvars32.bat" GOTO NO_VS10
call "%VS100COMNTOOLS%vsvars32.bat"
nmake -f makefile.vc DEBUG=0 SHARE=0 clean
nmake -f makefile.vc DEBUG=1 SHARE=0 clean
nmake -f makefile.vc DEBUG=0 SHARE=1 clean
nmake -f makefile.vc DEBUG=1 SHARE=1 clean
:NO_VS10
set PATH="E:\Compilers\Embarcadero\RAD Studio\7.0\bin"
make -f makefile.bcc DEBUG=0 SHARE=0 clean
make -f makefile.bcc DEBUG=1 SHARE=0 clean
make -f makefile.bcc DEBUG=0 SHARE=1 clean
make -f makefile.bcc DEBUG=1 SHARE=1 clean
set PATH=E:\Compilers\MinGW\bin
mingw32-make -f makefile.mgw DEBUG=0 SHARE=0 clean
mingw32-make -f makefile.mgw DEBUG=1 SHARE=0 clean
mingw32-make -f makefile.mgw DEBUG=0 SHARE=1 clean
mingw32-make -f makefile.mgw DEBUG=1 SHARE=1 clean
IF NOT EXIST "%ICPP_COMPILER11%bin\iclvars.bat" GOTO NO_INTEL
call "%ICPP_COMPILER11%bin\iclvars.bat" ia32
nmake -f makefile.icw DEBUG=0 SHARE=0 clean
nmake -f makefile.icw DEBUG=1 SHARE=0 clean
nmake -f makefile.icw DEBUG=0 SHARE=1 clean
nmake -f makefile.icw DEBUG=1 SHARE=1 clean
:NO_INTEL
set PATH=%OLD_PATH%
pause
