/**
 * equiv_trimmer.cc
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
#include "equiv_trimmer.h"

#include <unordered_set>

#include "qv/equiv_quiver_matrix.h"
#include "qv/equiv_underlying_graph.h"
#include "qv/oriented_cycle_info.h"
#include "qv/stream_iterator.h"

namespace qvtrim {

EquivTrimmer::EquivTrimmer(IStream& in, OStream& out)
	: Trimmer(in, out) {}

void EquivTrimmer::run() {
	typedef cluster::EquivQuiverMatrix Matrix;
	typedef std::shared_ptr<Matrix> MatrixPtr;
	typedef cluster::StreamIterator<Matrix> Iter;

	std::unordered_set<MatrixPtr> set;

	Iter iter(*in_);

	while(iter.has_next()) {
		MatrixPtr m = iter.next();
		if(set.insert(m).second) {
			/* Matrix successfully inserted so has not been seen before. */
			*out_ << *m << std::endl;
		}
	}
}

}

