/** 
 * Root class of the operating system class hierarchy.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2018, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_OBJECT_HPP_
#define SYSTEM_OBJECT_HPP_

#include "Object.hpp"
#include "system.Allocator.hpp"

namespace local
{
    namespace system
    {
        class Object : public ::local::Object<Allocator>
        {
            typedef ::local::Object<Allocator> Parent;
        
        public:
        
            /** 
             * Constructor.
             */  
            Object();
    
            /** 
             * Destructor.
             */    
            virtual ~Object();       
        
        };
    }
}
#endif // SYSTEM_OBJECT_HPP_
