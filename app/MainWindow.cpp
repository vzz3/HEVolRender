/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "MainWindow.hpp"
//#include <QVulkanFunctions>
//#include <QApplication>
//#include <QVBoxLayout>
//#include <QPlainTextEdit>
//#include <QPushButton>

#include <QFileDialog>
#include <QMessageBox>
#include <QTabWidget>
#include "../src/rendering/Camera.hpp"
#include "../src/rendering/EncryptedVulkanRenderer.hpp"
#include "../src/rendering/test/BigIntTestFactory.hpp"
#include "../src/rendering/data/VolumeFactory.hpp"
#include "../src/rendering/data/CryptoUtil.hpp"
#include "../src/util/DurationDisplay.hpp"
#include "../src/rendering/data/ImageUtil.hpp"
#include "../src/rendering/VulkanUtility.hpp"

#include "VulkanWindow.hpp"
#include "VulkanRenderer.hpp"

using ppvr::rendering::Camera;
using ppvr::rendering::EncryptedVulkanRenderer;
using ppvr::rendering::test::BigIntTestCase;
using ppvr::rendering::test::BigIntTestFactory;
using ppvr::rendering::data::VolumeFactory;
using ppvr::rendering::data::CryptoUtil;
using ppvr::util::DurationDisplay;
using ppvr::rendering::VulkanUtility;
using ppvr::paillier::crypto::SecureKey;

MainWindow::MainWindow() {

	/*
    m_info = new QPlainTextEdit;
    m_info->setReadOnly(true);

    m_number = new QLCDNumber(3);
    m_number->setSegmentStyle(QLCDNumber::Filled);

    QPushButton *grabButton = new QPushButton(tr("&Grab"));
    grabButton->setFocusPolicy(Qt::NoFocus);

    connect(grabButton, &QPushButton::clicked, this, &MainWindow::onGrabRequested);

    QPushButton *quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);

    connect(quitButton, &QPushButton::clicked, qApp, &QCoreApplication::quit);

    QVBoxLayout *layout = new QVBoxLayout;
    m_infoTab = new QTabWidget(this);
    m_infoTab->addTab(m_info, tr("Vulkan Info"));
    m_infoTab->addTab(logWidget, tr("Debug Log"));
    layout->addWidget(m_infoTab, 2);
    layout->addWidget(m_number, 1);
    layout->addWidget(wrapper, 5);
    layout->addWidget(grabButton, 1);
    layout->addWidget(quitButton, 1);
    setLayout(layout);
    */
	
    m_Ui = new Ui_MainWindow();
	m_Ui->setupUi(this);
	//QLayout *layout = m_Ui->controls->layout();
	//layout->setAlignment(Qt::AlignTop);
	//m_Ui->controls->setLayout(layout);
	
	m_Ui->infoPlainTextEdit->setReadOnly(true);
	
	m_scene4EncryptedImageView = new QGraphicsScene(this);
	this->m_Ui->encryptedTabGraphicsView->setScene(m_scene4EncryptedImageView);
	
	connect(m_Ui->actionGrabFrame, &QAction::triggered, this, &MainWindow::onGrabRequested);
	connect(m_Ui->actionRenderEncrypted, SIGNAL(triggered()), this, SLOT(renderEcrypted()));
	connect(m_Ui->actionTestGpuBigInt, SIGNAL(triggered()), this, SLOT(testGpuBigInt()));
}

MainWindow::~MainWindow() {
	if(m_secureKey != nullptr) {
		delete m_secureKey;
		m_secureKey = nullptr;
	}
	if(m_encryptedVolume != nullptr) {
		delete m_encryptedVolume;
		m_encryptedVolume = nullptr;
	}
	if(m_encryptedVolumeKey != nullptr) {
		delete m_encryptedVolumeKey;
		m_encryptedVolumeKey = nullptr;
	}
	
	delete qvInstance;
	qvInstance = nullptr;
	delete m_Ui;
	m_Ui = nullptr;
	delete m_scene4EncryptedImageView;
	m_scene4EncryptedImageView = nullptr;	
}

