/**
 * size_trimmer.h
 */
#pragma once

#include "trimmer.h"

namespace qvtrim {

class SizeTrimmer : public Trimmer {

	public:
		SizeTrimmer(int size, IStream& in, OStream& out);
		SizeTrimmer(int size, IPtr in, OPtr out)
			: Trimmer(in, out), size_(size) {}

		virtual void run();

	private:
		int size_;

};
}
