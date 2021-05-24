// https://eigen.tuxfamily.org/dox/TopicFunctionTakingEigenTypes.html

#include <iostream>
#include <Eigen/Eigen>

using namespace std;
using namespace Eigen;

template <class Derived, class OtherDerived>
void conv(const MatrixBase<Derived> &x, const MatrixBase<Derived> &y,
          MatrixBase<OtherDerived> const &z) // const reference
{
    typedef typename Derived::Scalar Scalar;
    typedef typename OtherDerived::Scalar OutScalar;
    typedef typename internal::plain_row_type<Derived>::type RowVectorType;

    const Scalar num_observations = static_cast<Scalar>(x.rows());
    RowVectorType x_mean = x.colwise().sum() / num_observations;
    RowVectorType y_mean = y.colwise().sum() / num_observations;
    // cast constness away
    const_cast<MatrixBase<OtherDerived> &>(z) = (x.rowwise() - x_mean).transpose() * (y.rowwise() - y_mean) / num_observations;
}

void testFloat()
{
    Matrix3f x = Matrix3f::Random();
    Matrix3f y = Matrix3f::Random();
    MatrixXf z = MatrixXf::Zero(3, 6);
    cout << "z" << endl;
    cout << z << endl;
    conv(x, y, z.block(0, 0, 3, 3));
    cout << "z" << endl;
    cout << z << endl;
}

void testDouble()
{
    Matrix3d x = Matrix3d::Random();
    Matrix3d y = Matrix3d::Random();
    MatrixXd z = MatrixXd::Zero(3, 6);
    cout << "z" << endl;
    cout << z << endl;
    conv(x, y, z.block(0, 0, 3, 3));
    cout << "z" << endl;
    cout << z << endl;
}

void testWrongMatrixSize()
{
    Matrix3d x = Matrix3d::Random();
    Matrix3d y = Matrix3d::Random();
    MatrixXd z;
    conv(x, y, z);
    cout << "z" << endl;
    cout << z << endl;
}
int main()
{
    // testFloat();
    // testDouble();
    testWrongMatrixSize();
    return 0;
}