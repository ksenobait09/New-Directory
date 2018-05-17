#include "user.h"
#include "simplecrypt.h"
#include <qjson-qt5/parser.h>
#include <qjson-qt5/qjson_export.h>

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

bool User::sendMessage(int chatId, QString message){
    return false;
}

QString User::getChatsJSON() {
    db.getChatsForUser(this->id);

}
