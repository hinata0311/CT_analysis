// -----------------------------------------------------------------------
// ------------------------- Compilation ---------------------------------
// `root-config --cxx` `root-config --cflags`  -O2 -W ce65TreeReader.cpp -o offline_analysis `root-config --ldflags` `root-config --glibs`
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------

#include "ce65TreeReader.h"

bool terminate_process = false;

void ce65TreeReader::OpenOutTree(TString sufix = "")
{
  TString data_dir = DEFAULT_OUTPUT_DATA_PATH;
  _out_data_file = TFile::Open(data_dir + fileName + sufix + ".root", "recreate");
  std::cout << "Output file created: " << "../data/" + fileName + sufix + ".root" << std::endl;
  _out_data_file->cd();
  outfile.open("output_results.txt", std::ios_base::app); // append instead of overwrite
}

void ce65TreeReader::ReadCalibData(TString dc_calib_path = "no_path", TString ac_calib_path = "no_path")
{
  TFile *f_ac_calib_data = new TFile(ac_calib_path);

  if (!f_ac_calib_data || f_ac_calib_data->IsZombie())
  {
    h2_ac_gain_map = new TH2D("h2_ac_gain_map", "h2_ac_gain_map;X;Y", X_MX_SIZE, 0, X_MX_SIZE, Y_MX_SIZE, 0, Y_MX_SIZE);
    h2_noisy_pixels_map = new TH2D("h2_noisy_pixels_map", "h2_noisy_pixels_map;X;Y", X_MX_SIZE, 0, X_MX_SIZE, Y_MX_SIZE, 0, Y_MX_SIZE);
    for (int xPix = 0; xPix < X_MX_SIZE; xPix++)
    {
      for (int yPix = 0; yPix < Y_MX_SIZE; yPix++)
      {
        h2_ac_gain_map->SetBinContent(xPix + 1, yPix + 1, 1);
      }
    }
  }

  else
  {
    h2_ac_gain_map = (TH2D *)f_ac_calib_data->Get("h2_ac_gain_map");
    MSG(CNTR, "[CNTR]  AC  Gain tree loaded: " << h2_ac_gain_map->GetBinContent(45, 15) << h2_ac_gain_map->GetTitle());
  }
}

void ce65TreeReader::CloseOutTree()
{
  _out_data_file->cd();
  _out_data_file->Write();
  //_out_data_file ->Close();
}

// HistoInit ----------------------------------------------------------------------------------

