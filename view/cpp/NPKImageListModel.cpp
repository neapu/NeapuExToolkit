//
// Created by liu86 on 24-7-21.
//

#include "NPKImageListModel.h"
#include "NPKImageHandler.h"

namespace neapu_ex_view {
void NPKImageListModel::setImages(const std::vector<std::shared_ptr<neapu_ex_npk::NPKImageHandler>>& images)
{
    beginResetModel();
    m_data.clear();
    for (size_t i = 0; i < images.size(); ++i) {
        QString name = QString::fromStdString(images[i]->getShortName());
        m_data.push_back({static_cast<int>(i), name});
    }
    endResetModel();
}

void NPKImageListModel::setSelectedIndex(int32_t index)
{
    if (m_selectedIndex == index) return;
    m_selectedIndex = index;
    emit selectedIndexChanged(index);
}

int NPKImageListModel::rowCount(const QModelIndex& parent) const
{
    return m_data.size();
}

QHash<int, QByteArray> NPKImageListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IndexRole] = "index";
    roles[NameRole] = "name";
    return roles;
}

QVariant NPKImageListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) return {};

    const auto& [rowIndex, rowName] = m_data[index.row()];
    switch (role) {
    case IndexRole: return rowIndex;
    case NameRole: return rowName;
    default: return {};
    }
}
} // neapu_ex_view