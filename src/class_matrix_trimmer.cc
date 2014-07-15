/**
 * class_matrix_trimmer.cc
 */
#include "class_matrix_trimmer.h"

namespace qvtrim {

ClassMatrixTrimmer::ClassMatrixTrimmer(MatrixPtr& matrix, IPtr& in,
		OPtr& out)
	: MatrixTrimmer(matrix, in, out),
		class_(*matrix) {}

bool ClassMatrixTrimmer::valid(const MatrixPtr& matrix) const {
	return class_.contains(matrix);
}

}

