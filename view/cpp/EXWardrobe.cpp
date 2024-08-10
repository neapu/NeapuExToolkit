//
// Created by liu86 on 24-7-21.
//

#include "EXWardrobe.h"

#include <QImage>
#include <QUuid>

#include "NPKImageHandler.h"
#include "NPKPublic.h"
#include "NPKMatrixConvertor.h"

namespace neapu_ex_view {
std::shared_ptr<EXWardrobe> EXWardrobe::m_instance = nullptr;

EXWardrobe::EXWardrobe(QObject* parent)
    : QObject(parent)
{
    m_npkImageListModel = new NPKImageListModel(this);
    m_title = "未打开";

    connect(m_npkImageListModel, &NPKImageListModel::selectedIndexChanged, [this](int index) {
        m_currentFrame = 0;
        m_currentPaletteIndex = 0;
        m_totalFrames = m_npkHandler->getImage(index)->getFrameCount();
        updateFrame();
        emit totalFramesChanged();
        emit currentFrameChanged();
        emit imgVersionChanged();
        emit paletteCountChanged();
        emit currentPaletteIndexChanged();
    });
}

std::shared_ptr<EXWardrobe> EXWardrobe::getInstance()
{
    if (!m_instance) {
        m_instance = std::make_shared<EXWardrobe>();
    }
    return m_instance;
}

int EXWardrobe::imgVersion() const
{
    if (!m_npkHandler) return 0;
    auto img = m_npkHandler->getImage(m_npkImageListModel->selectedIndex());
    if (img) {
        return img->version();
    }
    return 0;
}

QVariantMap EXWardrobe::frameProperty() const
{
    // 帧相关的属性暴露给QML
    QVariantMap map;
    map["colorType"] = "UNKNOWN";
    map["width"] = 0;
    map["height"] = 0;
    map["is_link"] = 0;
    map["link_info"] = "";
    map["is_dds"] = 0;
    map["dds_info"] = "";
    map["dds_index"] = 0;

    if (!m_npkHandler) return map;
    auto img = m_npkHandler->getImage(m_npkImageListModel->selectedIndex());
    if (!img) return map;


    neapu_ex_npk::ColorType type = img->getFrameColorType(m_currentFrame);

    map["colorType"] = QString::fromStdString(neapu_ex_npk::colorTypeToString(type));
    map["width"] = img->getFrameWidth(m_currentFrame);
    map["height"] = img->getFrameWidth(m_currentFrame);
    map["is_link"] = img->getFrameIsLink(m_currentFrame);
    map["link_info"] = QString::fromStdString(img->getFrameLinkInfo(m_currentFrame));
    map["is_dds"] = img->getFrameIsDDS(m_currentFrame);
    map["dds_info"] = QString::fromStdString(img->getFrameDDSClipInfo(m_currentFrame));
    map["dds_index"] = img->getFrameDDSIndex(m_currentFrame);
    return map;
}

int EXWardrobe::currentFrame() const
{
    if (totalFrames() == 0) return 0;
    return m_currentFrame + 1;
}

int EXWardrobe::paletteCount() const
{
    auto img = getCurrentImage();
    if (!img) return 0;
    return img->getPalletCount();
}

int EXWardrobe::currentPaletteIndex() const
{
    if (paletteCount() == 0) return 0;
    return m_currentPaletteIndex + 1;
}

void EXWardrobe::openNpk(QUrl path)
{
    qDebug() << "Open NPK: " << path;
    m_npkHandler = std::make_shared<neapu_ex_npk::NPKHandler>();
    if (!m_npkHandler->loadNPK(path.toLocalFile().toStdString())) {
        qCritical() << "Failed to load NPK: " << path.toLocalFile();
        return;
    }

    m_title = QString::fromStdString(m_npkHandler->getNpkName());
    emit titleChanged();

    m_npkImageListModel->setImages(m_npkHandler->getImages());
    if (m_npkHandler->getImageCount() != 0) {
        m_npkImageListModel->setSelectedIndex(0);
    }
}

void EXWardrobe::nextFrame()
{
    if (m_totalFrames == 0 || m_totalFrames == 1) return;
    if (m_currentFrame < m_totalFrames - 1) {
        m_currentFrame++;
        emit currentFrameChanged();
    } else {
        m_currentFrame = 0;
        emit currentFrameChanged();
    }
    updateFrame();
}

void EXWardrobe::lastFrame()
{
    if (m_totalFrames == 0 || m_totalFrames == 1) return;
    if (m_currentFrame > 0) {
        m_currentFrame--;
        emit currentFrameChanged();
    } else {
        m_currentFrame = m_totalFrames - 1;
        emit currentFrameChanged();
    }
    updateFrame();
}

void EXWardrobe::nextPalette()
{
    auto _paletteCount = paletteCount();
    if (_paletteCount == 0 || _paletteCount == 1) return;
    if (m_currentPaletteIndex < _paletteCount - 1) {
        m_currentPaletteIndex++;
        emit currentPaletteIndexChanged();
    } else {
        m_currentPaletteIndex = 0;
        emit currentPaletteIndexChanged();
    }
    updateFrame();
}

void EXWardrobe::lastPalette()
{
    auto _paletteCount = paletteCount();
    if (_paletteCount == 0 || _paletteCount == 1) return;
    if (m_currentPaletteIndex > 0) {
        m_currentPaletteIndex--;
        emit currentPaletteIndexChanged();
    } else {
        m_currentPaletteIndex = _paletteCount - 1;
        emit currentPaletteIndexChanged();
    }
    updateFrame();
}

QImage EXWardrobe::getImageFromID(QString imgID)
{
    return m_frameCache[imgID];
}

void EXWardrobe::updateFrame()
{
    emit framePropertyChanged();
    QString imgID = "ExplorerMain";
    auto img = m_npkHandler->getImage(m_npkImageListModel->selectedIndex());
    if (!img) {
        qCritical() << "Failed to get image.";
        return;
    }

    const auto matrix = img->getFrameMatrix(m_currentFrame);
    if (!matrix) {
        qWarning() << "Failed to get matrix.";
        m_frameCache[imgID] = {};
        emit frameChanged(imgID);
        return;
    }

    m_frameCache[imgID] = NPKMatrixConvertor::npkMatrixToQImage(matrix);
    emit frameChanged(imgID);
}

std::shared_ptr<neapu_ex_npk::NPKImageHandler> EXWardrobe::getCurrentImage() const
{
    if (!m_npkHandler) return nullptr;
    return m_npkHandler->getImage(m_npkImageListModel->selectedIndex());
}
} // neapu_ex_view