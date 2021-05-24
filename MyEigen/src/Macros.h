#pragma once

/* EIGEN_ALIGN_128 forces data to be 16-byte aligned, EVEN if vectorization (EIGEN_VECTORIZE) is disabled,
 * so that vectorization doesn't affect binary compatibility.
 *
 * If we made alignment depend on whether or not EIGEN_VECTORIZE is defined, it would be impossible to link
 * vectorized and non-vectorized code.
 */
#if (defined __GNUC__)
#define EIGEN_ALIGN_128 __attribute__((aligned(16)))
#elif (defined _MSC_VER)
#define EIGEN_ALIGN_128 __declspec(align(16))
#else
#define EIGEN_ALIGN_128
#endif

#ifdef EIGEN_DEFAULT_TO_ROW_MAJOR
#define EIGEN_DEFAULT_MATRIX_STORAGE_ORDER_OPTION RowMajor
#else
#define EIGEN_DEFAULT_MATRIX_STORAGE_ORDER_OPTION ColMajor
#endif

#define EIGEN_INHERIT_ASSIGNMENT_OPERATOR(Derived, Op)                        \
    template <typename OtherDerived>                                          \
    inline Derived &operator Op(const Eigen::MatrixBase<OtherDerived> &other) \
    {                                                                         \
        return Eigen::MatrixBase<Derived>::operator Op(other.derived());      \
    }
