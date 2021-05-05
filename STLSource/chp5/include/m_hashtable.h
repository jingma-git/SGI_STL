#pragma once
#include "m_iterator_base_funcs.h"
#include "m_alloc.h"
#include "m_vector.h"
#include "m_algo.h"
#include "m_hash_fun.h"
#include "m_function.h"
#include "m_pair.h"

namespace mj
{
    template <class Value>
    struct __hashtable_node
    {
        __hashtable_node *next;
        Value val;
    };
    template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
    class hashtable;

    template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
    struct __hashtable_iterator;

    template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
    struct __hashtable_const_iterator;

    template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
    struct __hashtable_iterator
    {
        typedef hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> _hashtable;
        typedef __hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> iterator;
        typedef __hashtable_const_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> const_iterator;
        typedef __hashtable_node<Value> node;

        typedef forward_iterator_tag iterator_category;
        typedef Value value_type;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
        typedef Value &reference;
        typedef Value *pointer;

        node *cur; // node the iterator point to
        _hashtable *ht;

        __hashtable_iterator(node *n, _hashtable *tab) : cur(n), ht(tab) {}
        __hashtable_iterator() {}
        reference operator*() const { return cur->val; }
        pointer operator->() const { return &(operator*()); }
        iterator &operator++()
        {
            const node *old = cur;
            cur = cur->next;
            if (!cur)
            {
                // go to next bucket
                size_type bucket = ht->bkt_num(old->val);
                while (!cur && ++bucket < ht->buckets.size())
                {
                    cur = ht->buckets[bucket];
                }
                return *this;
            }
        }
        iterator &operator++(int)
        {
            iterator tmp = *this;
            ++*this;
            return tmp;
        }
        bool operator==(const iterator &it) const { return cur == it.cur; }
        bool operator!=(const iterator &it) const { return cur != it.cur; }
    };

    template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
    struct __hashtable_const_iterator
    {
        typedef hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> _hashtable;
        typedef __hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> iterator;
        typedef __hashtable_const_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> const_iterator;
        typedef __hashtable_node<Value> node;

        typedef forward_iterator_tag iterator_category;
        typedef Value value_type;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
        typedef const Value &reference;
        typedef const Value *pointer;

        const node *cur; // node the iterator point to
        const _hashtable *ht;

        __hashtable_const_iterator(const node *n, const _hashtable *tab) : cur(n), ht(tab) {}
        __hashtable_const_iterator() {}
        __hashtable_const_iterator(const iterator &__it)
            : cur(__it.cur), ht(__it.ht) {}

        reference operator*() const { return cur->val; }
        pointer operator->() const { return &(operator*()); }
        const_iterator &operator++()
        {
            const node *old = cur;
            cur = cur->next;
            if (!cur)
            {
                // go to next bucket
                size_type bucket = ht->bkt_num(old->val);
                while (!cur && ++bucket < ht->buckets.size())
                {
                    cur = ht->buckets[bucket];
                }
                return *this;
            }
        }
        const_iterator &operator++(int)
        {
            const_iterator tmp = *this;
            ++*this;
            return tmp;
        }
        bool operator==(const const_iterator &it) const { return cur == it.cur; }
        bool operator!=(const const_iterator &it) const { return cur != it.cur; }
    };

    // Note: assumes long is at least 32 bits.
    enum
    {
        __stl_num_primes = 28
    };

    static const unsigned long __stl_prime_list[__stl_num_primes] =
        {
            53ul, 97ul, 193ul, 389ul, 769ul,
            1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
            49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
            1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
            50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
            1610612741ul, 3221225473ul, 4294967291ul};

    inline unsigned long __stl_next_prime(unsigned long __n)
    {
        const unsigned long *__first = __stl_prime_list;
        const unsigned long *__last = __stl_prime_list + (int)__stl_num_primes;
        const unsigned long *pos = lower_bound(__first, __last, __n);
        return pos == __last ? *(__last - 1) : *pos;
    }

    template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc = alloc>
    class hashtable
    {
    public:
        typedef HashFcn hasher;
        typedef EqualKey key_equal;
        typedef size_t size_type;
        typedef Value value_type;
        typedef Key key_type;

