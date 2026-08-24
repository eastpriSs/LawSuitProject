#ifndef FORM_PRESENTER_H
#define FORM_PRESENTER_H

#include <QObject>
#include "../view/file_list_model.h"
#include "../models/form_model.h"
#include "../view/highlight.h"

class FormPresenter : public QObject
{
    Q_OBJECT
public:
    explicit FormPresenter(FileListModel* view, FormModel* model, Highlight* highlight, QObject *parent = nullptr);

private:
    FileListModel* view;
    FormModel* model;
    Highlight* highlight_view;
};

#endif // FORM_PRESENTER_H
