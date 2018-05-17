#include "user.h"
#include "simplecrypt.h"
//#include <qjson-qt5/parser.h>
//#include <qjson-qt5/qjson_export.h>

User::User(QString login, QString password)
{

    this->login = login;
    this->password = hashPassword(password);
    db.userRegister(login, this->password);
    this->id = db.userLogin(login, this->password);
}

QString User::hashPassword(QString password)
{
     SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f023));
     QString result = crypto.encryptToString(password);
     return result;
}

int User::addContact(QString login){
   int chatId = db.createChat(this->login, login);
   return chatId;
}

// fix usage of non-static data member
bool User::sendMessage(int chatId, QString message) {

    QTcpSocket * socket = server.getOutConnection(this->login);
    QString typeMessage = "MSGP";

    typeMessage += "&" + this->login + "&";
    typeMessage += chatId + "&";
    typeMessage += message + "&";

    socket->write(typeMessage.toUtf8());

    return true;
}

QString User::getChatsJSON() {
    db.getChatsForUser(this->id);

}
