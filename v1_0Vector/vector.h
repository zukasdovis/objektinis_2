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
 */

/**
 * @class Vector
 * @brief Dinaminio masyvo konteineris
 * @tparam T elementų tipas
 */
template <typename T>
class Vector
{
private:
    T *data_;
    size_t size_;
    size_t capacity_;

public:
    using value_type = T;
    using size_type = size_t;
    using reference = T &;
    using const_reference = const T &;
    using pointer = T *;
    using const_pointer = const T *;
    using iterator = T *;
    using const_iterator = const T *;

    // =============================================
    /// @name Konstruktoriai
    /// @{
    // =============================================

    /** @brief Tuščias vektorius */
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    /**
     * @brief n elementų su reikšme val
     * @param n kiekis, @param val reikšmė
     */
    explicit Vector(size_type n, const T &val = T())
        : data_(nullptr), size_(0), capacity_(0)
    {
        resize(n, val);
    }

    /**
     * @brief Kopijuoja visus elementus iš kitas
     * @param kitas kopijuojamas vektorius
     */
    Vector(const Vector &kitas)
        : data_(nullptr), size_(0), capacity_(0)
    {
        reserve(kitas.capacity_);
        for (size_type i = 0; i < kitas.size_; i++)
            new (data_ + i) T(kitas.data_[i]);
        size_ = kitas.size_;
    }

    /**
     * @brief Perima atmintį, kitas tampa tuščias
     * @param kitas perkeliamas vektorius
     */
    Vector(Vector &&kitas) noexcept
        : data_(kitas.data_), size_(kitas.size_), capacity_(kitas.capacity_)
    {
        kitas.data_ = nullptr;
        kitas.size_ = 0;
        kitas.capacity_ = 0;
    }

    /**
     * @brief Iš inicializavimo sąrašo
     * @param il pvz. {1,2,3}
     */
    Vector(std::initializer_list<T> il)
        : data_(nullptr), size_(0), capacity_(0)
    {
        reserve(il.size());
        for (const auto &val : il)
            push_back(val);
    }

    /** @brief Sunaikina elementus ir atlaisvina atmintį */
    ~Vector()
    {
        clear();
        ::operator delete(data_);
    }

    /// @}

    // =============================================
    /// @name Priskyrimo operatoriai
    /// @{
    // =============================================

    /**
     * @brief Kopijuoja iš kitas
     * @return *this
     */
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

    /**
     * @brief Perima atmintį iš kitas
     * @return *this
     */
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

    /**
     * @brief Priskiria iš sąrašo, pvz. v = {1,2,3}
     * @return *this
     */
    Vector &operator=(std::initializer_list<T> il)
    {
        clear();
        reserve(il.size());
        for (const auto &val : il)
            push_back(val);
        return *this;
    }

    /// @}

    // =============================================
    /// @name Elementų prieiga
    /// @{
    // =============================================

    /**
     * @brief Prieiga su ribų tikrinimu
     * @throws std::out_of_range jei i >= size()
     */
    reference at(size_type i)
    {
        if (i >= size_)
            throw std::out_of_range("Vector::at - indeksas uz ribu");
        return data_[i];
    }

    /** @copydoc at(size_type) */
    const_reference at(size_type i) const
    {
        if (i >= size_)
            throw std::out_of_range("Vector::at - indeksas uz ribu");
        return data_[i];
    }

    /** @brief Prieiga be ribų tikrinimo */
    reference operator[](size_type i) { return data_[i]; }

    /** @copydoc operator[](size_type) */
    const_reference operator[](size_type i) const { return data_[i]; }

    /** @brief Pirmas elementas */
    reference front() { return data_[0]; }

    /** @copydoc front() */
    const_reference front() const { return data_[0]; }

    /** @brief Paskutinis elementas */
    reference back() { return data_[size_ - 1]; }

    /** @copydoc back() */
    const_reference back() const { return data_[size_ - 1]; }

    /** @brief Rodyklė į vidinį masyvą */
    pointer data() { return data_; }

    /** @copydoc data() */
    const_pointer data() const { return data_; }

    /// @}

    // =============================================
    /// @name Iteratoriai
    /// @{
    // =============================================

    /** @brief Iteratorius į pirmą elementą */
    iterator begin() { return data_; }

    /** @copydoc begin() */
    const_iterator begin() const { return data_; }

    /** @brief Const iteratorius į pirmą elementą */
    const_iterator cbegin() const { return data_; }

    /** @brief Iteratorius už paskutinio elemento */
    iterator end() { return data_ + size_; }

    /** @copydoc end() */
    const_iterator end() const { return data_ + size_; }

    /** @brief Const iteratorius už paskutinio elemento */
    const_iterator cend() const { return data_ + size_; }

    /// @}

    // =============================================
    /// @name Dydis ir talpa
    /// @{
    // =============================================

