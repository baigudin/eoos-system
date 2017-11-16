/** 
 * One program synchronization for executing in several processor units.
 * 
 * This interface provides a synchronization of one program 
 * which is being executed by several processor units. 
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef API_SYNCHRONIZABLE_HPP_
#define API_SYNCHRONIZABLE_HPP_

#include "api.Object.hpp"

namespace api
{
    class Synchronizable : public ::api::Object
    {
  
    public:
      
        /** 
         * Destructor.
         */
        virtual ~Synchronizable(){};
        
        /** 
         * Synchronizes an executing code section.
         *
         * The method waits while other processor units get this program pointer
         * and continues executing the program after this.
         */ 
        virtual void synchronize() = 0;
        
        /** 
         * Recasts given data to a gauge.
         *
         * The method compares given data with a gauge and recasts to it 
         * if the data does not equal to the gauge.
         *
         * @param ptr     address of data for synchronizing.
         * @param size    number of bytes for synchronizing.
         * @param channel number of processor core which data is the gauge of synchronization.
         * @return true if given data was recast to the gauge.
         */ 
        virtual bool recast(void* ptr, int32 size, int32 channel) = 0;
        
        /** 
         * Tests if given data equals the gauge.
         *
         * @param ptr     address of data for synchronizing.
         * @param size    number of bytes for synchronizing.
         * @param channel number of processor core which data is the gauge of synchronization.
         * @return true if given data equals to the gauge.
         */ 
        virtual bool isEqual(void* ptr, int32 size, int32 channel) = 0;    

  };
}
#endif // API_SYNCHRONIZABLE_HPP_
