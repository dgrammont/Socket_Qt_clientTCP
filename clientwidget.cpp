#include "clientwidget.h"
#include "ui_clientwidget.h"


ClientWidget::ClientWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    socketDialogueAvecServeur = new QTcpSocket;
    connect(socketDialogueAvecServeur,
            QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this,
            &ClientWidget::onTcpSocket_error);

    connect(socketDialogueAvecServeur,&QTcpSocket::stateChanged,this,&ClientWidget::onTcpSocket_stateChanged);
    connect(socketDialogueAvecServeur,&QTcpSocket::connected,this,&ClientWidget::onTcpSocket_conneted);
    connect(socketDialogueAvecServeur,&QTcpSocket::disconnected,this,&ClientWidget::onTcpSocket_disconnected);
    connect(socketDialogueAvecServeur,&QTcpSocket::aboutToClose,this,&ClientWidget::onTcpSocket_aboutToClose);
    connect(socketDialogueAvecServeur,&QTcpSocket::bytesWritten,this,&ClientWidget::onTcpSocket_bytesWritten);
    connect(socketDialogueAvecServeur,&QTcpSocket::readChannelFinished,this,&ClientWidget::onTcpSocket_readChannelFinished);
    connect(socketDialogueAvecServeur,&QTcpSocket::readyRead,this,&ClientWidget::onTcpSocket_readyRead);
    ui->groupBox_client->hide();
}

ClientWidget::~ClientWidget()
{
    delete ui;
    delete  socketDialogueAvecServeur;
}


void ClientWidget::on_pushButton_connexion_clicked()
{
    if(ui->pushButton_connexion->text()=="Connexion"){
        QHostAddress addresse(ui->lineEdit_adresse->text());
        socketDialogueAvecServeur->connectToHost(addresse,ui->lineEdit_port->text().toUInt());
    }
    else {
        socketDialogueAvecServeur->disconnectFromHost();
    }

}

void ClientWidget::on_pushButton_nomOrdi_clicked()
{
    typeDeDemande="c";
    socketDialogueAvecServeur->write(typeDeDemande.toLatin1());
}

void ClientWidget::on_pushButton_nomUti_clicked()
{
    typeDeDemande="u";
    socketDialogueAvecServeur->write(typeDeDemande.toLatin1());
}

void ClientWidget::on_pushButton_os_clicked()
{
    typeDeDemande="o";
    socketDialogueAvecServeur->write(typeDeDemande.toLatin1());
}

void ClientWidget::on_pushButton_proco_clicked()
{
    typeDeDemande="a";
    socketDialogueAvecServeur->write(typeDeDemande.toLatin1());
}

void ClientWidget::onTcpSocket_conneted()
{
    ui->lineEdit_etat->append("conneté");
    ui->groupBox_client->show();
    ui->lineEdit_port->setEnabled(false);
    ui->lineEdit_adresse->setEnabled(false);
    ui->pushButton_connexion->setText("Deconnexion");
}

void ClientWidget::onTcpSocket_disconnected()
{
    ui->lineEdit_etat->append("déco");
    ui->groupBox_client->hide();
    ui->lineEdit_port->setEnabled(true);
    ui->lineEdit_adresse->setEnabled(true);
    ui->pushButton_connexion->setText("Connexion");
    ui->lineEdit_proco->setText("");
    ui->lineEdit_os->setText("");
    ui->lineEdit_nomOrdi->setText("");
    ui->lineEdit_nomUti->setText("");
}

void ClientWidget::onTcpSocket_error(QAbstractSocket::SocketError socketError)
{
    ui->lineEdit_etat->append(socketDialogueAvecServeur->errorString());
}

void ClientWidget::onTcpSocket_hostFoud()
{
    ui->lineEdit_etat->append("hôte trouvé");
}

void ClientWidget::onTcpSocket_stateChanged(QAbstractSocket::SocketState socketState)
{
    ui->lineEdit_etat->append("état changé");
}

void ClientWidget::onTcpSocket_aboutToClose()
{
    ui->lineEdit_etat->append("close");
}

void ClientWidget::onTcpSocket_bytesWritten(quint64 bytes)
{

    ui->lineEdit_etat->append("écrire");
}

void ClientWidget::onTcpSocket_readChannelFinished()
{
    ui->lineEdit_etat->append("fin de la communication");
}

void ClientWidget::onTcpSocket_readyRead()
{
    ui->lineEdit_etat->append("pret a lire");
    QByteArray data = socketDialogueAvecServeur->readAll();


    switch (typeDeDemande.at(0).toLatin1()) {
    case 'u':
        ui->lineEdit_nomUti->setText(data);
        break;
    case 'c':
        ui->lineEdit_nomOrdi->setText(data);
        break;
    case 'o':
        ui->lineEdit_os->setText(data);
        break;
    case 'a':
        ui->lineEdit_proco->setText(data);
        break;
    default:
        break;
    }
}
