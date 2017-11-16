/** 
 * Heap memory.
 *
 * Hardware address for system heap memory has to be aligned to eight.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2016, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef LIBRARY_HEAP_HPP_
#define LIBRARY_HEAP_HPP_

#include "api.Heap.hpp"
#include "api.Toggle.hpp"

namespace library
{
    class Heap : public ::api::Heap
    {
      
    public:
    
        /** 
         * Constructor.
         *     
         * @param size total heap size.
         */    
        Heap(int64 size) :
            data_ (size),
            temp_ (){
            setConstruct( construct() );
        }    
      
        /** 
         * Constructor.
         *
         * Reference to global interrupt interface pointer is used for
         * a possibility to change a value of that pointer.
         * Until that pointer is NULL golobal interrupt is not used.
         * This gives you a possibility to change using golobal interrupts
         * on fly.   
         *     
         * @param size   total heap size.
         * @param toggle reference to pointer to global interrupts toggle interface.
         */    
        Heap(int64 size, ::api::Toggle*& toggle) :
            data_  (size, toggle),
            temp_ (){
            setConstruct( construct() );
        }    
        
        /** 
         * Destructor.
         */
        virtual ~Heap()
        {
            data_.key = 0;
        }
      
        /**
         * Allocates memory.
         *
         * @param size required memory size in byte.
         * @param ptr  NULL value becomes to allocate memory, and 
         *             other given values are simply returned 
         *             as memory address.
         * @return pointer to allocated memory or NULL.
         */    
        virtual void* allocate(size_t size, void* ptr)
        {
            if(!isConstructed()) return NULL;
            if(ptr != NULL) return ptr;
            bool is = disable();
            ptr = firstBlock()->alloc(size);
            enable(is);
            return ptr;
        }
          
        /**
         * Frees an allocated memory.
         *
         * @param ptr pointer to allocated memory.
         */      
        virtual void free(void* ptr)
        {
            if(ptr == NULL) return;
            if(!isConstructed()) return;  
            bool is = disable();
            heapBlock(ptr)->free();
            enable(is);
        }
        
        /**
         * Frees an allocated memory.
         *
         * @param toggle reference to pointer to global interrupts toggle interface.
         */      
        virtual void setToggle(::api::Toggle*& toggle)
        {
            data_.toggle = &toggle;
        }    
      
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        virtual bool isConstructed() const
        {
            return data_.key == HEAP_KEY ? true : false;
        }
        
        /**
         * Operator new.
         *
         * Method initiates a building of heap memory
         * checks and tests self memory structure data
         * and leads to call the class constructor.
         *
         * @param size unused.
         * @param ptr  aligned to eight memory address.
         * @return address of memory or NULL.
         */
        void* operator new(size_t, void* ptr)
        {
            return create(ptr);
        }
      
        /**
         * Operator delete.
         *
         * @param ptr   address of allocated memory block or a null pointer.
         * @param place pointer used as the placement parameter in the matching placement new.
         */
        void operator delete(void*, void*)
        {
        }
  
    private:
    
        class HeapBlock;
      
        /**
         * Sets the object constructed flag.
         *
         * @param flag constructed flag.
         */      
        void setConstruct(bool flag)
        {
            if(data_.key == HEAP_KEY) data_.key = flag ? HEAP_KEY : 0;
        }
        
        /** 
         * Constructor.
         *
         * @return true if object has been constructed successfully.
         */
        bool construct()
        {
            // Crop a size to multiple of eight
            if(sizeof(HeapBlock) + 16 > data_.size) return false;
            // Test Heap and HeapBlock structures sizes witch has to be multipled to eight
            if(sizeof(Heap) & 0x7) return false;
            if(sizeof(HeapBlock) & 0x7) return false;
            // Test memory
            uint32 addr = reinterpret_cast<uint32>(this) + sizeof(Heap);
            void*  ptr  = reinterpret_cast<void*>(addr);
            if( !isMemoryAvailable(ptr, data_.size) ) return false;
            // Alloc first heap block
            data_.block = new ( firstBlock() ) HeapBlock(this, data_.size);
            return data_.block != NULL ? true : false;
        }
        
        /** 
         * Disables a controller.
         *
         * @return an enable source bit value of a controller before method was called.
         */ 
        bool disable()
        {
            if(data_.toggle == NULL) return false;
            register ::api::Toggle* toggle = *data_.toggle;
            return toggle != NULL ? toggle->disable() : false;      
        }
      
        /** 
         * Enables a controller.
         *
         * @param status returned status by disable method.
         */    
        void enable(bool status)
        {
            if(data_.toggle == NULL) return;
            register ::api::Toggle* toggle = *data_.toggle;
            if(toggle != NULL) toggle->enable(status);
        }
        
        /**
         * Returns a first heap block address.
         *
         * @return pointer to heap block.
         */
        HeapBlock* firstBlock()
        {
            uint32 addr = reinterpret_cast<uint32>(this) + sizeof(Heap);
            return reinterpret_cast<HeapBlock*>(addr);
        }
        
        /**
         * Returns a heap block by user data address.
         *
         * @return pointer to heap block.
         */
        HeapBlock* heapBlock(void* data)
        {
            uint32 addr = reinterpret_cast<uint32>(data) - sizeof(HeapBlock);
            return reinterpret_cast<HeapBlock*>(addr);
        }
        
        /**
         * Tests memory.
         *
         * TODO: normal type casts should be done.
         *
         * @param addr memory address pointer.
         * @param size size in byte.
         * @return true if test complete.
         */
        static bool isMemoryAvailable(void* addr, int64 size)
        {
            cell mask = -1;
            cell* ptr = reinterpret_cast<cell*>(addr);
            // Value test
            for( int64 i=0; i<size; i++) 
                ptr[i] = static_cast<cell>(i & mask);
            for( int64 i=0; i<size; i++) 
                if(ptr[i] != static_cast<cell>(i & mask))
                    return false;
            // 0x55 test
            for( int64 i=0; i<size; i++) 
                ptr[i] = static_cast<cell>(0x55555555 & mask);
            for( int64 i=0; i<size; i++) 
                if(ptr[i] != static_cast<cell>(0x55555555 & mask))
                    return false;
            // 0xAA test          
            for( int64 i=0; i<size; i++) 
              ptr[i] = static_cast<cell>(0xaaaaaaaa & mask);
            for( int64 i=0; i<size; i++) 
                if(ptr[i] != static_cast<cell>(0xaaaaaaaa & mask))
                    return false;          
            // Zero test          
            for( int64 i=0; i<size; i++) 
                ptr[i] = 0x00;
            for( int64 i=0; i<size; i++) 
                if(ptr[i] != 0x00)
                    return false;                  
            return true;
        }
      
        /**
         * Allocates memory for heap.
         *
         * Method initiates a building of heap memory
         * checks and tests self memory structure data
         * and leads to call the class constructor.
         *
         * @param ptr  aligned to eight memory address.
         * @return address of memory or NULL.
         */
        static void* create(void* ptr)
        {
            // Size of this class has to be multipled to eight
            if(sizeof(Heap) & 0x7) ptr = NULL;
            // Testing memory for self structure data
            if(!isMemoryAvailable(ptr, sizeof(Heap))) ptr = NULL;
            // Memory address has to be aligned to eight
            if(reinterpret_cast<uint32>(ptr) & 0x7) ptr = NULL;
            return ptr;
        }
        
        /** 
         * Copy constructor.
         *
         * @param obj reference to source object.
         */ 
        Heap(const Heap& obj);
        
        /**
         * Assignment operator.
         *
         * @param src reference to source object.
         * @return reference to this object.     
         */    
        Heap& operator =(const Heap&);
        
        /**
         * Operator new.
         *
         * Method is defined for blocking operator new.
         *
         * @param size number of bytes to allocate.
         * @return always null pointer.
         */
        void* operator new(size_t)
        {
            return NULL;
        }
        
        /**
         * Operator delete.
         *
         * Method does nothing and is defined for blocking operator delete.
         *
         * @param ptr address of allocated memory.
         */  
        void operator delete(void*)
        {
        }
        
        /** 
         * Operator new.
         *
         * @param size number of bytes to allocate.
         * @return allocated memory address or a null pointer.
         */  
        void* operator new[](size_t size);
        
        /** 
         * Operator delete.
         *
         * @param ptr address of allocated memory block or a null pointer.
         */  
        void operator delete[](void* ptr);
      
        /** 
         * Operator new.
         *
         * @param size number of bytes to allocate.
         * @param ptr  pointer to a memory area to initialize the object
         * @return allocated memory address or a null pointer.
         */  
        void* operator new[](size_t size, void* ptr);
        
        /** 
         * Operator delete.
         *
         * @param ptr   address of allocated memory block or a null pointer.
         * @param place pointer used as the placement parameter in the matching placement new.
         */  
        void operator delete[](void* ptr, void* place);
        
        /**
         * Heap class aligner aligns that to eight.
         *
         * Note: if given SIZEOF is already multiple 8, 
         * the class size will be 8 bytes.
         *
         * @param SIZEOF size of Heap class.
         */  
        template <int32 SIZEOF>
        struct Aligner
        {
        
        public:
          
            /** 
             * Constructor.
             */
            Aligner()
            {
                #ifdef EOOS_DEBUG
                for(int32 i=0; i<SIZE; i++) val_[i] = 0x0A;
                #endif
            }
            
            /** 
             * Destructor.
             */
           ~Aligner(){}       
        
        private:
          
            /**
             * Aligning data size.
             */
            static const int32 SIZE = (SIZEOF & ~0x7) + 0x8 - SIZEOF;
            
            /**
             * Temp array.
             */      
            cell val_[SIZE];
      
        };
        
        /**
         * Contains a Virtual Function Table only.
         *
         * Probably, decision for using this empty class 
         * is not delicate, but it is working for understanding 
         * about size of Heap class Virtual Function Table.
         *
         * Note: int64 was used because some compilers can put 64 bit variable 
         * to aligned 8 memory address. Therefore, size of classes 
         * with 32 bit pointer to virtual table and one 64 bit variable is 16 bytes.
         */    
        class VirtualTable : public ::api::Heap{int64 temp;};    
        
        /** 
         * Heap memory block.
         *
         * The class data has to be aligned to 8.
         */    
        class HeapBlock    
        {
      
        public:
      
            /** 
             * Constructor.
             *
             * @param heap pointer to heap class.
             * @param size size of byte given to this new block.
             */    
            HeapBlock(::api::Heap* heap, int64 size) :
                heap_  (heap),
                prev_  (NULL),
                next_  (NULL),
                attr_  (0),
                size_  (size - sizeof(HeapBlock)),
                key_   (BLOCK_KEY),
                temp_  (0xbbbbbbbb){
            }
            
            /** 
             * Destructor.
             */
           ~HeapBlock()
            {
            }
            
            /**
             * Operator new.
             *
             * @param size unused.
             * @param ptr  address of memory.
             * @return address of memory.
             */   
            void* operator new(size_t, void* ptr)
            {
                // Size of this class has to be multipled to eight
                if(sizeof(HeapBlock) & 0x7) return NULL;
                return ptr;
            }
            
            /**
             * Allocates a memory block.
             *
             * @param size size in byte.
             * @return pointer to an allocated memory.
             */  
            void* alloc(size_t size)
            {
                if(size == 0) return NULL;    
                // Align a size to 8 byte boudary
                if(size & 0x7) size = (size & ~0x7) + 0x8;
                HeapBlock* curr = this;
                while(curr)
                {
                    if(curr->isUsed())
                    {
                        curr = curr->next_;
                        continue;
                    }
                    if(curr->size_ < size)
                    {
                        curr = curr->next_;
                        continue;
                    }
                    break;
                }
                if(curr == NULL) return NULL;
                // has a need size of memory and new heap block
                if(curr->size_ >= size + sizeof(HeapBlock))
                {
                    HeapBlock* next = new ( curr->next(size) ) HeapBlock(heap_, curr->size_ - size);
                    next->next_ = curr->next_;
                    next->prev_ = curr;
                    if(next->next_) next->next_->prev_ = next;        
                    curr->next_ = next;        
                    curr->size_ = size;
                }
                curr->attr_|= ATTR_USED;
                return curr->data();
            }
            
            /**
             * Frees allocated memory by this block.
             *
             * @return true if this block is freed.
             */  
            bool free()
            {
                if(canDelete() == false) return false;
                int32 sibling = 0;
                if(prev_ != NULL && !prev_->isUsed()) sibling |= PREV_FREE;
                if(next_ != NULL && !next_->isUsed()) sibling |= NEXT_FREE;    
                switch(sibling)
                {
                    case PREV_FREE | NEXT_FREE:
                        prev_->size_ += 2 * sizeof(HeapBlock) + size_ + next_->size_;
                        prev_->next_ = next_->next_;
                        if(prev_->next_ != NULL) prev_->next_->prev_ = prev_;
                        break;
                        
                    case PREV_FREE:
                        prev_->size_ += sizeof(HeapBlock) + size_;
                        prev_->next_ = next_;
                        if(next_ != NULL) next_->prev_ = prev_;
                        break;
                        
                    case NEXT_FREE:
                        size_ += sizeof(HeapBlock) + next_->size_;
                        next_ = next_->next_;
                        if(next_ != NULL) next_->prev_ = this;
                        attr_ &= ~ATTR_USED;
                        break;
                    default:
                        attr_ &= ~ATTR_USED;
                }
                return true;
            }
      
        private:
      
            /**
             * Tests if this memory block is available for deleting.
             *
             * @return true if it may be deleted.
             */  
            bool canDelete()
            {
                if(!isMemory()) return false;
                if(!heap_->isConstructed()) return false;
                return true;
            }
            
            /**
             * Tests if this memory block is available.
             *
             * @return true if memory block is available.
             */  
            bool isMemory()
            {
                return key_ == BLOCK_KEY ? true : false;
            }
            
            /**
             * Tests if this memory block is available.
             *
             * @return true if memory block is available.
             */  
            bool isUsed()
            {
                return (attr_ & ATTR_USED) != 0 ? true : false;
            }
            
            /**
             * Returns an address to data of this block.
             *
             * @return pointer to memory.
             */
            void* data()
            {
                uint32 addr = reinterpret_cast<uint32>(this) + sizeof(HeapBlock);
                return reinterpret_cast<void*>(addr);
            }
            
            /**
             * Returns an address to next block.
             *
             * @return pointer to memory.
             */
            void* next(size_t size)
            {
                uint32 addr = reinterpret_cast<uint32>(this) + sizeof(HeapBlock) + size;
                return reinterpret_cast<void*>(addr);
            }
            
            /**
             * Copy constructor.
             *
             * @param obj reference to source object.
             */
            HeapBlock(const HeapBlock& obj);
            
            /**
             * Assignment operator.
             *
             * @param src reference to source object.
             * @return reference to this object.       
             */
            HeapBlock& operator =(const HeapBlock&);
            
            /**
             * Heap block definition key.
             */
            static const int32 BLOCK_KEY = 0x19820401;
            
            /**
             * Block is used.
             */
            static const int32 ATTR_USED = 0x00000001;
            
            /**
             * Next block is free.
             */    
            static const int32 NEXT_FREE = 0x00000001;
            
            /**
             * Previous block is free.
             */    
            static const int32 PREV_FREE = 0x00000002;
            
            /**
             * Heap page of this block.
             */    
            ::api::Heap* heap_;
            
            /**
             * Next block.
             */
            HeapBlock* prev_;
            
            /**
             * Previous block.
             */    
            HeapBlock* next_;
            
            /**
             * Attributes of this block.
             */    
            int32 attr_;
            
            /**
             * Size in byte of this block.
             */    
            int64 size_;
            
            /**
             * Heap block definition key.
             */    
            int32 key_;
            
            /**
             * Temp aligning value.
             */    
            int32 temp_;
      
        };
        
        /**
         * Heap data.
         *
         * This structure is needed for aligning heap data or otherwise 
         * this Heap class can not de aligned because it is incompleted.
         */
        struct HeapData
        {
            /** 
             * Constructor.
             *
             * @param ikey  heap key constant.       
             * @param isize total heap size.
             */
            HeapData(int64 isize) :
                block  (NULL),
                toggle (NULL),
                size   ((isize & ~0x7) - sizeof(Heap)),
                key    (HEAP_KEY){
            }
          
            /** 
             * Constructor.
             *
             * @param ikey    heap key constant.       
             * @param i1size  total heap size.
             * @param itoggle reference to pointer to global interrupts interface.       
             */
            HeapData(int64 isize, ::api::Toggle*& itoggle) :
                block  (NULL),
                toggle (&itoggle),
                size   ((isize & ~0x7) - sizeof(Heap)),
                key    (HEAP_KEY){
            }
            
            /** 
             * Destructor.
             */
           ~HeapData(){}       
              
            /**
             * First memory block of heap page memory.
             */
            HeapBlock* block;
          
            /**
             * Threads switching off key.
             *
             * This interface controls a global thread switch off key
             * by toggle interface. That interface has to disable
             * a changing thread context. The most useful case is to give
             * a global interrupts toggle interface.
             */
            ::api::Toggle** toggle;       
          
            /**
             * Actual size of heap.
             */
            int64 size;
          
            /**
             * Heap page memory definition key.
             */
            int32 key;
          
        private:
      
            /**
             * Copy constructor.
             *
             * @param obj reference to source object.
             */
            HeapData(const HeapData& obj);
          
            /**
             * Assignment operator.
             *
             * @param obj reference to source object.
             * @return reference to this object.       
             */
            HeapData& operator =(const HeapData& obj);
      
        };    
        
        /**
         * Size of this Heap class without aligned data.
         */    
        static const int32 SIZEOF_HEAP = sizeof(HeapData) + sizeof(VirtualTable) - sizeof(int64);        
        
        /**
         * Heap page memory definition key.
         */
        static const int32 HEAP_KEY = 0x19811019;
        
        /**
         * Data of this heap.
         */    
        HeapData data_;    
        
        /**
         * Aligning data.
         */        
        Aligner<SIZEOF_HEAP> temp_;  

    };
}
#endif // LIBRARY_HEAP_HPP_
