//
// Created by liu86 on 24-7-21.
//

#ifndef NPKIMAGELISTMODEL_H
#define NPKIMAGELISTMODEL_H

#include <QQmlEngine>
#include <QModelIndex>

namespace neapu_ex_npk {
class NPKImageHandler;
}

namespace neapu_ex_view {
class NPKImageListModel : public QAbstractListModel {
    Q_OBJECT
    QML_ELEMENT
public:
    explicit NPKImageListModel(QObject* parent = nullptr) : QAbstractListModel(parent) {}
    void setImages(const std::vector<std::shared_ptr<neapu_ex_npk::NPKImageHandler>>& images);

    Q_PROPERTY(int32_t selectedIndex READ selectedIndex WRITE setSelectedIndex NOTIFY selectedIndexChanged)

    int32_t selectedIndex() const { return m_selectedIndex; }
    void setSelectedIndex(int32_t index);

    int rowCount(const QModelIndex& parent) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex& index, int role) const override;

signals:
    void selectedIndexChanged(int index);

private:
    enum DataRoles {
        IndexRole = Qt::UserRole + 1,
        NameRole,
    };

    typedef struct NPKImage {
        int index;
        QString name;
    } NPKImage;

    QVector<NPKImage> m_data;

    int32_t m_selectedIndex{-1};
};

} // neapu_ex_view

#endif //NPKIMAGELISTMODEL_H
