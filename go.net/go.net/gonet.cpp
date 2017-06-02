#include "gonet.h"

gonet::gonet(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setFixedSize(364, 480);

	// init controllers and widgets
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

	// get local ip
	this->localIp = this->getLocalIp();

	// listen to any message from network
	infoReceiver = new DataReceiver(this, this->port);
	infoReceiver->listenToBroadcast();
	// get any message, then go to Action()
	QObject::connect(infoReceiver, &DataReceiver::dataReady, this, &gonet::Action);

	// set to online, broadcast the online message
	setOnline();

	QObject::connect(goBtn, &QPushButton::clicked, this, &gonet::goBtnClicked);
	QObject::connect(fiveBtn, &QPushButton::clicked, this, &gonet::fiveBtnClicked);
	QObject::connect(lanListView, &QListView::clicked, this, &gonet::itemClicked);
}

void gonet::goBtnClicked(bool arg)
{
	// send a request to the remote ip
	DataGram *backDataGram = new DataGram();
	backDataGram->messageType = REQUEST;
	backDataGram->chessType = true;   // true for go game
	backDataGram->fromIp = this->localIp;
	backDataGram->toIp = this->remoteIp;
	string tmp = backDataGram->toJson();
	DataSender *onlineMessageSender = new DataSender(this);
	onlineMessageSender->sendToSpecificClient(
		QString::fromStdString(this->remoteIp),
		this->port,
		tmp.c_str(),
		tmp.length()
	);
}

void gonet::fiveBtnClicked(bool arg)
{
	// send a request to the remote ip
	DataGram *backDataGram = new DataGram();
	backDataGram->messageType = REQUEST;
	backDataGram->chessType = false;   // false for five-in-a-row game
	backDataGram->fromIp = this->localIp;
	backDataGram->toIp = this->remoteIp;
	string tmp = backDataGram->toJson();
	DataSender *onlineMessageSender = new DataSender(this);
	onlineMessageSender->sendToSpecificClient(
		QString::fromStdString(this->remoteIp),
		this->port,
		tmp.c_str(),
		tmp.length()
	);
}

string gonet::getLocalIp()
{
	QString tmpResult;

	QList<QHostAddress> list = QNetworkInterface::allAddresses();
	foreach(QHostAddress address, list)
	{
		if (address.protocol() == QAbstractSocket::IPv4Protocol)
		{
			if (address.toString().contains("127.0.") || address.toString().contains("169."))
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
	//std::set<string>::iterator itr;
	switch (result["messageType"].toInt())
	{
	case MessageType::ONLINE:
		receiveOnlineMessage(result);
		break;
	case MessageType::OFFLINE:
		receiveOfflineMessage(result);
		break;
	case MessageType::REQUEST:
		receiveRequestMessage(result);
		break;
	case MessageType::REFUSE:
		receiveRefuseMessage(result);
		break;
	case MessageType::AGREE:
		receiveAgreeMessage(result);
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

void gonet::receiveOnlineMessage(Object result)
{
	string tmpRemote = result["fromIp"].toString();
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
}

void gonet::receiveOfflineMessage(Object result)
{
	string tmpRemote = result["fromIp"].toString();
	auto itr = this->lanList->find(tmpRemote);
	if (itr != this->lanList->end())
	{
		this->lanList->erase(itr);
	}
	updateLanListView();
}

// received a request from remote, 
// display a message to choose agree or refuse
void gonet::receiveRequestMessage(Object result)
{
	string tmpRemote = result["fromIp"].toString();

	requestedWindow = new MessageWindow(result["messageType"].toInt(),
		result["chessType"].toBool(), tmpRemote, this->localIp, this->port, this);
	requestedWindow->show();

	QObject::connect(requestedWindow, &MessageWindow::gameReady, this, &gonet::agreeToPlay);
}

// Agreed, open game window to play with remote player
void gonet::receiveAgreeMessage(Object result)
{
	// remote player agree to play
	bool chessType;

	string tmpLocalIp = result["toIp"].toString();
	string tmpRemoteIp = result["fromIp"].toString();
	bool tmpChessType = result["chessType"].toBool();

	this->gameWindow = new GameWindow(tmpLocalIp, tmpRemoteIp,  tmpChessType, WHITE, this);

	this->hide();
	this->gameWindow->show();
	this->setOffline();

	QObject::connect(gameWindow, &GameWindow::gameWindowClose, this, &gonet::afterGameWindowClosed);
}

// Refused, just show a message window
void gonet::receiveRefuseMessage(Object result)
{
	string tmpRemote = result["fromIp"].toString();

	refusedWindow = new MessageWindow(result["messageType"].toInt(),
		result["chessType"].toBool(), tmpRemote, this->localIp, this->port, this);
	refusedWindow->show();
}

void gonet::agreeToPlay(string remoteIp, string localIp, bool chessType)
{
	// agree to play, set to white, and setOffline
	this->gameWindow = new GameWindow(localIp, remoteIp,  chessType, BLACK, this);

	this->hide();
	this->gameWindow->show();
	this->setOffline();

	QObject::connect(gameWindow, &GameWindow::gameWindowClose, this, &gonet::afterGameWindowClosed);
}

// when the gaming window closed
// show the main window and set to online
void gonet::afterGameWindowClosed()
{
	this->show();
	this->setOnline();
}


// when closing the application(getting offline), tell everyone
void gonet::closeEvent(QCloseEvent * event)
{
	this->setOffline();
}

void gonet::itemClicked(QModelIndex index)
{
	this->remoteIp = index.data().toString().toStdString();
}