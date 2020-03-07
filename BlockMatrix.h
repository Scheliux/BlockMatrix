#ifndef BLOCKMATRIX_H
#define BLOCKMATRIX_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

class BlockMatrix
{
    public:
        /// Querries
        /**unsigned int getSizeB1() {return _b1;}
        unsigned int getSizeB2() {return _b2;}
        std::vector<int> getBlock1() {return _block1;}
        std::vector<int> getBlock2() {return _block2;}*/

        enum Exceptions {OPEN_ERROR, OVERINDEXED, DIFFERENT_SIZE, INPUT_ERROR};

        BlockMatrix(const std::string& filename);
        BlockMatrix(const std::vector<int>& vec1, const std::vector<int>& vec2);
        int getElem(const unsigned int i, const unsigned int j) const;

        bool operator== (const BlockMatrix& BM);
        friend std::ostream& operator<< (std::ostream& os, const BlockMatrix& BM);
        friend BlockMatrix operator+ (const BlockMatrix& a, const BlockMatrix& b);
        friend BlockMatrix operator* (const BlockMatrix& a, const BlockMatrix& b);

    private:
        unsigned int _b1;
        unsigned int _b2;
        std::vector<int> _block1;
        std::vector<int> _block2;
};

#endif // BLOCKMATRIX_H
