#ifndef EIGEN_MATRIXSTORAGE_H
#define EIGEN_MATRIXSTORAGE_H

struct ei_constructor_without_unaligned_array_assert
{
};

/** \internal
  * Static array automatically aligned if the total byte size is a multiple of 16 and the matrix options require auto alignment
  */
template <typename T, int Size, int MatrixOptions,
          bool Align = (MatrixOptions & AutoAlign) && (((Size * sizeof(T)) & 0xf) == 0)>
struct ei_matrix_array
{
    EIGEN_ALIGN_128 T array[Size];

    ei_matrix_array()
    {
#ifndef EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT
        ei_assert((reinterpret_cast<size_t>(array) & 0xf) == 0 && "this assertion is explained here: http://eigen.tuxfamily.org/dox/UnalignedArrayAssert.html  **** READ THIS WEB PAGE !!! ****");
#endif
    }

    ei_matrix_array(ei_constructor_without_unaligned_array_assert) {}
};

template <typename T, int Size, int MatrixOptions>
struct ei_matrix_array<T, Size, MatrixOptions, false>
{
    T array[Size];
    ei_matrix_array() {}
    ei_matrix_array(ei_constructor_without_unaligned_array_assert) {}
};

/** \internal
  *
  * \class ei_matrix_storage
  *
  * \brief Stores the data of a matrix
  *
  * This class stores the data of fixed-size, dynamic-size or mixed matrices
  * in a way as compact as possible.
  *
  * \sa Matrix
  */
template <typename T, int Size, int _Rows, int _Cols, int _Options>
class ei_matrix_storage;

// purely fixed-size matrix
template <typename T, int Size, int _Rows, int _Cols, int _Options>
class ei_matrix_storage
{
    ei_matrix_array<T, Size, _Options> m_data;

public:
    inline explicit ei_matrix_storage() {}
    inline ei_matrix_storage(ei_constructor_without_unaligned_array_assert)
        : m_data(ei_constructor_without_unaligned_array_assert()) {}
    inline ei_matrix_storage(int, int, int) {}
    inline void swap(ei_matrix_storage &other) { std::swap(m_data, other.m_data); }
    inline static int rows(void) { return _Rows; }
    inline static int cols(void) { return _Cols; }
    inline void resize(int, int, int) {}
    inline const T *data() const { return m_data.array; }
    inline T *data() { return m_data.array; }
};

// dynamic-size matrix with fixed-size storage
template <typename T, int Size, int _Options>
class ei_matrix_storage<T, Size, Dynamic, Dynamic, _Options>
{
    ei_matrix_array<T, Size, _Options> m_data;
    int m_rows;
    int m_cols;

public:
    inline explicit ei_matrix_storage() : m_rows(0), m_cols(0) {}
    inline ei_matrix_storage(ei_constructor_without_unaligned_array_assert)
        : m_data(ei_constructor_without_unaligned_array_assert()), m_rows(0), m_cols(0) {}
    inline ei_matrix_storage(int, int rows, int cols) : m_rows(rows), m_cols(cols) {}
    inline ~ei_matrix_storage() {}
    inline void swap(ei_matrix_storage &other)
    {
        std::swap(m_data, other.m_data);
        std::swap(m_rows, other.m_rows);
        std::swap(m_cols, other.m_cols);
    }
    inline int rows(void) const { return m_rows; }
    inline int cols(void) const { return m_cols; }
    inline void resize(int, int rows, int cols)
    {
        m_rows = rows;
        m_cols = cols;
    }
    inline const T *data() const { return m_data.array; }
    inline T *data() { return m_data.array; }
};

// dynamic-size matrix with fixed-size storage and fixed width
template <typename T, int Size, int _Cols, int _Options>
class ei_matrix_storage<T, Size, Dynamic, _Cols, _Options>
{
    ei_matrix_array<T, Size, _Options> m_data;
    int m_rows;

public:
    inline explicit ei_matrix_storage() : m_rows(0) {}
    inline ei_matrix_storage(ei_constructor_without_unaligned_array_assert)
        : m_data(ei_constructor_without_unaligned_array_assert()), m_rows(0) {}
    inline ei_matrix_storage(int, int rows, int) : m_rows(rows) {}
    inline ~ei_matrix_storage() {}
    inline void swap(ei_matrix_storage &other)
    {
        std::swap(m_data, other.m_data);
        std::swap(m_rows, other.m_rows);
    }
    inline int rows(void) const { return m_rows; }
    inline int cols(void) const { return _Cols; }
    inline void resize(int /*size*/, int rows, int)
    {
        m_rows = rows;
    }
    inline const T *data() const { return m_data.array; }
    inline T *data() { return m_data.array; }
};

