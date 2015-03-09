/**
 * cycle_trimmer.h
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
 * Trimmer which outputs only those matrices with cycles which are not
 * equivalent to any seen before.
 */
#pragma once

#include "trimmer.h"

#include <unordered_set>

#include "qv/equiv_quiver_matrix.h"
#include "qv/equiv_underlying_graph.h"
#include "qv/oriented_cycle_info.h"

namespace qvtrim {

class CycleTrimmer : public __Trimmer<cluster::EquivQuiverMatrix> {

	public:
		CycleTrimmer(IStream& in, OStream& out);
		CycleTrimmer(IPtr in, OPtr out) : __Trimmer(in, out) {}
		virtual ~CycleTrimmer() = default;
	private:
		typedef cluster::OrientedCycleInfo Cycle;
		typedef cluster::EquivUnderlyingGraph Graph;

		std::unordered_set<MatrixPtr> set_;
		std::unordered_set<Cycle> cycle_set_;
		std::unordered_set<Graph> graph_set_;

		virtual bool valid(MatrixPtr) final;
};
}
