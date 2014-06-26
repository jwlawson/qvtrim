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
#include "qv/quiver_matrix.h"
#include "qv/underlying_graph.h"

using cluster::EquivQuiverMatrix;
using cluster::EquivUnderlyingGraph;
using cluster::OrientedCycleInfo;
using cluster::QuiverMatrix;
using cluster::UnderlyingGraph;

void equiv_trim(std::istream & istream, std::ostream & ostream) {
	typedef std::shared_ptr<EquivQuiverMatrix> eq_ptr;
	std::unordered_set<eq_ptr> set;
	std::string str;

	while(std::getline(istream, str)) {
		eq_ptr m = std::make_shared<EquivQuiverMatrix>(str);
		if(set.insert(m).second) {
			/* Matrix successfully inserted so has not been seen before. */
			ostream << *m << std::endl;
		}
	}
}

void graph_trim(std::istream & istream, std::ostream & ostream) {

	typedef std::shared_ptr<UnderlyingGraph> gr_ptr;
	typedef std::shared_ptr<EquivQuiverMatrix> eq_ptr;
	typedef std::shared_ptr<EquivUnderlyingGraph> greq_ptr;
	std::unordered_set<eq_ptr> set;
	std::unordered_set<gr_ptr> gr_set;
	std::unordered_set<greq_ptr> sm_set;
	std::string str;

	while(std::getline(istream, str)) {
		if(str[0] == '{') {
			eq_ptr m = std::make_shared<EquivQuiverMatrix>(str);
			gr_ptr graph = std::make_shared<UnderlyingGraph>(*m);
			greq_ptr egr = std::make_shared<EquivUnderlyingGraph>(*m);
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
	Check chk;
	std::string str;

	while(std::getline(in, str)) {
		if(str[0] == '{') {
			Matrix mat(str);
			chk.is_finite(mat);
			if(chk.last_new_class()) {
				out << mat << std::endl;
			}
		}
	}
}

void run_function(void (*f)(std::istream&, std::ostream&), 
		std::istream & istream = std::cin, 
		std::ostream & ostream = std::cout) {
	f(istream, ostream);
}

void try_function(bool cycle, bool equiv, bool graph, bool clazz,
		std::istream & istream = std::cin,
		std::ostream & ostream = std::cout) {
	if(cycle) {
		run_function(cycle_trim, istream, ostream);
	} else if (equiv) {
		run_function(equiv_trim, istream, ostream);
	} else if (graph) {
		run_function(graph_trim, istream, ostream);
	} else if (clazz) {
		run_function(class_trim, istream, ostream);
	}
}

void try_function_out_only(bool cycle, bool equiv, bool graph, bool clazz,
		std::ostream & ostream = std::cout) {
	if(cycle) {
		run_function(cycle_trim, std::cin, ostream);
	} else if (equiv) {
		run_function(equiv_trim, std::cin, ostream);
	} else if (graph) {
		run_function(graph_trim, std::cin, ostream);
	} else if (clazz) {
		run_function(class_trim, std::cin, ostream);
	}
}

int run(std::string sfile, std::string ofile, bool cycle, bool equiv,
		bool graph, bool clazz) {
	if(sfile.empty() && ofile.empty()) {
		try_function(cycle, equiv, graph, clazz);
	} else if (sfile.empty()){
		std::ofstream file_out;
		file_out.open(ofile);
		if(!file_out.is_open()) {
			std::cout << "Error opening file "<< ofile << std::endl;
			return 1;
		}
		try_function_out_only(cycle, equiv, graph, clazz, file_out);
		file_out.close();
	} else if (ofile.empty()) {

		std::ifstream file;
		file.open(sfile);
		if(!file.is_open()) {
			std::cout << "Error opening file "<< sfile << std::endl;
			return 1;
		}
		try_function(cycle, equiv, graph, clazz, file);
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
		try_function(cycle, equiv, graph, clazz, file, file_out);
		file.close();
		file_out.close();
	}
	return 0;
}

void usage() {
	std::cout << "qvtrim -cegl [-i input] [-o output]" << std::endl;
	std::cout << "  -c Only show matrices with different oriented cycles " << std::endl;
	std::cout << "  -e Only show matrices which are equivalent up to permutation" << std::endl;
	std::cout << "  -g Only show matrices with different underlying graphs" << std::endl;
	std::cout << "  -l Only show matrices from different mutation classes" << std::endl;
	std::cout << "  -i Specify input file of matrices, if absent stdin is used." << std::endl;
	std::cout << "  -o Specify output or use stdout" << std::endl;
}

int main(int argc, char *argv[]) {
	bool equiv = false;
	bool graph = false;
	bool cycle = false;
	bool clazz = false;
	std::string ifile;
	std::string ofile;
	int c;

	while ((c = getopt (argc, argv, "cegli:o:")) != -1) {
		switch (c){
			case 'c':
				cycle = true;
				break;
			case 'e':
				equiv = true;
				break;
			case 'g':
				graph = true;
				break;
			case 'l':
				clazz = true;
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

	return run(ifile, ofile, cycle, equiv, graph, clazz);
}

