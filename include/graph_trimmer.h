/**
 * graph_trimmer.h
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
/**
 * Trimmer which outputs matrices which have graphs that have not been seen
 * before.
 */
#pragma once

#include "trimmer.h"

#include <unordered_set>

#include "qv/equiv_quiver_matrix.h"
#include "qv/equiv_underlying_graph.h"
#include "qv/underlying_graph.h"

namespace qvtrim {

class GraphTrimmer : public __Trimmer<cluster::EquivQuiverMatrix> {

	public:
		GraphTrimmer(IStream& in, OStream& out) : __Trimmer(in, out) {}
		GraphTrimmer(IPtr in, OPtr out) : __Trimmer(in, out) {}
		virtual ~GraphTrimmer() = default;
	private:
		typedef cluster::EquivUnderlyingGraph EquivGraph;
		typedef cluster::UnderlyingGraph Graph;
		typedef std::shared_ptr<Graph> GPtr;
		typedef std::shared_ptr<EquivGraph> EGPtr;

		std::unordered_set<MatrixPtr> m_set_;
		std::unordered_set<GPtr> g_set_;
		std::unordered_set<EGPtr> eg_set_;

		virtual bool valid(MatrixPtr) final;
};
}