    /** @brief true jei size() == 0 */
    bool empty() const { return size_ == 0; }

    /** @brief Elementų kiekis */
    size_type size() const { return size_; }

    /** @brief Rezervuota talpa */
    size_type capacity() const { return capacity_; }

    /** @brief Maksimalus galimas dydis */
    size_type max_size() const { return std::numeric_limits<size_type>::max(); }

    /**
     * @brief Rezervuoja n vietų, perkelia jei reikia
     * @param n norima talpa
     */
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

    /** @brief Sumažina capacity iki size */
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

    /// @}

    // =============================================
    /// @name Modifikatoriai
    /// @{
    // =============================================

    /** @brief Sunaikina elementus, capacity lieka */
    void clear()
    {
        for (size_type i = 0; i < size_; i++)
            data_[i].~T();
        size_ = 0;
    }

    /**
     * @brief Prideda kopiją į galą, dvigubina capacity jei pilna
     * @param val pridedama reikšmė
     */
    void push_back(const T &val)
    {
        if (size_ == capacity_)
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        new (data_ + size_) T(val);
        size_++;
    }

    /**
     * @brief Prideda move į galą
     * @param val perkeliama reikšmė
     */
    void push_back(T &&val)
    {
        if (size_ == capacity_)
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        new (data_ + size_) T(std::move(val));
        size_++;
    }

    /**
     * @brief Konstruoja elementą vietoje gale
     * @param args konstruktoriaus argumentai
     */
    template <typename... Args>
    void emplace_back(Args &&...args)
    {
        if (size_ == capacity_)
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        new (data_ + size_) T(std::forward<Args>(args)...);
        size_++;
    }

    /** @brief Pašalina paskutinį elementą */
    void pop_back()
    {
        if (size_ > 0)
        {
            data_[size_ - 1].~T();
            size_--;
        }
    }

    /**
     * @brief Keičia dydį, nauji elementai = val
     * @param n naujas dydis, @param val užpildymo reikšmė
     */
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

    /**
     * @brief Įterpia val prieš pos
     * @return iteratorius į įterptą elementą
     */
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

    /**
     * @brief Įterpia intervalą [first,last) prieš pos
     * @return iteratorius į pirmą įterptą elementą
     */
    template <typename InputIt>
    iterator insert(iterator pos, InputIt first, InputIt last)
    {
        size_type idx = pos - data_;
        size_type count = std::distance(first, last);
        if (size_ + count > capacity_)
            reserve((size_ + count) * 2);
        for (size_type i = size_ + count - 1; i >= idx + count; i--)
        {
            new (data_ + i) T(std::move(data_[i - count]));
            data_[i - count].~T();
        }
        size_type i = idx;
        for (InputIt it = first; it != last; it++, i++)
            new (data_ + i) T(*it);
        size_ += count;
        return data_ + idx;
    }

    /**
     * @brief Ištrina elementą pos
     * @return iteratorius į elementą po ištrintojo
     */
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

    /**
     * @brief Ištrina intervalą [first,last)
     * @return iteratorius į elementą po paskutiniojo
     */
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

    /**
     * @brief Sukeičia du vektorius vietomis
     * @param kitas kitas vektorius
     */
    void swap(Vector &kitas) noexcept
    {
        std::swap(data_, kitas.data_);
        std::swap(size_, kitas.size_);
        std::swap(capacity_, kitas.capacity_);
    }

    /**
     * @brief Išvalo ir užpildo n kartų val
     * @param n kiekis, @param val reikšmė
     */
    void assign(size_type n, const T &val)
    {
        clear();
        resize(n, val);
    }

    /// @}

    // =============================================
    /// @name Lyginimo operatoriai
    /// @{
    // =============================================

    /** @brief true jei vienodas dydis ir visi elementai lygūs */
    bool operator==(const Vector &kitas) const
    {
        if (size_ != kitas.size_)
            return false;
        for (size_type i = 0; i < size_; i++)
            if (data_[i] != kitas.data_[i])
                return false;
        return true;
    }

    /** @brief true jei vektoriai skiriasi */
    bool operator!=(const Vector &kitas) const { return !(*this == kitas); }

    /** @brief Leksikografinis palyginimas */
    bool operator<(const Vector &kitas) const
    {
        return std::lexicographical_compare(begin(), end(),
                                            kitas.begin(), kitas.end());
    }

    /** @brief true jei didesnis leksikografiškai */
    bool operator>(const Vector &kitas) const { return kitas < *this; }

    /** @brief true jei mažesnis arba lygus */
    bool operator<=(const Vector &kitas) const { return !(kitas < *this); }

    /** @brief true jei didesnis arba lygus */
    bool operator>=(const Vector &kitas) const { return !(*this < kitas); }

    /// @}
};

#endif