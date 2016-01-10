#include <QtCore/QStringList>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "plot.h"
#include <QString>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dataArray(0)
{
    ui->setupUi(this);

/* UI Elements */
    createActions();
    createMenus();
    createToolBars();
    createCentralWidget();
    initMainWidgetCloseState();
    connect(controlButton, SIGNAL(triggered()), this, SLOT(openPortButtonClick()));

    procEnumerate();

/* SerialPort */
    serial = new QSerialPort();
    connect(serial, SIGNAL(readyRead()), this, SLOT(serialDataReceive()));
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)),
            this,   SLOT(serialErrorHandler(QSerialPort::SerialPortError)));

    connect(sendButton, SIGNAL(clicked()), this, SLOT(serialDataSend()));

    dumbTimer = new QTimer();
    dumbTimer->setInterval(20);
    connect(dumbTimer, SIGNAL(timeout()), this, SLOT(serialDataReceive()));
    dumbTimer->start();
     plot->start();
}


MainWindow::~MainWindow()
{
    if (this->serial && this->serial->isOpen())
        this->serial->close();

    delete ui;
}


void MainWindow::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);

    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;

    default:
        break;
    }
}





/* Private SLOTS section */
void MainWindow::procEnumerate(/*const QStringList &l*/)
{
    // Fill ports box.
    portBox->clear();

    QStringList list;

    //QSerialPortInfo info = enumerator->availablePorts();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        list.append(info.portName());

    portBox->addItems(list);
}


void MainWindow::openPortButtonClick()
{
    if(this->serial)
    {
        bool result = this->serial->isOpen();
        if(result)
        {
            this->serial->close();
            qDebug() << "Port closed";
            ui->statusBar->showMessage(tr("Port closed"));
            result = false;
        }
        else
        {
            //SettingsDialog::Settings p = settings->settings();
            serial->setPortName(this->portBox->currentText());
            serial->setBaudRate(QSerialPort::Baud115200);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);

            result = this->serial->open(QIODevice::ReadWrite);

            if(!result)
            {
                qDebug() << "!Serial device: " << this->serial->objectName() << " open fail!";
                QMessageBox::critical(this, tr("Error"), serial->errorString());
                ui->statusBar->showMessage(tr("Error Port opening!"));
                return;
            }
            else
            {
                qDebug() << "Port opened";
                ui->statusBar->showMessage(tr("Port opened"));
                /*ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                                       .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                                       .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
                   */
            }

            plot->start();
        }

        (result) ? this->initMainWidgetOpenState() : this->initMainWidgetCloseState();
        this->sendButton->setEnabled(result ? true : false);
    }
}


void MainWindow::procSerialMessages(const QString &msg, QDateTime dt)
{
    qDebug()<< "procSerialMessages" << " ...";
    QString s = dt.time().toString() + " > " + msg;
    textEdit->appendPlainText(s);
}


