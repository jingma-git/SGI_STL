#pragma once

const int Dynamic = -1;

/** \ingroup flags
  *
  * for a matrix, this means that the storage order is row-major.
  * If this bit is not set, the storage order is column-major.
  * For an expression, this determines the storage order of
  * the matrix created by evaluation of that expression. */
const unsigned int RowMajorBit = 0x1;

/** \ingroup flags
  *
  * Short version: means the expression might be vectorized
  *
  * Long version: means that the coefficients can be handled by packets
  * and start at a memory location whose alignment meets the requirements
  * of the present CPU architecture for optimized packet access. In the fixed-size
  * case, there is the additional condition that the total size of the coefficients
  * array is a multiple of the packet size, so that it is possible to access all the
  * coefficients by packets. In the dynamic-size case, there is no such condition
  * on the total size, so it might not be possible to access the few last coeffs
  * by packets.
  *
  * \note This bit can be set regardless of whether vectorization is actually enabled.
  *       To check for actual vectorizability, see \a ActualPacketAccessBit.
  */
const unsigned int PacketAccessBit = 0x8;

/** \ingroup flags
  *
  * Short version: means the expression can be seen as 1D vector.
  *
  * Long version: means that one can access the coefficients
  * of this expression by coeff(int), and coeffRef(int) in the case of a lvalue expression. These
  * index-based access methods are guaranteed
  * to not have to do any runtime computation of a (row, col)-pair from the index, so that it
  * is guaranteed that whenever it is available, index-based access is at least as fast as
  * (row,col)-based access. Expressions for which that isn't possible don't have the LinearAccessBit.
  *
  * If both PacketAccessBit and LinearAccessBit are set, then the
  * packets of this expression can be accessed by packet(int), and writePacket(int) in the case of a
  * lvalue expression.
  *
  * Typically, all vector expressions have the LinearAccessBit, but there is one exception:
  * Product expressions don't have it, because it would be troublesome for vectorization, even when the
  * Product is a vector expression. Thus, vector Product expressions allow index-based coefficient access but
  * not index-based packet access, so they don't have the LinearAccessBit.
  */
const unsigned int LinearAccessBit = 0x10;

/** \ingroup flags
  *
  * Means that the underlying array of coefficients can be directly accessed. This means two things.
  * First, references to the coefficients must be available through coeffRef(int, int). This rules out read-only
  * expressions whose coefficients are computed on demand by coeff(int, int). Second, the memory layout of the
  * array of coefficients must be exactly the natural one suggested by rows(), cols(), stride(), and the RowMajorBit.
  * This rules out expressions such as DiagonalCoeffs, whose coefficients, though referencable, do not have
  * such a regular memory layout.
  */
const unsigned int DirectAccessBit = 0x20;

/** \ingroup flags
  *
  * means the first coefficient packet is guaranteed to be aligned */
const unsigned int AlignedBit = 0x40;

enum
{
    ColMajor = 0,
    RowMajor = 0x1, // it is only a coincidence that this is equal to RowMajorBit -- don't rely on that
    /** \internal Don't require alignment for the matrix itself (the array of coefficients, if dynamically allocated, may still be
                requested to be aligned) */
    DontAlign = 0,
    /** \internal Align the matrix itself if it is vectorizable fixed-size */
    AutoAlign = 0x2
};