/**
 * size_matrix_trimmer.h
 *
 * Trimmer which only outputs matrices which are the same size as the input
 * matrix.
 */
#pragma once
#include "matrix_trimmer.h"

#include "qv/int_matrix.h"

namespace qvtrim {

class SizeMatrixTrimmer : public MatrixTrimmer<cluster::IntMatrix> {

	public:
		SizeMatrixTrimmer(MatrixPtr& matrix, IPtr& in, OPtr& out);

	protected:
		virtual bool valid(const MatrixPtr& mat) const final;

	private:
		int rows_;
		int cols_;
};

}