        typedef ptrdiff_t difference_type;
        typedef value_type *pointer;
        typedef const value_type *const_pointer;
        typedef value_type &reference;
        typedef const value_type &const_reference;

        typedef __hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> iterator;
        friend struct
            __hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>;

        typedef __hashtable_const_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> const_iterator;
        friend struct
            __hashtable_const_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>;

    private:
        hasher hash;
        key_equal equals;
        ExtractKey get_key;

        typedef __hashtable_node<Value> node;
        typedef mj::allocator<node> node_allocator;

        mj::vector<node *, mj::allocator<node *>> buckets;
        size_type num_elements;

    public:
        hashtable(size_type n, const HashFcn &hf, const EqualKey &eql)
            : hash(hf), equals(eql), get_key(ExtractKey()), num_elements(0)
        {
            initialize_buckets(n);
        }

        void initialize_buckets(size_type n)
        {
            const size_type n_buckets = next_size(n);
            buckets.reserve(n);
            buckets.insert(buckets.end(), n_buckets, (node *)0);
            num_elements = 0;
        }

        hasher hash_funct() const { return hash; }
        key_equal key_eq() const { return equals; }

        size_type bucket_count() const { return buckets.size(); }

        size_type max_bucket_count() const { return __stl_prime_list[__stl_num_primes - 1]; }

        size_type max_size() const { return size_type(-1); }

        size_type next_size(size_type n) const { return __stl_next_prime(n); }

        bool empty() const { return size() == 0; }

        void swap(hashtable &__ht)
        {
            mj::swap(hash, __ht.hash);
            mj::swap(equals, __ht.equals);
            mj::swap(get_key, __ht.get_key);
            buckets.swap(__ht.buckets);
            mj::swap(num_elements, __ht.num_elements);
        }

        node *new_node(const value_type &obj)
        {
            node *n = node_allocator::allocate();
            n->next = 0;
            try
            {
                construct(&n->val, obj);
                return n;
            }
            catch (...)
            {
                node_allocator::deallocate(n);
                throw;
            }
        }

        void delete_node(node *n)
        {
            destroy(&n->val);
            node_allocator::deallocate(n);
        }

        size_type elems_in_bucket(size_type i)
        {
            node *cur = buckets[i];
            size_type n = 0;
            for (; cur; cur = cur->next)
                ++n;
            return n;
        }

        iterator find(const key_type &key)
        {
            size_type n = bkt_num(key);
            node *first;
            for (first = buckets[n]; first && !equals(get_key(first->val), key); first = first->next)
            {
            }
            return iterator(first, this);
        }

        const_iterator find(const key_type &key) const
        {
            size_type n = bkt_num(key);
            node *first;
            for (first = buckets[n]; first && !equals(get_key(first->val), key); first = first->next)
            {
            }
            return const_iterator(first, this);
        }

        size_type count(const key_type &key) const
        {
            size_type n = bkt_num(key);
            size_type result = 0;
            for (const node *cur = buckets[n]; cur; cur = cur->next)
                if (equals(get_key(cur->val), key))
                    ++result;
            return result;
        }

        // insert element, repetition not allowed
        pair<iterator, bool> insert_unique(const value_type &obj)
        {
            resize(num_elements + 1); // whether need to re-create table
            return insert_unique_noresize(obj);
        }

        template <class _InputIterator>
        void insert_unique(_InputIterator __f, _InputIterator __l)
        {
            insert_unique(__f, __l, __ITERATOR_CATEGORY(__f));
        }

        template <class _InputIterator>
        void insert_unique(_InputIterator __f, _InputIterator __l,
                           input_iterator_tag)
        {
            for (; __f != __l; ++__f)
                insert_unique(*__f);
        }

        template <class _ForwardIterator>
        void insert_unique(_ForwardIterator __f, _ForwardIterator __l,
                           forward_iterator_tag)
        {
            size_type __n = distance(__f, __l);
            resize(num_elements + __n);
            for (; __n > 0; --__n, ++__f)
                insert_unique_noresize(*__f);
        }

