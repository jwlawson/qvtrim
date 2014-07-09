/**
 * class_trimmer.h
 */
#pragma once

#include "trimmer.h"

namespace qvtrim {

class ClassTrimmer : public Trimmer {

	public:
		ClassTrimmer(IStream& in, OStream& out);
		ClassTrimmer(IPtr in, OPtr out)
			: Trimmer(in, out) {}

		virtual void run();

};
}