void ce65TreeReader::HistoInit()
{
  MSG(CNTR, "[TREE] Control plots histograms initialization...");
  gStyle->SetPalette(kViridis);

  TDirectory *directory = gDirectory;
  TDirectory *local_directory = directory->mkdir("pix_spectra");
  local_directory->cd();

  for (int xPix = 0; xPix < X_MX_SIZE; xPix++)
  {
    for (int yPix = 0; yPix < Y_MX_SIZE; yPix++)
    {
      hPixRawSpectra[xPix][yPix] = new TH1D(
          "hPixRawSpectra[" + TString::Itoa(xPix, 10) + "][" + TString::Itoa(yPix, 10) + "]",
          "Raw amp pixel[" + TString::Itoa(xPix, 10) + "][" + TString::Itoa(yPix, 10) + "];raw_amp;#",
          30000, -15000, 15000);
      hPixSignalSpectra[xPix][yPix] = new TH1D(
          "hPixSignalSpectra[" + TString::Itoa(xPix, 10) + "][" + TString::Itoa(yPix, 10) + "]",
          "Signal amp pixel[" + TString::Itoa(xPix, 10) + "][" + TString::Itoa(yPix, 10) + "];raw_amp;#",
          30000, -15000, 15000);
      h_bl_in_time[xPix][yPix] = new TH1D(
          "h_bl_in_time[" + TString::Itoa(xPix, 10) + "][" + TString::Itoa(yPix, 10) + "]",
          "Pixel baseline in time [" + TString::Itoa(xPix, 10) + "][" + TString::Itoa(yPix, 10) + "];t[ms];ADU",
          100000, 0, 30000);
    }
  }

  directory->cd();

  h_mxAmpAC_baseline = new TH1D("h_mxAmpAC_baseline", "MX AapAC baseline;baseline [ADU];#", DAC_BOARD_ADC_MAX_COUNTS / 10, -DAC_BOARD_ADC_MAX_COUNTS / 2, DAC_BOARD_ADC_MAX_COUNTS / 2);

  h_mxAmpAC_noise = new TH1D("h_mxAmpAC_noise", "MX AapAC noise;noise [ADU];#", 200, 0, 2000);

  h_cluster_size = new TH1D("h_cluster_size", "cluster size;cluster size;#", 20, 0.5, 20.5);

  h2_CE65_baseline = new TH2D("h2_CE65_baseline", "baseline;baseline [ADU];#", X_MX_SIZE, 0, X_MX_SIZE, Y_MX_SIZE, 0, Y_MX_SIZE);
  h2_CE65_noise = new TH2D("h2_CE65_noise", "noise;noise [ADU];#", X_MX_SIZE, 0, X_MX_SIZE, Y_MX_SIZE, 0, Y_MX_SIZE);

  h2_CE65_nb_of_hits = new TH2D("h2_CE65_nb_of_hits", "nb of hits;nb of hits [ADU];#", X_MX_SIZE, 0, X_MX_SIZE, Y_MX_SIZE, 0, Y_MX_SIZE);
  h2_CE65_signal_mean = new TH2D("h2_CE65_signal_mean", "signal mean;signal_mean [ADU];#", X_MX_SIZE, 0, X_MX_SIZE, Y_MX_SIZE, 0, Y_MX_SIZE);
  h2_CE65_signal_width = new TH2D("h2_CE65_signal_width", "signal width;signal width [ADU];#", X_MX_SIZE, 0, X_MX_SIZE, Y_MX_SIZE, 0, Y_MX_SIZE);

  h_mxAmpAC_quick_spectra = new TH1D("h_mxAmpAC_quick_spectra", "h_mxAmpAC_quick_spectra;signal [ADU];#", 10000, 0, 10000);

  h_single_ev_signal_map = new TH2D("h_single_ev_signal_map", "h_single_ev_signal_map;#X; Y", X_MX_SIZE, 0, X_MX_SIZE, Y_MX_SIZE, 0, Y_MX_SIZE);
  //  h_single_ev_time_signal = new TH1D("h_single_ev_time_signal", "Pixel signal in time SF;#farame; signal [ADU]", 20,0,20);
  c_single_ev_time_signal = new TCanvas("c_single_ev_time_signal", "c_single_ev_time_signal", 1200, 800);
  c_single_ev_time_signal->SetGrid();

  //	--------------------------------------------------------------------------
  h_mxAmpAC_sig_in_time = new TH1D("h_mxAmpAC_sig_in_time", "Pixel signal in time AmpAC;#farame; signal [ADU]", 20, 0, 20);
  c_mxAmpAC_sig_in_time = new TCanvas("c_mxAmpAC_sig_in_time", "c_mxAmpAC_sig_in_time", 1200, 800);
  c_mxAmpAC_sig_in_time->SetGrid();

  h_noisy_pix_map = new TH2D("h_noisy_pix_map", "h_noisy_pix_map;#X; Y", X_MX_SIZE, 0, X_MX_SIZE, Y_MX_SIZE, 0, Y_MX_SIZE);
  h_hit_map = new TH2D("h_hit_map", "h_hit_map;#X; Y", X_MX_SIZE, 0, X_MX_SIZE, Y_MX_SIZE, 0, Y_MX_SIZE);

  h2_unity_map = new TH2D("h2_unity_map", "h2_unity_map;X;Y", X_MX_SIZE, 0, X_MX_SIZE, Y_MX_SIZE, 0, Y_MX_SIZE);
  for (int xPix = 0; xPix < X_MX_SIZE; xPix++)
  {
    for (int yPix = 0; yPix < Y_MX_SIZE; yPix++)
    {
      h2_unity_map->Fill(xPix, yPix);
    }
  }

  h_cluster_multiplicity = new TH1D("h_cluster_multiplicity", "h_cluster_multiplicity; event frame ; cluster multiplicity", 10000, 0, 100000);

  h_cluster_charge = new TH1D("h_cluster_charge", "cluster charge;charge [ADCu]; count", 5000, 0, 50000);

  h_seed_charge = new TH1D("h_seed_charge", "h_seed_charge;charge [ADCu]; count", 5000, 0, 50000);

  h_neighbor_charge = new TH1D("h_neighbor_charge", "neighbor charge; [ADCu]; count", 5000, 0, 50000);

  h_seed_vs_neighbor = new TH2D("h_seed_vs_neighbor", "seed vs neighbor charge;seed charge [ADCu];neighbor charge [ADCu]", 100, -1000, 10000, 100, -1000, 10000);

  for (int i = 0; i < 10; ++i)
  {
    h2_1eve_clstr_hitmap[i] = new TH2D(
        "h2_1eve_clstr_hitmap[" + TString::Itoa(i, 11) + "]",
        "h2_1eve_clstr_hitmap[" + TString::Itoa(i, 11) + "]",
        X_MX_SIZE, 0, X_MX_SIZE, Y_MX_SIZE, 0, Y_MX_SIZE);
  }
}

