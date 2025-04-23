#include "User.h"

User::User(): _email(""), _password(""), _name(""), _role(""){}
User::User(const QString& email, const QString& password, const QString& name, const QString& role): _email(email), _password(password), _name(name), _role(role){}

QString User::email() const{
    return _email;
}

QString User::password() const{
    return _password;
}

QString User::name() const{
    return _name;
}

QString User::role() const{
    return _role;
}

void User::setEmail(const QString& email){
    _email = email;
}
void User::setPassord(const QString& password){
    _password = password;
}
void User::setName(const QString& name){
    _name = name;
}
void User::setRole(const QString& role){
    _role = role;
}

bool User::isValid() const{
    bool validEmail = _email.contains('@') && _email.indexOf('.', _email.indexOf('@')) > _email.indexOf('@');
    return !_email.isEmpty() 
    && !_password.isEmpty() 
    && !_name.isEmpty()
    && !_role.isEmpty()
    && validEmail;
}

