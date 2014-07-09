/**
 * zero_trimmer.h
 */
#pragma once

#include "trimmer.h"

namespace qvtrim {

class ZeroTrimmer : public Trimmer {

	public:
		ZeroTrimmer(IStream& in, OStream& out);
		ZeroTrimmer(IPtr in, OPtr out) : Trimmer(in, out) {}

		virtual void run();

};
}
