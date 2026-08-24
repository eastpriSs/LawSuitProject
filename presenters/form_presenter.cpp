#include "form_presenter.h"

FormPresenter::FormPresenter(FileListModel *view, FormModel *model, Highlight *highlight, QObject *parent)
    : view(view), model(model), highlight_view(highlight)
{
    if (!view || !model || !highlight)
        return;

    connect(model, &FormModel::templatesGot, view, &FileListModel::updateFileList);
    connect(view, &FileListModel::itemCheckedChanged, model, &FormModel::templateChecked);
    connect(model, &FormModel::highlightFieldsRequested, highlight_view, &Highlight::setActiveFields);
    model->templatesRequested();
}
