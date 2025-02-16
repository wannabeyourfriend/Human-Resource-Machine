#include <QFile>
#include <QTextStream>
#include <QDebug>

void setupDebugLogging() {
    QFile file("debug_log.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "Logging started\n";
        qInstallMessageHandler([](QtMsgType, const QMessageLogContext&, const QString& msg) {
            QFile file("debug_log.txt");
            if (file.open(QIODevice::Append | QIODevice::Text)) {
                QTextStream out(&file);
                out << msg << "\n";
            }
            });
    }
}
