#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <limits>

/**
 * @file Vector.h
 * @brief Nuosavas dinaminis masyvas - std::vector analogas
 * @version 3.0
 *
 * @details
 * Realizuoti metodai:
 * - Konstruktoriai (default, copy, move, size, initializer_list)
 * - Rule of Five (copy/move konstruktoriai ir assignment, destruktorius)
 * - Elementų prieiga (at, operator[], front, back, data)
 * - Iteratoriai (begin, end, cbegin, cend)
 * - Talpa (size, capacity, empty, reserve, shrink_to_fit, max_size)
 * - Modifikatoriai (push_back, pop_back, emplace_back, insert,
 *                   erase, clear, resize, swap, assign)
 * - Lyginimo operatoriai (==, !=, <, >, <=, >=)
 *
 * Naudojimo pavyzdys:
 * @code
 * Vector<int> v = {1, 2, 3};
 * v.push_back(4);
 * std::sort(v.begin(), v.end());
 * for (auto x : v) std::cout << x << " ";
 * @endcode
 */

template <typename T>
class Vector
{
private:
    T *data_;         ///< rodyklė į duomenis
    size_t size_;     ///< elementų kiekis
    size_t capacity_; ///< rezervuota atminties

public:
    // --- tipų apibrėžimai (kaip std::vector) ---
    using value_type = T;
    using size_type = size_t;
    using reference = T &;
    using const_reference = const T &;
    using pointer = T *;
    using const_pointer = const T *;
    using iterator = T *;
    using const_iterator = const T *;

    // =============================================
    // KONSTRUKTORIAI
    // =============================================

    /// Default konstruktorius
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    /// Konstruktorius su dydžiu
    explicit Vector(size_type n, const T &val = T())
        : data_(nullptr), size_(0), capacity_(0)
    {
        resize(n, val);
    }

    /// Copy konstruktorius
    Vector(const Vector &kitas)
        : data_(nullptr), size_(0), capacity_(0)
    {
        reserve(kitas.capacity_);
        for (size_type i = 0; i < kitas.size_; i++)
            new (data_ + i) T(kitas.data_[i]);
        size_ = kitas.size_;
    }

    /// Move konstruktorius
    Vector(Vector &&kitas) noexcept
        : data_(kitas.data_), size_(kitas.size_), capacity_(kitas.capacity_)
    {
        kitas.data_ = nullptr;
        kitas.size_ = 0;
        kitas.capacity_ = 0;
    }

    /// Initializer list konstruktorius
    Vector(std::initializer_list<T> il)
        : data_(nullptr), size_(0), capacity_(0)
    {
        reserve(il.size());
        for (const auto &val : il)
            push_back(val);
    }

    /// Destruktorius
    ~Vector()
    {
        clear();
        ::operator delete(data_);
    }

    // =============================================
    // PRISKYRIMO OPERATORIAI
    // =============================================

    /// Copy assignment
    Vector &operator=(const Vector &kitas)
    {
        if (this == &kitas)
            return *this;
        clear();
        reserve(kitas.capacity_);
        for (size_type i = 0; i < kitas.size_; i++)
            new (data_ + i) T(kitas.data_[i]);
        size_ = kitas.size_;
        return *this;
    }

    /// Move assignment
    Vector &operator=(Vector &&kitas) noexcept
    {
        if (this == &kitas)
            return *this;
        clear();
        ::operator delete(data_);
        data_ = kitas.data_;
        size_ = kitas.size_;
        capacity_ = kitas.capacity_;
        kitas.data_ = nullptr;
        kitas.size_ = 0;
        kitas.capacity_ = 0;
        return *this;
    }

    /// Initializer list assignment
    Vector &operator=(std::initializer_list<T> il)
    {
        clear();
        reserve(il.size());
        for (const auto &val : il)
            push_back(val);
        return *this;
    }

    // =============================================
    // ELEMENTŲ PRIEIGA
    // =============================================

    /// Prieiga su ribų tikrinimu
    reference at(size_type i)
    {
        if (i >= size_)
            throw std::out_of_range("Vector::at - indeksas uz ribu");
        return data_[i];
    }

    const_reference at(size_type i) const
    {
        if (i >= size_)
            throw std::out_of_range("Vector::at - indeksas uz ribu");
        return data_[i];
    }

    /// Prieiga be ribų tikrinimo
    reference operator[](size_type i) { return data_[i]; }
    const_reference operator[](size_type i) const { return data_[i]; }

    /// Pirmas elementas
    reference front() { return data_[0]; }
    const_reference front() const { return data_[0]; }

    /// Paskutinis elementas
    reference back() { return data_[size_ - 1]; }
    const_reference back() const { return data_[size_ - 1]; }

    /// Rodyklė į duomenis
    pointer data() { return data_; }
    const_pointer data() const { return data_; }

    // =============================================
    // ITERATORIAI
    // =============================================

    iterator begin() { return data_; }
    const_iterator begin() const { return data_; }
    const_iterator cbegin() const { return data_; }

    iterator end() { return data_ + size_; }
    const_iterator end() const { return data_ + size_; }
    const_iterator cend() const { return data_ + size_; }

    // =============================================
    // DYDIS IR TALPA
    // =============================================

    bool empty() const { return size_ == 0; }
    size_type size() const { return size_; }
    size_type capacity() const { return capacity_; }
    size_type max_size() const { return std::numeric_limits<size_type>::max(); }