void MainWindow::serialDataReceive()
{
    //static int fuck = 0;
    //fuck += qrand()%10-5;


    //if((int)(elapsed)%10 > 5) return;

   /* QPointF point(elapsed, fuck);
    QPointF point2(elapsed, fuck*2);*/
//qDebug() << "Point X:" << point.x() << " Y:" << point.y();
    //plot->appendPoint(point,point2);
static bool isEn = true;

    if (this->serial && this->serial->isOpen())
    {

        if(isEn == false)
        {
            plot->start();
            isEn = true;
        }
        double elapsed = plot->d_clock.elapsed()/1000.0;

        QByteArray Rx = this->serial->readAll();
        //textEdit->insertPlainText(Rx);


        //qDebug() << " ++"<< Rx.size()<< "  ... "<<Rx;

        /* Check if string contains Start, Middle, Stop symbols */
        bool flagA=false, flagB=false, flagC=false;
        for(int i=0; i<Rx.size(); i++)
           if(Rx.at(i)=='A') flagA = true;
        for(int i=0; i<Rx.size(); i++)
           if(Rx.at(i)=='B') flagB = true;
        for(int i=0; i<Rx.size(); i++)
           if(Rx.at(i)=='C') flagC = true;

        if(!flagA || !flagB || !flagC) return;

        /* parser */
        int ptr = 0, ptr1=0, ptr2=0;
        char pos[10], pwm[10];
        /* Find Start symbol */
        for(; (Rx.at(ptr) != 'A') && (ptr<=Rx.size()); ptr++){}
        ptr++;

        /* Find Middle symbol & copy 1st num */
        for(; Rx.at(ptr) != 'B'; ptr++, ptr1++)
            pos[ptr1] = Rx.at(ptr);
        pos[ptr1] = '\0';

        ptr++;
        /* Find Stop Mark symbol & copy 2nd num */
        for(; Rx.at(ptr) != 'C'; ptr++, ptr2++)
            pwm[ptr2] = Rx.at(ptr);
        pwm[ptr2] = '\0';

       /* QString a = "";
        a.append("POSITION = ");
        a.append(pos);
        a.append(", PWM = ");
        a.append(pwm);
        a.append('\n');

        textEdit->insertPlainText(a);*/
        QString a = pos, b = pwm;
        int aa = a.toInt(), bb=b.toInt();

        static bool pause = false;
        if(abs(aa)>500)
        {
            //plot->stop();
            plot->flagUpd=false;
            pause = true;
            return;
        }
        else
        {
            if(pause)
            {
                pause = false;
                plot->flagUpd=true;
                //plot->start();
            }
        }
        //qDebug() << "---"<<aa<<"   "<<bb;
        QPointF point(elapsed, aa);
        QPointF point2(elapsed, bb/2);
        plot->appendPoint(point,point2);
   // int val =

    }
    else
    {
        if(isEn == true)
        {
            plot->stop();
            isEn = false;
        }
    }
#if 0
#define END_S '\n'

        if(Rx.indexOf("\n") != -1)
        {
            // Получили переход на новую строку - значит приняли данные
            dataArray += Rx;

            // Грязная магия - парсим данные. Делим массив на две части: до пробела (команда) и после (параметры)
            // Затем очищаем параметры от \r\n, и преобразуем в unsigned int
            uint adc_value = 0;//dataArray.split(' ').at(1).split('\r').at(0).toUInt();

            //ui->leADC->setText(QString::number(adc_value));

                // Print parsed number
                {
                    QString string;

                    QString alertHtml = "<font color=\"DeepPink\">";
                    QString notifyHtml = "<font color=\"Lime\">";
                    QString infoHtml = "<font color=\"Aqua\">";
                    QString endHtml = "</font><br>";

                    string.append(alertHtml);
                    QString time = QTime::currentTime().toString();
                    string.append(time);
                    string.append(": ");
                    string.append(QString::number(adc_value));
                    string.append(endHtml);

                    textEdit->appendHtml(string);
                }

            dataArray.clear();
        }
        else
        {
            dataArray += Rx;
        }

        static int fuck = 0;
        fuck += qrand()%100-50.0;

        double elapsed = plot->dclock_elapsed();
        QPointF point(elapsed, fuck);
qDebug() << "Point X:" << point.x() << " Y:" << point.y();
        plot->appendPoint(point);
        //plot->setIntervalLength(plot->dclock_elapsed()/1000.0);


#if 0
        if(byte.at(0) != '\n')
        {
            dataArray.append(byte);

            qDebug() << "3";

          /*  double elapsed = (plot->dclock_elapsed())/ 1000.0;
            QPointF point(elapsed, 9);
            plot->appendPoint(point);
            QPointF point2(elapsed, 15);
            plot->appendPoint(point2);
            plot->setIntervalLength(plot->dclock_elapsed()/1000.0);*/
        }
        else
        {
            qDebug() << "4 size = " << dataArray.size();

            if(dataArray.size() == 0) return;

//#if 0
            if(dataArray.at(0)=='C')
            {
                qDebug() << "5";

                if(dataArray.at(3) == '3')
                {
                   double elapsed = (plot -> dclock_elapsed())/ 1000.0;
                   QByteArray u;
                   //u[0]= dataArray.at(5);
                   int j=5;
                   /*for(j=5;j<9;j++)
                   {
                        if(dataArray.at(j)!='\r') u[j-5]= dataArray.at(j);
                   }*/
                   while(dataArray.at(j)!='\r')
                   {
                       u[j-5]= dataArray.at(j);
                       j++;
                   }
                   QPointF point(elapsed,u.toDouble()*5/1024);
                   plot ->appendPoint(point);
                   RecToFile(point);
                }
            }
//#endif

            dataArray = 0;
         }
#endif
    }
#endif
}

#if 0
void MainWindow::RecToFile(QPointF point)
{
    qDebug() << "RecToFile ...recording";
    /*
    QFile f("test.dat");
    if (f.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&f);
        out << point.x() << "\t" << point.y() << "\n";
        f.close();
    }
    else
    {
        qWarning("Can not open file test.dat");
    }
    */
}
#endif

void MainWindow::serialErrorHandler(QSerialPort::SerialPortError error)
{
    qDebug() << "serial Error: " << serial->errorString();
    if(error == QSerialPort::ResourceError)
    {
        openPortButtonClick();
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());        
    }

    ui->statusBar->showMessage(tr("Error!"));
}


void MainWindow::serialDataSend()
{
    qDebug() << "Data sending...";
    QByteArray data = textSend->toPlainText().toUtf8();

    if(this->checkSendL->isChecked()) data.append('\n');
    if(this->checkSendN->isChecked()) data.append('\0');

    QString string;

    QString alertHtml = "<font color=\"DeepPink\">";
    QString notifyHtml = "<font color=\"Lime\">";
    QString infoHtml = "<font color=\"Aqua\">";
    QString endHtml = "</font><br>";

    string.append(notifyHtml);
    QString time = QTime::currentTime().toString();
    string.append(time);
    string.append(": ");
    string.append(data);
    string.append(endHtml);

    textEdit->appendHtml(string);

    serial->write(data);
}






