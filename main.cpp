#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "view/cpp/EXWardrobe.h"
#include <iostream>
#include "view/cpp/MatrixRenderer.h"
#include "QCryptographicHash"

int main(int argc, char* argv[])
{
    neapu_ex_npk::NPKHandler::sha256 = [](const uint8_t* source, const uint64_t sourceLen, uint8_t* dst, const uint64_t dstLen) -> bool {
        auto hash = QCryptographicHash::hash(QByteArray(reinterpret_cast<const char*>(source), sourceLen), QCryptographicHash::Sha256);
        if (hash.size() > dstLen) {
            return false;
        }
        memcpy(dst, hash.data(), hash.size());
        return true;
    };
    QGuiApplication a(argc, argv);
    qInstallMessageHandler([](QtMsgType type, const QMessageLogContext& context, const QString& msg) {
        switch (type) {
        case QtDebugMsg:
            // neapu::Logger(neapu::LM_DEBUG) << msg.toStdString();
            std::cout << "[" << context.file << ":" << context.line << "][Debug]" << msg.toStdString() << std::endl;
            break;
        case QtInfoMsg:
            // neapu::Logger(neapu::LM_INFO) << msg.toStdString();
            std::cout << "[" << context.file << ":" << context.line << "][Info]" << msg.toStdString() << std::endl;
            break;
        case QtWarningMsg:
            // neapu::Logger(neapu::LM_WARNING) << msg.toStdString();
            std::cout << "[" << context.file << ":" << context.line << "][Warning]" << msg.toStdString() << std::endl;
            break;
        case QtCriticalMsg:
            // neapu::Logger(neapu::LM_ERROR) << msg.toStdString();
            std::cout << "[" << context.file << ":" << context.line << "][Error]" << msg.toStdString() << std::endl;
            break;
        case QtFatalMsg:
            // neapu::Logger(neapu::LM_DEADLY) << msg.toStdString();
            std::cout << "[" << context.file << ":" << context.line << "][Fatal]" << msg.toStdString() << std::endl;
            break;
        }
    });

    qmlRegisterType<neapu_ex_view::MatrixRenderer>("NeapuExView", 1, 0, "MatrixRenderer");
    QQmlApplicationEngine engine;
    auto exWardrobe = neapu_ex_view::EXWardrobe::getInstance();
    engine.rootContext()->setContextProperty("exWardrobe", exWardrobe.get());
    engine.rootContext()->setContextProperty("imageListModel", exWardrobe->getNPKImageListModel());
    const QUrl url(QStringLiteral("qrc:/view/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &a, []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
    engine.load(url);

    return a.exec();
}
