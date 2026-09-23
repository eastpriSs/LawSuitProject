#ifndef FORM_PRESENTER_H
#define FORM_PRESENTER_H

#include <QObject>
#include "../view/file_list_model.h"
#include "../models/form_model.h"
#include "../view/highlight.h"
#include "../view/error_handler.h"

class FormPresenter : public QObject
{
    Q_OBJECT
public:
    explicit FormPresenter(FileListModel* view, FormModel* model,
                           Highlight* highlight, ErrorHandler* errHandler, QObject *parent = nullptr);

public slots:
    void saveRequested(QString dist, QStringList files, const QVariantMap &formData);

private:
    FileListModel* view;
    FormModel* model;
    Highlight* highlight_view;
    ErrorHandler* errHandler;
};

#endif // FORM_PRESENTER_H
