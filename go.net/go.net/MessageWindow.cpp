#include "MessageWindow.h"

MessageWindow::MessageWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

MessageWindow::~MessageWindow()
{
}

MessageWindow::MessageWindow(int type, bool chessType, string fromIp, string localIp, quint16 port, QWidget * parent)
{
	ui.setupUi(this);

	this->messageType = type;
	this->chessType = chessType;
	this->fromIp = fromIp;
	this->localIp = localIp;
	this->port = port;

	switch (this->messageType)
	{
	case MessageType::REQUEST:
		generateRequestedWindow();
		break;
	case MessageType::REFUSE:
		generateRefuseWindow();
		break;
	default:
		break;
	}
}

void MessageWindow::generateRequestedWindow()
{
	this->setFixedSize(300, 240);

	string gameType = this->chessType ? "GO game." : "five-in-a-row game.";
	string message = "You have a request from " + this->fromIp + " inviting you to play " + gameType;
	QLabel *requestLabel = new QLabel(QString::fromStdString(message), this);
	requestLabel->setWordWrap(true);

	QPushButton *agreeBtn = new QPushButton("Agree", this);
	QPushButton *refuseBtn = new QPushButton("Refuse", this);

	QGridLayout *layout = new QGridLayout(this);
	layout->addWidget(requestLabel, 0, 0, 1, 2);
	layout->addWidget(agreeBtn, 1, 0, 1, 1);
	layout->addWidget(refuseBtn, 1, 1, 1, 1);

	QObject::connect(agreeBtn, &QPushButton::clicked, this, &MessageWindow::agreeBtnClicked);
	QObject::connect(refuseBtn, &QPushButton::clicked, this, &MessageWindow::refuseBtnClicked);
}

void MessageWindow::generateRefuseWindow()
{
	this->setFixedSize(300, 240);

	string message = "Your request to play with " + this->fromIp + " has been refused.";
	QLabel *refuseLabel = new QLabel(QString::fromStdString(message), this);
	refuseLabel->setWordWrap(true);

	QGridLayout *layout = new QGridLayout(this);
	layout->addWidget(refuseLabel, 0, 0, 1, 1);

	this->setLayout(layout);
}

void MessageWindow::refuseBtnClicked(bool arg)
{
	// send a refuse message to remote
	DataGram *backDataGram = new DataGram();
	backDataGram->messageType = REFUSE;
	backDataGram->fromIp = this->localIp;
	backDataGram->toIp = this->fromIp;
	string tmp = backDataGram->toJson();
	DataSender *onlineMessageSender = new DataSender(this);
	onlineMessageSender->sendToSpecificClient(
		QString::fromStdString(this->fromIp),
		this->port,
		tmp.c_str(),
		tmp.length()
	);

	this->close();
}

void MessageWindow::agreeBtnClicked(bool arg)
{
	// send a agree message to remote
	DataGram *backDataGram = new DataGram();
	backDataGram->messageType = AGREE;
	backDataGram->chessType = this->chessType;
	backDataGram->fromIp = this->localIp;
	backDataGram->toIp = this->fromIp;
	string tmp = backDataGram->toJson();
	DataSender *onlineMessageSender = new DataSender(this);
	onlineMessageSender->sendToSpecificClient(
		QString::fromStdString(this->fromIp),
		this->port,
		tmp.c_str(),
		tmp.length()
	);

	emit gameReady(this->fromIp, this->localIp, this->chessType);

	this->close();
}