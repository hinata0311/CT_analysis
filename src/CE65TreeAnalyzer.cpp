// -----------------------------------------------------------------------
// ------------------------- Compilation ---------------------------------
// `root-config --cxx` `root-config --cflags`  -O2 -W CE65TreeAnalyzer.cpp -o offline_analysis `root-config --ldflags` `root-config --glibs`
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------

#include "CE65TreeAnalyzer.h"

bool terminate_process = false;

void CE65TreeAnalyzer::OpenOutTree(TString sufix = "")
{
  _out_data_file = TFile::Open(_output_data_dir + _input_data_name + sufix + ".root", "recreate");
  MSG(INFO, "[CONF] Output file created: " << "../data/" + _input_data_name + sufix + ".root");
  _out_data_file->cd();
}

void CE65TreeAnalyzer::ReadCalibData(TString dc_calib_path = "no_path", TString ac_calib_path = "no_path")
{
  if (!(ac_calib_path == "no_path")){
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
    TFile * f_ac_calib_data = new TFile(ac_calib_path);
    h2_ac_gain_map = (TH2D *)f_ac_calib_data->Get("h2_ac_gain_map");
    MSG(CNTR, "[CNTR]  AC  Gain tree loaded: " << h2_ac_gain_map->GetBinContent(45, 15) << h2_ac_gain_map->GetTitle());
  }
}

void CE65TreeAnalyzer::CloseOutTree()
{
  _out_data_file->cd();
  _out_data_file->Write();
  //_out_data_file ->Close();
}

// HistoInit ----------------------------------------------------------------------------------

