#include "DataReceiver.h"

DataReceiver::DataReceiver(QObject *parent, quint16 port)
{
	this->parent = parent;
	this->port = port;
}

void DataReceiver::listenToBroadcast()
{
	socket = new QUdpSocket(this);
	this->socket->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);

	connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
}

void DataReceiver::listenToSpecificRemote(std::string remoteIp)
{
	socket = new QUdpSocket(this);
	host = new QHostAddress(QString::fromStdString(remoteIp));
	socket->bind(*host, port);

	connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
}

void DataReceiver::read()
{
	QByteArray data;
	data.resize(socket->pendingDatagramSize());
	socket->readDatagram(data.data(), data.size());

	std::string str(data.data(), data.size());
	emit dataReady(str);
}

DataReceiver::~DataReceiver()
{
	delete socket;
	delete host;
}
