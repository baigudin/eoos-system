/** 
 * Root class of the operating system class hierarchy.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2018, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.Object.hpp"

namespace local
{
    namespace system
    {
        /** 
         * Constructor.
         */  
        Object::Object() : Parent()
        {
        }
        
        /** 
         * Destructor.
         */    
        Object::~Object()
        {
        }      
    
    }
}