void CE65TreeAnalyzer::HistoInit()
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

  TDirectory *eve_directory = directory->mkdir("1eve_hitmaps");
  eve_directory->cd();
  for (int i = 0; i < 10; ++i)
  {
    h2_1eve_clstr_hitmap[i] = new TH2D(
        "h2_1eve_clstr_hitmap[" + TString::Itoa(i, 11) + "]",
        "h2_1eve_clstr_hitmap[" + TString::Itoa(i, 11) + "]",
        X_MX_SIZE, 0, X_MX_SIZE, Y_MX_SIZE, 0, Y_MX_SIZE);
    //h2_pixel_hitmap[i] = new TH2D(
        // "h2_pixel_hitmap[" + TString::Itoa(i, 11) + "]",
        // "h2_pixel_hitmap[" + TString::Itoa(i, 11) + "]",
        // X_MX_SIZE, 0, X_MX_SIZE, Y_MX_SIZE, 0, Y_MX_SIZE);
  }

  TDirectory *cluster_charge_directory = directory->mkdir("cluster_charge");
  cluster_charge_directory->cd();
  for (int i = 0; i < 5; ++i)
  {
    h1_cluster_charge[i] = new TH1D(
        "h_cluster_charge[" + TString::Itoa(i, 11) + "]",
        "h_cluster_charge[" + TString::Itoa(i, 11) + "];charge [ke^-];count",
        1000,0,15);
  } 

  directory->cd();

  h_baseline = new TH1D("h_baseline", "MX AapAC baseline;baseline [ADU];#", DAC_BOARD_ADC_MAX_COUNTS / 10, -DAC_BOARD_ADC_MAX_COUNTS / 2, DAC_BOARD_ADC_MAX_COUNTS / 2);

  h_noise = new TH1D("h_noise", "MX AapAC noise;noise [ADU];#", 200, 0, 2000);

  h_cluster_size = new TH1D("h_cluster_size", "cluster size;cluster size;#", 20, 0.5, 20.5);

  h2_CE65_baseline = new TH2D("h2_CE65_baseline", "baseline;baseline [ADU];#", X_MX_SIZE, 0, X_MX_SIZE, Y_MX_SIZE, 0, Y_MX_SIZE);
  h2_CE65_noise = new TH2D("h2_CE65_noise", "noise;noise [ADU];#", X_MX_SIZE, 0, X_MX_SIZE, Y_MX_SIZE, 0, Y_MX_SIZE);

  h2_CE65_signal_mean = new TH2D("h2_CE65_signal_mean", "signal mean;signal_mean [ADU];#", X_MX_SIZE, 0, X_MX_SIZE, Y_MX_SIZE, 0, Y_MX_SIZE);
  h2_CE65_signal_width = new TH2D("h2_CE65_signal_width", "signal width;signal width [ADU];#", X_MX_SIZE, 0, X_MX_SIZE, Y_MX_SIZE, 0, Y_MX_SIZE);

  h_single_ev_signal_map = new TH2D("h_single_ev_signal_map", "h_single_ev_signal_map;#X; Y", X_MX_SIZE, 0, X_MX_SIZE, Y_MX_SIZE, 0, Y_MX_SIZE);
  c_single_ev_time_signal = new TCanvas("c_single_ev_time_signal", "c_single_ev_time_signal", 1200, 800);
  c_single_ev_time_signal->SetGrid();

  //	--------------------------------------------------------------------------
  h_noisy_pix_map = new TH2D("h_noisy_pix_map", "h_noisy_pix_map;#X; Y", X_MX_SIZE, 0, X_MX_SIZE, Y_MX_SIZE, 0, Y_MX_SIZE);
  h_cluster_hit_map = new TH2D("h_cluster_hit_map", "h_cluster_hit_map;#X; Y", X_MX_SIZE, 0, X_MX_SIZE, Y_MX_SIZE, 0, Y_MX_SIZE);
  h_cluster_multiplicity = new TH1D("h_cluster_multiplicity", "h_cluster_multiplicity; event frame ; cluster multiplicity", 100000, 0, 100000);

  h_cluster_charge = new TH1D("h_cluster_charge", "cluster charge;charge [ADCu]; count", 5000, 0, 50000);
  h_seed_charge = new TH1D("h_seed_charge", "h_seed_charge;charge [ADCu]; count", 5000, 0, 50000);
  h_neighbor_charge = new TH1D("h_neighbor_charge", "neighbor charge; [ADCu]; count", 5000, 0, 50000);

  h_cluster_charge_calibrated = new TH1D("h_cluster_charge_calibrated", "cluster charge calibrated;charge [ke^-]; count", 1500, 0, 15);
  h_seed_charge_calibrated = new TH1D("h_seed_charge_calibrated", "h_seed_charge calibrated;charge [ke^-]; count", 1000, 0, 10);
  h_neighbor_charge_calibrated = new TH1D("h_neighbor_charge_calibrated", "neighbor charge calibrated; [ke^-]; count", 1000, 0, 15);

  h_seed_vs_neighbor = new TH2D("h_seed_vs_neighbor", "seed vs neighbor charge;seed charge [ADCu];neighbor charge [ADCu]", 100, -1000, 10000, 100, -1000, 10000);
  h_seed_vs_neighbors = new TH2D("h_seed_vs_neighbors", "seed vs neighbor charge;seed charge [ADCu];neighbor charge [ADCu]", 100, -1000, 10000, 100, -1000, 10000);

  h_charge_vs_size = new TH2D("h_charge_vs_size", "cluster charge vs cluster size;cluster charge [ADCu]; cluster size [pixels]", 100, -1000, 10000, 20, -2, 18);
  h_seedcharge_vs_size = new TH2D("h_seedcharge_vs_size", "seed charge vs cluster size;cluster charge [ADCu]; cluster size [pixels]", 100, -1000, 10000, 20, -2, 18);

  h_cluster_mat_charge = new TH2D("h_cluster_mat_charge", "mean charge in cluster matrix", 3, -1.5, 1.5, 3, -1.5, 1.5);
  h_cluster_mat_ratio = new TH2D("h_cluster_mat_ratio", "ratio in cluster matrix", 3, -1.5, 1.5, 3, -1.5, 1.5);

  h_pixel_charge_calibrated = new TH1D("h_pixel_charge_calibrated", "pixel charge calibrated;charge [e^-]; count", 15000, 0, 15000);

  h2_size_vs_cluster_charge = new TH2D("h2_size_vs_cluster_charge", "cluster size vs cluster charge;cluster size [pixels]; cluster charge [ke^-]", 15, 0.5, 15.5, 100, 0, 15);

  h2_clustersize4 = new TH2D("h2_clustersize4", "cluster size = 4 histogtram",4.0,0.5,4.5,4.0,0.5,4.5);

  //h2_pixel_hitmap = new TH2D("h2_pixel_hitmap", "pixel hitmap;#X; Y", X_MX_SIZE, 0, X_MX_SIZE, Y_MX_SIZE, 0, Y_MX_SIZE);
}

