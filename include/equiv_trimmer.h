/**
 * equiv_trimmer.h
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
 * Trimmer which outputs matrices not equivalent to any seen before.
 */
#pragma once

#include "trimmer.h"

#include <unordered_set>

#include "qv/equiv_quiver_matrix.h"

namespace qvtrim {

class EquivTrimmer : public __Trimmer<cluster::EquivQuiverMatrix> {

	public:
		EquivTrimmer(IStream& in, OStream& out);
		EquivTrimmer(IPtr in, OPtr out) : __Trimmer(in, out) {}
		virtual ~EquivTrimmer() = default;
	private:
		std::unordered_set<MatrixPtr> set_;

		virtual bool valid(MatrixPtr) final;
};
}
