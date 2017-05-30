#include "DataSender.h"

DataSender::DataSender(QObject *parent)
{
	this->parent = parent;
}

DataSender::~DataSender()
{
	delete socket;
	delete host;
}

int DataSender::sendToSpecificClient(QString host, quint16 port, const char * p, int len)
{
	this->socket = new QUdpSocket();
	this->host = new QHostAddress(host);

	return socket->writeDatagram(p, (qint64)len, *(this->host), port);
}

int DataSender::broadcast(quint16 port, const char * p, int len)
{
	this->socket = new QUdpSocket(this->parent);
	this->socket->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);

	return socket->writeDatagram(p, (qint64)len, QHostAddress::Broadcast, port);
}


