#ifndef REGISTRY_H
#define REGISTRY_H

#include <QHash>
#include <QString>
#include <QSharedPointer>
#include <typeinfo>
#include <any>

#include <QDebug>

class Registry {
private:
    inline static QHash<QString, std::any> _instances;

public:
    template<typename T>
    static void addSingleton(QSharedPointer<T> instance) {
        _instances.insert(QString::fromStdString(typeid(T).name()), instance);
    }

    template<typename T>
    static QSharedPointer<T> getSingleton() {
        auto it = _instances.constFind(QString::fromStdString(typeid(T).name()));
        if (it != _instances.constEnd()) {
            try {
                return std::any_cast<QSharedPointer<T>>(it.value());
            } catch (const std::bad_any_cast& e) {
                qWarning() << "Bad cast when getting singleton for type:" << typeid(T).name();
                return nullptr;
            }
        }
        return nullptr;
    }

    // Phương thức để xóa tất cả instances
    static void clear() {
        _instances.clear();
    }

    // Kiểm tra xem service đã được đăng ký chưa
    template<typename T>
    static bool isRegistered() {
        return _instances.contains(QString::fromStdString(typeid(T).name()));
    }

    // Lấy danh sách tất cả các type đã đăng ký
    static QStringList getRegisteredTypes() {
        return _instances.keys();
    }
};

#endif // REGISTRY_H
