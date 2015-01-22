/**
 * graph_trimmer.cc
 * Copyright 2014-2015 John Lawson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "graph_trimmer.h"

#include <unordered_set>

#include "qv/equiv_quiver_matrix.h"
#include "qv/equiv_underlying_graph.h"
#include "qv/stream_iterator.h"
#include "qv/underlying_graph.h"

namespace qvtrim {

GraphTrimmer::GraphTrimmer(IStream& in, OStream& out)
	: Trimmer(in, out) {}

void GraphTrimmer::run() {
	typedef cluster::EquivQuiverMatrix Matrix;
	typedef cluster::StreamIterator<Matrix> Iter;
	typedef cluster::EquivUnderlyingGraph EquivGraph;
	typedef cluster::UnderlyingGraph Graph;

	typedef std::shared_ptr<Matrix> MatrixPtr;
	typedef std::shared_ptr<Graph> GPtr;
	typedef std::shared_ptr<EquivGraph> EGPtr;

	std::unordered_set<MatrixPtr> m_set;
	std::unordered_set<GPtr> g_set;
	std::unordered_set<EGPtr> eg_set;

	Iter iter(*in_);

	while(iter.has_next()) {
		MatrixPtr p = iter.next();
		GPtr g = std::make_shared<Graph>(*p);
		EGPtr e = std::make_shared<EquivGraph>(*p);
		if(m_set.emplace(p).second
				&& g_set.insert(g).second
				&& eg_set.insert(e).second) {
			*out_ << *p << std::endl;
		}
	}
}

}

