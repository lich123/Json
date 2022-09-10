#include "Doc.h"
#include <QFile>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>

Doc::Doc(QObject *parent)
    : QObject{parent}
{

}

//void Doc::Read(QString path)
//{
//    QFile file(path);
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
//        qDebug() << "Error";
//        return;
//    }
//    QByteArray bytes = file.readAll();
//    file.close();
//    QJsonParseError err;
//    QJsonDocument doc = QJsonDocument::fromJson(bytes, &err);

//    //nếu kiểu dữ liễu -> nên làm cái chi
//    QJsonObject rootObj = doc.object();
//    QJsonObject glossaryObj = rootObj.value("glossary").toObject();
//    QJsonObject GlossDivObj = glossaryObj.value("GlossDiv").toObject();



//   qDebug() << rootObj.value("name").toString();
//   qDebug() << glossaryObj.value("title").toString();
//   qDebug() << GlossDivObj.value("title").toString();
//}

void Doc::Read(QString path){

    QFile file(path);
    if(file.exists()){
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug() << "Error";
            return;
        }
        QByteArray bytes = file.readAll();
        file.close();
        QJsonParseError err;
        QJsonDocument myDoc = QJsonDocument::fromJson(bytes, &err);
        QJsonObject myObject = myDoc.object();
        if(myObject.isEmpty()){
            qDebug() << "Object is empty";
        }else{
            ReadRecursion(myObject);
        }
    }else{
        qDebug() << "File not exist";
    }
}

void Doc::ReadRecursion(QJsonObject myObject)
{
    for(int i = 0; i < myObject.size(); i ++){
        QString key = myObject.keys().at(i);
        if(myObject[key].isBool()){
            qDebug() << key + " : "<<myObject.value(key).toBool();
        }else if(myObject[key].isDouble()){
            qDebug() << key + " : "<<myObject.value(key).toDouble();
        }else if(myObject[key].isString()){
            qDebug() << key + " : "<<myObject.value(key).toString();
        }else if(myObject[key].isArray()){
            ReadArrRecursion(myObject[key].toArray());
        }else {
            qDebug() << key;
            QJsonObject myObj = myObject[key].toObject();
            ReadRecursion(myObj);
        }
    }
}

void Doc::ReadArrRecursion(QJsonArray myArr)
{
    for(int i = 0; i < myArr.size(); i ++){
        if(myArr[i].isObject()){
            ReadRecursion(myArr[i].toObject());
        }else if(myArr[i].isBool()){
            qDebug() << myArr[i].toBool();
        }else if(myArr[i].isDouble()){
            qDebug() << myArr[i].toDouble();
        }else if(myArr[i].isString()){
            qDebug() << myArr[i].toString();
        }else if(myArr[i].isArray()){
            QJsonArray myA = myArr[i].toArray();
            ReadArrRecursion(myA);
        }
    }
}

void Doc::Write(QString path1)
{
    QFile file(path1);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
    }
    QJsonObject testObj;
    QJsonObject testBigObj;
    QJsonObject testSmallObj;
    QJsonDocument Ghi;
    testSmallObj.insert("xe","SH");
    testBigObj.insert("address","hai ba trung");
    testObj.insert("name","LichHT1");
    testBigObj.insert("vehicle",testSmallObj);
    testObj.insert("phone",testBigObj);
    Ghi.setObject(testObj);
    file.write(Ghi.toJson());
    file.close();
}
