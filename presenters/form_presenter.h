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
    void getReadyUi();
signals:
    void suitDataLoaded(QVariantMap formData);

    void courtModelLoaded(const QStringList &items);
    void expertModelLoaded(const QStringList &items);
    void expertiseTypeLoaded(const QStringList &items);

public slots:
    void saveRequested(QString dist, QStringList files, const QVariantMap &formData);
    void openRequested(QStringList files, const QVariantMap &formData);
    void loadRequested(QString file);

    void requestCourtModel();
    void requestExpertModel();
    void requestExpertiseType();

    void saveCourtModel(const QStringList &items);
    void saveExpertModel(const QStringList &items);
    void saveExpertiseType(const QStringList &items);

private:
    FileListModel* view;
    FormModel* model;
    Highlight* highlight_view;
    ErrorHandler* errHandler;
};

#endif // FORM_PRESENTER_H
