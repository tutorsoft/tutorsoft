#ifndef QXMESSAGEBOX_H
#define QXMESSAGEBOX_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QLabel>

class QXMessageBox : public QDialog
{
    Q_OBJECT
public:
    explicit QXMessageBox(QWidget *parent = 0);

    void initFrom();

protected:
    void resizeEvent(QResizeEvent *);
    bool eventFilter(QObject *obj, QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:



public slots:

    void on_btnExit_clicked();

    void on_btnYes_clicked();
    void on_btnNo_clicked();
    void on_btnCancel_clicked();

    void setlabelTitleStr(QString value);
    void setlabelMsgStr(QString value);

private:

    bool mDrag;             //是否在拖动
    QPoint mDragPos;        //拖动起始点
    bool mIsMax;            //当前是否最大化
    QRect mLocation;        //最大化后恢复时的位置


    QWidget *widgetTitle;
    QHBoxLayout *horizontalLayout;
    QLabel *labelIcon;
    QLabel *labelTitle;
    QLabel *labelMsg;

    QPushButton *btnExit;
    QPushButton *m_btnYes;
    QPushButton *m_btnNo;
    QPushButton *m_btnCancel;

    QString labelTitleStr;
    QString labelMsgStr;

};

#endif // QXMESSAGEBOX_H
