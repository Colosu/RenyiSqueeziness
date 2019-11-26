/*
 * Checkups.cpp
 *
 *  Created on: 29 jul. 2017
 *      Author: colosu
 */

#include <fst/fstlib.h>
#include "Graph.h"
#include "Checkups.h"
#include "Operations.h"

namespace fst {

Checkups::Checkups() {

}

Checkups::~Checkups() {

}

bool Checkups::are_equivalent(Graph* g1, Graph* g2) {

	if (Equivalent(*(g1->getTransducer()->Copy()), *(g2->getTransducer()->Copy()))) {
		cout << "are equal" << endl;
		return true;
	} else {
		return false;
	}
}

bool Checkups::is_valid(Graph* g) {

	if (g->getTransducer()->Properties(kIDeterministic, true) == kIDeterministic) {
		if (g->getTransducer()->Properties(kAccessible, true) == kAccessible) {
			if (g->getTransducer()->Properties(kCoAccessible, true) == kCoAccessible) {
				return true;
			}
		}
	}
	return false;
}

bool Checkups::is_validMutation(Graph* g) {

	if (g->getTransducer()->Properties(kIDeterministic, true) == kIDeterministic) {
		//if (g->getTransducer()->Properties(kCoAccessible, true) == kCoAccessible) {
			return true;
		//}
	}
	return false;
}

} /* namespace std */
