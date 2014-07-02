/*
 * main.cc
 */
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <unordered_set>

#include "qv/equiv_quiver_matrix.h"
#include "qv/equiv_underlying_graph.h"
#include "qv/mass_finite_check.h"
#include "qv/oriented_cycle_info.h"
#include "qv/stream_iterator.h"
#include "qv/quiver_matrix.h"
#include "qv/underlying_graph.h"

const int k_unset = -1;
const int k_equiv = 1;
const int k_graph = 2;
const int k_cycle = 3;
const int k_class = 4;
const int k_zero = 5;

void equiv_trim(std::istream & istream, std::ostream & ostream) {
	typedef cluster::EquivQuiverMatrix Matrix;
	typedef std::shared_ptr<Matrix> eq_ptr;
	std::unordered_set<eq_ptr> set;
	std::string str;

	while(std::getline(istream, str)) {
		eq_ptr m = std::make_shared<Matrix>(str);
		if(set.insert(m).second) {
			/* Matrix successfully inserted so has not been seen before. */
			ostream << *m << std::endl;
		}
	}
}

void graph_trim(std::istream & istream, std::ostream & ostream) {

	typedef cluster::EquivQuiverMatrix Matrix;
	typedef cluster::EquivUnderlyingGraph EquivGraph;
	typedef cluster::UnderlyingGraph Graph;
	typedef std::shared_ptr<Graph> gr_ptr;
	typedef std::shared_ptr<Matrix> eq_ptr;
	typedef std::shared_ptr<EquivGraph> greq_ptr;
	std::unordered_set<eq_ptr> set;
	std::unordered_set<gr_ptr> gr_set;
	std::unordered_set<greq_ptr> sm_set;
	std::string str;

	while(std::getline(istream, str)) {
		if(str[0] == '{') {
			eq_ptr m = std::make_shared<Matrix>(str);
			gr_ptr graph = std::make_shared<Graph>(*m);
			greq_ptr egr = std::make_shared<EquivGraph>(*m);
			if(gr_set.insert(graph).second
					&& set.insert(m).second
					&& sm_set.insert(egr).second ) {
				/* Matrix successfully inserted so has not been seen before. */
				ostream << *m << std::endl;
			}
		}
	}
}

void cycle_trim(std::istream & istream, std::ostream & ostream) {

	typedef cluster::EquivQuiverMatrix Matrix;
	typedef std::shared_ptr<Matrix> MatrixPtr;
	typedef cluster::OrientedCycleInfo Cycle;
	typedef cluster::EquivUnderlyingGraph Graph;

	std::unordered_set<MatrixPtr> set;
	std::unordered_set<Cycle> cycle_set;
	std::unordered_set<Graph> graph_set;
	std::string str;

	while(std::getline(istream, str)) {
		if(str[0] == '{') {
			MatrixPtr m = std::make_shared<Matrix>(str);
			if(set.insert(m).second) {
				if(cycle_set.emplace(*m).second) {
					/* Matrix successfully inserted so has not been seen before. */
					graph_set.emplace(*m);
					ostream << *m << std::endl;
				} else if(graph_set.emplace(*m).second) {
					ostream << *m << std::endl;
				}
			}
		}
	}
}

void class_trim(std::istream& in, std::ostream& out) {
	typedef cluster::MassFiniteCheck Check;
	typedef cluster::EquivQuiverMatrix Matrix;
	typedef cluster::StreamIterator<Matrix> Iter;
	Check chk;

	Iter iter(in);
	while(iter.has_next()) {
		Matrix mat = *iter.next();
		chk.is_finite(mat);
		if(chk.last_new_class()) {
			out << mat << std::endl;
		}
	}
}

void zero_row_trim(std::istream& in, std::ostream& out) {
	typedef cluster::IntMatrix Matrix;
	typedef std::shared_ptr<Matrix> MPtr;
	typedef cluster::StreamIterator<Matrix> Iter;

	Iter iter(in);
	while(iter.has_next()) {
		MPtr p = iter.next();
		if(p->zero_row() == -1) {
			out << *p << std::endl;
		}
	}
}

