#if !defined(__PURE_MVC_TEST_COMMAND_HPP__)
#define __PURE_MVC_TEST_COMMAND_HPP__

#include <pure_mvc.h>
#include "SimpleCommandTestVO.hpp"

namespace data
{
    using PureMVC::Patterns::SimpleCommand;
    using PureMVC::Interfaces::INotification;
    /**
     * A PureMVCTestCommand subclass used by SimpleCommand.
     *
     */
    struct PureMVCTestCommand: SimpleCommand
    {

        /**
         * Constructor.
         */
        PureMVCTestCommand()
            :SimpleCommand()
        { }
        
        /**
         * Fabricate a result by multiplying the input by 2
         * 
         * @param event the <code>INotification</code> carrying the <code>int</code>
         */
        virtual void execute(INotification const& note)
        {
            int& vo= *(int*)note.getBody();
            vo *= 2;
        }
    };
}

#endif /* __PURE_MVC_TEST_COMMAND_HPP__ */
