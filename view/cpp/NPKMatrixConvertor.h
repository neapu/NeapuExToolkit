//
// Created by liu86 on 24-7-26.
//

#ifndef NPKMATRIXCONVERTOR_H
#define NPKMATRIXCONVERTOR_H
#include <QImage>

namespace neapu_ex_npk {
class NPKMatrix;
}

namespace neapu_ex_view {

class NPKMatrixConvertor {
public:
    static QImage npkMatrixToQImage(const std::shared_ptr<neapu_ex_npk::NPKMatrix>& matrix);
};

} // neapu_ex_view

#endif //NPKMATRIXCONVERTOR_H
