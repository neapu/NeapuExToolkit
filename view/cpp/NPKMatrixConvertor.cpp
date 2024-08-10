//
// Created by liu86 on 24-7-26.
//

#include "NPKMatrixConvertor.h"
#include "NPKMatrix.h"
#include <QDebug>

namespace neapu_ex_view {
QImage NPKMatrixConvertor::npkMatrixToQImage(const std::shared_ptr<neapu_ex_npk::NPKMatrix>& matrix)
{
    // 将像素点矩阵转换为QImage
    const auto width = matrix->canvasWidth();
    const auto height = matrix->canvasHeight();
    const auto dataSize = width * height * 4;
    QImage img(width, height, QImage::Format_ARGB32);
    auto* bits = img.bits();
    const int ret = memcpy_s(bits, dataSize, matrix->data(), dataSize);
    if (ret != 0) {
        qWarning() << "Failed to copy data to QImage.";
    }
    return img;
}
} // neapu_ex_view