void MainWindow::initVulkanWindow() {
	
    qvInstance = new QVulkanInstance{};
	
    QByteArrayList vkInstExtensions;
	QByteArrayList vkDeviceExtensions;
	
    //vkInstExtensions << "VK_KHR_get_physical_device_properties2" // prevent validation error from QVulkanWindowPrivate::init():2021-01-03 23:58:27.397796+0100 ppvr_vulkan[91162:3916830] vkDebug: Validation: 0: Validation Error: [ VUID-vkCreateDevice-ppEnabledExtensionNames-01387 ] Object 0: VK_NULL_HANDLE, type = VK_OBJECT_TYPE_INSTANCE; | MessageID = 0x12537a2c | Missing extension required by the device extension VK_KHR_portability_subset: VK_KHR_get_physical_device_properties2. The Vulkan spec states: All required extensions for each extension in the VkDeviceCreateInfo::ppEnabledExtensionNames list must also be present in that list (https://vulkan.lunarg.com/doc/view/1.2.162.0/mac/1.2-extensions/vkspec.html#VUID-vkCreateDevice-ppEnabledExtensionNames-01387)

	//vkDeviceExtensions << "VK_KHR_portability_subset"  // prevent validation error from QVulkanWindowPrivate::init(): 2021-01-03 23:50:50.122671+0100 ppvr_vulkan[91036:3905482] vkDebug: Validation: 0: Validation Error: [ VUID-VkDeviceCreateInfo-pProperties-04451 ] Object 0: handle = 0x10efb65e0, type = VK_OBJECT_TYPE_PHYSICAL_DEVICE; | MessageID = 0x3a3b6ca0 | vkCreateDevice: VK_KHR_portability_subset must be enabled because physical device VkPhysicalDevice 0x10efb65e0[] supports it The Vulkan spec states: If the [VK_KHR_portability_subset] extension is included in pProperties of vkEnumerateDeviceExtensionProperties, ppEnabledExtensions must include "VK_KHR_portability_subset". (https://vulkan.lunarg.com/doc/view/1.2.162.0/mac/1.2-extensions/vkspec.html#VUID-VkDeviceCreateInfo-pProperties-04451)

#ifdef NDEBUG
#else
#ifndef Q_OS_ANDROID
    qvInstance->setLayers(QByteArrayList()
    	<< "VK_LAYER_KHRONOS_validation"
    	//<< "VK_LAYER_LUNARG_api_dump"
    	<< "VK_LAYER_LUNARG_standard_validation"
	);
	
	vkDeviceExtensions << "VK_KHR_shader_non_semantic_info";
#else
    inst->setLayers(QByteArrayList()
                   << "VK_LAYER_GOOGLE_threading"
                   << "VK_LAYER_LUNARG_parameter_validation"
                   << "VK_LAYER_LUNARG_object_tracker"
                   << "VK_LAYER_LUNARG_core_validation"
                   << "VK_LAYER_LUNARG_image"
                   << "VK_LAYER_LUNARG_swapchain"
                   << "VK_LAYER_GOOGLE_unique_objects");
#endif
#endif

	 qvInstance->setExtensions(vkInstExtensions);

    if (!qvInstance->create()) {
        qFatal("Failed to create Vulkan instance: %d", qvInstance->errorCode());
	}
	//VkInstance	vkTestInstance = qvInstance->vkInstance();
    m_vulkanWindow = new VulkanWindow;
    m_vulkanWindow->setVulkanInstance(qvInstance);
	
	
	m_vulkanWindow->setDeviceExtensions(vkDeviceExtensions);
	// QVulkanWindowPrivate::recreateSwapChain()
	
	MainWindow* mainWindow = this;
    QObject::connect(m_vulkanWindow, &VulkanWindow::vulkanInfoReceived, mainWindow, &MainWindow::onVulkanInfoReceived);
    QObject::connect(m_vulkanWindow, &VulkanWindow::frameQueued, mainWindow, &MainWindow::onFrameQueued);
	
    QWidget *wrapper = QWidget::createWindowContainer(m_vulkanWindow);
	//m_glWidget = new GLWidget(this, this);
	m_Ui->vkLayout->addWidget(wrapper);
	
	//m_window->show();
}

void MainWindow::onVulkanInfoReceived(const QString &text)
{
   //m_info->setPlainText(text);
   m_Ui->infoPlainTextEdit->appendPlainText(text);
}

void MainWindow::onLogMessageReceived(const QString &text) {
	 m_Ui->logPlainTextEdit->appendPlainText(text);
}

void MainWindow::onFrameQueued(int colorValue)
{
    //m_number->display(colorValue);
}

void MainWindow::onGrabRequested()
{
    if (!m_vulkanWindow->supportsGrab()) {
        QMessageBox::warning(this, tr("Cannot grab"), tr("This swapchain does not support readbacks."));
        return;
    }

    QImage img = m_vulkanWindow->grab();

    // Our startNextFrame() implementation is synchronous so img is ready to be
    // used right here.

    QFileDialog fd(this);
    fd.setAcceptMode(QFileDialog::AcceptSave);
    fd.setDefaultSuffix("png");
    fd.selectFile("test.png");
    if (fd.exec() == QDialog::Accepted)
        img.save(fd.selectedFiles().first());
}

void MainWindow::encryptVolume(const PublicKey &yPK) {
	size_t volumeSize = 256;

	if(m_encryptedVolume != nullptr) {
		delete m_encryptedVolume;
		m_encryptedVolume = nullptr;
	}
	
	// create volume
	Volume<uint16_t> plainVolume;
	PRINT_DURATION( VolumeFactory::createVolume(plainVolume, volumeSize), "create volume");
	
	// encrypt volume
	m_encryptedVolume = new Volume<PaillierInt>{};
	PRINT_DURATION(CryptoUtil::encrypt(yPK, plainVolume, *m_encryptedVolume), "encrypt volume");
	
	if(m_encryptedVolumeKey != nullptr) {
		delete m_encryptedVolumeKey;
		m_encryptedVolumeKey = nullptr;
	}
	m_encryptedVolumeKey = new PublicKey{yPK};
}

