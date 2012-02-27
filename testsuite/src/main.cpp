//  main.cpp
//  PureMVC_C++ Test suite
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#include <tut/tut.hpp>
#include <tut/tut_console_reporter.hpp>
#include <tut/tut_cppunit_reporter.hpp>
#include <iostream>
#include <cstring>
#include <memory>
#include <csignal>
#include <stdio.h>
#include <stdlib.h>
// Only available for MacOS 10.5 above
#if defined(__linux) || defined(__APPLE__ ) || defined(__bsdi__)
#include <execinfo.h>
#include <cxxabi.h>
#endif
#include <PureMVC/PureMVC.hpp>

using namespace tut;

// For tracing crash problem
void print_stacktrace(FILE *out = stderr, unsigned int max_frames = 63);
void dump(int type);

int main(int argc , char* argv[])
{
    (void)argc;
    (void)argv;
    std::signal(SIGSEGV, dump);
    std::signal(SIGFPE, dump);
    std::signal(SIGILL, dump);


    try
    {
        std::cout << "================ PureMVC Unit Test ================" << std::endl;
        tut::console_reporter *reporter;
        tut::cppunit_reporter unit_reporter;
        tut::test_result result;
        reporter = new tut::console_reporter;

        tut::runner.get().set_callback(reporter);
        tut::runner.get().insert_callback(&unit_reporter);

        // Check command line options.
        switch(argc)
        {
            case 1: // No options: run all tests.
                std::cout << "--> Run all tests" << std::endl;
                tut::runner.get().run_tests();
                std::cout << "--> Finished" << std::endl;
                break;

            case 2: // One paramter: run group of specified name.
                std::cout << "--> Run test: " << argv[1] << std::endl;
                tut::runner.get().run_tests(argv[1]);
                std::cout << "--> Finished" << std::endl;
                break;

            case 3: // Two paramters: run specified test from specified group.
                std::cout << "--> Run test: " << argv[1] << " group: " << argv[2] << std::endl;
                tut::runner.get().run_test(argv[1], std::atoi(argv[2]), result);
                std::cout << "--> Finished" << std::endl;
                break;

            default:    // Parameters error.
                std::cerr<<"incorrect number of arguments. usage:"<<std::endl;
                std::cerr<<"  "<<argv[0]<<std::endl;
                std::cerr<<"  "<<argv[0]<<" <test_group_name>"<<std::endl;
                std::cerr<<"  "<<argv[0]<<" <test_group_name> <test_case_number>"<<std::endl;
                std::cin.get();
                return 2;
                break;      // Never rech here.
        }// switch(argc)


        int returnValue = ( reporter->all_ok() ) ? 0 : 1;

        delete reporter;
        std::cin.get();
        return returnValue;   // Invert logic for shell.
    }
    catch(const tut::no_such_group &ex)
    {
        std::cerr<<argv[0]<<": tut::no_such_goup caught: "<<ex.what()<<std::endl;
        std::cin.get();
        return 120;
    }
    catch(const tut::tut_error &ex)
    {
        std::cerr<<argv[0]<<": tut::tut_error caught: "<<ex.what()<<std::endl;
        std::cin.get();
        return 130;
    }
    catch(const std::exception &ex)
    {
        std::cerr<<argv[0]<<": std::exception caught: "<<ex.what()<<std::endl;
        std::cin.get();
        return 140;
    }
    catch(...)
    {
        std::cerr<<argv[0]<<": unknown exception caught"<<std::endl;
        std::cin.get();
        return 150;
    }

    // Should never reach that far.
    std::cin.get();
    return 180;
}

/** Print a demangled stack backtrace of the caller function to FILE* out. */
void print_stacktrace(FILE *out, unsigned int max_frames)
{
#if defined(__linux) || defined(__APPLE__ ) || defined(__bsdi__)

    fprintf(out, "stack trace:\n");

    // storage array for stack trace address data
    void* addrlist[max_frames+1];

    // retrieve current stack addresses
    int addrlen = backtrace(addrlist, sizeof(addrlist) / sizeof(void*));

    if (addrlen == 0) {
        fprintf(out, "  <empty, possibly corrupt>\n");
        return;
    }

    // resolve addresses into strings containing "filename(function+address)",
    // this array must be free()-ed
    char** symbollist = backtrace_symbols(addrlist, addrlen);

    // allocate string which will be filled with the demangled function name
    size_t funcnamesize = 256;
    char* funcname = (char*)malloc(funcnamesize);

    // iterate over the returned symbol lines. skip the first, it is the
    // address of this function.
    for (int i = 1; i < addrlen; i++)
    {
        char *begin_name = 0, *begin_offset = 0, *end_offset = 0;

        // find parentheses and +address offset surrounding the mangled name:
        // ./module(function+0x15c) [0x8048a6d]
        for (char *p = symbollist[i]; *p; ++p)
        {
            if (*p == '(')
                begin_name = p;
            else if (*p == '+')
                begin_offset = p;
            else if (*p == ')' && begin_offset) {
                end_offset = p;
                break;
            }
        }

        if (begin_name && begin_offset && end_offset
            && begin_name < begin_offset)
        {
            *begin_name++ = '\0';
            *begin_offset++ = '\0';
            *end_offset = '\0';

            // mangled name is now in [begin_name, begin_offset) and caller
            // offset in [begin_offset, end_offset). now apply
            // __cxa_demangle():

            int status;
            char* ret = abi::__cxa_demangle(begin_name,
                funcname, &funcnamesize, &status);
            if (status == 0) {
                funcname = ret; // use possibly realloc()-ed string
                fprintf(out, "  %s : %s+%s\n",
                    symbollist[i], funcname, begin_offset);
            }
            else {
                // demangling failed. Output function name as a C function with
                // no arguments.
                fprintf(out, "  %s : %s()+%s\n",
                    symbollist[i], begin_name, begin_offset);
            }
        }
        else
        {
            // couldn't parse the line? print the whole line.
            fprintf(out, "  %s\n", symbollist[i]);
        }
    }

    free(funcname);
    free(symbollist);
#else
    (void)out;
    (void)max_frames;
#endif
}

void dump(int type)
{
    std::cout << std::endl << "What!???" << std::endl;
    switch(type)
    {
    case SIGSEGV: std::signal(SIGSEGV, SIG_DFL);break;
    case SIGFPE: std::signal(SIGFPE, SIG_DFL);break;
    case SIGILL: std::signal(SIGILL, SIG_DFL);break;
    }
    std::cout << "Oops!!! Die..." << std::endl;
    print_stacktrace();
}
