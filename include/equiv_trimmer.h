/**
 * cycle_trimmer.h
 */
#pragma once

#include "trimmer.h"

namespace qvtrim {

class EquivTrimmer : public Trimmer {

	public:
		EquivTrimmer(IStream& in, OStream& out);
		EquivTrimmer(IPtr in, OPtr out) : Trimmer(in, out) {}

		virtual void run();

};
}
