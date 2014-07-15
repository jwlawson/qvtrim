/**
 * trimmer_builder.cc
 */
#include "trimmer_builder.h"

#include <iostream>

#include "class_matrix_trimmer.h"
#include "class_trimmer.h"
#include "cycle_matrix_trimmer.h"
#include "cycle_trimmer.h"
#include "equiv_matrix_trimmer.h"
#include "equiv_trimmer.h"
#include "graph_matrix_trimmer.h"
#include "graph_trimmer.h"
#include "size_matrix_trimmer.h"
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

void TrimmerBuilder::matrix(const std::string& mat) {
	matrix_ = mat;
}

std::shared_ptr<Trimmer> TrimmerBuilder::build() {
	if(!validate()) {
		// TODO Panic!
	}
	if(matrix_.empty()) {
		/* Just a regular trimmer needed */
		return trimmer();
	}
	/* Otherwise need a matrix trimmer */
	return matrix_trimmer();
}

std::shared_ptr<Trimmer> TrimmerBuilder::trimmer() {
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

std::shared_ptr<Trimmer> TrimmerBuilder::matrix_trimmer() {
	typedef std::shared_ptr<cluster::IntMatrix> IMatrix;
	typedef std::shared_ptr<cluster::EquivQuiverMatrix> EMatrix;
	IMatrix m1 = std::make_shared<cluster::IntMatrix>(matrix_);
	switch(func_) {
		case CYCLE:
			return std::make_shared<CycleMatrixTrimmer>(m1, in_, out_);
			break;
		case EQUIV:
			{ /* Braces keep the scope right. */
			EMatrix m2 = std::make_shared<cluster::EquivQuiverMatrix>(*m1);
			return std::make_shared<EquivMatrixTrimmer>(m2, in_, out_);
			break;
			}
		case GRAPH:
			return std::make_shared<GraphMatrixTrimmer>(m1, in_, out_);
			break;
		case CLASS:
			{ /* Braces keep the scope right. */
			EMatrix m2 = std::make_shared<cluster::EquivQuiverMatrix>(*m1);
			return std::make_shared<ClassMatrixTrimmer>(m2, in_, out_);
			break;
			}
		case SIZE:
			return std::make_shared<SizeMatrixTrimmer>(m1, in_, out_);
			break;
		case ZERO:
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
