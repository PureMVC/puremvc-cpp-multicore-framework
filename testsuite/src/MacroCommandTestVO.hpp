//  MacroCommandTestVO.hpp
//  PureMVC_C++ Test suite
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__MACRO_COMMAND_TEST_VO_HPP__)
#define __MACRO_COMMAND_TEST_VO_HPP__

namespace data
{
    /**
    * A utility class used by MacroCommandTest.
    */
    struct MacroCommandTestVO
    {
        int input;
        int result1;
        int result2;
        /**
         * Constructor.
         * 
         * @param input the number to be fed to the MacroCommandTestCommand
         */
        MacroCommandTestVO(int input)
        {
            this->input = input;
            this->result1 = 0;
            this->result2 = 0;
        }
    };
}

#endif /* __MACRO_COMMAND_TEST_VO_HPP__ */
