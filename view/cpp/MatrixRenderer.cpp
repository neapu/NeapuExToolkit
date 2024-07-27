//
// Created by liu86 on 24-7-22.
//

#include "MatrixRenderer.h"
#include <QPainter>

#include "EXWardrobe.h"

namespace neapu_ex_view {
void MatrixRenderer::paint(QPainter* painter)
{
    // 黑色底
    painter->fillRect(this->boundingRect(), Qt::black);
    // painter->drawImage(0, 0, m_image.scaled(m_image.width()*2, m_image.height()*2));
    painter->drawImage(0, 0, m_image);
}

void MatrixRenderer::updateImage(const QString& imgID)
{
    m_image = EXWardrobe::getInstance()->getImageFromID(imgID);
    update();
}
} // neapu_ex_view