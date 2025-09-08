#ifndef PIXEL_h
#define PIXEL_h

class Pixel {
public:
    // --- Default Constructor ---
    Pixel() = default;
    // --- Donstructor takes arguments ---
    Pixel(int column, int row, int charge)
        : m_column(column), m_row(row), m_charge(charge) {}

    // --- Define method ---
    int column() const { return m_column; }
    int row() const { return m_row; }
    int charge() const { return m_charge; }

    void setColumn(int col) { m_column = col; }
    void setRow(int row) { m_row = row; }
    void setCharge(int charge) { m_charge = charge; }

private:
    int m_column;
    int m_row;
    int m_charge = 0;
};

#endif