// LoadTree --------------------------------------------------------------------------------

int ce65TreeReader::LoadTree()
{

  MSG(CNTR, "[TREE] Loading input tree/trees...");

  TString name;
  _input_tree_name = "CE65Data";
  //_input_data_dir        = "/scratch/rbugiel/CE65_DATA/";
  _input_data_dir = DEFAULT_INPUT_DATA_PATH;

  _input_data_name = fileName;

  // tree = new TChain(_input_tree_name);

  name = _input_data_dir + _input_data_name + ".root";
  // name = "/home/alice/DATA/TB_run_485105326_211203_105339.root";
  TFile *f = new TFile(name);

  if (!f)
  {
    MSG(ERR, "[TREE] Tree: " << name << " NOT LOADED.");
    exit(0);
    return 0;
  }

  else if (f->IsZombie())
  {
    MSG(ERR, "[TREE]  Tree: " << name << " IS ZOMBIE.");
    exit(0);
    return 0;
  }
  else
  {
    MSG(CNTR, "[TREE]  Tree: " << name << " will be loaded.");
  }

  tree = (TTree *)f->Get(_input_tree_name);

  // MSG(CNTR, "[TREE]  File: " << _input_data_dir+ "/" + _input_data_name +"_" +TString::Itoa(r,10)+ ".root loaded.");

  tree->SetBranchAddress("ev_number", &ev_number);
  tree->SetBranchAddress("frames_per_event", &frames_per_event);
  tree->SetBranchAddress("frame", &frame);
  tree->GetEntry(0);

  this->TreeInfo();
  MSG(CNTR, "[TREE]  Tree loaded");

  return 1;
}

// TreeInfo ---------------------------------------------------------

void ce65TreeReader::TreeInfo()
{
  MSG(INFO, "[TREE] Entires in tree: " << tree->GetEntries());
  MSG(INFO, "[TREE] Skipped events in the analysis: " << _skipEvents << ". " << _statisticFraction*100. << "% of the statistic will be analysed");
  MSG(INFO, "[TREE] ev_number: " << ev_number);
  MSG(INFO, "[TREE] frames_per_event: " << frames_per_event);
}

// ------------------------------------------------------------------

