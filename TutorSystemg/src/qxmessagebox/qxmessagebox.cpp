#include "qxmessagebox.h"
#include <QApplication>
#include <QDesktopWidget>


QXMessageBox::QXMessageBox(QWidget *parent) : QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    this->resize(800,300);
    initFrom();
}

void QXMessageBox::initFrom()
{
    labelTitleStr = "title";
    labelMsgStr = "msg";
    m_btnYes = new QPushButton(this);
    m_btnNo = new QPushButton(this);
    m_btnCancel = new QPushButton(this);
    m_btnYes->setText("Yes");
    m_btnNo->setText("No");
    m_btnCancel->setText("Cancel");

    widgetTitle = new QWidget(this);
    widgetTitle->setGeometry(QRect(0,0,this->width(),this->height()*0.1));
    widgetTitle->setObjectName(QStringLiteral("widgetTitle"));
    widgetTitle->setMinimumSize(QSize(0, 30));
    widgetTitle->setMaximumSize(QSize(16777215, 30));
    widgetTitle->setStyleSheet(QLatin1String("QWidget{background:#363636;}\n"
                                             "QLabel{color:white;padding:8px 0px 5px;}\n"
                                             ));
    QPalette palette;
    palette.setColor(QPalette::Background,QColor(47,79,79));
    this->setPalette(palette);
    this->setStyleSheet(QLatin1String("QPushButton{"
                                      "border-style:none;"
                                      "border:1px solid #111214;"
                                      "color:#D7E2E9;"
                                      "padding:5px;"
                                      "min-height:15px;"
                                      "border-radius:1px;"
                                      "background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #242629,stop:1 #141518);"
                                      "}"
                                      "QPushButton:hover{"
                                      "background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #007DC4,stop:1 #0074BF);"
                                      "}"
                                      "QPushButton:pressed{"
                                      "background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #242629,stop:1 #141518);}"));
    horizontalLayout = new QHBoxLayout(widgetTitle);
    horizontalLayout->setGeometry(QRect(0,0,this->width(),this->height()*0.1));
    horizontalLayout->setSpacing(0);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
    horizontalLayout->setContentsMargins(5, 0, 0, 2);
    labelIcon = new QLabel(widgetTitle);
    labelIcon->setObjectName(QStringLiteral("labelIcon"));
    labelIcon->setMinimumSize(QSize(26, 26));
    labelIcon->setMaximumSize(QSize(26, 26));
    labelIcon->setPixmap(QPixmap(QString::fromUtf8(":/main.ico")));
    labelIcon->setScaledContents(true);

    horizontalLayout->addWidget(labelIcon);
    labelMsg = new QLabel(this);
    labelTitle = new QLabel(widgetTitle);
    labelTitle->setObjectName(QStringLiteral("labelTitle"));
    QFont font;
    font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
    font.setPointSize(9);
    font.setBold(true);
    font.setWeight(75);
    labelTitle->setFont(font);
    labelTitle->setStyleSheet(QStringLiteral(""));

    horizontalLayout->addWidget(labelTitle);


    btnExit = new QPushButton(widgetTitle);
    btnExit->setObjectName(QStringLiteral("btnExit"));

    btnExit->setMinimumSize(QSize(30, 30));
    btnExit->setMaximumSize(QSize(30, 30));
    btnExit->setAutoDefault(true);
    btnExit->setFlat(true);

    horizontalLayout->addWidget(btnExit);

    widgetTitle->raise();
    labelTitle->raise();


    widgetTitle->installEventFilter(this);

    btnExit->setIcon(QIcon(":/image/exit.png"));

    labelTitle->setText(labelTitleStr);
    labelMsg->setText(labelMsgStr);

    connect(btnExit,SIGNAL(clicked()),this,SLOT(on_btnExit_clicked()));

    connect(m_btnYes,SIGNAL(clicked()),this,SLOT(on_btnYes_clicked()));
    connect(m_btnNo,SIGNAL(clicked()),this,SLOT(on_btnNo_clicked()));
    connect(m_btnCancel,SIGNAL(clicked()),this,SLOT(on_btnCancel_clicked()));
}

void QXMessageBox::resizeEvent(QResizeEvent *)
{
    labelMsg->setGeometry(this->width()*0.1,this->height()*0.3,this->width()*0.8,this->height()*0.2);
    m_btnYes->setGeometry(this->width()*0.4,this->height()*0.85,this->width()*0.15,this->height()*0.1);
    m_btnNo->setGeometry(this->width()*0.6,this->height()*0.85,this->width()*0.15,this->height()*0.1);
    m_btnCancel->setGeometry(this->width()*0.8,this->height()*0.85,this->width()*0.15,this->height()*0.1);

}

bool QXMessageBox::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == this->widgetTitle)
    {
        if(e->type() == QEvent::MouseButtonDblClick)
        {

            return true;
        }
    }
    return QObject::eventFilter(obj, e);
}

void QXMessageBox::mousePressEvent(QMouseEvent *e)//鼠标按下事件
{
    if (e->button() == Qt::LeftButton)
    {
        mDrag = true;
        mDragPos = e->globalPos() - pos();
        e->accept();
    }
}

void QXMessageBox::mouseMoveEvent(QMouseEvent *e)//鼠标移动事件
{
    if (mDrag && (e->buttons() && Qt::LeftButton))
    {
        move(e->globalPos() - mDragPos);
        e->accept();
    }
}

void QXMessageBox::mouseReleaseEvent(QMouseEvent *e)//鼠标释放事件
{
    mDrag = false;
}

void QXMessageBox::on_btnExit_clicked()
{
    done(0);
}

void QXMessageBox::on_btnYes_clicked()
{
    done(1);
}

void QXMessageBox::on_btnNo_clicked()
{
    done(2);

}

void QXMessageBox::on_btnCancel_clicked()
{
    done(3);
}

void QXMessageBox::setlabelTitleStr(QString value)
{
    labelTitleStr = value;
    labelTitle->setText(labelTitleStr);
}

void QXMessageBox::setlabelMsgStr(QString value)
{
    labelMsgStr = value;
    QFont ft;
    ft.setPointSize(18);
    labelMsg->setFont(ft);
    labelMsg->setText(labelMsgStr);
    labelMsg->setAlignment(Qt::AlignCenter);
}