void run_function(void (*f)(std::istream&, std::ostream&), 
		std::istream & istream = std::cin, 
		std::ostream & ostream = std::cout) {
	f(istream, ostream);
}

void try_function(int func,
		std::istream & istream = std::cin,
		std::ostream & ostream = std::cout) {
	if(func == k_cycle) {
		run_function(cycle_trim, istream, ostream);
	} else if (func == k_equiv) {
		run_function(equiv_trim, istream, ostream);
	} else if (func == k_graph) {
		run_function(graph_trim, istream, ostream);
	} else if (func == k_class) {
		run_function(class_trim, istream, ostream);
	} else if (func == k_zero) {
		run_function(zero_row_trim, istream, ostream);
	}
}

void try_function_out_only(int func,
		std::ostream & ostream = std::cout) {
	if(func == k_cycle) {
		run_function(cycle_trim, std::cin, ostream);
	} else if (func == k_equiv) {
		run_function(equiv_trim, std::cin, ostream);
	} else if (func == k_graph) {
		run_function(graph_trim, std::cin, ostream);
	} else if (func == k_class) {
		run_function(class_trim, std::cin, ostream);
	} else if (func == k_zero) {
		run_function(zero_row_trim, std::cin, ostream);
	}
}

int run(std::string sfile, std::string ofile, int func) {
	if(sfile.empty() && ofile.empty()) {
		try_function(func);
	} else if (sfile.empty()){
		std::ofstream file_out;
		file_out.open(ofile);
		if(!file_out.is_open()) {
			std::cout << "Error opening file "<< ofile << std::endl;
			return 1;
		}
		try_function_out_only(func, file_out);
		file_out.close();
	} else if (ofile.empty()) {

		std::ifstream file;
		file.open(sfile);
		if(!file.is_open()) {
			std::cout << "Error opening file "<< sfile << std::endl;
			return 1;
		}
		try_function(func, file);
		file.close();
	} else {
		/* Using file provided. */
		std::ifstream file;
		file.open(sfile);
		if(!file.is_open()) {
			std::cout << "Error opening file "<< sfile << std::endl;
			return 1;
		}
		std::ofstream file_out;
		file_out.open(ofile);
		if(!file_out.is_open()) {
			std::cout << "Error opening file "<< ofile << std::endl;
			return 1;
		}
		try_function(func, file, file_out);
		file.close();
		file_out.close();
	}
	return 0;
}

void usage() {
	std::cout << "qvtrim -ceglz [-i input] [-o output]" << std::endl;
	std::cout << "  -c Only show matrices with different oriented cycles " << std::endl;
	std::cout << "  -e Only show matrices which are equivalent up to permutation" << std::endl;
	std::cout << "  -g Only show matrices with different underlying graphs" << std::endl;
	std::cout << "  -l Only show matrices from different mutation classes" << std::endl;
	std::cout << "  -z Only show matrices which do not contain an all zero row" << std::endl;
	std::cout << "  -i Specify input file of matrices, if absent stdin is used." << std::endl;
	std::cout << "  -o Specify output or use stdout" << std::endl;
}

int main(int argc, char *argv[]) {
	int func = k_unset;
	std::string ifile;
	std::string ofile;
	int c;

	while ((c = getopt (argc, argv, "ceglzi:o:")) != -1) {
		switch (c){
			case 'c':
				func = k_cycle;
				break;
			case 'e':
				func = k_equiv;
				break;
			case 'g':
				func = k_graph;
				break;
			case 'l':
				func = k_class;
				break;
			case 'z':
				func = k_zero;
				break;
			case 'i':
				ifile = optarg;
				break;
			case 'o':
				ofile = optarg;
				break;
			case '?':
				usage();
				return 1;
			default:
				usage();
				return 2;
		}
	}

	if(func == k_unset) {
		usage();
		std::cout << "Specify an option" << std::endl;
		return 0;
	} else {
		return run(ifile, ofile, func);
	}
}

