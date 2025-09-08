/*! \class 		ce65TreeReader
 *  \brief 		Header file for ce65TreeReader
 *  \author    	Szymon Bugie, Roma Bugiel
 *  \date      	March 2020
 *  \pre       	ROOT installation, shared libraries of plane_str
 *  \warning   	Exeception handling not added
 *	\details	Class for reading the input data ROOT Tree - example as provided after test-beam campaing, no major changes. main
 *  \todo
 */

#ifndef ce65TreeReaderL_h
#define ce65TreeReaderL_h

#include <bitset>
#include "../inc/CE65Event.h"
#include "../inc/globals.h"
#include "../inc/cout_msg.h"
#include "../inc/Cluster.h"
#include "TBenchmark.h"

#include <TString.h>
#include <TFile.h>
#include <TH2.h>
#include <TH1.h>
#include <TChain.h>
#include <TDirectory.h>
#include <TTree.h>
#include "TCanvas.h"
#include "TStyle.h"
#include "TH3.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TString.h"
#include "TF1.h"
#include "TEnv.h"
#include <fstream>
#include <TROOT.h>
#include <TSystem.h>

#include <regex>
#include <queue>
#include <set>
#include <cstdlib>	//atof
#include <iostream> //cout, cin, endl
#include <csignal>	//SIGINT

/*! \brief Number of planes definition, for initializing the &Plane array
 * * \todo this should be parameter taken from config file, but since the array init have to take constant value, it should be solved in other way than assigning this variable to NB_OF_PLANES*/
const int PLANES_NUMBER = 3;
extern bool terminate_process;
void SignalHandler(int signum);

class ce65TreeReader
{

public:
	/*!  \brief Default contructor -- creates shared libraries */
	ce65TreeReader()
	{
		// --- Create dictionary with the output file objects collection
		#if !defined(__CINT__)
			// Explicitly load the dictionary library created by the makefile
			TString dictPath = gSystem->ExpandPathName("./build/lib/libce65dict.so");
			if (gSystem->AccessPathName(dictPath) == 0) {
				gSystem->Load(dictPath.Data());
			} else {
				// If the library is not found, print a warning.
				// It might still work if LD_LIBRARY_PATH is set correctly.
				std::cout << "Warning: Dictionary library not found at " << dictPath << std::endl;
			}
		#endif /* !defined(__CINT__) */
		#ifdef __MAKECINT__
		#pragma link C++ class ce65_frame + ;
		#pragma link C++ class ce65_event + ;
		#endif
	}

	void SetSeedTh(double seed_thr) { thSeed = seed_thr; }
	void SetNbhrTh(double nbhr_thr) { thNeighbor = nbhr_thr; }
	void SetEveMax(double eve_max) { eveMax = eve_max; }
	/*! \brief Initializes the class memebers. */
	void init(const char *config_file);

	/*! \brief Finds out which runs has to be taken to analysis (TChain)
	 * \details Creates a run list starting from #_run_start to #_run_end with the step of #_step. In addition, adds the runs from _incl list. In the end excludes the runs from #_excl list.*/

	TH1D *histo_test;
	TH1D *get_histo_test();

	const int width = 1600;
	const int height = 600;

	int signalFrame = 5;
	int baselineFrame = 4;

	double thSeed = 1000;
	double thNeighbor = 210;
	double eveMax;

	unsigned long T0 = 0;

	// ----  Branches definition ----
	Long64_t ev_number = -1;
	int frames_per_event = -1;
	std::vector<ce65_frame> *frame = 0;
	TString fileName;
	int chip_variant = 3;
;
	// class functions
	int LoadTree();
	void OpenOutTree(TString sufix);
	void CloseOutTree();
	void TreeInfo();

	void FillSinglePixelRawSpectra(int iFrame = 0);
	void FillSinglePixelSignalSpectra();
	void AnalyseOnePixel(TH1D *h, int xPix, int yPix);
	void FillBaselineSpectra();
	void FillSingleEvent();
	void FillSignalMap();
	void ReadCalibData(TString dc_calib_path, TString ac_calib_path);
	void HistoInit();
	void Process();

	//! Default constructor
	~ce65TreeReader() {};

	std::ofstream outfile;

	TH1D *hPixRawSpectra[X_MX_SIZE][Y_MX_SIZE];
	TH1D *hPixSignalSpectra[X_MX_SIZE][Y_MX_SIZE];
	TH1D *h_mxAmpAC_baseline;

	TH2D *h2_CE65_baseline;
	TH2D *h2_CE65_noise;
	TH2D *h2_calib_noise_map;

	TH2D *h2_CE65_nb_of_hits;
	TH2D *h2_CE65_signal_mean;
	TH2D *h2_CE65_signal_width;

	TH1D *h_mxAmpAC_noise;
	TH1D *h_mxAmpAC_quick_spectra;
	TH2D *h2_unity_map;
	TH2D *h2_noisy_pixels_map;
	TH2D *h2_ac_gain_map;
	TH2D *h_noisy_pix_map;
	TH2D *h_hit_map;
	TH1D *h_mxAmpAC_sig_in_time;
	TH1D *h_cluster_multiplicity;
	TCanvas *c_mxAmpAC_sig_in_time;

	TH2D *h2_1eve_clstr_hitmap[10];

	TH1D *h_cluster_size;
	TH1D *h_cluster_charge;
	TH1D *h_seed_charge;
	TH1D *h_neighbor_charge;

	TH1D *h_bl_in_time[X_MX_SIZE][Y_MX_SIZE];
	TH2D *h_single_ev_signal_map;
	TH1D *h_single_ev_time_signal;
	TH2D *h_seed_vs_neighbor;
	TCanvas *c_single_ev_time_signal;

	// --- Clustering methods ---
	const std::vector<Cluster>& getClusters() const { return _clusters; } 
	void setCluster(Cluster&& cluster) { _clusters.push_back(std::move(cluster)); }
	void resetClusters() { _clusters.clear(); }
	std::vector<std::unique_ptr<Pixel>> findSeedCandidates();
	void Clustering();
	void CalClusterPos();
	void FillClusterHist();

private:
	TEnv config;
	TTree *tree; /*!< \todo [HIGH PRIOR] Input data are read out as a TChain. Needs to add possibility to provide the range of runs in config. */

	TString _output_image_path{""}; /*!< \brief path to output plots directory  */
	TString _input_data_dir{""};	/*!< \brief path to input data directory */
	TString _input_data_name{""};	/*!< \brief core of the input file name */
	TString _input_tree_name{""};	/*!< \brief input tree name */
	TFile *_out_data_file;
	TTree *_out_tree;
	uint _skipEvents = 0;
	double _statisticFraction = 1;

	int sample_cntr = 0;
	uint _iEvent = 0;
	uint _i_saved_to_1eveh2hitmap = 0;
	std::vector<Cluster> _clusters;
};

#endif
