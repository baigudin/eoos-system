/** 
 * The operating system kernel class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2018, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_KERNEL_HPP_
#define SYSTEM_KERNEL_HPP_

#include "system.Object.hpp"
#include "api.Kernel.hpp"
#include "api.SystemHeap.hpp"
#include "cpu.Cpu.hpp"
#include "Configuration.hpp"
#include "Error.hpp"

namespace global
{
    namespace system
    {
        class Kernel : public system::Object, public api::Kernel
        {
            typedef system::Kernel Self;    
            typedef system::Object Parent;    
        
        public:
        
            /** 
             * Constructor.
             *
             * @param config a operating system configuration.
             */    
            Kernel(Configuration config);
            
            /** 
             * Destructor.
             */
            virtual ~Kernel();
            
            /**
             * Tests if this object has been constructed.
             *
             * @return true if object has been constructed successfully.
             */    
            virtual bool isConstructed() const;        
            
            /**
             * Returns the kernel heap memory.
             *
             * @return the kernel heap memory.
             */
            virtual api::Heap& getHeap() const;
            
            /** 
             * Returns the kernel runtime environment.
             *
             * @return the kernel runtime environment.
             */      
            virtual api::Runtime& getRuntime() const;        
            
            /** 
             * Returns a value of the kernel running time in nanoseconds.
             *
             * @return the running time in nanoseconds.
             */      
            virtual api::Value<int64>& getExecutionTime() const;
            
            /** 
             * Returns the kernel scheduler.
             *
             * @return the kernel scheduler.
             */      
            virtual api::Scheduler& getScheduler() const;        
            
            /** 
             * Returns a global interrupt controller.
             *
             * @return a global interrupt controller.
             */      
            virtual api::Toggle& getGlobalInterrupt() const;
    
            /** 
             * Creates a new mutex resource.
             *
             * @return a new mutex resource, or NULL if an error has been occurred.
             */      
            virtual api::Mutex* createMutex();
            
            /** 
             * Creates a new unfair semaphore resource.
             *
             * @param permits the initial number of permits available.   
             * @return a new semaphore resource, or NULL if an error has been occurred.
             */      
            virtual api::Semaphore* createSemaphore(int32 permits);
            
            /** 
             * Creates a new semaphore resource.
             *
             * @param permits the initial number of permits available.      
             * @param isFair  true if this semaphore will guarantee FIFO granting of permits under contention.
             * @return a new semaphore resource, or NULL if an error has been occurred.         
             */      
            virtual api::Semaphore* createSemaphore(int32 permits, bool isFair);
            
            /**
             * Creates a new interrupt resource.
             *
             * @param handler user class which implements an interrupt handler interface.
             * @param source  available interrupt source number.
             * @return a new interrupt resource, or NULL if an error has been occurred.
             */  
            virtual api::Interrupt* createInterrupt(api::Task& handler, int32 source);        
            
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
            Kernel(const Kernel& obj);
        
            /**
             * Assignment operator.
             *
             * @param obj a reference to source object.
             * @return reference to this object.     
             */
            Kernel& operator =(const Kernel& obj);           
    
            #ifdef NO_STRICT_MISRA_RULES    
            
            /**    
             * The operaing system kernel heap.
             */        
            api::SystemHeap* heap_;        
            
            #endif // NO_STRICT_MISRA_RULES    
            
            /**    
             * Configuration of the operating system.
             */
            Configuration config_;
            
            /**
             * The operating system executing CPU.
             */
            cpu::Cpu cpu_;
            
        };
    }
}
#endif // SYSTEM_KERNEL_HPP_
