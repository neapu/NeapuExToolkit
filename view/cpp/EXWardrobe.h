//
// Created by liu86 on 24-7-21.
//

#ifndef EXWARDROBE_H
#define EXWARDROBE_H
#include <qobject.h>
#include <QQmlEngine>

#include "NPKImageListModel.h"
#include "../npk/NPKHandler.h"

namespace neapu_ex_view {

class EXWardrobe : public QObject{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit EXWardrobe(QObject* parent = nullptr);
    ~EXWardrobe() override = default;
    static std::shared_ptr<EXWardrobe> getInstance();

    Q_PROPERTY(QString title READ title NOTIFY titleChanged)

    // Image属性
    Q_PROPERTY(int imgVersion READ imgVersion NOTIFY imgVersionChanged)
    Q_PROPERTY(int totalFrames READ totalFrames NOTIFY totalFramesChanged)
    Q_PROPERTY(int currentFrame READ currentFrame NOTIFY currentFrameChanged)
    Q_PROPERTY(int paletteCount READ paletteCount NOTIFY paletteCountChanged)
    Q_PROPERTY(int currentPaletteIndex READ currentPaletteIndex NOTIFY currentPaletteIndexChanged)

    // Frame属性
    Q_PROPERTY(QVariantMap frameProperty READ frameProperty NOTIFY framePropertyChanged)

    QString title() const { return m_title; }
    int imgVersion() const;
    QVariantMap frameProperty() const;
    int totalFrames() const { return m_totalFrames; }
    int currentFrame() const;   // QML界面显示用，内部逻辑不从这里获取
    int paletteCount() const;
    int currentPaletteIndex() const; // QML界面显示用，内部逻辑不从这里获取

    Q_INVOKABLE void openNpk(QUrl path);
    Q_INVOKABLE void nextFrame();
    Q_INVOKABLE void lastFrame();
    Q_INVOKABLE void nextPalette();
    Q_INVOKABLE void lastPalette();

    NPKImageListModel* getNPKImageListModel() const { return m_npkImageListModel; }
    QImage getImageFromID(QString imgID);

signals:
    void titleChanged();
    void imgVersionChanged();
    void framePropertyChanged();
    void totalFramesChanged();
    void currentFrameChanged();
    void paletteCountChanged();
    void currentPaletteIndexChanged();
    void frameChanged(QString imgID); // QImage无法直接在QML中使用，只能在EXWardrobe中做一个缓存

private:
    void updateFrame();
    std::shared_ptr<neapu_ex_npk::NPKImageHandler> getCurrentImage() const;

private:
    NPKImageListModel* m_npkImageListModel{nullptr};
    std::shared_ptr<neapu_ex_npk::NPKHandler> m_npkHandler{nullptr};

    QString m_title;
    uint32_t m_currentFrame{0};
    uint32_t m_totalFrames{0};
    int m_currentPaletteIndex{0};

    QMap<QString, QImage> m_frameCache;

    static std::shared_ptr<EXWardrobe> m_instance;
};

} // neapu_ex_view

#endif //EXWARDROBE_H