void ce65TreeReader::FillSinglePixelRawSpectra(int iFrame)
{

  int skip_boundary_pix = 0;
  double signal = 0;

  for (int xPix = 0 + skip_boundary_pix; xPix < X_MX_SIZE - skip_boundary_pix; xPix++)
  {
    for (int yPix = 0 + skip_boundary_pix; yPix < Y_MX_SIZE - skip_boundary_pix; yPix++)
    {
      for (unsigned int iFrame = 0; iFrame < frame->size(); iFrame++)
      {
        //  	hPixRawSpectra[xPix][yPix] -> Fill( frame->at(iFrame).raw_amp[xPix][yPix] );
      }
      //	hPixRawSpectra[xPix][yPix] -> Fill( frame->at(0).raw_amp[xPix][yPix] );
      hPixRawSpectra[xPix][yPix]->Fill(frame->at(signalFrame).raw_amp[xPix][yPix]);
      if (iFrame < 100000)
        h_bl_in_time[xPix][yPix]->SetBinContent(h_bl_in_time[xPix][yPix]->FindBin((frame->at(signalFrame).time_stamp - T0) / 100000.), frame->at(signalFrame).raw_amp[xPix][yPix]);
    }
  }
}

void ce65TreeReader::FillSinglePixelSignalSpectra()
{
  int skip_boundary_pix = 0;
  double signal = 0;

  for (int xPix = 0 + skip_boundary_pix; xPix < X_MX_SIZE - skip_boundary_pix; xPix++)
  {
    for (int yPix = 0 + skip_boundary_pix; yPix < Y_MX_SIZE - skip_boundary_pix; yPix++)
    {
      // Determine signal
      signal = frame->at(signalFrame).raw_amp[xPix][yPix] - frame->at(baselineFrame).raw_amp[xPix][yPix];
      hPixSignalSpectra[xPix][yPix]->Fill(signal);

      // Remove border pixels
      // if(xPix == 0 || xPix == X_MX_SIZE-1) continue;
      // if(yPix == 0 || yPix == Y_MX_SIZE-1) continue;
      // if(xPix == 0 || xPix == 63) continue;

      if (xPix == 0 || xPix == X_MX_SIZE - 1)
        continue;
      if (yPix == 0 || yPix == Y_MX_SIZE - 1)
        continue;

      // Skip noisy pixels
      if (h2_noisy_pixels_map->GetBinContent(xPix + 1, yPix + 1) > 0)
        continue;
    }
  }
}

// ----- new Clustering method -----

std::vector<std::unique_ptr<Pixel>> ce65TreeReader::findSeedCandidates()
{
  std::vector<std::unique_ptr<Pixel>> seed_candidates;
  int skip_boundary_pix = 0;
  int signal;

  for (int x = 0 + skip_boundary_pix; x < X_MX_SIZE - skip_boundary_pix; x++)
  {
    for (int y = 0 + skip_boundary_pix; y < Y_MX_SIZE - skip_boundary_pix; y++)
    {
      signal = frame->at(signalFrame).raw_amp[x][y] - frame->at(baselineFrame).raw_amp[x][y];
      if (signal > thSeed)
      {
        // std::unique_ptr<Pixel> seed_candidate = ;
        seed_candidates.push_back(std::make_unique<Pixel>(x, y, signal));
      }
    }
  }
  return seed_candidates;
}

bool isWithinBounds(int x, int y)
{
  return x >= 0 && x < X_MX_SIZE && y >= 0 && y < Y_MX_SIZE;
}