// LoadTree --------------------------------------------------------------------------------

int CE65TreeAnalyzer::LoadTree()
{

  MSG(CNTR, "[TREE] Loading input tree/trees...");

  std::string name;
  _input_tree_name = "CE65Data";

  name = _input_data_dir + _input_data_name + ".root";
  TFile *f = new TFile(static_cast<TString>(name));

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

  tree = (TTree *)f->Get(static_cast<TString>(_input_tree_name));

  tree->SetBranchAddress("ev_number", &ev_number);
  tree->SetBranchAddress("frames_per_event", &frames_per_event);
  tree->SetBranchAddress("frame", &frame);
  tree->GetEntry(0);

  this->TreeInfo();
  MSG(CNTR, "[TREE]  Tree loaded");

  return 1;
}

// TreeInfo ---------------------------------------------------------

void CE65TreeAnalyzer::TreeInfo()
{
  MSG(INFO, "[TREE] Entires in tree: " << tree->GetEntries());
  MSG(INFO, "[TREE] Skipped events in the analysis: " << _skipEvents << ". " << _statisticFraction*100. << "% of the statistic will be analysed");
  MSG(INFO, "[TREE] ev_number: " << ev_number);
  MSG(INFO, "[TREE] frames_per_event: " << frames_per_event);
}

// ------------------------------------------------------------------

void CE65TreeAnalyzer::FillSinglePixelRawSpectra(int iFrame)
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

void CE65TreeAnalyzer::FillSinglePixelSignalSpectra()
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

std::vector<std::unique_ptr<Pixel>> CE65TreeAnalyzer::findSeedCandidates()
{
  std::vector<std::unique_ptr<Pixel>> seed_candidates;
  int signal;
  // default _skip_edge_seed = 2;
  for (int x = 0 + _skip_edge_seed; x < X_MX_SIZE - _skip_edge_seed; x++)
  {
    for (int y = 0 + _skip_edge_seed; y < Y_MX_SIZE - _skip_edge_seed; y++)
    {
      signal = frame->at(signalFrame).raw_amp[x][y] - frame->at(baselineFrame).raw_amp[x][y];

      h_pixel_charge_calibrated->Fill(signal*_calib_factor);
      if (signal > _threshold_seed && !isMasked(x, y))
      {
        seed_candidates.push_back(std::make_unique<Pixel>(x, y, signal));
      }
    }
  }
  return seed_candidates;
}

bool CE65TreeAnalyzer::isMasked(int x, int y)
{
  std::vector<std::pair<int, int>> masked_pixels = {
    {2,7}, {45,8}, {13,4},{27,8}
  };
  std::pair<int, int>target = std::make_pair(x, y);
  return target == masked_pixels[0] || target == masked_pixels[1] || target == masked_pixels[2] || target == masked_pixels[3];
}

bool CE65TreeAnalyzer::isWithinBounds(int x, int y)
{
  // default _skip_edge_clustering = 1;
  return x >= _skip_edge_clustering && x < X_MX_SIZE - _skip_edge_clustering &&
         y >= _skip_edge_clustering && y < Y_MX_SIZE - _skip_edge_clustering;
}

