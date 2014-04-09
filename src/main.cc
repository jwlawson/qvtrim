/*
 * main.cc
 */

#include <unordered_set>
#include <memory>
#include <iostream>
#include <fstream>
#include "quiver_matrix.h"
#include "equiv_quiver_matrix.h"
#include "underlying_graph.h"
#include <unistd.h>

using cluster::EquivQuiverMatrix;
using cluster::QuiverMatrix;
using cluster::UnderlyingGraph;

void graph_trim(std::istream & istream, std::ostream & ostream) {
	typedef std::shared_ptr<UnderlyingGraph> gr_ptr;
	std::unordered_set<gr_ptr> set;
	std::string str;

	while(std::getline(istream, str)) {
		QuiverMatrix qv(str);
		gr_ptr m = std::make_shared<UnderlyingGraph>(qv);
		if(set.insert(m).second) {
			/* Matrix successfully emplaced, so has not been seen before. */
			ostream << m << std::endl;
		}
	}
}

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

void trim(std::istream & istream, std::ostream & ostream) {

	typedef std::shared_ptr<UnderlyingGraph> gr_ptr;
	typedef std::shared_ptr<EquivQuiverMatrix> eq_ptr;
	std::unordered_set<eq_ptr> set;
	std::unordered_set<gr_ptr> gr_set;
	std::unordered_set<gr_ptr> sm_set;
	std::string str;

	while(std::getline(istream, str)) {
		eq_ptr m = std::make_shared<EquivQuiverMatrix>(str);
		gr_ptr graph = std::make_shared<UnderlyingGraph>(*m);
		if(gr_set.insert(graph).second
				&& set.insert(m).second
				&& sm_set.insert(graph).second ) {
			/* Matrix successfully inserted so has not been seen before. */
			ostream << *m << std::endl;
		}
	}
}

void run_function(void (*f)(std::istream&, std::ostream&), 
		std::istream & istream = std::cin, 
		std::ostream & ostream = std::cout) {
	f(istream, ostream);
}

void try_function(bool equiv, bool graph, std::istream & istream = std::cin) {
	if(equiv && graph) {
		run_function(trim, istream);
	} else if (equiv) {
		run_function(equiv_trim, istream);
	}else if (graph) {
		run_function(graph_trim, istream);
	}
}


int run(std::string sfile, bool equiv, bool graph) {
	if(sfile.empty()) {
		try_function(equiv, graph);
	} else {
		/* Using file provided. */
		std::ifstream file;
		file.open(sfile);
		if(!file.is_open()) {
			std::cout << "Error opening file "<< sfile << std::endl;
			return 1;
		}
		try_function(equiv, graph, file);
		file.close();
	}
	return 0;
}

int main(int argc, char *argv[]) {
	bool equiv = true;
	bool graph = false;
	std::string ifile;
	int c;

	while ((c = getopt (argc, argv, "egi:")) != -1) {
		switch (c){
			case 'e':
				equiv = true;
				break;
			case 'g':
				graph = true;
				break;
			case 'i':
				ifile = optarg;
				break;
			case '?':
				return 1;
			default:
				return 2;
		}
	}

	return run(ifile, equiv, graph);
}

