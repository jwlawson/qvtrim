/**
 * sinksource_trimmer.h
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
 * Trims matrices by only outputting those not sink-source equivalent to any
 * seen before.
 */
#pragma once

#include "trimmer.h"

#include <unordered_set>

#include "qv/equiv_quiver_matrix.h"
#include "qv/move_class_loader.h"

namespace qvtrim {
class SinkSourceTrimmer : public __Trimmer<cluster::EquivQuiverMatrix> {

	public:
		SinkSourceTrimmer(IStream& in, OStream& out);
		SinkSourceTrimmer(IPtr in, OPtr out)	: __Trimmer(in, out) {}
		virtual ~SinkSourceTrimmer() = default;

	private:
		typedef cluster::MoveClassLoader Loader;
		typedef std::unordered_set<MatrixPtr> Set;

		Set _set;

		virtual bool valid(MatrixPtr) final;
};
}

