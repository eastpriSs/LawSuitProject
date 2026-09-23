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
    case NumberRole: return item.note;
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
        bool newChecked = value.toBool();
        if (item.checked != newChecked) {
            item.checked = newChecked;
            emit dataChanged(index, index, {role});
            emit itemCheckedChanged(item.name, newChecked);
        }
        return true;
    }
    return false;
}

void FileListModel::setItemChecked(int row, bool checked)
{
    if (row < 0 || row >= m_items.size()) return;
    FileItem &item = m_items[row];
    item.checked = checked;
    emit itemCheckedChanged(item.name, checked);
    QModelIndex idx = index(row);
    emit dataChanged(idx, idx, {CheckedRole});

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

void FileListModel::appendItem(const QString &name, const QString &note, bool checked)
{
    beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
    m_items.append({name, note, checked});
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

void FileListModel::clearModel()
{
    if (m_items.isEmpty()) return;
    beginRemoveRows(QModelIndex(), 0, m_items.size() - 1);
    m_items.clear();
    endRemoveRows();
    emit countChanged();
}

QStringList FileListModel::getCheckedFiles()
{
    QStringList checked;
    foreach (FileItem file, m_items) {
        if (file.checked)
            checked.append(file.name);
    }
    return checked;
}

void FileListModel::setItems(const QVector<FileItem> &items)
{
    beginResetModel();
    m_items = items;
    endResetModel();
    emit countChanged();
}

void FileListModel::updateNote(QString name, QString note)
{
    for (auto i = m_items.begin(); i != m_items.end(); ++i) {
        if (i->name == name) {
            i->note = note;
            return;
        }
    }
}

void FileListModel::updateFileList(QStringList files)
{
    foreach (QString file, files) {
        appendItem(file, "", false);
    }
}
