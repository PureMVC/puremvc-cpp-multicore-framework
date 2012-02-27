#if !defined(__PURE_MVC_TEST_COMMAND_4_HPP__)
#define __PURE_MVC_TEST_COMMAND_4_HPP__

#include <pure_mvc.h>
#include "SimpleCommandTestVO.hpp"

namespace data
{
    using PureMVC::Patterns::SimpleCommand;
    using PureMVC::Interfaces::INotification;
   /**
     * A PureMVCTestCommand4 subclass used by SimpleCommand.
     *
     */
    struct PureMVCTestCommand4: SimpleCommand
    {

        /**
         * Constructor.
         */
        PureMVCTestCommand4()
            :SimpleCommand()
        { }
        
        /**
         * Fabricate a result by multiplying the input by 5
         * 
         * @param event the <code>INotification</code> carrying the <code>int</code>
         */
        virtual void execute(INotification const& note)
        {
            int& vo= *(int*)note.getBody();
            vo *= 5;
        }
    };
}

#endif /* __PURE_MVC_TEST_COMMAND_4_HPP__ */
