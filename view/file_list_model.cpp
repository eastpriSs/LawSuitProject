#include "file_list_model.h"

FileListModel::FileListModel(QObject *parent) : QAbstractListModel(parent) {}

int FileListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_items.size();
}

QVariant FileListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_items.size())
        return QVariant();

    const FileItem &item = m_items[index.row()];
    switch (role) {
    case NameRole:   return item.name;
    case NumberRole: return item.number;
    case CheckedRole: return item.checked;
    default: return QVariant();
    }
}

bool FileListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_items.size())
        return false;

    FileItem &item = m_items[index.row()];
    if (role == CheckedRole) {
        item.checked = value.toBool();
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

QHash<int, QByteArray> FileListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[NumberRole] = "number";
    roles[CheckedRole] = "checked";
    return roles;
}

Qt::ItemFlags FileListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
}

void FileListModel::appendItem(const QString &name, const QString &number, bool checked)
{
    beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
    m_items.append({name, number, checked});
    endInsertRows();
    emit countChanged();
}

void FileListModel::removeItem(int row)
{
    if (row < 0 || row >= m_items.size()) return;
    beginRemoveRows(QModelIndex(), row, row);
    m_items.removeAt(row);
    endRemoveRows();
    emit countChanged();
}

void FileListModel::setItemChecked(int row, bool checked)
{
    if (row < 0 || row >= m_items.size()) return;
    m_items[row].checked = checked;
    QModelIndex idx = index(row);
    emit dataChanged(idx, idx, {CheckedRole});
}

void FileListModel::clearModel()
{
    if (m_items.isEmpty()) return;
    beginRemoveRows(QModelIndex(), 0, m_items.size() - 1);
    m_items.clear();
    endRemoveRows();
    emit countChanged();
}

void FileListModel::setItems(const QVector<FileItem> &items)
{
    beginResetModel();
    m_items = items;
    endResetModel();
    emit countChanged();
}
