/*
 * main.cpp
 *
 *  Created on: 19 sept. 2017
 *      Author: colosu
 */

#include <iostream>
#include <fstream>
#include <string>
#include <pthread.h>
#include <gsl/gsl_statistics.h>
#include <fst/fst-decl.h>
#include <fst/fstlib.h>
#include "src/SqueezinessLib.h"

using namespace fst;

#define INI 1 //Initial test set
#define REP 7 //Ending test set
#define LEN 10 //Length of the input sequences
#define N 500 //Number of FSMs per block
#define EXP 1 //Number of blocks

typedef struct {
	Mutations* Mutator;
	Checkups* Checker;
	Graph* G;
	double* FEP;
	int i;
} arguments;

int main(int argc, char * argv[]) {

	//Initialization
	IOHandler* IOH = new IOHandler();
	Checkups* Checker = new Checkups();
	Operations* Ops = new Operations();

	//File names.
	std::string Ifile = "binary.fst";
	std::string Ofile = "PearsonResults.txt";
	std::string Ofile2 = "SpearmanResults.txt";
	std::string FEPfile = "fep.txt";
	std::string Sqfile1 = "Sq1.txt";
	std::string Sqfile2 = "Sq2.txt";
	std::string Sqfile3 = "Sq3.txt";
	std::string Sqfile4 = "Sq4.txt";
	std::string Sqfile5 = "Sq5.txt";
	std::string Sqfile6 = "Sq6.txt";
	std::string Sqfile7 = "Sq7.txt";
	std::string Sqfile8 = "Sq8.txt";
	std::string Sqfile9 = "Sq9.txt";
	std::string Sqfile10 = "Sq10.txt";

	//File variables
	std::ofstream OFile;
	std::ofstream OFile2;
	std::ofstream FEPFile;
	std::ofstream SqFile1;
	std::ofstream SqFile2;
	std::ofstream SqFile3;
	std::ofstream SqFile4;
	std::ofstream SqFile5;
	std::ofstream SqFile6;
	std::ofstream SqFile7;
	std::ofstream SqFile8;
	std::ofstream SqFile9;
	std::ofstream SqFile10;

	//Needed variables
	Graph* G;
	double PCollG = 0;
	double Sq1G = 0;
	double Sq2G = 0;
	double Sq3G = 0;
	double Sq4G = 0;
	double Sq5G = 0;
	double Sq6G = 0;
	double Sq7G = 0;
	double Sq8G = 0;
	double Sq9G = 0;
	double Sq10G = 0;
	double FEP[N];
	double GSq1[N];
	double GSq2[N];
	double GSq3[N];
	double GSq4[N];
	double GSq5[N];
	double GSq6[N];
	double GSq7[N];
	double GSq8[N];
	double GSq9[N];
	double GSq10[N];
	double Ps1 = 0;
	double Ps2 = 0;
	double Ps3 = 0;
	double Ps4 = 0;
	double Ps5 = 0;
	double Ps6 = 0;
	double Ps7 = 0;
	double Ps8 = 0;
	double Ps9 = 0;
	double Ps10 = 0;
	double Ss1 = 0;
	double Ss2 = 0;
	double Ss3 = 0;
	double Ss4 = 0;
	double Ss5 = 0;
	double Ss6 = 0;
	double Ss7 = 0;
	double Ss8 = 0;
	double Ss9 = 0;
	double Ss10 = 0;
	double MeanPs1 = 0;
	double MeanPs2 = 0;
	double MeanPs3 = 0;
	double MeanPs4 = 0;
	double MeanPs5 = 0;
	double MeanPs6 = 0;
	double MeanPs7 = 0;
	double MeanPs8 = 0;
	double MeanPs9 = 0;
	double MeanPs10 = 0;
	double MeanSs1 = 0;
	double MeanSs2 = 0;
	double MeanSs3 = 0;
	double MeanSs4 = 0;
	double MeanSs5 = 0;
	double MeanSs6 = 0;
	double MeanSs7 = 0;
	double MeanSs8 = 0;
	double MeanSs9 = 0;
	double MeanSs10 = 0;
	double aux[2*N];

	//Experiments loop
	//REP = number of experiments (n/10 where n is the number of states of the FSMs)
	for (int K = INI; K <= REP; K++) {

		//Means initialization
		MeanPs1 = 0;
		MeanPs2 = 0;
		MeanPs3 = 0;
		MeanPs4 = 0;
		MeanPs5 = 0;
		MeanPs6 = 0;
		MeanPs7 = 0;
		MeanPs8 = 0;
		MeanPs9 = 0;
		MeanPs10 = 0;
		MeanSs1 = 0;
		MeanSs2 = 0;
		MeanSs3 = 0;
		MeanSs4 = 0;
		MeanSs5 = 0;
		MeanSs6 = 0;
		MeanSs7 = 0;
		MeanSs8 = 0;
		MeanSs9 = 0;
		MeanSs10 = 0;

		//Initialization of output file names
		Ofile = "PearsonResults" + to_string(K*10) + ".txt";
		Ofile2 = "SpearmanResults" + to_string(K*10) + ".txt";

		//Open output files
		OFile.open(Ofile);
		if (!OFile.is_open()) {
			std::cerr << "I can't create the output file." << std::endl;
			return 1;
		}
		OFile2.open(Ofile2);
		if (!OFile2.is_open()) {
			cerr << "I can't create the output file." << endl;
			return 1;
		}

		//Write head of output files
		OFile << "| #Test | Pearson correlation Sq1 | Pearson correlation Sq2 | Pearson correlation Sq3 | Pearson correlation Sq4 | Pearson correlation Sq5 | Pearson correlation Sq6 | Pearson correlation Sq7 | Pearson correlation Sq8 | Pearson correlation Sq9 | Pearson correlation Sq10 |" << std::endl;
		OFile2 << "| #Test | Spearman correlation Sq1 | Spearman correlation Sq2 | Spearman correlation Sq3 | Spearman correlation Sq4 | Spearman correlation Sq5 | Spearman correlation Sq6 | Spearman correlation Sq7 | Spearman correlation Sq8 | Spearman correlation Sq9 | Spearman correlation Sq10 |" << std::endl;

		//Main loop
		//INI = first test block
		//EX = number of test blocks to test
		for (int J = 0; J < EXP; J++) {

			//Initialize arrays to 0
			for (int i = 0; i < N; i++) {
				FEP[i] = 0;
				GSq1[i] = 0;
				GSq2[i] = 0;
				GSq3[i] = 0;
				GSq4[i] = 0;
				GSq5[i] = 0;
				GSq6[i] = 0;
				GSq7[i] = 0;
				GSq8[i] = 0;
				GSq9[i] = 0;
				GSq10[i] = 0;
			}

			//Initialization of output file names
			FEPfile = "./Results/" + to_string(K*10) + "/FEP/fep" + to_string(J+1) + ".txt";
			Sqfile1 = "./Results/" + to_string(K*10) + "/Sq1/Sq" + to_string(J+1) + ".txt";
			Sqfile2 = "./Results/" + to_string(K*10) + "/Sq2/Sq" + to_string(J+1) + ".txt";
			Sqfile3 = "./Results/" + to_string(K*10) + "/Sq3/Sq" + to_string(J+1) + ".txt";
			Sqfile4 = "./Results/" + to_string(K*10) + "/Sq4/Sq" + to_string(J+1) + ".txt";
			Sqfile5 = "./Results/" + to_string(K*10) + "/Sq5/Sq" + to_string(J+1) + ".txt";
			Sqfile6 = "./Results/" + to_string(K*10) + "/Sq6/Sq" + to_string(J+1) + ".txt";
			Sqfile7 = "./Results/" + to_string(K*10) + "/Sq7/Sq" + to_string(J+1) + ".txt";
			Sqfile8 = "./Results/" + to_string(K*10) + "/Sq8/Sq" + to_string(J+1) + ".txt";
			Sqfile9 = "./Results/" + to_string(K*10) + "/Sq9/Sq" + to_string(J+1) + ".txt";
			Sqfile10 = "./Results/" + to_string(K*10) + "/Sq10/Sq" + to_string(J+1) + ".txt";

			//Block loop
			//N = number of tests per block
			for (int I = 0; I < N; I++) {

				//Initialization of input file name
//				Ifile = "./Tests/" + to_string(K*10) + "/test" + to_string((J*N)+(I+1)) + "/binary.fst";
				Ifile = "./Tests/" + to_string(K*10) + "/test" + to_string(I+1) + "/binary.fst";
//				Ifile = "./Tests/Phone/binary.fst";

				//Read graph
				G = IOH->readGraph(Ifile);

				if (G == NULL) {
					std::cerr << "Null graph." << std::endl;
					return 1;
				}

				if (!Checker->is_valid(G)) {
					std::cerr << "Not valid graph." << std::endl;
					return 1;
				}

				//Main computation
				try {
					Ops->SqueezinessAndPColl(G, LEN, PCollG, Sq1G, Sq2G, Sq3G, Sq4G, Sq5G, Sq6G, Sq7G, Sq8G, Sq9G, Sq10G);
					FEP[I] = PCollG;
					GSq1[I] = Sq1G;
					GSq2[I] = Sq2G;
					GSq3[I] = Sq3G;
					GSq4[I] = Sq4G;
					GSq5[I] = Sq5G;
					GSq6[I] = Sq6G;
					GSq7[I] = Sq7G;
					GSq8[I] = Sq8G;
					GSq9[I] = Sq9G;
					GSq10[I] = Sq10G;

					//Test control (in order to know where we are during computation)
//					cout << "FSM " << to_string((J*N)+(I+1)) << endl;
					cout << "FSM " << to_string(I+1) << endl;

					//Delete FSM
					delete G;

				} catch (exception &e) {
					cerr << "Exception: " << e.what() << endl;
				}
			}

			//Test control (in order to know where we are during computation)
			cout << "test " << to_string(J+1) << endl;

			//Open result files.
			FEPFile.open(FEPfile);
			if (!FEPFile.is_open()) {
				std::cerr << "I can't create the fep output file." << std::endl;
				return 1;
			}
			SqFile1.open(Sqfile1);
			if (!SqFile1.is_open()) {
				std::cerr << "I can't create the Sq1 output file." << std::endl;
				return 1;
			}
			SqFile2.open(Sqfile2);
			if (!SqFile2.is_open()) {
				std::cerr << "I can't create the Sq2 output file." << std::endl;
				return 1;
			}
			SqFile3.open(Sqfile3);
			if (!SqFile3.is_open()) {
				std::cerr << "I can't create the Sq3 output file." << std::endl;
				return 1;
			}
			SqFile4.open(Sqfile4);
			if (!SqFile4.is_open()) {
				std::cerr << "I can't create the Sq4 output file." << std::endl;
				return 1;
			}
			SqFile5.open(Sqfile5);
			if (!SqFile5.is_open()) {
				std::cerr << "I can't create the Sq5 output file." << std::endl;
				return 1;
			}
			SqFile6.open(Sqfile6);
			if (!SqFile6.is_open()) {
				std::cerr << "I can't create the Sq6 output file." << std::endl;
				return 1;
			}
			SqFile7.open(Sqfile7);
			if (!SqFile7.is_open()) {
				std::cerr << "I can't create the Sq7 output file." << std::endl;
				return 1;
			}
			SqFile8.open(Sqfile8);
			if (!SqFile8.is_open()) {
				std::cerr << "I can't create the Sq8 output file." << std::endl;
				return 1;
			}
			SqFile9.open(Sqfile9);
			if (!SqFile9.is_open()) {
				std::cerr << "I can't create the Sq9 output file." << std::endl;
				return 1;
			}
			SqFile10.open(Sqfile10);
			if (!SqFile10.is_open()) {
				std::cerr << "I can't create the Sq10 output file." << std::endl;
				return 1;
			}

			//Write results to files
			for (int i = 0; i < N; i++){
				FEPFile << FEP[i] << endl;
				SqFile1 << GSq1[i] << endl;
				SqFile2 << GSq2[i] << endl;
				SqFile3 << GSq3[i] << endl;
				SqFile4 << GSq4[i] << endl;
				SqFile5 << GSq5[i] << endl;
				SqFile6 << GSq6[i] << endl;
				SqFile7 << GSq7[i] << endl;
				SqFile8 << GSq8[i] << endl;
				SqFile9 << GSq9[i] << endl;
				SqFile10 << GSq10[i] << endl;
			}

			//Close result files
			FEPFile.close();
			SqFile1.close();
			SqFile2.close();
			SqFile3.close();
			SqFile4.close();
			SqFile5.close();
			SqFile6.close();
			SqFile7.close();
			SqFile8.close();
			SqFile9.close();
			SqFile10.close();

			//Compute correlations
			Ps1 = gsl_stats_correlation(FEP, 1, GSq1, 1, N);
			Ps2 = gsl_stats_correlation(FEP, 1, GSq2, 1, N);
			Ps3 = gsl_stats_correlation(FEP, 1, GSq3, 1, N);
			Ps4 = gsl_stats_correlation(FEP, 1, GSq4, 1, N);
			Ps5 = gsl_stats_correlation(FEP, 1, GSq5, 1, N);
			Ps6 = gsl_stats_correlation(FEP, 1, GSq6, 1, N);
			Ps7 = gsl_stats_correlation(FEP, 1, GSq7, 1, N);
			Ps8 = gsl_stats_correlation(FEP, 1, GSq8, 1, N);
			Ps9 = gsl_stats_correlation(FEP, 1, GSq9, 1, N);
			Ps10 = gsl_stats_correlation(FEP, 1, GSq10, 1, N);
			Ss1 = gsl_stats_spearman(FEP, 1, GSq1, 1, N, aux);
			Ss2 = gsl_stats_spearman(FEP, 1, GSq2, 1, N, aux);
			Ss3 = gsl_stats_spearman(FEP, 1, GSq3, 1, N, aux);
			Ss4 = gsl_stats_spearman(FEP, 1, GSq4, 1, N, aux);
			Ss5 = gsl_stats_spearman(FEP, 1, GSq5, 1, N, aux);
			Ss6 = gsl_stats_spearman(FEP, 1, GSq6, 1, N, aux);
			Ss7 = gsl_stats_spearman(FEP, 1, GSq7, 1, N, aux);
			Ss8 = gsl_stats_spearman(FEP, 1, GSq8, 1, N, aux);
			Ss9 = gsl_stats_spearman(FEP, 1, GSq9, 1, N, aux);
			Ss10 = gsl_stats_spearman(FEP, 1, GSq10, 1, N, aux);

			//Add to correlation means
			MeanPs1 += Ps1;
			MeanPs2 += Ps2;
			MeanPs3 += Ps3;
			MeanPs4 += Ps4;
			MeanPs5 += Ps5;
			MeanPs6 += Ps6;
			MeanPs7 += Ps7;
			MeanPs8 += Ps8;
			MeanPs9 += Ps9;
			MeanPs10 += Ps10;
			MeanSs1 += Ss1;
			MeanSs2 += Ss2;
			MeanSs3 += Ss3;
			MeanSs4 += Ss4;
			MeanSs5 += Ss5;
			MeanSs6 += Ss6;
			MeanSs7 += Ss7;
			MeanSs8 += Ss8;
			MeanSs9 += Ss9;
			MeanSs10 += Ss10;

			//Write final results
			OFile << J+1 << " & " << Ps1 << " & " << Ps2 << " & " << Ps3 << " & " << Ps4 << " & " << Ps5 << " & " << Ps6 << " & " << Ps7 << " & " << Ps8 << " & " << Ps9 << " & " << Ps10 << "\\\\" << endl;
			OFile << "\\hline" << endl;
			OFile2 << J+1 << " & " << Ss1 << " & " << Ss2 << " & " << Ss3 << " & " << Ss4 << " & " << Ss5 << " & " << Ss6 << " & " << Ss7 << " & " << Ss8 << " & " << Ss9 << " & " << Ss10 << "\\\\" << endl;
			OFile2 << "\\hline" << endl;
		}

		//Write final means
		OFile << "mean" << " & " << MeanPs1/EXP << " & " << MeanPs2/EXP << " & " << MeanPs3/EXP << " & " << MeanPs4/EXP << " & " << MeanPs5/EXP << " & " << MeanPs6/EXP << " & " << MeanPs7/EXP << " & " << MeanPs8/EXP << " & " << MeanPs9/EXP << " & " << MeanPs10/EXP << "\\\\" << endl;
		OFile << "\\hline" << endl;
		OFile2 << "mean" << " & " << MeanSs1/EXP << " & " << MeanSs2/EXP << " & " << MeanSs3/EXP << " & " << MeanSs4/EXP << " & " << MeanSs5/EXP << " & " << MeanSs6/EXP << " & " << MeanSs7/EXP << " & " << MeanSs8/EXP << " & " << MeanSs9/EXP << " & " << MeanSs10/EXP << "\\\\" << endl;
		OFile2 << "\\hline" << endl;

		//Close output files
		OFile.close();
		OFile2.close();
	}

	//Delete auxiliary objects
	delete IOH;
	delete Checker;
	delete Ops;

	//End process
	return 0;
}