void MainWindow::renderEcrypted() {
	// rendering config
	QSize imageSize{512, 512};
	
	// create key
	if(m_secureKey == nullptr) {
		m_secureKey = new SecureKey{SecureKey::create(PAILLIER_MODULUS_BIT_LENGTH)};
	}
	
	if(m_encryptedVolume == nullptr) {
		this->encryptVolume(m_secureKey->publicKey);
	}
	
	PaillierInt rayNormalizationDivisor = PaillierInt::fromInt64(m_encryptedVolume->depth()/2);
	
	SecureKey sk = *m_secureKey;
	PublicKey pk = sk.publicKey;
	std::cout << "Key: P=" << sk.p.toStringHex() << ", Q=" << sk.q.toStringHex() << ", M=" << pk.modulus.toStringHex() << ", M^2=" << pk.getModulusSquared().toStringHex() << std::endl;
	
	
	Image<PaillierInt> encryptedImage;
	Image<uint16_t> paintextImage;
	
	// inizialize GPU rendering
	Camera cameraCopy = m_vulkanWindow->m_vulkanRenderer->camera();
	cameraCopy.setViewportSize(imageSize.width(), imageSize.height());
	EncryptedVulkanRenderer* encRenderer = new EncryptedVulkanRenderer(qvInstance, m_vulkanWindow->physicalDevice(), cameraCopy);
	encRenderer->setEncryptedVolume(&pk, m_encryptedVolume);
	encRenderer->initGpuResources();
	encRenderer->initSwapChainResources(imageSize, 1);
	
	for(size_t f = 0; f < 5; f++) {
		// draw cube postions textures and render an encrypted image from the encrypted Volume
		PRINT_DURATION(encRenderer->draw(0), "draw on GPU");
		
		// copy the result from the GPU memory to the main memory
		//QImage img = encRenderer->framebuffer2host();
		encRenderer->framebuffer2host(encryptedImage);
		
		// decrypt (and normalize) the resulting image
		PRINT_DURATION( CryptoUtil::decrypt(sk, rayNormalizationDivisor, encryptedImage, paintextImage), "decrypt");
		QImage img = ppvr::rendering::data::ImageUtil::convertToNewQImage(paintextImage);
		
		// show image in QT GUI
		m_scene4EncryptedImageView->clear();
		m_scene4EncryptedImageView->addPixmap(QPixmap::fromImage(img));
		m_scene4EncryptedImageView->setSceneRect(img.rect());
	}
	// cleanup GPU resources
	encRenderer->releaseSwapChainResources();
	encRenderer->releaseGpuResources();
	delete encRenderer;
}

void MainWindow::testGpuBigInt() {
	std::cout << "BigInt GPU info: molulusLength=" << PAILLIER_MODULUS_BIT_LENGTH << "bit"
	 	<< ", storageLength=" << PAILLIER_INT_STORAGE_BIT_LENGTH << "bit"
		<< ", calculationLength=" << PAILLIER_INT_BIT_LENGTH << "bit"
		<< ", bitPerWord=" << BIG_INT_BITS_PER_WORD << "bit"
		<< ", vulkanTextureFormat=" << VulkanUtility::textureFormatName(GPU_INT_TEXTURE_FORMAT)
		<< ", vulkanWordsPerTexture=" << GPU_INT_TEXTURE_WORD_COUNT
		<< ", vulkanTextureCount=" << GPU_INT_TEXTURE_SIZE
		<< ", vulkanAttachmentFormat=" << VulkanUtility::textureFormatName(GPU_INT_ATTACHMENT_FORMAT)
		<< ", vulkanWordsPerAttachment=" << GPU_INT_ATTACHMENT_WORD_COUNT
		<< ", vulkanAttachmentCount=" << GPU_INT_ATTACHMENT_SIZE
		<< std::endl;
	
	
	EncryptedVulkanRenderer* encRenderer = new EncryptedVulkanRenderer(qvInstance, m_vulkanWindow->physicalDevice(), m_vulkanWindow->m_vulkanRenderer->camera(), true);
	
	std::vector<BigIntTestCase> testCases = BigIntTestFactory::createAllTest();
	for(BigIntTestCase& testCase : testCases) {
		if(testCase.getRequiredFboSize().height() <= 0) {
			std::cout << "The Test Case " << testCase.name << " does not have any assertions." << std::endl;
			continue;
		}
		encRenderer->setBigIntTestCase(&testCase);
		
		encRenderer->initGpuResources();
		encRenderer->initSwapChainResources(testCase.getRequiredFboSize(), 1);
		
		encRenderer->evaluateTest();
		
		encRenderer->releaseSwapChainResources();
		encRenderer->releaseGpuResources();
	}
	
	delete encRenderer;
	
}

