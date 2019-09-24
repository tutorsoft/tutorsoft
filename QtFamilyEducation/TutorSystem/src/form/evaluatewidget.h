#ifndef EVALUATEWIDGET_H
#define EVALUATEWIDGET_H

#include <QDialog>
#include <QStandardItemModel>
#include "MuListItemData.h"
#include "MuItemDelegate.h"

namespace Ui {
class EvaluateWidget;
}

class EvaluateWidget : public QDialog
{
    Q_OBJECT

public:
    explicit EvaluateWidget(QWidget *parent = nullptr);
    ~EvaluateWidget();
signals:
    void sendWriteSocket(QString);
public slots:
    void setTeacher(QString );
    void acceptSocketData(QString );
private slots:
    void on_btn_ok_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::EvaluateWidget *ui;
    QStandardItemModel *pModel;
    QStringList icons;
    QString evaluate;
    QStringList singers;
};

#endif // EVALUATEWIDGET_H
