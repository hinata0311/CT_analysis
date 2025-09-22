#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "json.hpp"

class ConfigManager {
public:
    /**
     * @brief Read configuration and initialization parameters
     * @param file_name path to json setting file
     * @throw std::runtime_error
     */
    explicit ConfigManager(std::string file_name) {
        // --- Open configuration file ---
        std::ifstream ifs(file_name);
        if (!ifs.is_open()) {
            throw std::runtime_error("Failed to open config file: " + file_name);
        }
        // --- Start reading json ---
        try {
            // Parse json
            ifs >> m_json;

            // Read parameters from json
            if (m_json.contains("input_dir")) {
                _input_dir = m_json.at("input_dir").get<std::string>();
            }
            if (m_json.contains("output_dir")) {
                _output_dir = m_json.at("output_dir").get<std::string>();
            }
            if (m_json.contains("input_data_name")) {
                _input_data_name = m_json.at("input_data_name").get<std::string>();
            }
            if (m_json.contains("skip_edge_seed")) {
                _skip_edge_seed = m_json.at("skip_edge_seed").get<int>();
            }
            if (m_json.contains("skip_edge_clustering")) {
                _skip_edge_clustering = m_json.at("skip_edge_clustering").get<int>();
            }
            if (m_json.contains("threshold_seed")) {
                _threshold_seed = m_json.at("threshold_seed").get<int>();
            }
            if (m_json.contains("threshold_neighbor")) {
                _threshold_neighbor = m_json.at("threshold_neighbor").get<int>();
            }
            if (m_json.contains("clustering_method")) {
                _clustering_method = m_json.at("clustering_method").get<std::string>();
            }
            if (m_json.contains("eve_max")) {
                _eve_max = m_json.at("eve_max").get<int>();
            }
            if (m_json.contains("calib_factor")) {
                _calib_factor = m_json.at("calib_factor").get<double>();
            }
        } catch (const nlohmann::json::exception& e) {
            throw std::runtime_error("JSON parsing error: " + std::string(e.what()));
        }
    }

    ConfigManager() = delete;
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

    ~ConfigManager() = default;

    // --- Method to access to private members ---
    const std::string& getInputDir() const { return _input_dir; }
    const std::string& getOutputDir() const { return _output_dir; }
    const std::string getInputDataName() const { return _input_data_name; }
    int getSkipEdgeSeed() const { return _skip_edge_seed; }
    int getSkipEdgeClustering() const { return _skip_edge_clustering; }
    int getThresholdSeed() const { return _threshold_seed; }
    int getThresholdNeighbor() const { return _threshold_neighbor; }
    const std::string& getClusteringMethod() const { return _clustering_method; }
    int getEveMax() const { return _eve_max; }
    double getCalibFactor() const { return _calib_factor; }

private:
    nlohmann::json m_json;
    std::string _input_dir;
    std::string _output_dir;
    std::string _input_data_name;
    double _calib_factor = 1;
    int _eve_max = -1;
    int _skip_edge_seed = 2;
    int _skip_edge_clustering = 1;
    int _threshold_seed = 1000;
    int _threshold_neighbor = 300; 
    std::string _clustering_method = "CLUSTER";
}; // class ConfigManager

#endif /* CONFIG_MANAGER_H */