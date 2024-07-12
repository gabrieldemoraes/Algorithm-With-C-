//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#ifndef SMART_PTR_HPP
#define SMART_PTR_HPP

#include <type_traits>

namespace smart_ptr
{
    template <typename T, typename = std::enable_if_t<std::is_pointer<T>::value>>
    using owner = T;
    
    namespace internal
    {
        template <typename T>
        struct scoped_ptr_default_deleter final
        {
            static inline void dealloc(T* ptr)
            {
                delete ptr;
            }
        };
    }

    template <typename T, typename Deleter = internal::scoped_ptr_default_deleter<T>>
    class scoped_ptr final
    {
    public:
        using value_type = T;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = T*;
        using const_pointer = const T*;
        using storage_type = pointer; //raw pointer
        using pointer_type = pointer; //type returned by operator->, can be different from the storage type (ex.: proxy)
        using reference_type = reference; //type returned by operator*
        
        explicit scoped_ptr(storage_type ptr = nullptr) noexcept : ptr(ptr) {}       
        scoped_ptr(const scoped_ptr&) = delete;
        scoped_ptr& operator=(const scoped_ptr&) = delete;        
        ~scoped_ptr() noexcept { if (ptr) Deleter::dealloc(ptr); }

        reference_type operator*() const noexcept
        {
            return *ptr;
        }

        pointer_type operator->() const noexcept
        {
            return ptr;
        }

        storage_type get() const noexcept
        {
            return ptr;
        }

        void reset(storage_type ptr = nullptr) noexcept
        {
            //assert (ptr == nullptr || ptr != this->ptr)
            scoped_ptr(ptr).swap(*this);
        }

        void swap(scoped_ptr& that) noexcept
        {
            storage_type temp = that.ptr;
            that.ptr = ptr;
            ptr = temp;
        }

        explicit operator bool() const noexcept
        {
            return ptr != nullptr;
        }
   
    private:
        storage_type ptr;
    };
}

#endif /* SMART_PTR_HPP */