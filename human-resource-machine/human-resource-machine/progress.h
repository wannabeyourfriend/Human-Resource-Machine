#pragma once
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <iostream>

class PlayerProgress {
public:
    int currentLevel;  // 当前关卡
    bool isCompleted;  // 是否完成当前关卡


    PlayerProgress() : currentLevel(1), isCompleted(false) {}

    // 保存进度到文件
    void saveProgress(const QString& filename) {
        QJsonObject progressData;
        progressData["currentLevel"] = currentLevel;
        progressData["isCompleted"] = isCompleted;

        QJsonDocument doc(progressData);
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(doc.toJson());
            file.close();
        }
    }

    // 从文件加载进度
    void loadProgress(const QString& filename) {
        //如果文件不存在，则创建文件并写入默认进度
        if (!QFile(filename).exists()) {
            saveProgress(filename);
            std::cout << "Progress file not found, creating a new one." << std::endl;
            return;
        }
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly)) {
            QByteArray data = file.readAll();
            QJsonDocument doc = QJsonDocument::fromJson(data);
            QJsonObject progressData = doc.object();

            currentLevel = progressData.value("currentLevel").toInt();
            isCompleted = progressData.value("isCompleted").toBool();
            file.close();
        }
    }
};
