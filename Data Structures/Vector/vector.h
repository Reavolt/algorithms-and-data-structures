#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <memory>
#include <cstddef>
#include <new>
#include <iostream>
#include <type_traits>
#include <iterator>
#include <limits>

//----------------------------------------------------------------------------------------------------
template <typename Type>
class Allocator
{
public:
    using value_type = typename std::conditional_t<std::is_const_v<Type>, const Type, Type>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type;
    using is_always_equal = std::true_type;
public:
    //Member functions
    constexpr Allocator() noexcept = default;
    constexpr Allocator(const Allocator& other) noexcept = default;
    template<typename Allocator_Type>
    constexpr explicit Allocator(const Allocator<Allocator_Type>& other) noexcept;
    constexpr ~Allocator() = default;

    constexpr value_type* allocate(size_type count);
    constexpr void deallocate(value_type* value_type_ptr, size_type count);

    //Non-member functions
    template<typename lhs_type, typename rhs_type>
    friend constexpr bool operator==(const Allocator<lhs_type>& lhs, const Allocator<rhs_type>& rhs ) noexcept;
    template<typename lhs_type, typename rhs_type>
    friend constexpr bool operator!=(const Allocator<lhs_type>& lhs, const Allocator<rhs_type>& rhs ) noexcept;
};
//----------------------------------------------------------------------------------------------------
template <typename Type>
template <typename Allocator_Type>
constexpr Allocator<Type>::Allocator(const Allocator<Allocator_Type>& other) noexcept
{

}
//----------------------------------------------------------------------------------------------------
template <typename Type>
constexpr typename Allocator<Type>::value_type* Allocator<Type>::allocate(size_type count)
{
    return reinterpret_cast<value_type*>(::operator new(count * sizeof(value_type)));
}
//----------------------------------------------------------------------------------------------------
template <typename Type>
constexpr void Allocator<Type>::deallocate(value_type* value_type_ptr, size_type count)
{
    ::operator delete(value_type_ptr);
}
//----------------------------------------------------------------------------------------------------
template<typename lhs_type, typename rhs_type>
constexpr bool operator==(const Allocator<lhs_type>& lhs, const Allocator<rhs_type>& rhs ) noexcept
{
    return lhs == rhs;
}
//----------------------------------------------------------------------------------------------------
template<typename lhs_type, typename rhs_type>
constexpr bool operator!=(const Allocator<lhs_type>& lhs, const Allocator<rhs_type>& rhs) noexcept
{
    return lhs != rhs;
}
//----------------------------------------------------------------------------------------------------
template <typename Type>
class Iterator
{
public:
    using iterator_type = Type;
    using value_type        = typename std::iterator_traits<iterator_type>::value_type;
    using difference_type   = typename std::iterator_traits<iterator_type>::difference_type;
    using pointer           = typename std::iterator_traits<iterator_type>::pointer;
    using reference         = typename std::iterator_traits<iterator_type>::reference;
    using iterator_category = typename std::iterator_traits<iterator_type>::iterator_category;
    using iterator_concept  = std::contiguous_iterator_tag;
public:
    constexpr Iterator();
    template <typename Itr, typename = std::enable_if_t<std::is_convertible<Itr, iterator_type>::value>*>
    constexpr Iterator(const Iterator<Itr>& itr);
    constexpr Iterator(const Iterator& itr);
    constexpr explicit Iterator(pointer ptr);
    constexpr ~Iterator();

    constexpr reference operator*() const;
    constexpr pointer operator->();

    constexpr Iterator& operator++();
    constexpr Iterator operator++(int);
    constexpr Iterator& operator--();
    constexpr Iterator operator--(int);
    constexpr Iterator& operator=(const Iterator& itr);

    constexpr Iterator operator+(difference_type value);
    constexpr Iterator operator-(difference_type value);

    template <typename type_swap>
    friend void swap(const Iterator<type_swap>& lhs, const Iterator<type_swap>& rhs);
    template <typename type_operator>
    friend bool operator==(const Iterator<type_operator>& lhs, const Iterator<type_operator>& rhs);
    template <typename type_operator>
    friend bool operator!=(const Iterator<type_operator>& lhs, const Iterator<type_operator>& rhs);

