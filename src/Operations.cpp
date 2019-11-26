/*
 * Operations.cpp
 *
 *  Created on: 29 jul. 2017
 *      Author: colosu
 */

#include <string>
#include <cmath>
#include <pthread.h>
#include <semaphore.h>
#include <fst/fstlib.h>
#include "Graph.h"
#include "Operations.h"

namespace fst {

Operations::Operations() {

}

Operations::~Operations() {

}

void Operations::minimization(Graph* g) {
	Minimize(g->getTransducer());
}

StdMutableFst* Operations::product(Graph* g1, Graph* g2) {
	//TODO: Complete it.
	StdMutableFst* a1 = g1->getTransducer()->Copy();
	StdMutableFst* a2 = g2->getTransducer()->Copy();
	//StdMutableFst* prod = Times(a1, a2);
	delete a1;
	delete a2;
	return NULL; //prod;
}

void Operations::Squeeziness(Graph* g, int length, double Sq[], int I) {

	if (length <= 0) {
		return;
	}

	int* inputs = new int;
	*inputs = 0;
	Sq[I] = 0;
	std::map<string, int>* mapOtoI = new std::map<string, int>;
	sem_t* sem = new sem_t;
	args* argum = new args;
	argum->fsm = g->getTransducer();
	argum->qid = g->getTransducer()->Start();
	argum->iter = 0;
	argum->length = length;
	argum->inputs = inputs;
	argum->mapOtoI = mapOtoI;
	argum->output = "";

	SqueezinessAux(argum);

	for (std::map<string, int>::iterator it = mapOtoI->begin(); it != mapOtoI->end(); it++) {
		Sq[I] += it->second * std::log2((long double)it->second);
	}
	Sq[I] = Sq[I]/(*inputs);
	delete inputs;
	delete sem;
	delete argum;
}

void Operations::SqueezinessAndPColl(Graph* g, int length, double &PColl, double &Sq1, double &Sq2, double &Sq3, double &Sq4, double &Sq5, double &Sq6, double &Sq7, double &Sq8, double &Sq9, double &Sq10) {

	if (length <= 0) {
		return;
	}

	int* inputs = new int;
	*inputs = 0;
	double TPColl = 0;
	double TSq1 = 0;
	double TSq2 = 0;
	double TSq3 = 0;
	double TSq4 = 0;
	double TSq5 = 0;
	double TSq6 = 0;
	double TSq7 = 0;
	double TSq8 = 0;
	double TSq9 = 0;
	double TSq10 = 0;
	double a1 = 3.1; //Done with: 0, 1, 20, 2.1, 3.1
	double a2 = M_PI; //Done with: 0.1, 2, 30, 2.2, PI
	double a3 = 3.2; //Done with: 0.2, 3, 40, 2.3, 3.2
	double a4 = 3.3; //Done with: 0.3, 4, 50, 2.4, 3.3
	double a5 = 3.4; //Done with: 0.4, 5, 60, 2.5, 3.4
	double a6 = 3.5; //Done with: 0.5, 6, 70, 2.6, 3.5
	double a7 = 3.6; //Done with: 0.6, 7, 80, 2.7, 3.6
	double a8 = 3.7; //Done with: 0.7, 8, 90, e, 3.7
	double a9 = 3.8; //Done with: 0.8, 9, 100, 2.8, 3.8
	double a10 = 3.9; //Done with: 0.9, 10, \infty, 2.9, 3.9

	sem_t sem;
	sem_init(&sem, 0, 1);
	std::map<string, int>* mapOtoI = new std::map<string, int>;
	args* argum = new args;
	argum->fsm = g->getTransducer();
	argum->qid = g->getTransducer()->Start();
	argum->iter = 0;
	argum->length = length;
	argum->inputs = inputs;
	argum->mapOtoI = mapOtoI;
	argum->output = "";
	argum->sem = &sem;

	try {
		SqueezinessAux((void *)argum);
	} catch (exception &e) {
		throw e;
	}


	sem_close(&sem);
//	double max = 0.0;
	for (std::map<string, int>::iterator it = mapOtoI->begin(); it != mapOtoI->end(); it++) {
		TPColl += (double)(it->second) * (it->second - 1);

//		TSq1 += it->second * std::log2((long double)it->second);
		TSq1 += std::pow((double)it->second, a1);
		TSq2 += std::pow((double)it->second, a2);
		TSq3 += std::pow((double)it->second, a3);
		TSq4 += std::pow((double)it->second, a4);
		TSq5 += std::pow((double)it->second, a5);
		TSq6 += std::pow((double)it->second, a6);
		TSq7 += std::pow((double)it->second, a7);
		TSq8 += std::pow((double)it->second, a8);
		TSq9 += std::pow((double)it->second, a9);
		TSq10 += std::pow((double)it->second, a10);

//		if (it->second > max) {
//			max = it->second;
//		}
	}

	PColl = TPColl/((double)(*inputs) * (*inputs - 1));

//	Sq1 = TSq1/((double)*inputs);
	Sq1 = (1.0/(1.0 - a1))*std::log2((double)*inputs / TSq1);
	Sq2 = (1.0/(1.0 - a2))*std::log2((double)*inputs / TSq2);
	Sq3 = (1.0/(1.0 - a3))*std::log2((double)*inputs / TSq3);
	Sq4 = (1.0/(1.0 - a4))*std::log2((double)*inputs / TSq4);
	Sq5 = (1.0/(1.0 - a5))*std::log2((double)*inputs / TSq5);
	Sq6 = (1.0/(1.0 - a6))*std::log2((double)*inputs / TSq6);
	Sq7 = (1.0/(1.0 - a7))*std::log2((double)*inputs / TSq7);
	Sq8 = (1.0/(1.0 - a8))*std::log2((double)*inputs / TSq8);
	Sq9 = (1.0/(1.0 - a9))*std::log2((double)*inputs / TSq9);
	Sq10 = (1.0/(1.0 - a10))*std::log2((double)*inputs / TSq10);
//	Sq10 = std::log2(max);

	delete inputs;
	delete mapOtoI;
	delete argum;
}



void* SqueezinessAux(void * argum) {

	int N = 100;
	int M = 2;
	args arg = *((args*)argum);
	args* arguments[N];
	ArcIterator<StdMutableFst> arcIter(*(arg.fsm), arg.qid);
	pthread_t th[N];
	try {
		if (!arcIter.Done()) {
			if (arg.iter == arg.length) {
				sem_wait(arg.sem);
				*(arg.inputs) = *(arg.inputs) + 1;
				if (arg.mapOtoI->find(arg.output) != arg.mapOtoI->end()) {
					arg.mapOtoI->at(arg.output)++;
				} else {
					arg.mapOtoI->emplace(arg.output, 1);
				}
				sem_post(arg.sem);
			} else {
				int count = 0;
				for ( ; !arcIter.Done(); arcIter.Next()) {
					arguments[count] = new args();
					arguments[count]->fsm = arg.fsm;
					arguments[count]->qid = arcIter.Value().nextstate;
					arguments[count]->iter = arg.iter + 1;
					arguments[count]->length = arg.length;
					arguments[count]->inputs = arg.inputs;
					arguments[count]->mapOtoI = arg.mapOtoI;
					arguments[count]->output = arg.output + to_string(arcIter.Value().olabel);
					arguments[count]->sem = arg.sem;
					count++;
				}
				if (arg.iter < M) {
					for (int i = 0; i < count; i++){
						pthread_create(&th[i], NULL, SqueezinessAux, (void *)arguments[i]);
					}
					for (int i = 0; i < count; i++) {
						pthread_join(th[i], NULL);
					}
				} else {
					for (int i = 0; i < count; i++){
						SqueezinessAux(arguments[i]);
					}
				}
				for (int i = 0; i < count; i++) {
					delete arguments[i];
				}
			}
		} else {
			if (arg.iter > 0) {
				sem_wait(arg.sem);
				*(arg.inputs) = *(arg.inputs) + 1;
				if (arg.mapOtoI->find(arg.output) != arg.mapOtoI->end()) {
					arg.mapOtoI->at(arg.output)++;
				} else {
					arg.mapOtoI->emplace(arg.output, 1);
				}
				sem_post(arg.sem);
			}
		}
	} catch (exception &e) {
		throw e;
	}

	if(arg.iter > 0 && arg.iter < M + 1) {
		pthread_exit(0);
	}
	return NULL;
}

} /* namespace std */
