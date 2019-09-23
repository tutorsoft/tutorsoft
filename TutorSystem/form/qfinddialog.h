#ifndef QFINDDIALOG_H
#define QFINDDIALOG_H

#include <QDialog>
#include "evaluatewidget.h"
namespace Ui {
class QFindDialog;
}

class QFindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QFindDialog(QWidget *parent = 0);
    ~QFindDialog();

protected:
    void showEvent(QShowEvent *);

public slots:
    void on_btn_resiger_clicked();

    void setAllInfo(QStringList);

private slots:
    void on_btn_evaluate_clicked();

private:
    Ui::QFindDialog *ui;

};

#endif // QFINDDIALOG_H
