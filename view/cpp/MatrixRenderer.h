//
// Created by liu86 on 24-7-22.
//

#ifndef MATRIXRENDERER_H
#define MATRIXRENDERER_H

#include <QImage>
#include <QQuickPaintedItem>

namespace neapu_ex_view {
class MatrixRenderer : public QQuickPaintedItem {
    Q_OBJECT

public:
    explicit MatrixRenderer(QQuickItem* parent = nullptr)
        : QQuickPaintedItem(parent)
    {
    }

protected:
    void paint(QPainter* painter) override;

public slots:
    void updateImage(const QString& imgID);

private:
    QImage m_image;
};
} // neapu_ex_view

#endif //MATRIXRENDERER_H