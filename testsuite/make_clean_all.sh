make -f makefile.gcc DEBUG=0 SHARE=0 clean
make -f makefile.gcc DEBUG=1 SHARE=0 clean
make -f makefile.gcc DEBUG=0 SHARE=1 clean
make -f makefile.gcc DEBUG=1 SHARE=1 clean
