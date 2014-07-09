/**
 * trimmer_builder.cc
 */
#include "trimmer_builder.h"

#include <iostream>

#include "class_trimmer.h"
#include "cycle_trimmer.h"
#include "equiv_trimmer.h"
#include "graph_trimmer.h"
#include "size_trimmer.h"
#include "zero_trimmer.h"

namespace qvtrim {

void TrimmerBuilder::input_stream(std::istream& in) {
	in_ = IPtr(&in, NullDeleter());
}

void TrimmerBuilder::output_stream(std::ostream& out) {
	out_ = OPtr(&out, NullDeleter());
}

void TrimmerBuilder::function(enum Function func) {
	func_ = func;
}

void TrimmerBuilder::size(int size) {
	size_ = size;
}

std::shared_ptr<Trimmer> TrimmerBuilder::build() {
	if(!validate()) {
		// TODO Panic!
	}
	switch(func_) {
		case CYCLE:
			return std::make_shared<CycleTrimmer>(in_, out_);
			break;
		case EQUIV:
			return std::make_shared<EquivTrimmer>(in_, out_);
			break;
		case GRAPH:
			return std::make_shared<GraphTrimmer>(in_, out_);
			break;
		case CLASS:
			return std::make_shared<ClassTrimmer>(in_, out_);
			break;
		case SIZE:
			return std::make_shared<SizeTrimmer>(size_, in_, out_);
			break;
		case ZERO:
			return std::make_shared<ZeroTrimmer>(in_, out_);
			break;
		case UNSET:
			// Should never happen
			break;
	}
	return nullptr;
}

bool TrimmerBuilder::validate() {
	if(func_ == UNSET) {
		return false;
	}
	if(func_ == SIZE && size_ < 0) {
		return false;
	}
	if(!in_) {
		input_stream(std::cin);
	}
	if(!out_) {
		output_stream(std::cout);
	}
	return true;
}

}
