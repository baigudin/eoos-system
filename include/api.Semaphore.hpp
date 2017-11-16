/**
 * Semaphore interface.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2015-2016, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef API_SEMAPHORE_HPP_
#define API_SEMAPHORE_HPP_

#include "api.Resource.hpp"

namespace api
{  
    class Semaphore : public ::api::Resource
    {
  
    public:
    
        /** 
         * Destructor.
         */
        virtual ~Semaphore(){}
        
        /**
         * Acquires one permit from this semaphore.
         *
         * The method acquires one permit or waits
         * while the permit will be released.
         *
         * @return true if the semaphore is acquired successfully.
         */  
        virtual bool acquire() = 0;
        
        /**
         * Acquires the given number of permits from this semaphore.
         *
         * The method acquires given permits number or waits
         * while the number will be released.
         *
         * @param permits the number of permits to acquire.
         * @return true if the semaphore is acquired successfully.
         */  
        virtual bool acquire(int32 permits) = 0;
        
        /**
         * Releases one permit.
         *
         * The method releases from one permit and returns this to the semaphore.
         */
        virtual void release() = 0;
        
        /**
         * Releases the given number of permits.
         *
         * The method releases from the permits and returns these to the semaphore.     
         *
         * @param permits the number of permits to release.
         */  
        virtual void release(int32 permits) = 0;
        
        /**
         * Tests if this semaphore is fair.
         *
         * @return true if this semaphore has fairness set true.
         */  
        virtual bool isFair() const = 0;
  
    };
}
#endif // API_SEMAPHORE_HPP_