void ce65TreeReader::Clustering()
{
  std::vector<std::unique_ptr<Pixel>> seed_candidates = findSeedCandidates();
  std::set<std::pair<int, int>> used_pixels;
  int tmpX, tmpY;
  for (auto &seed : seed_candidates)
  {
    int seed_x = seed->column();
    int seed_y = seed->row();
    double seed_charge = seed->charge();

    // Check if the current seed has already been used in another cluster.
    if (used_pixels.count({seed_x, seed_y}))
    {
      continue;
    }

    // Initialize a new cluster and its properties.
    Cluster new_cluster;
    std::queue<std::pair<int, int>> pixel_queue;

    // Add the seed pixel to the queue and mark it as used.
    pixel_queue.push({seed_x, seed_y});
    used_pixels.insert({seed_x, seed_y});

    // Add the seed pixel to the new cluster.
    new_cluster.addPixel(std::move(seed));
    new_cluster.setColumn(seed_x);
    new_cluster.setRow(seed_y);

    // Use a breadth-first search (BFS) to find all adjacent pixels.
    while (!pixel_queue.empty())
    {
      std::pair<int, int> current_pixel = pixel_queue.front();
      pixel_queue.pop();

      int current_x = current_pixel.first;
      int current_y = current_pixel.second;

      // Search the 8 neighboring pixels.
      for (int dx = -1; dx <= 1; ++dx)
      {
        for (int dy = -1; dy <= 1; ++dy)
        {
          // Skip the current pixel itself.
          if (dx == 0 && dy == 0)
            continue;

          int neighbor_x = current_x + dx;
          int neighbor_y = current_y + dy;

          // Check if the neighbor is within bounds and has not been used yet.
          if (isWithinBounds(neighbor_x, neighbor_y) && used_pixels.count({neighbor_x, neighbor_y}) == 0)
          {
            int neighbor_signal = frame->at(signalFrame).raw_amp[neighbor_x][neighbor_y] - frame->at(baselineFrame).raw_amp[neighbor_x][neighbor_y];

            // Check if the neighbor signal exceeds the adjacency threshold.
            if (neighbor_signal > thNeighbor)
            {
              // Add the neighbor to the queue and mark it as used.
              pixel_queue.push({neighbor_x, neighbor_y});
              used_pixels.insert({neighbor_x, neighbor_y});

              // Add the neighbor to the new cluster.
              // std::unique_ptr<Pixel> neighbor = ;
              new_cluster.addPixel(std::make_unique<Pixel>(neighbor_x, neighbor_y, neighbor_signal));
            }
          }
        }
      }
    }
    setCluster(std::move(new_cluster));
  }
}

void ce65TreeReader::CalClusterPos() {
  // Write your code for calculating cluster center-of-gravity
}

void ce65TreeReader::FillClusterHist()
{
  for (const auto &cluster : getClusters())
  {
    h_hit_map->Fill(cluster.colmun(), cluster.row());
    h_cluster_size->Fill(cluster.size());
    h_cluster_charge->Fill(cluster.charge());

    int seed_charge = cluster.getSeedPixel()->charge();
    h_seed_charge->Fill(seed_charge);

    for (const auto &neighbor : cluster.getNeighbors())
    {
      int neighbor_charge = neighbor->charge();
      h_neighbor_charge->Fill(neighbor_charge);
      h_seed_vs_neighbor->Fill(seed_charge, neighbor_charge);
    }
  }

  int cluster_multiplicity = getClusters().size();
  h_cluster_multiplicity->Fill(_iEvent, cluster_multiplicity);
  if (cluster_multiplicity > 10 && _i_saved_to_1eveh2hitmap < 10)
  {
    for (const auto &cluster : getClusters())
    {
      h2_1eve_clstr_hitmap[_i_saved_to_1eveh2hitmap]->Fill(cluster.colmun(), cluster.row());
    }
    _i_saved_to_1eveh2hitmap++;
  }
}

void ce65TreeReader::AnalyseOnePixel(TH1D *h, int xPix = 30, int yPix = 15)
{
  double signal = frame->at(signalFrame).raw_amp[xPix][yPix] - frame->at(baselineFrame).raw_amp[xPix][yPix];
  h->Fill(signal);
}

void ce65TreeReader::FillBaselineSpectra()
{

  for (int xPix = 0; xPix < X_MX_SIZE; xPix++)
  {
    for (int yPix = 0; yPix < Y_MX_SIZE; yPix++)
    {

      h2_CE65_baseline->Fill(xPix, yPix, hPixRawSpectra[xPix][yPix]->GetMean());
      h2_CE65_noise->Fill(xPix, yPix, hPixRawSpectra[xPix][yPix]->GetRMS());
      h_mxAmpAC_baseline->Fill(hPixRawSpectra[xPix][yPix]->GetMean());
      h_mxAmpAC_noise->Fill(hPixRawSpectra[xPix][yPix]->GetRMS());
    }
  }
}

