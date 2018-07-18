/** 
 * The operating system class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2018, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_SYSTEM_HPP_
#define SYSTEM_SYSTEM_HPP_

#include "system.Object.hpp"
#include "api.System.hpp"
#include "system.Kernel.hpp"
#include "Configuration.hpp"
#include "Error.hpp"

namespace local
{
    namespace system
    {
        class System : public system::Object, public api::System
        {
            typedef system::System Self;    
            typedef system::Object Parent;    
        
        public:
        
            /** 
             * Constructor.
             */    
            System();
            
            /** 
             * Destructor.
             */
            virtual ~System();
            
            /**
             * Tests if this object has been constructed.
             *
             * @return true if object has been constructed successfully.
             */    
            virtual bool isConstructed() const;
            
            /**
             * Returns the operating system heap memory.
             *
             * @return the heap memory.
             */
            virtual api::Heap& getHeap() const;
            
            /**
             * Returns running time of the operating system in nanoseconds.
             *
             * @return time in nanoseconds.
             */
            virtual int64 getTime() const;
            
            /**
             * Terminates the operating system execution.
             */
            virtual void terminate() const;                   
            
            /**
             * Executes the operating system.
             *
             * @return zero, or error code if the execution has been terminated.
             */
            int32 execute();        
        
            /** 
             * Returns the operating system syscall interface.
             *
             * @return the operating system syscall interface.
             */      
            static api::System& call();
            
        private:
        
            /**
             * Constructs this object.
             *
             * @return true if object has been constructed successfully.     
             */    
            bool construct();
            
            /**
             * Terminates the operating system execution.
             *
             * @param error a termination status code.
             */
            static void terminate(Error error);
            
            /**
             * Copy constructor.
             *
             * @param obj a reference to source object.
             */
            System(const System& obj);
        
            /**
             * Assignment operator.
             *
             * @param obj a reference to source object.
             * @return reference to this object.     
             */
            System& operator =(const System& obj);        
        
            /**
             * The operatin system interface.
             */
            static api::System* system_;
            
            /**    
             * Configuration of the operating system .    
             *
             * NOTE: The variable must be the first, as it must be initialized first.
             */
            const Configuration config_;        
            
            /**
             * The operating system kernel.
             */
            system::Kernel kernel_;      
            
        };
    }
}
#endif // SYSTEM_SYSTEM_HPP_
