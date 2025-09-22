/*! @file RunControl.cpp
 *  @brief main()
 * 	@details Read in from config file the input data directory, file name, run number. Opens TApplication which allows to run some plots from Online Monitor. Opens TreeOnFireReader.
 *  @todo Move gStyle to other fil
 */

#include "TSystem.h"
#include "TROOT.h"

#include "TInterpreter.h"
#include "TApplication.h"
#include "TGClient.h"
#include "TGFileDialog.h"

#include "../inc/CE65Event.h"
#include "../inc/globals.h"
#include "../inc/cout_msg.h"
#include "../inc/ConfigManager.h"

#include "CE65TreeAnalyzer.h"

int main(int argc, char **argv)
{
    std::cout << "\033[32m" << "\n<<<<<< Running data RunControl for FLAME analysis >>>>>>" <<  "\033[0m" << std::endl;	

    gSystem->AddIncludePath("-I./src");
    gSystem->AddIncludePath("-I./inc");
    gROOT->ForceStyle();
    gStyle->SetOptStat(1);
    gStyle->SetPalette(kCool);

    // --- Config reader ---
    ConfigManager * conf = nullptr;
    if(argc == 2) 
    {
        conf = new ConfigManager(argv[1]);
    }
    else 
    {
        MSG(ERR, "Argumant is not configuration file\n >>>>> Usage : ./run_basic_analysis <path_to_config>")
        return 1;
    }

    CE65TreeAnalyzer *reader = new CE65TreeAnalyzer();

    reader->setOutputDir(conf->getOutputDir());
    reader->setInputDir(conf->getInputDir());
	reader->setDataName(conf->getInputDataName());
    reader->setSeedTh(conf->getThresholdSeed());
    reader->setNbhrTh(conf->getThresholdNeighbor());
    reader->setEveMax(conf->getEveMax());
	reader->setSkipEdgeSeed(conf->getSkipEdgeSeed());
	reader->setSkipEdgeClustering(conf->getSkipEdgeClustering());
	reader->setClusteringMethod(conf->getClusteringMethod());
    reader->setCalibFactor(conf->getCalibFactor());

    std::string outfile_suffix = "_seedthr"+ std::to_string(conf->getThresholdSeed()) + "_nbgrthr" + std::to_string(conf->getThresholdNeighbor());

    // PCB10_B4_10M_HV0_VBB1_fe
    MSG(INFO,"Running analysis for input file: " << reader->getDataName());
    reader->ReadCalibData(" ", " ");
    reader->LoadTree();
    reader->OpenOutTree(outfile_suffix);
    reader->HistoInit();
    reader->Process();
    reader->CloseOutTree();
    delete reader;
    return 0;
}
