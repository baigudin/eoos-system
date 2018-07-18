/** 
 * The operating system kernel class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2018, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.Kernel.hpp"
#include "library.Heap.hpp"

namespace local
{
    namespace system
    {
        /** 
         * Constructor.
         *
         * @param config a operating system configuration.
         */    
        Kernel::Kernel(Configuration const config) : Parent(),
            #ifdef NO_STRICT_MISRA_RULES    
            heap_   (NULL),
            #endif // NO_STRICT_MISRA_RULES
            config_ (config),
            cpu_    (config){
            bool const isConstructed = construct();
            setConstructed( isConstructed );
        }
        
        /** 
         * Destructor.
         */
        Kernel::~Kernel()
        {
        }
        
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        bool Kernel::isConstructed() const
        {
            return Parent::isConstructed();
        }
        
        /**
         * Returns the kernel heap memory.
         *
         * @return the kernel heap memory.
         */
        api::Heap& Kernel::getHeap() const
        {
            #ifdef NO_STRICT_MISRA_RULES    
            if( not Self::isConstructed() )
            {
                terminate(ERROR_SYSCALL_CALLED);
            }
            return *heap_;        
            #else    
            terminate(ERROR_SYSCALL_CALLED);
            #endif // NO_STRICT_MISRA_RULES    
        }
        
        /** 
         * Returns the kernel runtime environment.
         *
         * @return the kernel runtime environment.
         */      
        api::Runtime& Kernel::getRuntime() const
        {
        }        
        
        /** 
         * Returns a value of the kernel running time in nanoseconds.
         *
         * @return the running time in nanoseconds.
         */      
        api::Value<int64>& Kernel::getExecutionTime() const
        {
        }
        
        /** 
         * Returns the kernel scheduler.
         *
         * @return the kernel scheduler.
         */      
        api::Scheduler& Kernel::getScheduler() const
        {
        }        
        
        /** 
         * Returns a global interrupt controller.
         *
         * @return a global interrupt controller.
         */      
        api::Toggle& Kernel::getGlobalInterrupt() const
        {
        }
    
        /** 
         * Creates a new mutex resource.
         *
         * @return a new mutex resource, or NULL if an error has been occurred.
         */      
        api::Mutex* Kernel::createMutex()
        {
        }
        
        /** 
         * Creates a new unfair semaphore resource.
         *
         * @param permits the initial number of permits available.   
         * @return a new semaphore resource, or NULL if an error has been occurred.
         */      
        api::Semaphore* Kernel::createSemaphore(int32 const permits)
        {
        }
        
        /** 
         * Creates a new semaphore resource.
         *
         * @param permits the initial number of permits available.      
         * @param isFair  true if this semaphore will guarantee FIFO granting of permits under contention.
         * @return a new semaphore resource, or NULL if an error has been occurred.         
         */      
        api::Semaphore* Kernel::createSemaphore(int32 permits, bool const isFair)
        {
        }
        
        /**
         * Creates a new interrupt resource.
         *
         * @param handler user class which implements an interrupt handler interface.
         * @param source  available interrupt source number.
         * @return a new interrupt resource, or NULL if an error has been occurred.
         */  
        api::Interrupt* Kernel::createInterrupt(api::Task& handler, int32 const source)
        {
        }
        
        /**
         * Constructs this object.
         *
         * @return true if object has been constructed successfully.     
         */    
        bool Kernel::construct()
        {
            bool res = Self::isConstructed();
            while(res == true)
            {
                #ifdef NO_STRICT_MISRA_RULES
                // Construct a heap object
                heap_ = new (config_.heapAddr) library::Heap(config_.heapSize);
                if( heap_ == NULL || not heap_->isConstructed() ) 
                {
                    res = false;
                    continue;
                }
                #endif // NO_STRICT_MISRA_RULES
                // The construction completed successfully
                break;
            }
            return res;
        }
        
        /**
         * Terminates the operating system execution.
         *
         * @param error a termination status code.
         */
        void Kernel::terminate(Error const error)
        {
            // ... TODO ...
            volatile bool const isTerminate = true;
            while( isTerminate ){};
        }    
    }
}
