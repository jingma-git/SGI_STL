#pragma once

typedef long int ptrdiff_t;

///  Marking input iterators.
struct input_iterator_tag // read-only
{
};

///  Marking output iterators.
struct output_iterator_tag // write-only
{
};

/// Forward iterators support a superset of input iterator operations.
struct forward_iterator_tag : public input_iterator_tag
{
};

/// Bidirectional iterators support a superset of forward iterator
/// operations.
struct bidirectional_iterator_tag : public forward_iterator_tag
{
};