/* Private METHODS section */
void MainWindow::initMainWidgetCloseState()
{
    this->sendButton->setEnabled(false);
    portBox->setEnabled(true);
    controlButton->setText(QString(tr("Open")));
}


void MainWindow::initMainWidgetOpenState()
{
    portBox->setEnabled(false);
    controlButton->setText(QString(tr("Close")));
}


void MainWindow::createActions()
{
     aboutAct = new QAction(tr("About"), this);
     aboutAct->setStatusTip(tr("Show the About box"));
     connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

     aboutqtAct = new QAction(tr("AboutQT"), this);
     aboutqtAct->setStatusTip(tr("Show the Qt library's About box"));
     connect(aboutqtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

     controlButton = new QAction(tr("Open"), this);
     //controlButton->setStatusTip(tr("Open port"));
}


void MainWindow::createMenus()
{
     helpMenu = menuBar()->addMenu(tr("&Help"));
     helpMenu->addAction(aboutqtAct);
     helpMenu->addAction(aboutAct);
}


void MainWindow::createCentralWidget()
{
    plot = new Plot(this);

    subPlotHLayout = new QHBoxLayout();
    plotMode[0] = new QRadioButton("All");
    plotMode[0]->setChecked(true);
    plotMode[1] = new QRadioButton("Smooth");
    plotMode[2] = new QRadioButton("Frame");
    intervalBox = new QSpinBox();
    intervalBox->setMaximum(120);
    intervalBox->setMinimum(2);
    intervalBox->setValue(10);
    updateOnTime = new QCheckBox("TimeUpdate");
    updateOnTime->setChecked(true);

    checkSendL = new QCheckBox("\\n");
    checkSendN = new QCheckBox("\\0");
    checkSendL->setFixedWidth(30);
    checkSendN->setFixedWidth(30);

    textSend = new QPlainTextEdit;
    textSend->setFixedHeight(30);
    textSend->setFixedWidth(200);

    textEdit = new QPlainTextEdit;
    textEdit->setFixedWidth(260);

    sendButton = new QPushButton("Send");
    sendButton->setFixedWidth(260);

    HLayout = new QHBoxLayout();
    GridLayoutLeft = new QGridLayout();

    VLayoutRight = new QVBoxLayout();
    VLayoutRight->addWidget(plot);
    for(int i=0; i<3; i++)
        subPlotHLayout->addWidget(plotMode[i]);
    subPlotHLayout->addWidget(intervalBox);
    subPlotHLayout->addWidget(updateOnTime);
    VLayoutRight->addLayout(subPlotHLayout);

    GridLayoutLeft->addWidget(checkSendL, 0,1);
    GridLayoutLeft->addWidget(checkSendN, 0,2);
    GridLayoutLeft->addWidget(textSend, 0,0);
    GridLayoutLeft->addWidget(sendButton, 1,0, 1,3);
    GridLayoutLeft->addWidget(textEdit, 2,0, 2,3);

    HLayout->addLayout(GridLayoutLeft);
    HLayout->addLayout(VLayoutRight);

    centralWidget()->setLayout(HLayout);
    setWindowTitle(tr("UART Terminal & Graph"));

    this->resize(800,400);
    connect(plotMode[0], SIGNAL(pressed()), plot, SLOT(setScaleMode()));
    connect(plotMode[1], SIGNAL(pressed()), plot, SLOT(setScaleMode()));
    connect(plotMode[2], SIGNAL(pressed()), plot, SLOT(setScaleMode()));
    connect(intervalBox, SIGNAL(valueChanged(int)), plot, SLOT(intervalChanged(int)));
    connect(updateOnTime, SIGNAL(clicked(bool)), plot, SLOT(onUpdateOnTime(bool)));
    connect(updateOnTime, SIGNAL(clicked(bool)), this, SLOT(onUpdateOnTime(bool)));
}


void MainWindow::createToolBars()
{
    statusBar = new QStatusBar();

    portBox = new QComboBox(ui->mainToolBar);
    portBox->setObjectName("Ports");

    ui->mainToolBar->addWidget(portBox);
    ui->mainToolBar->addAction(controlButton);
}


void MainWindow::about()
{
    QMessageBox::about(this, tr("About Application"),
        tr("<b>Serial terminal & Graph</b>"));
}


void MainWindow::onUpdateOnTime(bool state)
{
    if(!state && plotMode[2]->isChecked())
    {
        plotMode[0]->setChecked(true);
        emit plotMode[0]->pressed();
    }
}
