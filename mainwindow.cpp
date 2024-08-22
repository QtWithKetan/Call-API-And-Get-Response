#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QNetworkAccessManager Manager;

    // this is open source API For Calling And Testing

    // You have to define your API Url To Get Response From Server.
    QUrl APIurl("https://api.country.is/103.145.146.95");
    // this IP Address Belong To The US Country
    QNetworkRequest request(APIurl);

    QNetworkReply *reply = Manager.get(request);

    // Wait For Reply and response
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();


    if (reply->error() == QNetworkReply::NoError)
    {
        qDebug() << "Error : " << reply->errorString();
        // Get Data From reply
        //QString Response = reply->readAll();

        QJsonDocument JDoc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject JObject = JDoc.object();
        QJsonValue value = JObject.value(QString("country"));
        qDebug() << value.toString();
        QJsonValue value1 = JObject.value(QString("ip"));
        qWarning() << value1.toString();


        qDebug() << JDoc;

        //qDebug() << " API Response : " << Response;
    }
    else
    {
        qDebug() << "Error : " << reply->errorString();
    }

    // Thanks For Watchig Video.
}

MainWindow::~MainWindow()
{
    delete ui;
}

