#pragma once

template <typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
struct ei_traits<Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>>
{
    typedef _Scalar Scalar;
    enum
    {
        RowsAtCompileTime = _Rows,
        ColsAtCompileTime = _Cols,
        MaxRowsAtCompileTime = _MaxRows,
        MaxColsAtCompileTime = _MaxCols,
        Flags = ei_compute_matrix_flags<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>::ret,
        CoeffReadCost = NumTraits<Scalar>::ReadCost
    };
};

template <typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
class Matrix
    : public MatrixBase<Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>>
{
protected:
    //  ei_matrix_storage<Scalar, MaxSizeAtCompileTime, RowsAtCompileTime, ColsAtCompileTime, Options> m_storage;
};