void ce65TreeReader::FillSignalMap()
{

  for (int xPix = 0; xPix < X_MX_SIZE; xPix++)
  {
    for (int yPix = 0; yPix < Y_MX_SIZE; yPix++)
    {

      // if(xPix == 0 || xPix == 63) continue;
      if (xPix == 0 || xPix == X_MX_SIZE - 1)
        continue;
      if (yPix == 0 || yPix == Y_MX_SIZE - 1)
        continue;

      h2_CE65_nb_of_hits->Fill(xPix, yPix, hPixSignalSpectra[xPix][yPix]->GetEntries());
      h2_CE65_signal_mean->Fill(xPix, yPix, hPixSignalSpectra[xPix][yPix]->GetMean());
      h2_CE65_signal_width->Fill(xPix, yPix, hPixSignalSpectra[xPix][yPix]->GetRMS());
    }
  }
}

void ce65TreeReader::FillSingleEvent()
{

  h_single_ev_signal_map->SetTitle("Signal map for event " + TString::Itoa(_iEvent, 10));

  for (int xPix = 0; xPix < X_MX_SIZE; xPix++)
  {
    for (int yPix = 0; yPix < Y_MX_SIZE; yPix++)
    {

      //	h_single_ev_time_signal 	-> Reset();
      // h_single_ev_signal_map 	-> Fill(xPix, yPix, frame->at(0).raw_amp[xPix][yPix]);

      h_single_ev_signal_map->Fill(xPix, yPix, frame->at(frame->size() - 1).raw_amp[xPix][yPix] - frame->at(0).raw_amp[xPix][yPix]);
      //	std::cout  << frame->at(0).raw_amp[xPix][yPix] << ",";
    }
  }
}

void ce65TreeReader::Process()
{

  TBenchmark *benchmark = new TBenchmark();
  benchmark->Start("SearchTime");

  // time_t begin, end;
  // float tdiff=0;
  // time(&begin);

  // Loop over events
  MSG(CNTR, "[TREE] Offline monitor running... wait for control plots.");

  if (!eveMax)
  {
    eveMax = _statisticFraction * tree->GetEntries();
  }
  MSG(INFO, "[CONF] max_event: " << eveMax);

  // --- start event roop ---

  for (signed int iEvent = _skipEvents; iEvent < eveMax; iEvent++)
  {
    _iEvent = iEvent;

    if (iEvent % 1000 == 0)
      std::cout << "iEvent: " << iEvent << std::endl;

    tree->GetEntry(iEvent);
    if (iEvent == (int)_skipEvents)
    {
      T0 = frame->at(0).time_stamp;
      std::cout << "T0 set to : " << T0 << std::endl;
    }

    // --- start frame roop ---
    for (int i = 1; i < frames_per_event; i++)
    {
      signalFrame = i;
      baselineFrame = i - 1;
      // std::cout << "Analysis for frames: " << signalFrame << " - " << baselineFrame << std::endl;

      FillSinglePixelRawSpectra(iEvent * 10 + i);
      FillSinglePixelSignalSpectra();

      // --- Cluster reset -> Clustering -> Fill histgrams ---
      resetClusters();
      Clustering();
      FillClusterHist();
    }

    if (iEvent == 1)
      FillSingleEvent();

    // MAKE CLUSTER

    if (terminate_process)
      break;
  } // iEvent end

  FillSignalMap();
  FillBaselineSpectra();

  std::cout << "Processing events + clusterization() time: ";
  benchmark->Show("SearchTime");
}

// This func just catches ctrl+c so that the .root file is actually written
// void ce65TreeReader::SignalHandler(int signum){
void SignalHandler(int signum)
{
  if (signum == SIGINT)
  {
    std::cout << "Caught Ctrl+c. Please wait while output .root file is written and execution terminates.\n"
              << std::flush;
    terminate_process = true;
  }
}