        // insert element, allow repetition
        iterator insert_equal(const value_type &obj)
        {
            resize(num_elements + 1);
            return insert_equal_no_resize(obj);
        }

        void resize(size_type num_elements_hint)
        {
            const size_type old_n = buckets.size();
            if (num_elements_hint > old_n)
            {
                const size_type n = next_size(num_elements_hint);
                if (n > old_n)
                {
                    vector<node *, mj::allocator<node *>> tmp(n, (node *)0);
                    for (size_type i = 0; i < old_n; ++i)
                    {
                        node *first = buckets[i];
                        while (first)
                        {
                            // find position in new_bucket
                            size_type new_bucket = bkt_num(first->val, n);
                            // be cautious for the following implementation, how pointer changes
                            // old_buckets[i] point to next node
                            buckets[i] = first->next;
                            // insert current node into new_bucket
                            first->next = tmp[new_bucket];
                            tmp[new_bucket] = first;
                            // go back to old_bucket's node chain, ready for next node
                            first = buckets[i];
                        }
                    }
                    buckets.swap(tmp);
                }
            }
        }

        pair<iterator, bool> insert_unique_noresize(const value_type &obj)
        {
            const size_type n = bkt_num(obj);
            node *first = buckets[n];

            for (node *cur = first; cur; cur = cur->next)
            {
                if (equals(get_key(cur->val), get_key(obj)))
                    return pair<iterator, bool>(iterator(cur, this), false);
            }
            node *tmp = new_node(obj);
            tmp->next = first;
            buckets[n] = tmp;
            ++num_elements;
            return pair<iterator, bool>(iterator(tmp, this), true);
        }

        iterator insert_equal_no_resize(const value_type &obj)
        {
            const size_type n = bkt_num(obj);
            node *first = buckets[n];

            for (node *cur = first; cur; cur = cur->next)
            {
                if (equals(get_key(cur->val), get_key(obj)))
                {
                    node *tmp = new_node(obj);
                    tmp->next = cur->next;
                    cur->next = tmp;
                    ++num_elements;
                    return iterator(tmp, this);
                }
            }

            node *tmp = new_node(obj);
            tmp->next = first;
            buckets[n] = tmp;
            ++num_elements;
            return iterator(tmp, this);
        }

        size_type size() { return num_elements; }

        size_type bkt_num(const value_type &obj, size_t n) const
        {
            return bkt_num_key(get_key(obj), n);
        }

        size_type bkt_num(const value_type &obj) const
        {
            return bkt_num_key(get_key(obj), buckets.size());
        }

        size_type bkt_num_key(const key_type &key, size_t n) const
        {
            return hash(key) % n;
        }

        iterator begin()
        {
            for (size_type i = 0; i < buckets.size(); ++i)
            {
                if (buckets[i])
                    return iterator(buckets[i], this);
            }
        }

        iterator end()
        {
            return iterator(0, this);
        }

        const_iterator begin() const
        {
            for (size_type __n = 0; __n < buckets.size(); ++__n)
                if (buckets[__n])
                    return const_iterator(buckets[__n], this);
            return end();
        }

        const_iterator end() const { return const_iterator(0, this); }

        void clear()
        {
            for (size_type i = 0; i < buckets.size(); ++i)
            {
                node *cur = buckets[i];
                while (cur)
                {
                    node *next = cur->next;
                    delete_node(cur);
                    cur = next;
                }
                buckets[i] = 0;
            }
            num_elements = 0;
        }

        void copy_from(const hashtable &ht)
        {
            buckets.clear();
            buckets.reserve(ht.buckets.size());
            buckets.insert(buckets.end(), ht.buckests.size(), (node *)0);

            for (size_type i = 0; i < ht.buckets.size(); ++i)
            {
                if (const node *cur = ht.buckets[i])
                {
                    node *copy = new_node(cur->val);
                    buckets[i] = copy;
                    for (node *next = cur->next; next; cur = next, next = cur->next)
                    {
                        copy->next = new_node(next->val);
                        copy = copy->next;
                    }
                }
            }
            num_elements = ht.num_elements;
        }
    };
};