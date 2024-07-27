#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "view/cpp/EXWardrobe.h"
#include <logger.h>
#include "view/cpp/MatrixRenderer.h"
#include "QCryptographicHash"

int main(int argc, char *argv[])
{
    neapu_ex_npk::NPKHandler::sha256 = [](const uint8_t* source, const uint64_t sourceLen, uint8_t* dst, const uint64_t dstLen)->bool {
        auto hash = QCryptographicHash::hash(QByteArray(reinterpret_cast<const char*>(source), sourceLen), QCryptographicHash::Sha256);
        if (hash.size() > dstLen) {
            return false;
        }
        memcpy(dst, hash.data(), hash.size());
        return true;
    };
    QGuiApplication a(argc, argv);
    qInstallMessageHandler([](QtMsgType type, const QMessageLogContext &context, const QString &msg) {
        switch (type) {
        case QtDebugMsg:
                neapu::Logger(LM_DEBUG) << msg.toStdString();
                break;
            case QtInfoMsg:
                neapu::Logger(LM_INFO) << msg.toStdString();
                break;
            case QtWarningMsg:
                neapu::Logger(LM_WARNING) << msg.toStdString();
                break;
            case QtCriticalMsg:
                neapu::Logger(LM_ERROR) << msg.toStdString();
                break;
            case QtFatalMsg:
                neapu::Logger(LM_DEADLY) << msg.toStdString();
                break;
        }
    });

    qmlRegisterType<neapu_ex_view::MatrixRenderer>("NeapuExView", 1, 0, "MatrixRenderer");
    QQmlApplicationEngine engine;
    auto exWardrobe = neapu_ex_view::EXWardrobe::getInstance();
    engine.rootContext()->setContextProperty("exWardrobe", exWardrobe.get());
    engine.rootContext()->setContextProperty("imageListModel", exWardrobe->getNPKImageListModel());
    const QUrl url(QStringLiteral("qrc:/view/qml/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &a,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return a.exec();
}
