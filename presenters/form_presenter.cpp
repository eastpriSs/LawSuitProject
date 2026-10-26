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
    connect(model, &FormModel::suitDataLoaded, this,  &FormPresenter::suitDataLoaded);

    connect(model, &FormModel::expertModelLoaded, this, &FormPresenter::expertModelLoaded);
    connect(model, &FormModel::courtModelLoaded, this, &FormPresenter::courtModelLoaded);
    connect(model, &FormModel::expertiseTypeLoaded, this, &FormPresenter::expertiseTypeLoaded);
}

void FormPresenter::getReadyUi()
{
    model->templatesRequested();
    model->requestCourtModel();
    model->requestExpertModel();
    model->requestExpertiseType();
}

void FormPresenter::saveCourtModel(const QStringList &items)
{
    model->saveCourtModel(items);
}
void FormPresenter::saveExpertModel(const QStringList &items)
{
    model->saveExpertModel(items);
}
void FormPresenter::saveExpertiseType(const QStringList &items)
{
    model->saveExpertiseType(items);
}

void FormPresenter::saveRequested(QString dist, QStringList files, const QVariantMap &formData)
{
    model->saveRequested(std::move(dist), std::move(files), formData);
}

void FormPresenter::openRequested(QStringList files, const QVariantMap &formData)
{
    model->openRequested(files, formData);
}

void FormPresenter::loadRequested(QString file)
{
    model->loadRequested(std::move(file));
}

void FormPresenter::requestCourtModel()
{
    model->requestCourtModel();
}

void FormPresenter::requestExpertModel()
{
    model->requestExpertModel();
}

void FormPresenter::requestExpertiseType()
{
    model->requestExpertiseType();
}
