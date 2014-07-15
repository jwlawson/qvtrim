/**
 * graph_matrix_trimmer.h
 *
 * Trimmer which only outputs matrices which are the same size as the input
 * matrix.
 */
#pragma once
#include "matrix_trimmer.h"

#include "qv/int_matrix.h"
#include "qv/equiv_underlying_graph.h"

namespace qvtrim {

class GraphMatrixTrimmer : public MatrixTrimmer<cluster::IntMatrix> {

	private:
		typedef cluster::EquivUnderlyingGraph Graph;

	public:
		GraphMatrixTrimmer(MatrixPtr& matrix, IPtr& in, OPtr& out);

	protected:
		virtual bool valid(const MatrixPtr& mat) const final;

	private:
		Graph graph_;
};

}

