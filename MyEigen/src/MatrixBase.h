#pragma once

/** \class MatrixBase
  *
  * \brief Base class for all matrices, vectors, and expressions
  *
  * This class is the base that is inherited by all matrix, vector, and expression
  * types. Most of the Eigen API is contained in this class. Other important classes for
  * the Eigen API are Matrix, Cwise, and PartialRedux.
  *
  * Note that some methods are defined in the \ref Array module.
  *
  * \param Derived is the derived type, e.g. a matrix type, or an expression, etc.
  *
  * When writing a function taking Eigen objects as argument, if you want your function
  * to take as argument any matrix, vector, or expression, just let it take a
  * MatrixBase argument. As an example, here is a function printFirstRow which, given
  * a matrix, vector, or expression \a x, prints the first row of \a x.
  *
  * \code
    template<typename Derived>
    void printFirstRow(const Eigen::MatrixBase<Derived>& x)
    {
      cout << x.row(0) << endl;
    }
  * \endcode
  *
  */
template <typename Derived>
class MatrixBase
{
public:
    class InnerIterator; //ToDO

    typedef typename ei_traits<Derived>::Scalar Scalar;
    typedef typename ei_packet_traits<Scalar>::type PacketScalar;

    enum
    {
        RowsAtCompileTime = ei_traits<Derived>::RowsAtCompileTime,
        ColsAtCompileTime = ei_traits<Derived>::ColsAtCompileTime,
        SizeAtCompileTime = (ei_size_at_compile_time<ei_traits<Derived>::RowsAtCompileTime,
                                                     ei_traits<Derived>::ColsAtCompileTime>::ret),
        MaxRowsAtCompileTime = ei_traits<Derived>::MaxRowsAtCompileTime,
        MaxColsAtCompileTime = ei_traits<Derived>::MaxColsAtCompileTime,
        MaxSizeAtCompileTime = (ei_size_at_compile_time<ei_traits<Derived>::MaxRowsAtCompileTime,
                                                        ei_traits<Derived>::MaxColsAtCompileTime>::ret),
        IsVectorAtCompileTime = ei_traits<Derived>::RowsAtCompileTime == 1 || ei_traits<Derived>::ColsAtCompileTime == 1,
        Flags = ei_traits<Derived>::Flags,
        /**< This stores expression \ref flags flags which may or may not be inherited by new expressions
          * constructed from this one. See the \ref flags "list of flags".
          */

        CoeffReadCost = ei_traits<Derived>::CoeffReadCost
        /**< This is a rough measure of how expensive it is to read one coefficient from
          * this expression.
          */
    };
};