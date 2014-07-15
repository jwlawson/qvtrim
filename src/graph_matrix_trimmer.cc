/**
 * graph_matrix_trimmer.cc
 */
#include "graph_matrix_trimmer.h"

namespace qvtrim {

GraphMatrixTrimmer::GraphMatrixTrimmer(MatrixPtr& matrix, IPtr& in,
		OPtr& out)
	: MatrixTrimmer(matrix, in, out),
		graph_(*matrix) {}

bool GraphMatrixTrimmer::valid(const MatrixPtr& matrix) const {
	Graph g(*matrix);
	return graph_.equals(g);
}

}

