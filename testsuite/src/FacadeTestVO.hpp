//  FacadeTestVO.hpp
//  PureMVC_C++ Test suite
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__FACADE_TEST_VO_HPP__)
#define __FACADE_TEST_VO_HPP__

namespace data
{
    /**
     * A utility class used by FacadeTest.
     * 
     * @see org.puremvc.as3.multicore.patterns.facade.FacadeTest FacadeTest
     * @see org.puremvc.as3.multicore.patterns.facade.FacadeTestCommand FacadeTestCommand
     */
    struct FacadeTestVO
    {
        int input;
        int result;
        /**
         * Constructor.
         * 
         * @param input the number to be fed to the FacadeTestCommand
         */
        FacadeTestVO(int input)
        {
            this->input = input;
            this->result = 0;
        }
    };
}

#endif /* __FACADE_TEST_VO_HPP__ */
