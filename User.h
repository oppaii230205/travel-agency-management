#ifndef _USER_H_
#define _USER_H_

#include<QString>
#include<QMetaType>

class User{
    private:
        QString _email;
        QString _password;
        QString _name;
        QString _role;
        QString _avatarUrl;
    public:
        User();
        User(const QString& email, const QString& password, const QString& name, const QString& role, const QString& avatarUrl);

        QString email() const;
        QString password() const;
        QString name() const;
        QString role() const;
        QString avatarUrl() const;

        void setAvatarUrl(const QString &url);
        void setEmail(const QString& email);
        void setPassord(const QString& password);
        void setName(const QString& name);
        void setRole(const QString& role);

        bool isValid() const;
};

Q_DECLARE_METATYPE(User)

#endif
