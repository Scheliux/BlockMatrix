#include "BlockMatrix.h"

BlockMatrix::BlockMatrix(const std::string& filename)
{
    std::ifstream f(filename.c_str());
    if (f.fail()) throw BlockMatrix::OPEN_ERROR;
    int num;
    f >> _b1 >> _b2;
    for (unsigned int i = 0; i < _b1*_b1; ++i)
    {
        f >> num;
        _block1.push_back(num);
    }
    for (unsigned int i = 0; i < _b2*_b2; ++i)
    {
        f >> num;
        _block2.push_back(num);
    }
    if (double(_b1) != sqrt(_block1.size()) || double(_b2) != sqrt(_block2.size())) throw BlockMatrix::INPUT_ERROR;
}

BlockMatrix::BlockMatrix(const std::vector<int>& vec1, const std::vector<int>& vec2)
{
    _b1 = sqrt(vec1.size());
    _b2 = sqrt(vec2.size());
    for (unsigned int i = 0; i < vec1.size(); ++i)
        _block1.push_back(vec1[i]);
    for (unsigned int i = 0; i < vec2.size(); ++i)
        _block2.push_back(vec2[i]);
    if (double(_b1) != sqrt(_block1.size()) || double(_b2) != sqrt(_block2.size())) throw BlockMatrix::INPUT_ERROR;
}

int BlockMatrix::getElem(const unsigned int i, const unsigned int j) const
{
    if (i+1 <= _b1 && j+1 <= _b1)
        return _block1[_b1*i+j];
    else if (i >= _b1 && j >= _b1 && i < _b1+_b2 && j < _b1+_b2)
        return _block2[_b2*(i-_b1)+j-_b1];
    else if (i < _b1+_b2 && j < _b1+_b2)
        return 0;
    else
        throw BlockMatrix::OVERINDEXED;
}

BlockMatrix operator+ (const BlockMatrix& a, const BlockMatrix& b)
{
    if (a._b1 != b._b1 || a._b2 != b._b2) throw BlockMatrix::DIFFERENT_SIZE;

    std::vector<int> result1;
    std::vector<int> result2;

    for (unsigned int i = 0; i < a._b1*a._b1; ++i)
        result1.push_back(a._block1[i] + b._block1[i]);
    for (unsigned int i = 0; i < a._b2*a._b2; ++i)
        result2.push_back(a._block2[i] + b._block2[i]);

    return BlockMatrix(result1, result2);
}

BlockMatrix operator* (const BlockMatrix& a, const BlockMatrix& b)
{
    if (a._b1 != b._b1 || a._b2 != b._b2) throw BlockMatrix::DIFFERENT_SIZE;

    std::vector<int> result1;
    std::vector<int> result2;

    for (unsigned int i = 0; i < a._b1; ++i)
        for (unsigned int j = 0; j < a._b1; ++j)
        {
            int s = 0;
            for (unsigned int k = 0; k < a._b1; ++k)
                s += a.getElem(i, k) * b.getElem(k, j);
            result1.push_back(s);
        }

    for (unsigned int i = 0; i < a._b2; ++i)
        for (unsigned int j = 0; j < a._b2; ++j)
        {
            int s = 0;
            for (unsigned int k = 0; k < a._b2; ++k)
                s += a.getElem(i+a._b1, k+a._b1) * b.getElem(k+a._b1, j+a._b1);
            result2.push_back(s);
        }

    return BlockMatrix(result1, result2);
}

std::ostream& operator<< (std::ostream& os, const BlockMatrix& BM) {
    for (unsigned int i = 0; i < BM._b1; ++i)
    {
        for (unsigned int j = 0; j < BM._b1; ++j)
            os << BM._block1[i*BM._b1+j] << " ";
        for (unsigned int j = 0; j < BM._b2; ++j)
            os << "0 ";
        os << "\n";
    }

    for (unsigned int i = 0; i < BM._b2; ++i)
    {
        for (unsigned int j = 0; j < BM._b1; ++j)
            os << "0 ";
        for (unsigned int j = 0; j < BM._b2; ++j)
            os << BM._block2[i*BM._b2+j] << " ";
        os<< "\n";
    }

	return os;
}

bool BlockMatrix::operator== (const BlockMatrix& BM)
{
    bool l = true;
    l = this->_b1 == BM._b1 && this->_b2 == BM._b2;
    for (unsigned int i = 0; i < BM._block1.size(); ++i)
        l = l && BM._block1[i] == this->_block1[i];
    for (unsigned int i = 0; i < BM._block2.size(); ++i)
        l = l && BM._block2[i] == this->_block2[i];
    return l;
}
