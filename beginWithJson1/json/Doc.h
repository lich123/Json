#ifndef DOC_H
#define DOC_H

#include <QObject>

class Doc : public QObject
{
    Q_OBJECT
public:
    explicit Doc(QObject *parent = nullptr);
    void Read(QString path);
    void Write(QString path1);
    void ReadRecursion(QJsonObject);
    void ReadArrRecursion(QJsonArray);

signals:

};

#endif // DOC_H
