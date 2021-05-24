#pragma once

#define EIGEN_VECTORIZE_SSE

//---std library-----------
#include <cstdlib>
#include <cmath>
#include <complex>
#include <cassert>
#include <functional>
#include <iostream>
#include <cstring>
#include <string>
#include <limits>

//---globals-------------
#include "Macros.h"
#include "Constants.h"
#include "ForwardDeclarations.h"
#include "XprHelper.h"
#include "Memory.h"

#include "NumTraits.h"

//---interface-----------------
#include "MatrixBase.h"

//---implementations-----------
#include "MatrixStorage.h"
#include "Matrix.h"