void CE65TreeAnalyzer::Clustering()
{
  std::vector<std::unique_ptr<Pixel>> seed_candidates = findSeedCandidates();
  std::set<std::pair<int, int>> used_pixels;
  int tmpX, tmpY;

  // sort by charge
  std::sort(
    seed_candidates.begin(), seed_candidates.end(),
    [](const std::unique_ptr<Pixel>& a, const std::unique_ptr<Pixel>& b)
    {
    return a->charge() > b->charge();
    }
  );

  for (auto &seed : seed_candidates)
  {
    int current_x = seed->column();
    int current_y = seed->row();
    double seed_charge = seed->charge();

    // Check if the current seed has already been used in another cluster->
    if (used_pixels.count({current_x, current_y}))
    {
      continue;
    }

    // Initialize a new cluster and its properties.
    std::unique_ptr<Cluster> new_cluster = std::make_unique<Cluster>();
    std::queue<std::pair<int, int>> pixel_queue;

    // Add the seed pixel to the queue and mark it as used.
    pixel_queue.push({current_x, current_y});
    used_pixels.insert({current_x, current_y});

    // Add the seed pixel to the new cluster.
    new_cluster->addPixel(std::move(seed));
    new_cluster->setColumn(current_x);
    new_cluster->setRow(current_y);

    // Use a breadth-first search (BFS) to find all adjacent pixels.
    do
    {
      // pixels should be explored is listed
      std::pair<int, int> current_pixel_coords = pixel_queue.front();
      pixel_queue.pop();

      int x = current_pixel_coords.first;
      int y = current_pixel_coords.second;
      int neighbor_mat = 0;

      // Search the 8 neighboring pixels.
      for (int dx = -1; dx <= 1; ++dx)
      {
        for (int dy = -1; dy <= 1; ++dy)
        {
          // Skip the current pixel itself.
          if (dx == 0 && dy == 0)
            continue;

          int neighbor_x = x + dx;
          int neighbor_y = y + dy;

          // Check if the neighbor is within bounds and has not been used yet.
          if (isWithinBounds(neighbor_x, neighbor_y) && used_pixels.count({neighbor_x, neighbor_y}) == 0 && !isMasked(neighbor_x, neighbor_y)) 
          {
            int neighbor_signal = frame->at(signalFrame).raw_amp[neighbor_x][neighbor_y] - frame->at(baselineFrame).raw_amp[neighbor_x][neighbor_y];
            if (_clustering_method == "CLUSTER")
            {
              this->setNbhrTh(_threshold_seed);
            }
            // Check if the neighbor signal exceeds the adjacency threshold.
            if (neighbor_signal > _threshold_neighbor)
            {
              // Add the neighbor to the queue and mark it as used.
              pixel_queue.push({neighbor_x, neighbor_y});
              used_pixels.insert({neighbor_x, neighbor_y});

              // Add the neighbor to the new cluster.
              // std::unique_ptr<Pixel> neighbor = ;
              new_cluster->addPixel(std::make_unique<Pixel>(neighbor_x, neighbor_y, neighbor_signal));
              _neighbor_mat_charge[neighbor_mat] += neighbor_signal;
              _neighbor_mat_number[neighbor_mat] ++;
            }
          }
          neighbor_mat++;
        }
      }
      if (_clustering_method == "WINDOW") {
        break;
      }
    } while (!pixel_queue.empty());
    setCluster(std::move(new_cluster));
  }
}

void CE65TreeAnalyzer::CalClusterPos() {
  double sum_charge_cross_x ;
  double sum_charge_cross_y ;
  for (auto &cluster : getClusters()) {
    sum_charge_cross_x = 0;
    sum_charge_cross_y = 0;
    for (auto & pixel : cluster->pixels()) {
      sum_charge_cross_x += pixel->column() * pixel->charge();
      sum_charge_cross_y += pixel->row() * pixel->charge();
    }
    cluster->setClusterCenter(
      sum_charge_cross_x / cluster->charge(),
      sum_charge_cross_y / cluster->charge()
    );
  }

}