// dynamic-size matrix with fixed-size storage and fixed height
template <typename T, int Size, int _Rows, int _Options>
class ei_matrix_storage<T, Size, _Rows, Dynamic, _Options>
{
    ei_matrix_array<T, Size, _Options> m_data;
    int m_cols;

public:
    inline explicit ei_matrix_storage() : m_cols(0) {}
    inline ei_matrix_storage(ei_constructor_without_unaligned_array_assert)
        : m_data(ei_constructor_without_unaligned_array_assert()), m_cols(0) {}
    inline ei_matrix_storage(int, int, int cols) : m_cols(cols) {}
    inline ~ei_matrix_storage() {}
    inline void swap(ei_matrix_storage &other)
    {
        std::swap(m_data, other.m_data);
        std::swap(m_cols, other.m_cols);
    }
    inline int rows(void) const { return _Rows; }
    inline int cols(void) const { return m_cols; }
    inline void resize(int, int, int cols)
    {
        m_cols = cols;
    }
    inline const T *data() const { return m_data.array; }
    inline T *data() { return m_data.array; }
};

// purely dynamic matrix.
template <typename T, int _Options>
class ei_matrix_storage<T, Dynamic, Dynamic, Dynamic, _Options>
{
    T *m_data;
    int m_rows;
    int m_cols;

public:
    inline explicit ei_matrix_storage() : m_data(0), m_rows(0), m_cols(0) {}
    inline ei_matrix_storage(ei_constructor_without_unaligned_array_assert)
        : m_data(0), m_rows(0), m_cols(0) {}
    inline ei_matrix_storage(int size, int rows, int cols)
        : m_data(ei_aligned_new<T>(size)), m_rows(rows), m_cols(cols) {}
    inline ~ei_matrix_storage() { ei_aligned_delete(m_data, m_rows * m_cols); }
    inline void swap(ei_matrix_storage &other)
    {
        std::swap(m_data, other.m_data);
        std::swap(m_rows, other.m_rows);
        std::swap(m_cols, other.m_cols);
    }
    inline int rows(void) const { return m_rows; }
    inline int cols(void) const { return m_cols; }
    void resize(int size, int rows, int cols)
    {
        if (size != m_rows * m_cols)
        {
            ei_aligned_delete(m_data, m_rows * m_cols);
            m_data = ei_aligned_new<T>(size);
        }
        m_rows = rows;
        m_cols = cols;
    }
    inline const T *data() const { return m_data; }
    inline T *data() { return m_data; }
};

// matrix with dynamic width and fixed height (so that matrix has dynamic size).
template <typename T, int _Rows, int _Options>
class ei_matrix_storage<T, Dynamic, _Rows, Dynamic, _Options>
{
    T *m_data;
    int m_cols;

public:
    inline explicit ei_matrix_storage() : m_data(0), m_cols(0) {}
    inline ei_matrix_storage(ei_constructor_without_unaligned_array_assert) : m_data(0), m_cols(0) {}
    inline ei_matrix_storage(int size, int, int cols) : m_data(ei_aligned_new<T>(size)), m_cols(cols) {}
    inline ~ei_matrix_storage() { ei_aligned_delete(m_data, _Rows * m_cols); }
    inline void swap(ei_matrix_storage &other)
    {
        std::swap(m_data, other.m_data);
        std::swap(m_cols, other.m_cols);
    }
    inline static int rows(void) { return _Rows; }
    inline int cols(void) const { return m_cols; }
    void resize(int size, int, int cols)
    {
        if (size != _Rows * m_cols)
        {
            ei_aligned_delete(m_data, _Rows * m_cols);
            m_data = ei_aligned_new<T>(size);
        }
        m_cols = cols;
    }
    inline const T *data() const { return m_data; }
    inline T *data() { return m_data; }
};

// matrix with dynamic height and fixed width (so that matrix has dynamic size).
template <typename T, int _Cols, int _Options>
class ei_matrix_storage<T, Dynamic, Dynamic, _Cols, _Options>
{
    T *m_data;
    int m_rows;

public:
    inline explicit ei_matrix_storage() : m_data(0), m_rows(0) {}
    inline ei_matrix_storage(ei_constructor_without_unaligned_array_assert) : m_data(0), m_rows(0) {}
    inline ei_matrix_storage(int size, int rows, int) : m_data(ei_aligned_new<T>(size)), m_rows(rows) {}
    inline ~ei_matrix_storage() { ei_aligned_delete(m_data, _Cols * m_rows); }
    inline void swap(ei_matrix_storage &other)
    {
        std::swap(m_data, other.m_data);
        std::swap(m_rows, other.m_rows);
    }
    inline int rows(void) const { return m_rows; }
    inline static int cols(void) { return _Cols; }
    void resize(int size, int rows, int)
    {
        if (size != m_rows * _Cols)
        {
            ei_aligned_delete(m_data, _Cols * m_rows);
            m_data = ei_aligned_new<T>(size);
        }
        m_rows = rows;
    }
    inline const T *data() const { return m_data; }
    inline T *data() { return m_data; }
};

#endif // EIGEN_MATRIX_H
