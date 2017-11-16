/** 
 * Buffer class in static and dynamic specializations.
 *
 * This class has two specializations of the template. 
 * The first one specializes a class with a buffer of elements
 * that is declared as the part of self class data structure.
 * The second one allocates necessary size of a buffer in 
 * dynamic memory.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2016, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef LIBRARY_BUFFER_HPP_
#define LIBRARY_BUFFER_HPP_

#include "library.AbstractBuffer.hpp"

namespace library
{ 
    /** 
     * Static buffer class.
     *
     * @param Type  data type of buffer element.     
     * @param COUNT count of buffer elements. 
     * @param Alloc heap memory allocator class.
     */ 
    template <typename Type, int32 COUNT=0, class Alloc=::Allocator>
    class Buffer : public ::library::AbstractBuffer<Type,Alloc>
    {
        typedef ::library::AbstractBuffer<Type,Alloc> Parent;
  
    public:      
  
        /** 
         * Constructor.
         */    
        Buffer() : Parent(COUNT),
            buf_ (arr_){
        }
    
        /** 
         * Constructor.
         *
         * @param illegal illegal value.
         */    
        Buffer(const Type illegal) : Parent(COUNT, illegal),
            buf_ (arr_){
        }
    
        /**
         * Destructor.
         */
        virtual ~Buffer()
        {
        }
    
        /**
         * Assignment operator.
         *
         * If the source buffer is greater than this buffer,
         * only cropped data of that will be copied.
         *
         * @param buf reference to source buffer.
         * @return reference to this object.     
         */
        Buffer& operator =(const Buffer<Type,COUNT,Alloc>& buf)
        {
            this->copy(buf);
            return *this;      
        }
    
        /**
         * Assignment operator.
         *
         * If the source buffer is greater than this buffer,
         * only cropped data of that will be copied.
         *
         * @param buf reference to source buffer.
         * @return reference to this object.     
         */
        Buffer& operator =(const AbstractBuffer<Type,Alloc>& buf)
        {
            this->copy(buf);
            return *this;
        }
  
    protected: 
  
        /**
         * Returns a pointer to the fist buffer element.
         *
         * @return pointer to buffer, or NULL.
         */
        virtual Type* getBuffer() const
        {
            if(!this->isConstructed()) return NULL;
            return buf_;
        }
  
    private: 
  
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        Buffer(const Buffer& obj);
      
        /**
         * Current array of Type elements.
         */  
        Type arr_[COUNT];
        
        /**
         * Pointer to current array.
         */    
        Type* buf_;
      
    };
  
    /** 
     * Dynamic buffer class.
     *
     * @param Type  data type of buffer element.     
     * @param Alloc heap memory allocator class.
     */
    template <typename Type, class Alloc>
    class Buffer<Type,0,Alloc> : public AbstractBuffer<Type,Alloc>
    {
        typedef ::library::AbstractBuffer<Type,Alloc> Parent;
  
    public:      
  
        /** 
         * Constructor.
         *
         * @param count count of buffer elements.
         */    
        Buffer(int32 count) : Parent(count),
            buf_      (NULL),
            isDelete_ (true){
            this->setConstruct( construct(count) );
        }
      
        /** 
         * Constructor.
         *
         * NOTE: Given external buffer has to exist until this object is being lived,
         * and will NOT be deleted when the buffer is being deleted.
         *
         * @param count number of elements.
         * @param buf   pointer to external buffer.
         */    
        Buffer(int32 count, Type* buf) : Parent (count),
            buf_      (buf),
            isDelete_ (false){
            this->setConstruct( construct(count) );
        }
      
        /** 
         * Constructor.
         *
         * @param count   count of buffer elements.
         * @param illegal illegal value.
         */    
        Buffer(int32 count, const Type illegal) : Parent(count, illegal),
            buf_      (NULL),
            isDelete_ (true){
            this->setConstruct( construct(count) );
        }
      
        /** 
         * Constructor.
         *
         * NOTE: Given external buffer has to exist until this object is being lived,
         * and will NOT be deleted when the buffer is being deleted.     
         *
         * @param count   number of elements.
         * @param illegal illegal value.
         * @param buf     pointer to external buffer.
         */    
        Buffer(int32 count, const Type illegal, Type* buf) : Parent(count, illegal),
            buf_      (buf),
            isDelete_ (false){
            this->setConstruct( construct(count) );
        }
      
      
        /**
         * Destructor.
         */
        virtual ~Buffer()
        {
            if(isDelete_) this->free(buf_);
        }
      
        /**
         * Assignment operator.
         *
         * If the source buffer is greater than this buffer,
         * only cropped data of that will be copied.
         *
         * @param buf reference to source buffer.
         * @return reference to this object.     
         */
        Buffer& operator =(const Buffer<Type,0,Alloc>& buf)
        {
            this->copy(buf);
            return *this;      
        }
      
        /**
         * Assignment operator.
         *
         * If the source buffer is greater than this buffer,
         * only cropped data of that will be copied.
         *
         * @param buf reference to source buffer.
         * @return reference to this object.     
         */
        Buffer& operator =(const AbstractBuffer<Type,Alloc>& buf)
        {
            this->copy(buf);
            return *this;
        }
  
    protected: 
  
        /**
         * Returns a pointer to the fist buffer element.
         *
         * @return pointer to buffer, or NULL.
         */
        virtual Type* getBuffer() const
        {
            if(!this->isConstructed()) return NULL;
            return buf_;
        }
  
    private: 
  
        /** 
         * Constructor.
         *
         * @param count count of buffer elements.
         * @return boolean result.
         */
        bool construct(int32 count)
        {
            if(!this->isConstructed()) return false;
            // If you have a WTF question looking at the next construction, then look
            // at description of 'allocate' template method of 'Object' template class.
            if(buf_ == NULL) buf_ = this->template allocate<Type*>(count * sizeof(Type));
            return buf_ == NULL ? false : true;
        }
      
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        Buffer(const Buffer& obj);
      
        /**
         * Pointer to external given or self created array.
         */     
        Type* buf_;
        
        /**
         * Deletet flag.
         *
         * Is set to true for self created array or 
         * set to false for external given array.
         */        
        bool isDelete_;
      
    };
}
#endif // LIBRARY_BUFFER_HPP_