// void CE65TreeAnalyzer::FillPixelHist()
// {
//   for(const auto & cluster : getClusters()) {
//     for(auto & pixel : cluster->pixels()) {
//       h2_pixel_hitmap->Fill(pixel->column(), pixel->row());
//     }
//   }
// }

void CE65TreeAnalyzer::FillClusterHist()
{

  for (const auto &cluster : getClusters())
  {
    h_cluster_hit_map->Fill(cluster->colmun(), cluster->row());
    h_cluster_size->Fill(cluster->size());
    h_cluster_charge->Fill(cluster->charge());
    h_cluster_charge_calibrated->Fill(cluster->charge()* _calib_factor / 1000);

    int seed_charge = cluster->getSeedPixel()->charge();
    h_seed_charge->Fill(seed_charge);
    h_seed_charge_calibrated->Fill(seed_charge* _calib_factor / 1000);

    h2_size_vs_cluster_charge->Fill(cluster->size(), cluster->charge()* _calib_factor / 1000);

    if(cluster->size() == 1) {
      h1_cluster_charge[0]->Fill(cluster->charge()* _calib_factor / 1000);
    } else if(cluster->size() == 2) {
      h1_cluster_charge[1]->Fill(cluster->charge()* _calib_factor / 1000);
    } else if(cluster->size() == 3) {
      h1_cluster_charge[2]->Fill(cluster->charge()* _calib_factor / 1000);
    } else if(cluster->size() == 4) {
      h1_cluster_charge[3]->Fill(cluster->charge()* _calib_factor / 1000);
      h2_clustersize4 -> Fill(cluster->colmun(),cluster->row());
    } else if(cluster->size() <= 5) {
      h1_cluster_charge[4]->Fill(cluster->charge()* _calib_factor / 1000);
    }

    

    for (const auto &neighbor : cluster->getNeighbors())
    {
      int neighbor_charge = neighbor->charge();
      h_neighbor_charge->Fill(neighbor_charge);
      h_neighbor_charge_calibrated->Fill(neighbor_charge * _calib_factor / 1000);
      h_seed_vs_neighbor->Fill(seed_charge, neighbor_charge);
    }
    h_seed_vs_neighbors->Fill(seed_charge, cluster->charge());
    h_charge_vs_size->Fill(cluster->charge(), cluster->size());
    h_seedcharge_vs_size->Fill(seed_charge, cluster->size());
  }

  int multiplicity = getClusters().size();

  // add new code ////////////////////////////////////////////////////////////////

  
  h_cluster_multiplicity->Fill(_iEvent, multiplicity);
  

  ///////////////////////////////////////////////////////////////////////////////

  if (multiplicity > 10 && _i_saved_to_1eveh2hitmap < 10)
  {
    for (const auto &cluster : getClusters())
    {
      h2_1eve_clstr_hitmap[_i_saved_to_1eveh2hitmap]->Fill(cluster->colmun(), cluster->row());
      //h2_pixel_hitmap[_i_saved_to_1eveh2hitmap]->Fill(cluster->getSeedPixel()->column(), cluster->getSeedPixel()->row());
    }
    // for (const auto &pixel : frame->at(signalFrame).raw_amp)
    // {
    //   h2_pixel_hitmap[_i_saved_to_1eveh2hitmap] -> Fill(pixel.colmun(), pixel.row());
    // }
    _i_saved_to_1eveh2hitmap++;
  }
}

