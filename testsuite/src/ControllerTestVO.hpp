//  ControllerTestVO.hpp
//  PureMVC_C++ Test suite
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__CONTROLLER_TEST_VO_HPP__)
#define __CONTROLLER_TEST_VO_HPP__

namespace data
{
       /**
       * A utility class used by ControllerTest.
       * 
       * @see org.puremvc.as3.multicore.core.controller.ControllerTest ControllerTest
       * @see org.puremvc.as3.multicore.core.controller.ControllerTestCommand ControllerTestCommand
       */
    struct ControllerTestVO
    {
        int input;
        int result;
        /**
         * Constructor.
         * 
         * @param input the number to be fed to the ControllerTestCommand
         */
        ControllerTestVO(int input)
        {
            this->input = input;
            this->result = 0;
        }
    };
}

#endif /* __CONTROLLER_TEST_VO_HPP__ */
