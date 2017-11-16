/** 
 * The configuration of a target processor.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef CONFIGURATION_HPP_
#define CONFIGURATION_HPP_

#include "Types.hpp"

struct Configuration
{

public:

    /**
     * Source clock of CPU oscillator in Hz.
     */      
    int64 sourceClock;
    
    /**
     * CPU clock in Hz.
     */  
    int64 cpuClock;
  
    /**
     * Start address of heap page.
     */      
    void* heapAddr;    
    
    /**
     * Size of heap page in bytes.
     */
    int64 heapSize; 

    /**
     * Size of stack of user main thread in bytes.
     */    
    int32 stackSize;
  
    /** 
     * Constructor.
     */     
    Configuration();
    
    /** 
     * Copy constructor.
     *
     * @param obj a source object.
     */     
    Configuration(const Configuration& obj) :
        sourceClock (obj.sourceClock),
        cpuClock    (obj.cpuClock),
        heapAddr    (obj.heapAddr),
        heapSize    (obj.heapSize),
        stackSize   (obj.stackSize){
    }
        
    /** 
     * Destructor.
     */
   ~Configuration()
    {
    }
  
    /**
     * Assignment operator.
     *
     * @param obj a source object.
     * @return this object.     
     */
    Configuration& operator =(const Configuration& obj)
    {
        sourceClock = obj.sourceClock;
        cpuClock    = obj.cpuClock;
        heapAddr    = obj.heapAddr;
        heapSize    = obj.heapSize;
        stackSize   = obj.stackSize;
        return *this;
    }
     
};
#endif // CONFIGURATION_HPP_
