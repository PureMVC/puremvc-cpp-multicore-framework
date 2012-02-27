#if !defined(__PURE_MVC_TEST_COMMAND_3_HPP__)
#define __PURE_MVC_TEST_COMMAND_3_HPP__

#include <pure_mvc.h>
#include "SimpleCommandTestVO.hpp"

namespace data
{
    using PureMVC::Patterns::SimpleCommand;
    using PureMVC::Interfaces::INotification;
   /**
     * A PureMVCTestCommand3 subclass used by SimpleCommand.
     *
     */
    struct PureMVCTestCommand3: SimpleCommand
    {

        /**
         * Constructor.
         */
        PureMVCTestCommand3()
            :SimpleCommand()
        { }
        
        /**
         * Fabricate a result by multiplying the input by 4
         * 
         * @param event the <code>INotification</code> carrying the <code>int</code>
         */
        virtual void execute(INotification const& note)
        {
            int& vo= *(int*)note.getBody();
            vo *= 4;
        }
    };
}

#endif /* __PURE_MVC_TEST_COMMAND_3_HPP__ */
