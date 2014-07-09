/**
 * cycle_trimmer.cc
 */
#include "cycle_trimmer.h"

#include <unordered_set>

#include "qv/equiv_quiver_matrix.h"
#include "qv/equiv_underlying_graph.h"
#include "qv/oriented_cycle_info.h"
#include "qv/stream_iterator.h"

namespace qvtrim {

CycleTrimmer::CycleTrimmer(IStream& in, OStream& out)
	: Trimmer(in, out) {}

void CycleTrimmer::run() {
	typedef cluster::EquivQuiverMatrix Matrix;
	typedef std::shared_ptr<Matrix> MatrixPtr;
	typedef cluster::StreamIterator<Matrix> Iter;
	typedef cluster::OrientedCycleInfo Cycle;
	typedef cluster::EquivUnderlyingGraph Graph;

	std::unordered_set<MatrixPtr> set;
	std::unordered_set<Cycle> cycle_set;
	std::unordered_set<Graph> graph_set;
	std::string str;

	Iter iter(*in_);

	while(iter.has_next()) {
		MatrixPtr m = iter.next();
		if(set.insert(m).second) {
			if(cycle_set.emplace(*m).second) {
				/* Matrix successfully inserted so has not been seen before. */
				graph_set.emplace(*m);
				*out_ << *m << std::endl;
			} else if(graph_set.emplace(*m).second) {
				*out_ << *m << std::endl;
			}
		}
	}
}

}
