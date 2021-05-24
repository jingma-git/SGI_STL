#pragma once

template <typename T>
struct ei_packet_traits
{
    typedef T type;
    enum
    {
        size = 1
    };
};

template <typename Scalar, int Rows, int Cols, int Options, int MaxRows, int MaxCols>
class ei_compute_matrix_flags
{
    enum
    {
        row_major_bit = Options & RowMajor ? RowMajorBit : 0,
        inner_max_size = row_major_bit ? MaxCols : MaxRows,
        is_big = inner_max_size == Dynamic,
        is_packet_size_multiple = (Cols * Rows) % ei_packet_traits<Scalar>::size == 0,
        aligned_bit = ((Options & AutoAlign) && (is_big || is_packet_size_multiple)) ? AlignedBit : 0,
        packet_access_bit = ei_packet_traits<Scalar>::size > 1 && aligned_bit ? PacketAccessBit : 0
    };

public:
    enum
    {
        ret = LinearAccessBit | DirectAccessBit | packet_access_bit | row_major_bit | aligned_bit
    };
};

template <int _Rows, int _Cols>
struct ei_size_at_compile_time
{
    enum
    {
        ret = (_Rows == Dynamic || _Cols == Dynamic) ? Dynamic : (_Rows * _Cols)
    };
};