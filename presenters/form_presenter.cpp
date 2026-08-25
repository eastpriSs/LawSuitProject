#include "form_presenter.h"

FormPresenter::FormPresenter(FileListModel *view, FormModel *model,
                             Highlight *highlight, ErrorHandler* err, QObject *parent)
    : view(view), model(model), highlight_view(highlight), errHandler(err)
{
    connect(model, &FormModel::templatesGot, view, &FileListModel::updateFileList);
    connect(view, &FileListModel::itemCheckedChanged, model, &FormModel::templateChecked);
    connect(model, &FormModel::highlightFieldsRequested, highlight_view, &Highlight::setActiveFields);
    connect(model, &FormModel::errorNoteRequested, view, &FileListModel::updateNote);
    connect(model, &FormModel::errorMasseageRequested, errHandler, &ErrorHandler::handleError);
    connect(model, &FormModel::appStateSwitchRequested, errHandler, &ErrorHandler::setAppState);
    model->templatesRequested();
}
