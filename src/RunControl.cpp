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

#include "CE65TreeAnalyzer.h"

int main(int argc, char **argv)
{
    std::cout << "\033[32m" << "\n<<<<<< Running data RunControl for FLAME analysis >>>>>>" <<  "\033[0m" << std::endl;	

    //   TApplication theApp("App", &argc, argv);
    gSystem->AddIncludePath("-I./src");
    gSystem->AddIncludePath("-I./inc");
    gROOT->ForceStyle();
    gStyle->SetOptStat(1);
    gStyle->SetPalette(kCool);

    // --- Reading config data
    /*
    const char *config_file {"config_file.cfg"};
    TEnv config;
    if(config.ReadFile("config_file.cfg", kEnvUser) < 0)
    {
        MSG(ERR, "Could not read configuration file in RunControl: config_file.cfg - exit");
        exit(0);
    }
    */

    TString outfile_suffix = "_wave";

    CE65TreeAnalyzer *reader = new CE65TreeAnalyzer();
    if (argc == 2)
    {
        reader->fileName = argv[1];
    }
    else if (argc > 2)
    {
        reader->fileName = argv[1];
        reader->SetSeedTh(atof(argv[2]));
        reader->SetNbhrTh(atof(argv[3]));
        if (argc == 5)
        {
            reader->SetEveMax(atof(argv[4]));
        }
        outfile_suffix = "_seedthr" + ((TString)argv[2]) + "_nbhrthr" + ((TString)argv[3]);
    }
    else
    {
        reader->fileName = "B4_PCB19_fe";
    }
    // PCB10_B4_10M_HV0_VBB1_fe
     MSG(INFO,"Running analysis for input file: " << reader->fileName);

    // reader		-> ReadCalibData("./calib_data/B4_PCB24_DC_gain_T10.root", "./calib_data/B4_PCB24_DC_gain_T10_2.root");
    //  reader		-> ReadCalibData("", "/home/akumar/ce65v2_daq/analysis/macros/out_data/AC_gain_CE65V2_PCB08_Proxy5_10V_Fe55_20231016.root");
    reader->ReadCalibData(" ", " ");

    // reader->chip_variant = reader             -> ReadChip();
    //  reader              -> ReadChip();
    //  std::cout<<"_chip_variant : "<<reader->chip_variant<<std::endl;
    //reader->SetSubmatrixBounds();

    reader->LoadTree();
    // reader		-> OpenOutTree("_ac_calib");
    // reader		-> OpenOutTree("_wave");
    reader->OpenOutTree(outfile_suffix);

    reader->HistoInit();

    reader->Process();
    reader->CloseOutTree();
    // reader->Plot();

    //	theApp.Run();

    // reader->delete();
    return 0;
}