void CE65TreeAnalyzer::FillClusterMatrix() {
  int mat = 0;
  double total_neighbors = std::accumulate(_neighbor_mat_number.begin(), _neighbor_mat_number.end(), 0.0);

  for (int dx = -1; dx <= 1; ++dx) {
    for (int dy = -1; dy <= 1; ++dy) {
      double neighbor_ratio = static_cast<double>(_neighbor_mat_number[mat])/total_neighbors;
      if (dx==0 && dy ==0) {
        h_cluster_mat_charge->Fill(dx+1, dy+1, h_seed_charge->GetMean());
        // h_cluster_mat_ratio->Fill(dx+1, dy+1, 1);
      } else {
        if(_neighbor_mat_number[mat] != 0) {
          h_cluster_mat_charge->Fill(dx, dy, _neighbor_mat_charge[mat]/_neighbor_mat_number[mat]);
          h_cluster_mat_ratio->Fill(dx, dy, neighbor_ratio);
        } else {
          h_cluster_mat_charge->Fill(dx, dy, _neighbor_mat_charge[mat]);
          h_cluster_mat_ratio->Fill(dx, dy, neighbor_ratio);
        }
        mat++;
      }
    }
  }
}

void CE65TreeAnalyzer::FillBaselineSpectra()
{

  for (int xPix = 0; xPix < X_MX_SIZE; xPix++)
  {
    for (int yPix = 0; yPix < Y_MX_SIZE; yPix++)
    {
      h2_CE65_baseline->Fill(xPix, yPix, hPixRawSpectra[xPix][yPix]->GetMean());
      h2_CE65_noise->Fill(xPix, yPix, hPixRawSpectra[xPix][yPix]->GetRMS());
      h_baseline->Fill(hPixRawSpectra[xPix][yPix]->GetMean());
      h_noise->Fill(hPixRawSpectra[xPix][yPix]->GetRMS());
    }
  }
}

void CE65TreeAnalyzer::FillSignalMap()
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
      h2_CE65_signal_mean->Fill(xPix, yPix, hPixSignalSpectra[xPix][yPix]->GetMean());
      h2_CE65_signal_width->Fill(xPix, yPix, hPixSignalSpectra[xPix][yPix]->GetRMS());
    }
  }
}

void CE65TreeAnalyzer::FillSingleEvent()
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

void CE65TreeAnalyzer::Process()
{

  TBenchmark *benchmark = new TBenchmark();
  benchmark->Start("SearchTime");

  // Loop over events
  MSG(CNTR, "[TREE] Offline monitor running... wait for control plots.");

  if (!_eve_max || _eve_max == -1)
  {
    _eve_max = _statisticFraction * tree->GetEntries();
  }
  MSG(INFO, "[CONF] max_event: " << _eve_max);

  constexpr auto ncols = 40;
  constexpr auto description = "\033[32m[EVENT ROOP]\033[0m";
  // --- Start event roop ---
  pbar::pbar bar(_eve_max, ncols, description);
  bar.enable_recalc_console_width(1);	
  bar.init();
  for (signed int iEvent = _skipEvents; iEvent < _eve_max; iEvent++, bar++)
  {
    // --- Get Tree ---
    _iEvent = iEvent;
    tree->GetEntry(iEvent);

    // --- Start frame roop ---
    for (int i = 1; i < frames_per_event; i++)
    {
      // --- Frame setting ---
      signalFrame = i;
      baselineFrame = i - 1;
      _iFrame ++;
      // --- Fill single pixel spevtra --- 
      FillSinglePixelRawSpectra(iEvent * 10 + i);
      FillSinglePixelSignalSpectra();
      // --- Cluster reset -> Clustering -> Fill histgrams ---
      resetClusters();
      Clustering();
      if(this->getClusters().size() < 6){
        continue;
      }
      FillClusterHist();
    }

    if (iEvent == 1)
      FillSingleEvent();

    if (terminate_process)
      break;
  } // iEvent end

  FillClusterMatrix();
  FillSignalMap();
  FillBaselineSpectra();
}

// This func just catches ctrl+c so that the .root file is actually written
// void CE65TreeAnalyzer::SignalHandler(int signum){
void SignalHandler(int signum)
{
  if (signum == SIGINT)
  {
    std::cout << "Caught Ctrl+c. Please wait while output .root file is written and execution terminates.\n"
              << std::flush;
    terminate_process = true;
  }
}
