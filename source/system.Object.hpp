/** 
 * Root class of the operating system class hierarchy.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_OBJECT_HPP_
#define SYSTEM_OBJECT_HPP_

#include "Object.hpp"
#include "system.Allocator.hpp"

namespace system
{
    class Object : public ::Object<Allocator>
    {
        typedef ::Object<Allocator> Parent;        
      
    public:
    
        /** 
         * Constructor.
         */  
        Object() : Parent(),
            isConstructed_ (getConstruct()){
        }
        
        /** 
         * Copy constructor.
         *
         * @param obj reference to source object.
         */ 
        Object(const Object& obj) : Parent(obj),
            isConstructed_ (getConstruct()){
        }
        
        /** 
         * Copy constructor.
         *
         * @param obj reference to source object.
         */ 
        Object(const ::api::Object& obj) : Parent(obj),
            isConstructed_ (getConstruct()){
        }    
        
        /** 
         * Destructor.
         */    
        virtual ~Object()
        {
        } 

        /** 
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.   
         */  
        Object& operator =(const Object& obj)
        {
            Parent::operator=(obj);
            return *this;
        }        
   
    protected:
        
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;
    
    };
}
#endif // MODULE_OBJECT_HPP_
