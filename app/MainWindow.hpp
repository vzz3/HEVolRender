#pragma once

#include <QMainWindow>

#include "ui_MainWindow.h"
//#include "../src/rendering/PlainVulkanRenderer.hpp"
#include "VulkanWindow.hpp"
#include "../src/paillier/Paillier_typeDev.h"
#include "../src/rendering/data/Volume.hpp"
#include "../src/paillier/crypto/SecureKey.hpp"
#include "../src/paillier/crypto/PublicKey.hpp"
/*
QT_BEGIN_NAMESPACE
class QTabWidget;
class QPlainTextEdit;
class QLCDNumber;
QT_END_NAMESPACE
*/

//using ppvr::rendering::PlainVulkanRenderer;
using ppvr::rendering::data::Volume;
using ppvr::paillier::crypto::SecureKey;
using ppvr::paillier::crypto::PublicKey;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();
	
    void initVulkanWindow();

public slots:
    void onVulkanInfoReceived(const QString &text);
    void onLogMessageReceived(const QString &text);
    void onFrameQueued(int colorValue);
    void onGrabRequested();
    
	void saveEncryptedVolume();
	void loadEncryptedVolume();
	
    void renderEcrypted();
    void testGpuBigInt();

private:
	void encryptVolume(const PublicKey &yPK);
	std::string makeHeVolFileName(const size_t ySize);

	#ifdef GPU_MONTGOMERY_REDUCTION
		static constexpr uint16_t volumeType = 3;
	#else
		static constexpr uint16_t volumeType = 1;
	#endif

	Ui_MainWindow *m_Ui;
	VulkanWindow *m_vulkanWindow = nullptr;
	//QTabWidget *m_infoTab;
	//QPlainTextEdit *m_info;
	//QLCDNumber *m_number;

	QVulkanInstance *qvInstance;

	QGraphicsScene *m_scene4EncryptedImageView;
	QPixmap pixmap4EncryptedImageView;

	SecureKey *m_secureKey = nullptr;
	Volume<PaillierInt> *m_encryptedVolume = nullptr;
	PublicKey *m_encryptedVolumeKey = nullptr;
};
