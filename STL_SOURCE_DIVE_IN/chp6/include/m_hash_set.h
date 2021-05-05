#pragma once
#include "m_hashtable.h"

namespace mj
{
    template <class Value,
              class HashFcn = hash<Value>,
              class EqualKey = equal_to<Value>,
              class Alloc = alloc>
    class hash_set
    {
    private:
        typedef hashtable<Value, Value, HashFcn, identity<Value>, EqualKey, Alloc> _Ht;
        _Ht rep;

    public:
        typedef typename _Ht::key_type key_type;
        typedef typename _Ht::value_type value_type;
        typedef typename _Ht::hasher hasher;
        typedef typename _Ht::key_equal key_equal;

        typedef typename _Ht::size_type size_type;
        typedef typename _Ht::difference_type difference_type;
        typedef typename _Ht::const_pointer pointer;
        typedef typename _Ht::const_pointer const_pointer;
        typedef typename _Ht::const_reference reference;
        typedef typename _Ht::const_reference const_reference;

        typedef typename _Ht::const_iterator iterator;
        typedef typename _Ht::const_iterator const_iterator;

        hasher hash_funct() const { return rep.hash_funct(); }
        key_equal key_eq() const { return rep.key_eq(); }

    public:
        hash_set() : rep(100, hasher(), key_equal()) {}
        explicit hash_set(size_type n) : rep(n, hasher(), key_equal()) {}
        hash_set(size_type n, const hasher &hf) : rep(n, hf, key_equal()) {}
        hash_set(size_type n, const hasher &hf, const key_equal &eql) : rep(n, hf, eql) {}

        template <class InputIter>
        hash_set(InputIter first, InputIter last) : rep(100, hasher(), key_equal())
        {
            rep.insert_unique(first, last);
        }

    public:
        size_type size() const { return rep.size(); }
        size_type bucket_count() const { return rep.bucket_count(); }
        size_type max_size() const { return rep.max_size(); }
        bool empty() const { return rep.empty(); }
        void swap(hash_set &hs) { rep.swap(hs.rep); }
        iterator begin() const { return rep.begin(); }
        iterator end() const { return rep.end(); }

    public:
        pair<iterator, bool> insert(const value_type &obj)
        {
            pair<typename _Ht::iterator, bool> p = rep.insert_unique(obj);
            return pair<iterator, bool>(p.first, p.second);
        }
        iterator find(const key_type &key) const { return rep.find(key); }
        size_type count(const key_type &key) const { return rep.count(key); }
        void clear() { rep.clear(); }
    };
}
