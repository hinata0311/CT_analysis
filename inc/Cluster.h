#ifndef CLUSTER_h
#define CLUSTER_h

#include <vector>
#include <memory>
#include "Pixel.h"

class Cluster {
public:
    Cluster() = default;
    void addPixel(std::unique_ptr<Pixel> pixel);
    double colmun() const { return m_column; }
    double row() const { return m_row; }
    int charge() const { return m_charge; }
    int size() const;

    void setColumn(double col) { m_column = col; }
    void setRow(double row) { m_row = row; }
    void setCharge(double charge) { m_charge = charge; }
    void setClusterCenter(double x, double y ) {m_column = x; m_row = y;}

    const std::vector<const Pixel*> pixels() const;
    const Pixel* getSeedPixel() const;
    const std::vector<Pixel*> getNeighbors() const;


private:
    double m_column = 0;
    double m_row = 0;
    int m_charge = 0;
    int m_size = 0;
    std::vector<std::unique_ptr<Pixel>> m_pixels;
};

#endif
