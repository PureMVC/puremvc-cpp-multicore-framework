#if !defined(__PURE_MVC_TEST_COMMAND_2_HPP__)
#define __PURE_MVC_TEST_COMMAND_2_HPP__

#include <pure_mvc.h>
#include "SimpleCommandTestVO.hpp"

namespace data
{
    using PureMVC::Patterns::SimpleCommand;
    using PureMVC::Interfaces::INotification;
   /**
     * A PureMVCTestCommand2 subclass used by SimpleCommand.
     *
     */
    struct PureMVCTestCommand2: SimpleCommand
    {

        /**
         * Constructor.
         */
        PureMVCTestCommand2()
            :SimpleCommand()
        { }
        
        /**
         * Fabricate a result by multiplying the input by 3
         * 
         * @param event the <code>INotification</code> carrying the <code>int</code>
         */
        virtual void execute(INotification const& note)
        {
            int& vo= *(int*)note.getBody();
            vo *= 3;
        }
    };
}

#endif /* __PURE_MVC_TEST_COMMAND_2_HPP__ */
