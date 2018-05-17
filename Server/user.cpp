#include "user.h"
#include "simplecrypt.h"

User::User(QString login, QString password)
{

    this->login = login;
    this->password = hashPassword(password);
    db.userRegister(login, password);
    this->id = db.userLogin(login, password);
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
