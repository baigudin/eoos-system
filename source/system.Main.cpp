/** 
 * The operating system main class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.Main.hpp" 
#include "system.Allocator.hpp" 
#include "system.TaskMain.hpp"
#include "system.Resource.hpp"
#include "Allocator.hpp" 

namespace system
{
    /**
     * The method which will be stated first.
     * 
     * @param config the operating system configuration.         
     * @param kernel a kernel resources factory.
     * @return error code or zero.
     */
    int32 Main::main(::api::Kernel& kernel)
    {
        if( not kernel.isConstructed() ) return -1;    
        Resource system(kernel);        
        system_ = &system;
        kernel_ = &kernel;        
        int32 stage = 0;
        int32 error = -1;
        ::api::Thread* thread = NULL;
        ::api::Toggle* global = &kernel.getGlobalInterrupt();                
        ::api::Heap& heap = kernel.getHeap();
        ::api::Scheduler& scheduler = kernel.getScheduler();        
        ::system::Allocator::setHeap(heap);        
        do
        {
            // Stage 1: set the system resource factory
            stage++;
            if(system_ == NULL || not system_->isConstructed()) break; 
            // Stage 2: set heap interrupt controller
            stage++;        
            heap.setToggle(global);            
            // Stage 3: create a first user thread
            stage++;
            TaskMain task( kernel.getStackSize() );
            thread = scheduler.createThread(task);
            if(thread == NULL || not thread->isConstructed() ) break; 
            // Stage complete: start the first user thread
            stage = -1;            
            thread->start();
            scheduler.yield();
            thread->join();
            error = task.error();
        }
        while(false);
        switch(stage)
        {
            default:
            case 3: 
                delete thread;
                            
            case 2: 
                heap.resetToggle();            
                            
            case 1:
                
            case 0: 
                break;
        }
        return error;
    }
    
    /**
     * Returns the operating system factory resource.
     *        
     * @return the operating system interface.
     */
    ::api::System& Main::getSystem()
    {
        if(system_ == NULL) kernel_->getGlobalInterrupt().disable();
        return *system_;
    }
    
    /**
     * The operating system factory resource (no boot).
     */
    ::api::System* Main::system_;
    
    /**
     * The operating system kernel factory resource (no boot).
     */
    ::api::Kernel* Main::kernel_;

}

