/**
 * matrix_trimmer.h
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
 * Trimmer which matches those matrices which share specific properties with a
 * provided comparison matrix.
 */
#pragma once

#include "trimmer.h"

#include "qv/stream_iterator.h"

namespace qvtrim {

template<class Matrix>
class MatrixTrimmer : public Trimmer {
	protected:
		typedef cluster::StreamIterator<Matrix> Iter;
		typedef std::shared_ptr<Matrix> MatrixPtr;

	public:
		virtual void run() final;

	protected:
		MatrixTrimmer(MatrixPtr& matrix, IPtr& in, OPtr& out)
			:	Trimmer(in, out),
				matrix_(matrix),
				iter_(*in_) {}

		MatrixPtr matrix_;

		virtual bool valid(const MatrixPtr& mat) const = 0;

	private:
		Iter iter_;

};
}
	
