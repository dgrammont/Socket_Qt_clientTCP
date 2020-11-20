#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>
#include <QByteArray>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class ClientWidget; }
QT_END_NAMESPACE

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    ClientWidget(QWidget *parent = nullptr);

    ~ClientWidget();

private slots:
    void on_pushButton_connexion_clicked();

    void on_pushButton_nomOrdi_clicked();

    void on_pushButton_nomUti_clicked();

    void on_pushButton_os_clicked();

    void on_pushButton_proco_clicked();

    void onTcpSocket_conneted();

     void onTcpSocket_disconnected();

     void onTcpSocket_error(QAbstractSocket::SocketError socketError);

     void onTcpSocket_hostFoud();

     void onTcpSocket_stateChanged(QAbstractSocket::SocketState socketState);

     void onTcpSocket_aboutToClose();

     void onTcpSocket_bytesWritten(quint64 bytes);

     void onTcpSocket_readChannelFinished();

     void onTcpSocket_readyRead();

private:
    Ui::ClientWidget *ui;
    QString typeDeDemande;
    QTcpSocket *socketDialogueAvecServeur;
};
#endif // CLIENTWIDGET_H
