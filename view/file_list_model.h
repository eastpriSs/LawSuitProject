#ifndef FILELISTMODEL_H
#define FILELISTMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include <QString>

struct FileItem {
    QString name;
    QString note;
    bool checked;
};

class FileListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        NumberRole,
        CheckedRole
    };

    explicit FileListModel(QObject *parent = nullptr);

    // QAbstractListModel interface
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QHash<int, QByteArray> roleNames() const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    Q_INVOKABLE void appendItem(const QString &name, const QString &note, bool checked = false);
    Q_INVOKABLE void removeItem(int row);
    Q_INVOKABLE void setItemChecked(int row, bool checked);
    Q_INVOKABLE void clearModel();

    void setItems(const QVector<FileItem> &items);
    void updateNote(QString name, QString note);

signals:
    void countChanged();
    void itemCheckedChanged(const QString &name, bool checked);

public slots:
    void updateFileList(QStringList);

private:
    QVector<FileItem> m_items;
};

#endif // FILELISTMODEL_H
