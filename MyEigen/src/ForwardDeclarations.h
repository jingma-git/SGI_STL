#pragma once

template <typename T>
struct ei_traits;

template <typename T>
struct NumTraits;

template <typename _Scalar, int _Rows, int _Cols,
          int _Options = EIGEN_DEFAULT_MATRIX_STORAGE_ORDER_OPTION | AutoAlign,
          int _MaxRows = _Rows, int _MaxCols = _Cols>
class Matrix;