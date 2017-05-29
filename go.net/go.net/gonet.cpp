#include "gonet.h"

gonet::gonet(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setFixedSize(364, 480);

	centralWidget = new QWidget();
	this->setCentralWidget(centralWidget);
	lanListView = new QListView(this);
	////lanListView->setFixedHeight(400);
	standardItemModel = new QStandardItemModel(this);
	lanListView->setModel(standardItemModel);
	lanList = new std::set<string>();
	layout = new QGridLayout(this);
	goBtn = new QPushButton("Go Game", this);
	fiveBtn = new QPushButton("Five-in-a-row Game", this);
	layout->addWidget(goBtn, 3, 0, 1, 1);
	layout->addWidget(fiveBtn, 4, 0, 1, 1);
	layout->addWidget(lanListView, 0, 0, 3, 1);
	centralWidget->setLayout(layout);

	this->localIp = this->getLocalIp();

	DataReceiver *infoReceiver = new DataReceiver(this, this->port);
	infoReceiver->listenToBroadcast();

	QObject::connect(infoReceiver, &DataReceiver::dataReady, this, &gonet::Action);

	// set to online, broadcast the online message
	setOnline();
}

string gonet::getLocalIp()
{
	QString tmpResult;

	QList<QHostAddress> list = QNetworkInterface::allAddresses();
	foreach(QHostAddress address, list)
	{
		if (address.protocol() == QAbstractSocket::IPv4Protocol)
		{
			if (address.toString().contains("127.0."))
			{
				continue;
			}
			tmpResult = address.toString();
		}
	}

	return tmpResult.toStdString();
}

void gonet::setOnline()
{
	DataSender *onlineMessageSender = new DataSender(this);

	DataGram *onlineMessage = new DataGram();
	onlineMessage->messageType = ONLINE;
	onlineMessage->fromIp = localIp;
	onlineMessage->toIp = "192.168.1.255";

	string tmp = onlineMessage->toJson();
	onlineMessageSender->broadcast(port, tmp.c_str(), tmp.length());
}

void gonet::setOffline()
{
	DataSender *onlineMessageSender = new DataSender(this);

	DataGram *onlineMessage = new DataGram();
	onlineMessage->messageType = OFFLINE;
	onlineMessage->fromIp = localIp;
	onlineMessage->toIp = "192.168.1.255";

	string tmp = onlineMessage->toJson();
	onlineMessageSender->broadcast(port, tmp.c_str(), tmp.length());
}

void gonet::Action(string data)
{
	JsonParser *tmpParser = new JsonParser();
	int p = 0;
	Object result = tmpParser->readObject(data, p);

	string tmpRemote;
	std::set<string>::iterator itr;
	switch (result["messageType"].toInt())
	{
	case ONLINE:
		tmpRemote = result["fromIp"].toString();
		if (tmpRemote != this->localIp 
			&& this->lanList->find(tmpRemote) == this->lanList->end())
		{
			this->lanList->insert(tmpRemote);
			updateLanListView();

			// return back local info to source ip
			DataGram *backDataGram = new DataGram();
			backDataGram->messageType = ONLINE;
			backDataGram->fromIp = localIp;
			backDataGram->toIp = tmpRemote;
			string tmp = backDataGram->toJson();
			DataSender *onlineMessageSender = new DataSender(this);
			onlineMessageSender->sendToSpecificClient(
				QString::fromStdString(tmpRemote),
				this->port, 
				tmp.c_str(), 
				tmp.length()
			);
		}
		break;
	case OFFLINE:
		tmpRemote = result["fromIp"].toString();
		itr = this->lanList->find(tmpRemote);
		if (itr != this->lanList->end())
		{
			this->lanList->erase(itr);
		}
		updateLanListView();
		break;
	default:
		break;
	}
}

void gonet::updateLanListView()
{
	this->standardItemModel->clear();
	for (auto itr = this->lanList->begin(); itr != this->lanList->end(); itr++)
	{
		QString remote = QString::fromStdString(*itr);
		QStandardItem *item = new QStandardItem(remote);
		standardItemModel->appendRow(item);
	}
}

void gonet::closeEvent(QCloseEvent * event)
{
	this->setOffline();
}

void gonet::itemClicked(QModelIndex index)
{
	this->remoteIp = index.data().toString().toStdString();
}