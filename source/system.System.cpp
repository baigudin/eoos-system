/** 
 * The operating system class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2018, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.System.hpp"
#include "Program.hpp"

namespace global
{
    namespace system
    {
        /** 
         * Constructor.
         */    
        System::System() : Parent(),
            config_ (),
            kernel_ (config_){
            const bool isConstructed = construct();
            setConstruct( isConstructed );
        }
        
        /** 
         * Destructor.
         */
        System::~System()
        {
        }
        
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        bool System::isConstructed() const
        {
            return getConstruct();
        }
        
        /**
         * Returns the operating system heap memory.
         *
         * @return the heap memory.
         */
        api::Heap& System::getHeap() const
        {
            if( not Self::isConstructed() )
            {
                terminate(SYSER_SYSCALL_CALLED);
            }
            return kernel_.getHeap();
        }    
        
        /**
         * Returns running time of the operating system in nanoseconds.
         *
         * @return time in nanoseconds.
         */
        int64 System::getTime() const
        {
            return 0;
        }
        
        /**
         * Terminates the operating system execution.
         *
         * @param status a termination status.
         */
        void System::terminate() const
        {
            terminate(SYSER_USER_TERMINATION);
        }
        
        /**
         * Executes the operating system.
         *
         * @return zero, or error code if the execution has been terminated.
         */
        int32 System::execute()
        {
            if( not Self::isConstructed() )
            {
                return SYSER_INITIALIZATION_FAILED;
            }
            return Program::start();
        }
    
        /** 
         * Returns the operating system syscall interface.
         *
         * @return the operating system syscall interface.
         */   
        api::System& System::call()
        {
            if(system_ == NULL)
            {
                terminate(SYSER_SYSCALL_CALLED);
            }
            return *system_;
        }
        
        /**
         * Constructs this object.
         *
         * @return true if object has been constructed successfully.     
         */    
        bool System::construct()
        {
            if( not Self::isConstructed() )
            {
                return false;
            }
            if( system_ != NULL )
            {
                return false;
            }
            if( not kernel_.isConstructed() )
            {
                return false;        
            }
            system_ = this;
            return true;
        }
        
        /**
         * Terminates the operating system execution.
         *
         * @param error a termination status code.
         */
        void System::terminate(Error)
        {
            // ... TODO ...
            while(true);
        }
        
        /**
         * The operatin system interface.
         */
        api::System* System::system_ = NULL;
    }
}

/**
 * The main function.
 * 
 * The following tasks must be done before the function called:
 * 1. Stack has been set.
 * 2. CPU registers have been set.
 * 3. Run-time initialization has been completed.
 * 4. Global variables have been set.
 * 5. Global constructors have been called.
 * 
 * @return error code or zero.
 */   
int main()
{
    ::global::system::System eoos;
    return eoos.execute();
}

