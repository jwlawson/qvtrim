/**
 * matrix_trimmer.h
 *
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
	