    /// Rezervuoja atmintį
    void reserve(size_type n)
    {
        if (n <= capacity_)
            return;
        T *naujas = static_cast<T *>(::operator new(n * sizeof(T)));
        for (size_type i = 0; i < size_; i++)
        {
            new (naujas + i) T(std::move(data_[i]));
            data_[i].~T();
        }
        ::operator delete(data_);
        data_ = naujas;
        capacity_ = n;
    }

    /// Sumažina capacity iki size
    void shrink_to_fit()
    {
        if (size_ == capacity_)
            return;
        T *naujas = static_cast<T *>(::operator new(size_ * sizeof(T)));
        for (size_type i = 0; i < size_; i++)
        {
            new (naujas + i) T(std::move(data_[i]));
            data_[i].~T();
        }
        ::operator delete(data_);
        data_ = naujas;
        capacity_ = size_;
    }

    // =============================================
    // MODIFIKATORIAI
    // =============================================

    /// Išvalo visus elementus
    void clear()
    {
        for (size_type i = 0; i < size_; i++)
            data_[i].~T();
        size_ = 0;
    }

    /// Prideda elementą į galą (copy)
    void push_back(const T &val)
    {
        if (size_ == capacity_)
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        new (data_ + size_) T(val);
        size_++;
    }

    /// Prideda elementą į galą (move)
    void push_back(T &&val)
    {
        if (size_ == capacity_)
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        new (data_ + size_) T(std::move(val));
        size_++;
    }

    /// Konstruoja elementą vietoje gale
    template <typename... Args>
    void emplace_back(Args &&...args)
    {
        if (size_ == capacity_)
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        new (data_ + size_) T(std::forward<Args>(args)...);
        size_++;
    }

    /// Pašalina paskutinį elementą
    void pop_back()
    {
        if (size_ > 0)
        {
            data_[size_ - 1].~T();
            size_--;
        }
    }

    /// Pakeičia dydį
    void resize(size_type n, const T &val = T())
    {
        if (n < size_)
        {
            for (size_type i = n; i < size_; i++)
                data_[i].~T();
        }
        else
        {
            reserve(n);
            for (size_type i = size_; i < n; i++)
                new (data_ + i) T(val);
        }
        size_ = n;
    }

    /// Įterpia elementą į poziciją
    iterator insert(iterator pos, const T &val)
    {
        size_type idx = pos - data_;
        if (size_ == capacity_)
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        for (size_type i = size_; i > idx; i--)
        {
            new (data_ + i) T(std::move(data_[i - 1]));
            data_[i - 1].~T();
        }
        new (data_ + idx) T(val);
        size_++;
        return data_ + idx;
    }
    /// Įterpia elementų intervalą iš iteratorių
    template <typename InputIt>
    iterator insert(iterator pos, InputIt first, InputIt last)
    {
        size_type idx = pos - data_;
        size_type count = std::distance(first, last);

        if (size_ + count > capacity_)
            reserve((size_ + count) * 2);

        // pastumiam esamus elementus į dešinę
        for (size_type i = size_ + count - 1; i >= idx + count; i--)
        {
            new (data_ + i) T(std::move(data_[i - count]));
            data_[i - count].~T();
        }

        // įterpiame naujus elementus
        size_type i = idx;
        for (InputIt it = first; it != last; it++, i++)
        {
            new (data_ + i) T(*it);
        }

        size_ += count;
        return data_ + idx;
    }

    /// Ištrina elementą iš pozicijos
    iterator erase(iterator pos)
    {
        size_type idx = pos - data_;
        data_[idx].~T();
        for (size_type i = idx; i < size_ - 1; i++)
        {
            new (data_ + i) T(std::move(data_[i + 1]));
            data_[i + 1].~T();
        }
        size_--;
        return data_ + idx;
    }

    /// Ištrina elementų intervalą
    iterator erase(iterator first, iterator last)
    {
        size_type idx = first - data_;
        size_type count = last - first;
        for (size_type i = idx; i < idx + count; i++)
            data_[i].~T();
        for (size_type i = idx; i < size_ - count; i++)
        {
            new (data_ + i) T(std::move(data_[i + count]));
            data_[i + count].~T();
        }
        size_ -= count;
        return data_ + idx;
    }

    /// Sukeičia du vektorius
    void swap(Vector &kitas) noexcept
    {
        std::swap(data_, kitas.data_);
        std::swap(size_, kitas.size_);
        std::swap(capacity_, kitas.capacity_);
    }

    /// Užpildo vektorių reikšmėmis
    void assign(size_type n, const T &val)
    {
        clear();
        resize(n, val);
    }

    // =============================================
    // LYGINIMO OPERATORIAI
    // =============================================

    bool operator==(const Vector &kitas) const
    {
        if (size_ != kitas.size_)
            return false;
        for (size_type i = 0; i < size_; i++)
            if (data_[i] != kitas.data_[i])
                return false;
        return true;
    }

    bool operator!=(const Vector &kitas) const { return !(*this == kitas); }

    bool operator<(const Vector &kitas) const
    {
        return std::lexicographical_compare(begin(), end(),
                                            kitas.begin(), kitas.end());
    }

    bool operator>(const Vector &kitas) const { return kitas < *this; }
    bool operator<=(const Vector &kitas) const { return !(kitas < *this); }
    bool operator>=(const Vector &kitas) const { return !(*this < kitas); }
};

#endif