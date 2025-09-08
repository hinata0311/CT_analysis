#include "Cluster.h"

void Cluster::addPixel(std::unique_ptr<Pixel> pixel){
    int charge = pixel->charge();
    m_pixels.push_back(std::move(pixel));
    m_charge += charge;
    m_size ++;
}

const Pixel* Cluster::getSeedPixel() const {
    // Check if the pixel vector is empty.
    if (m_pixels.empty()) {
        return nullptr;
    }

    Pixel* seed_pixel = nullptr;
    double max_charge = -1.0;

    // Iterate through all pixels to find the one with the maximum charge.
    for (const auto& pixel : m_pixels) {
        auto* pxl = pixel.get();
        double current_charge = pixel->charge();
        if (current_charge > max_charge) {
            max_charge = current_charge;
            seed_pixel = pxl;
        }
    }
    return seed_pixel;
}

const std::vector<Pixel*> Cluster::getNeighbors() const{
    if(m_pixels.empty()){
        return {};
    }
    std::vector<Pixel*> neighbors;
    double max_charge = -1.0;
    const Pixel* seed_pixel = getSeedPixel();
    
    for(const auto& pixel : m_pixels){
        if(pixel.get() != seed_pixel){
            neighbors.push_back(pixel.get());
        }
    }
    return neighbors;
}

const std::vector<const Pixel*> Cluster::pixels() const {
    std::vector<const Pixel*> pixelvec;
    for(const auto& pixel : m_pixels) {
        auto* pxl = pixel.get();
        if(pxl == nullptr) {
            return{};
        }
        pixelvec.emplace_back(pxl);
    }
    return pixelvec;
}