    iterator_type data() const {return value_ptr;}
private:
    iterator_type value_ptr;
};
//----------------------------------------------------------------------------------------------------
template <typename Type>
constexpr Iterator<Type>::Iterator() : value_ptr(nullptr)
{

}
//----------------------------------------------------------------------------------------------------
template <typename Type>
template <typename Itr, typename>
constexpr Iterator<Type>::Iterator(const Iterator<Itr>& itr) : value_ptr(itr.data())
{

}
//----------------------------------------------------------------------------------------------------
template <typename Type>
constexpr Iterator<Type>::Iterator(const Iterator& itr) : value_ptr(itr.value_ptr)
{

}
//----------------------------------------------------------------------------------------------------
template <typename Type>
constexpr Iterator<Type>::Iterator(pointer ptr) : value_ptr(ptr)
{

}
//----------------------------------------------------------------------------------------------------
template <typename Type>
constexpr Iterator<Type>::~Iterator()
{

}
//----------------------------------------------------------------------------------------------------
template <typename Type>
constexpr typename Iterator<Type>::reference Iterator<Type>::operator*() const
{
    return *value_ptr;
}
//----------------------------------------------------------------------------------------------------
template <typename Type>
constexpr typename Iterator<Type>::pointer Iterator<Type>::operator->()
{
    return value_ptr;
}
//----------------------------------------------------------------------------------------------------
template <typename Type>
constexpr Iterator<Type>& Iterator<Type>::operator++()
{
    value_ptr++;
    return *this;
}
//----------------------------------------------------------------------------------------------------
template <typename Type>
constexpr Iterator<Type> Iterator<Type>::operator++(int)
{
    Iterator temp = *this;
    ++*this;
    return temp;
}
//----------------------------------------------------------------------------------------------------
template <typename Type>
constexpr Iterator<Type>& Iterator<Type>::operator--()
{
    value_ptr--;
    return *this;
}
//----------------------------------------------------------------------------------------------------
template <typename Type>
constexpr Iterator<Type> Iterator<Type>::operator--(int)
{
    Iterator temp = *this;
    --*this;
    return temp;
}
//----------------------------------------------------------------------------------------------------
template <typename Type>
constexpr Iterator<Type>& Iterator<Type>::operator=(const Iterator& itr)
{
    if (this != &itr)
    {
        value_ptr = itr.value_ptr;
    }
    return *this;
}
//----------------------------------------------------------------------------------------------------
template <typename Type>
constexpr Iterator<Type> Iterator<Type>::operator+(difference_type value)
{
   return Iterator(value_ptr + value);
}
//----------------------------------------------------------------------------------------------------
template <typename Type>
constexpr Iterator<Type> Iterator<Type>::operator-(difference_type value)
{
   return Iterator(value_ptr - value);
}
//----------------------------------------------------------------------------------------------------
template <typename type_swap>
void swap(const Iterator<type_swap>& lhs, const Iterator<type_swap>& rhs)
{
    std::swap(lhs.value_ptr, rhs.value_ptr);
}
//----------------------------------------------------------------------------------------------------
template <typename type_operator>
bool operator==(const Iterator<type_operator>& lhs, const Iterator<type_operator>& rhs)
{
    return lhs.value_ptr == rhs.value_ptr;
}
//----------------------------------------------------------------------------------------------------
template <typename type_operator>
bool operator!=(const Iterator<type_operator>& lhs, const Iterator<type_operator>& rhs)
{
    return lhs.value_ptr != rhs.value_ptr;
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator = Allocator<Type>>
class Vector
{
    static_assert(std::is_same_v<typename std::remove_cv_t<Type>, Type>,
                  "Vector must have a non-const, non-volatile value_type");
public:
    using value_type             = Type;
    using allocator_type         = allocator;
    using pointer                = typename std::allocator_traits<allocator>::pointer;
    using const_pointer          = typename std::allocator_traits<allocator>::const_pointer;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;
    using iterator               = Iterator<pointer>;
    using const_iterator         = Iterator<const_pointer>;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
public:

    //Member functions
    constexpr Vector() noexcept(noexcept(allocator_type()));
    constexpr explicit Vector(const allocator_type& alloc) noexcept;
    constexpr explicit Vector(size_type count, const allocator_type& alloc = allocator_type());
    constexpr Vector(size_type count, const_reference value, const allocator_type& alloc = allocator_type());
    template<typename InputIt,
             typename = std::enable_if_t<std::is_base_of_v<std::input_iterator_tag,
             typename std::iterator_traits<InputIt>::iterator_category>>>
    constexpr Vector(InputIt first, InputIt last, const allocator_type& alloc = allocator_type());
    constexpr Vector(const Vector& value);
    constexpr Vector(Vector&& value) noexcept(std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value ||
                                              std::allocator_traits<allocator_type>::is_always_equal::value);
    constexpr Vector(const Vector& value, const allocator_type& alloc);
    constexpr Vector(Vector&& value, const allocator_type& alloc);
    constexpr Vector(std::initializer_list<value_type> init_list, const allocator_type& alloc = allocator_type());
    constexpr ~Vector();

    constexpr Vector& operator=(const Vector& value);
    constexpr Vector& operator=(Vector&& value) noexcept;
    constexpr Vector& operator=(std::initializer_list<value_type> init_list);

    template<typename InputIt,
             typename = std::enable_if_t<std::is_base_of_v<std::input_iterator_tag,
             typename std::iterator_traits<InputIt>::iterator_category>>>
    constexpr void           assign(InputIt first, InputIt last);
    constexpr void           assign(size_type count, const_reference value);
    constexpr void           assign(std::initializer_list<value_type> init_list);
    constexpr allocator_type get_allocator() const noexcept;

    //Iterators
    constexpr iterator               begin() noexcept;
    constexpr const_iterator         begin() const noexcept;
    constexpr iterator               end() noexcept;
    constexpr const_iterator         end() const noexcept;
    constexpr reverse_iterator       rbegin() noexcept;
    constexpr const_reverse_iterator rbegin() const noexcept;
    constexpr reverse_iterator       rend() noexcept;
    constexpr const_reverse_iterator rend() const noexcept;

    constexpr const_iterator         cbegin() const noexcept;
    constexpr const_iterator         cend() const noexcept;
    constexpr const_reverse_iterator crbegin() const noexcept;
    constexpr const_reverse_iterator crend() const noexcept;

    //Capacity
    constexpr bool      empty() const noexcept;
    constexpr size_type size() const noexcept;
    constexpr size_type max_size() const noexcept;
    constexpr size_type capacity() const noexcept;
    constexpr void      resize(size_type size);
    constexpr void      resize(size_type size, const_reference value);
    constexpr void      reserve(size_type capacity);
    constexpr void      shrink_to_fit();

    //Element access
    constexpr reference       operator[](size_type position);
    constexpr const_reference operator[](size_type position) const;
    constexpr const_reference at(size_type position) const;
    constexpr reference       at(size_type position);
    constexpr reference       front();
    constexpr const_reference front() const;
    constexpr reference       back();
    constexpr const_reference back() const;

    //Data access
//    constexpr reference       data() noexcept;
//    constexpr const_reference data() const noexcept;

    //Modifiers
//    template<class... Args>
//    constexpr reference emplace_back(Args&&... args);
//    constexpr void push_back(const reference x);
//    constexpr void push_back(value_type&& x);
//    constexpr void pop_back();

//    template<class... Args>
//    constexpr iterator emplace(const_iterator position, Args&&... args);
//    constexpr iterator insert(const_iterator position, const_reference x);
//    constexpr iterator insert(const_iterator position, value_type&& x);
//    constexpr iterator insert(const_iterator position, size_type n, const_reference x);
//    template<class InputIterator>
//    constexpr iterator insert(const_iterator position, InputIterator first, InputIterator last);
//    constexpr iterator erase(const_iterator position);
//    constexpr iterator erase(const_iterator first, const_iterator last);

//    constexpr void swap(Vector& lhs);
    constexpr void clear() noexcept;

    //Non-member functions

private:
    allocator_type array_allocator;
    pointer array_ptr;
    size_type array_size{};
    size_type array_capacity{};
};
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr Vector<Type, allocator>::Vector() noexcept(noexcept(allocator_type())) : Vector(allocator_type())
{

}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr Vector<Type, allocator>::Vector(const allocator_type& alloc) noexcept :
        array_allocator(alloc),
        array_ptr(nullptr),
        array_size(0),
        array_capacity(0)
{

}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr Vector<Type, allocator>::Vector(size_type count, const allocator_type& alloc) :
        array_allocator(alloc),
        array_ptr(std::allocator_traits<allocator_type>::allocate(array_allocator, count)),
        array_size(count),
        array_capacity(count)
{
    for (size_type i = 0; i < array_size; ++i)
    {
        std::allocator_traits<allocator_type>::construct(array_allocator, std::next(array_ptr, i), value_type());
    }
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr Vector<Type, allocator>::Vector(size_type count, const_reference value, const allocator_type& alloc) :
        array_allocator(alloc),
        array_ptr(std::allocator_traits<allocator_type>::allocate(array_allocator, count)),
        array_size(count),
        array_capacity(count)
{
    for (size_type i = 0; i < array_size; ++i)
    {
        std::allocator_traits<allocator_type>::construct(array_allocator, std::next(array_ptr, i), value);
    }
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
template <typename InputIt, typename>
constexpr Vector<Type, allocator>::Vector(InputIt first, InputIt last, const allocator_type& alloc) :
        array_allocator(alloc),
        array_ptr(std::allocator_traits<allocator_type>::allocate(array_allocator, std::distance(first, last))),
        array_size(std::distance(first, last)),
        array_capacity(std::distance(first, last))
{
    for (size_type i = 0; i < array_size; ++i)
    {
        std::allocator_traits<allocator_type>::construct(array_allocator, std::next(array_ptr, i), *std::next(first, i));
    }
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr Vector<Type, allocator>::Vector(const Vector& value) :
        array_allocator(std::allocator_traits<allocator_type>::select_on_container_copy_construction(value.get_allocator())),
        array_ptr(std::allocator_traits<allocator_type>::allocate(array_allocator, value.array_capacity)),
        array_size(value.array_size),
        array_capacity(value.array_capacity)
{
    for (size_type i = 0; i < array_size; ++i)
    {
        std::allocator_traits<allocator_type>::construct(array_allocator, std::next(array_ptr, i), value.array_ptr[i]);
    }
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr Vector<Type, allocator>::Vector(Vector&& value) noexcept(
        std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value ||
        std::allocator_traits<allocator_type>::is_always_equal::value) :
        array_allocator(std::move(value.array_allocator)),
        array_ptr(std::move(value.array_ptr)),
        array_size(std::move(value.array_size)),
        array_capacity(std::move(value.array_capacity))
{
    value.array_ptr = nullptr;
    value.array_size = 0;
    value.array_capacity = 0;
    value.array_allocator = allocator();
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr Vector<Type, allocator>::Vector(const Vector& value, const allocator_type& alloc) :
        array_allocator(alloc),
        array_ptr(std::allocator_traits<allocator_type>::allocate(array_allocator, value.array_capacity)),
        array_size(value.array_size),
        array_capacity(value.array_capacity)
{
    for (size_type i = 0; i < array_size; ++i)
    {
        std::allocator_traits<allocator_type>::construct(array_allocator, std::next(array_ptr, i), value.array_ptr[i]);
    }
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr Vector<Type, allocator>::Vector(Vector&& value, const allocator_type& alloc) :
        array_allocator(alloc),
        array_ptr(std::move(value.array_ptr)),
        array_size(std::move(value.array_size)),
        array_capacity(std::move(value.array_capacity))
{
    value.array_ptr = nullptr;
    value.array_size = 0;
    value.array_capacity = 0;
    value.array_allocator = allocator();
}
//----------------------------------------------------------------------------------------------------
template<typename Type, typename allocator>
constexpr Vector<Type, allocator>::Vector(std::initializer_list<value_type> init_list, const allocator_type &alloc) :
        array_allocator(alloc),
        array_ptr(std::allocator_traits<allocator_type>::allocate(array_allocator, init_list.size())),
        array_size(init_list.size()),
        array_capacity(init_list.size())
{
    for (size_type i = 0; i < init_list.size(); i++)
    {
        std::allocator_traits<allocator_type>::construct(array_allocator, std::next(array_ptr, i), *std::next(init_list.begin(), i));
    }
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr Vector<Type, allocator>::~Vector()
{
    clear();
    std::allocator_traits<allocator_type>::deallocate(array_allocator, array_ptr, array_capacity);
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr Vector<Type, allocator>& Vector<Type, allocator>::operator=(const Vector& value)
{
    if (this != &value)
    {
        if (std::allocator_traits<allocator>::propagate_on_container_copy_assignment::value &&
            array_allocator != value.array_allocator)
        {
            clear();
            std::allocator_traits<allocator_type>::deallocate(array_allocator, array_ptr, array_capacity);
            array_allocator = value.array_allocator;
            array_ptr = std::allocator_traits<allocator_type>::allocate(array_allocator, value.array_capacity);

            for (size_type i = 0; i < value.size(); ++i)
            {
                std::allocator_traits<allocator_type>::construct(array_allocator, std::next(array_ptr, i), value.array_ptr[i]);
            }
            array_size = value.array_size;
            array_capacity = value.array_capacity;
        }
        else
        {
            clear();
            std::allocator_traits<allocator_type>::deallocate(array_allocator, array_ptr, array_capacity);
            array_ptr = std::allocator_traits<allocator_type>::allocate(array_allocator, value.array_capacity);

            for (size_type i = 0; i < value.array_size; ++i)
            {
                std::allocator_traits<allocator_type>::construct(array_allocator, std::next(array_ptr, i), value.array_ptr[i]);
            }
            array_size = value.array_size;
            array_capacity = value.array_capacity;
        }
    }
    return *this;
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr Vector<Type, allocator>& Vector<Type, allocator>::operator=(Vector&& value) noexcept
{
    if (this != &value)
    {
        if (array_allocator == value.array_allocator)
        {
            std::swap(array_ptr, value.array_ptr);
            std::swap(array_size, value.array_size);
            std::swap(array_capacity, value.array_capacity);
        }
        else
        if (std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value)
        {
            std::swap(array_ptr, value.array_ptr);
            std::swap(array_size, value.array_size);
            std::swap(array_capacity, value.array_capacity);
            std::swap(array_allocator, value.array_allocator);
        }
    }
    return *this;
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr Vector<Type, allocator>& Vector<Type, allocator>::operator=(std::initializer_list<value_type> init_list)
{
    if(array_capacity < init_list.size())
    {
        clear();
        std::allocator_traits<allocator_type>::deallocate(array_allocator, array_ptr, array_capacity);
        array_ptr = std::allocator_traits<allocator_type>::allocate(array_allocator, init_list.size());

        for (size_type i = 0; i < init_list.size(); ++i)
        {
            std::allocator_traits<allocator_type>::construct(array_allocator, std::next(array_ptr, i), *std::next(init_list.begin(), i));
        }
        array_size = init_list.size();
        array_capacity = init_list.size();
    }
    else
    {
        clear();
        for (size_type i = 0; i < init_list.size(); ++i)
        {
            std::allocator_traits<allocator_type>::construct(array_allocator, std::next(array_ptr, i), *std::next(init_list.begin(), i));
        }
        array_size = init_list.size();
    }
    return *this;
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
template<typename InputIt, typename>
constexpr void Vector<Type, allocator>::assign(InputIt first, InputIt last)
{
    if(std::distance(first, last) > array_capacity)
    {
        clear();
        std::allocator_traits<allocator_type>::deallocate(array_allocator, array_ptr, array_capacity);
        array_ptr = std::allocator_traits<allocator_type>::allocate(array_allocator, std::distance(first, last));

        for (size_type i = 0; i < std::distance(first, last); ++i)
        {
            std::allocator_traits<allocator_type>::construct(array_allocator, std::next(array_ptr, i), *std::next(first, i));
        }
        array_size = std::distance(first, last);
        array_capacity = std::distance(first, last);
    }
    else
    {
        clear();
        for (size_type i = 0; i < std::distance(first, last); ++i)
        {
            std::allocator_traits<allocator_type>::construct(array_allocator, std::next(array_ptr, i), *std::next(first, i));
        }
        array_size = std::distance(first, last);
    }
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr void Vector<Type, allocator>::assign(size_type count, const_reference value)
{
    if(count > array_capacity)
    {
        clear();
        std::allocator_traits<allocator_type>::deallocate(array_allocator, array_ptr, array_capacity);
        array_ptr = std::allocator_traits<allocator_type>::allocate(array_allocator, count);

        for (size_type i = 0; i < count; ++i)
        {
            std::allocator_traits<allocator_type>::construct(array_allocator, std::next(array_ptr, i), value);
        }
        array_size = count;
        array_capacity = count;
    }
    else
    {
        clear();
        for (size_type i = 0; i < count; ++i)
        {
            std::allocator_traits<allocator_type>::construct(array_allocator, std::next(array_ptr, i), value);
        }
        array_size = count;
    }
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr void Vector<Type, allocator>::assign(std::initializer_list<value_type> init_list)
{
    if(init_list.size() > array_capacity)
    {
        clear();
        std::allocator_traits<allocator_type>::deallocate(array_allocator, array_ptr, array_capacity);
        array_ptr = std::allocator_traits<allocator_type>::allocate(array_allocator, init_list.size());

        for (size_type i = 0; i < init_list.size(); ++i)
        {
            std::allocator_traits<allocator_type>::construct(array_allocator, std::next(array_ptr, i), *std::next(init_list.begin(), i));
        }
        array_size = init_list.size();
        array_capacity = init_list.size();
    }
    else
    {
        clear();
        for (size_type i = 0; i < init_list.size(); ++i)
        {
            std::allocator_traits<allocator_type>::construct(array_allocator, std::next(array_ptr, i), *std::next(init_list.begin(), i));
        }
        array_size = init_list.size();
    }
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::allocator_type Vector<Type, allocator>::get_allocator() const noexcept
{
    return array_allocator;
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::iterator Vector<Type, allocator>::begin() noexcept
{
    return iterator(array_ptr);
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::const_iterator Vector<Type, allocator>::begin() const noexcept
{
    return const_iterator(array_ptr);
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::iterator Vector<Type, allocator>::end() noexcept
{
    return iterator(array_ptr + array_size);
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::const_iterator Vector<Type, allocator>::end() const noexcept
{
    return const_iterator(array_ptr + array_size);
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::reverse_iterator Vector<Type, allocator>::rbegin() noexcept
{
    return reverse_iterator(end());
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::const_reverse_iterator Vector<Type, allocator>::rbegin() const noexcept
{
    return const_reverse_iterator(end());
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::reverse_iterator Vector<Type, allocator>::rend() noexcept
{
    return reverse_iterator(begin());
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::const_reverse_iterator Vector<Type, allocator>::rend() const noexcept
{
    return const_reverse_iterator(begin());
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::const_iterator Vector<Type, allocator>::cbegin() const noexcept
{
    return const_iterator(array_ptr);
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::const_iterator Vector<Type, allocator>::cend() const noexcept
{
    return const_iterator(array_ptr + array_size);
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::const_reverse_iterator Vector<Type, allocator>::crbegin() const noexcept
{
    return const_reverse_iterator(cend());
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::const_reverse_iterator Vector<Type, allocator>::crend() const noexcept
{
    return const_reverse_iterator(cbegin());
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr bool Vector<Type, allocator>::empty() const noexcept
{
    return begin() == end();
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::size_type Vector<Type, allocator>::size() const noexcept
{
    return array_size;
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::size_type Vector<Type, allocator>::max_size() const noexcept
{
    const size_type diff_max = std::numeric_limits<difference_type>::max() / sizeof(value_type);
    const size_type alloc_max = std::allocator_traits<allocator_type>::max_size(array_allocator);
    return std::min(diff_max, alloc_max);
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::size_type Vector<Type, allocator>::capacity() const noexcept
{
    return array_capacity;
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr void Vector<Type, allocator>::resize(size_type capacity)
{

}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr void Vector<Type, allocator>::resize(size_type size, const_reference value)
{

}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr void Vector<Type, allocator>::reserve(size_type capacity)
{
    if(array_capacity < capacity)
    {
        clear();
        std::allocator_traits<allocator_type>::deallocate(array_allocator, array_ptr, array_capacity);
        array_ptr = std::allocator_traits<allocator_type>::allocate(array_allocator, capacity);

        for (size_type i = 0; i < array_size; ++i)
        {
            std::allocator_traits<allocator_type>::construct(array_ptr[i]);
        }

        array_capacity = capacity;
    }
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr void Vector<Type, allocator>::shrink_to_fit()
{
    clear();
    std::allocator_traits<allocator_type>::deallocate(array_allocator, array_ptr, array_capacity);
    array_ptr = std::allocator_traits<allocator_type>::allocate(array_allocator, array_size);

    for (size_type i = 0; i < array_size; ++i)
    {
        std::allocator_traits<allocator_type>::construct(array_ptr[i]);
    }

    array_capacity = array_size;
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::reference Vector<Type, allocator>::operator[](size_type position)
{
    return array_ptr[position];
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::const_reference Vector<Type, allocator>::operator[](size_type position) const
{
    return array_ptr[position];
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::const_reference Vector<Type, allocator>::at(size_type position) const
{

}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::reference Vector<Type, allocator>::at(size_type position)
{

}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::reference Vector<Type, allocator>::front()
{
    return *begin();
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::const_reference Vector<Type, allocator>::front() const
{
    return *begin();
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::reference Vector<Type, allocator>::back()
{
    return *(end() - 1);
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr typename Vector<Type, allocator>::const_reference Vector<Type, allocator>::back() const
{
    return *(end() - 1);
}
//----------------------------------------------------------------------------------------------------
template <typename Type, typename allocator>
constexpr void Vector<Type, allocator>::clear() noexcept
{
    for (size_type i = 0; i < array_size; ++i)
    {
        std::allocator_traits<allocator_type>::destroy(array_allocator, std::next(array_ptr, i));
    }
}
//----------------------------------------------------------------------------------------------------
#endif //VECTOR_VECTOR_H
