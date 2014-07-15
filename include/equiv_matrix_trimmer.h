/**
 * equiv_matrix_trimmer.h
 *
 * Trimmer which only outputs matrices which are equivalent to the provided
 * matrix.
 */
#pragma once
#include "matrix_trimmer.h"

#include "qv/equiv_quiver_matrix.h"

namespace qvtrim {

class EquivMatrixTrimmer : public MatrixTrimmer<cluster::EquivQuiverMatrix> {

	public:
		EquivMatrixTrimmer(MatrixPtr& matrix, IPtr& in, OPtr& out);

	protected:
		virtual bool valid(const MatrixPtr& mat) const final;

};

}

