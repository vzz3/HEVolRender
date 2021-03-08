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

#include <iostream>
#include <fstream>

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
	connect(m_Ui->actionOpenEncryptedVolume, SIGNAL(triggered()), this, SLOT(loadEncryptedVolume()));
	connect(m_Ui->actionSaveEncryptedVolume, SIGNAL(triggered()), this, SLOT(saveEncryptedVolume()));
	
	
	// set a not so secure private key for testing
	if(PAILLIER_MODULUS_BIT_LENGTH == 64) {
		m_secureKey = new ppvr::paillier::crypto::SecureKey(
			  PaillierInt::fromString("C456074F", 16)
			, PaillierInt::fromString("B2E819FB", 16)
		);
	} else if(PAILLIER_MODULUS_BIT_LENGTH == 128) {
		m_secureKey = new ppvr::paillier::crypto::SecureKey(
			  PaillierInt::fromString("D0D3F681BED1D223", 16)
			, PaillierInt::fromString("CA8BF0DF0FF05797", 16)
		);
	} else if(PAILLIER_MODULUS_BIT_LENGTH == 256) {
		m_secureKey = new ppvr::paillier::crypto::SecureKey(
			  PaillierInt::fromString("CDA36BE3D68106CC5801466E597D0925", 16)
			, PaillierInt::fromString("B2D541C69E76BE349840A867667C8F23", 16)
		);
	} else if(PAILLIER_MODULUS_BIT_LENGTH == 512) {
		m_secureKey = new ppvr::paillier::crypto::SecureKey(
			  PaillierInt::fromString("BD2EAAA4AB1501F2DC6D9DEC045A950D11DC8BFC30FAF210E100139289A8876B", 16)
			, PaillierInt::fromString("EBBE8A4F5B80457CE08D201096D0CA9171FC073AB182F564AFC34F8D98E54AB9", 16)
		);
	}
	else {
		m_secureKey = new SecureKey{SecureKey::create(PAILLIER_MODULUS_BIT_LENGTH)};
	}

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
	if(m_encryptedVolume != nullptr) {
		delete m_encryptedVolume;
		m_encryptedVolume = nullptr;
	}
	
	// create volume
	Volume<uint16_t> plainVolume;
	PRINT_DURATION( VolumeFactory::createVolume(plainVolume, testVolumeSize), "create volume");
	
	// encrypt volume
	m_encryptedVolume = new Volume<PaillierInt>{};
	PRINT_DURATION(CryptoUtil::encrypt(yPK, plainVolume, *m_encryptedVolume), "encrypt volume");
	
	if(m_encryptedVolumeKey != nullptr) {
		delete m_encryptedVolumeKey;
		m_encryptedVolumeKey = nullptr;
	}
	m_encryptedVolumeKey = new PublicKey{yPK};
}

std::string MainWindow::makeHeVolFileName(const size_t ySize) {
	std::string fileName = "test_k1_v" + std::to_string(ySize) + "_b" + std::to_string(PAILLIER_MODULUS_BIT_LENGTH); // test_k1_v256_b64_mont.hevol
	#ifdef GPU_MONTGOMERY_REDUCTION
		fileName += "_mont";
	#endif
    fileName += ".hevol";
    
    return fileName;
}

void MainWindow::saveEncryptedVolume() {
	QFileDialog fd(this);
    fd.setAcceptMode(QFileDialog::AcceptSave);
    fd.setDefaultSuffix("hevol");
    fd.selectFile(QString::fromStdString(makeHeVolFileName( ((m_encryptedVolume == nullptr) ? testVolumeSize : this->m_encryptedVolume->width()) )));
    if (fd.exec() == QDialog::Accepted) {
		// create encrypted volume if it does not exist
		if(m_encryptedVolume == nullptr) {
			this->encryptVolume(m_secureKey->publicKey);
		}
		
        //img.save(fd.selectedFiles().first());
		std::ofstream file(fd.selectedFiles().first().toStdString(), std::ios::out|std::ios::binary|std::ios::ate);
		if (file.is_open()) {
			constexpr size_t voxelSize = PAILLIER_INT_STORAGE_BIT_LENGTH / CHAR_BIT;
			
			uint16_t fileHeaderBuffer[5];// = {PAILLIER_INT_STORAGE_WORD_SIZE, this->m_encryptedVolume->width(), this->m_encryptedVolume->height(), this->m_encryptedVolume->depth()};
			fileHeaderBuffer[0] = volumeType;
			fileHeaderBuffer[1] = voxelSize;
			fileHeaderBuffer[2] = this->m_encryptedVolume->width();
			fileHeaderBuffer[3] = this->m_encryptedVolume->height();
			fileHeaderBuffer[4] = this->m_encryptedVolume->depth();
			
			// write storage size of an encrypted value, and volume width, height, and depth
			file.write(reinterpret_cast<const char*>(fileHeaderBuffer), sizeof(fileHeaderBuffer));
			
			// write the public key
			file.write(reinterpret_cast<const char*>(m_encryptedVolumeKey->modulus.getData()), voxelSize);
			
			const size_t volumeSize = m_encryptedVolume->length();
			for (size_t i=0; i < volumeSize; i++) {
				file.write(reinterpret_cast<const char*>(m_encryptedVolume->get(i).getData()), voxelSize);
			}
			
			file.close();
			std::cout << "saved file to " << fd.selectedFiles().first().toStdString() << "." << std::endl;
		}
	}
}

void MainWindow::loadEncryptedVolume() {
	QFileDialog fd(this);
    fd.setAcceptMode(QFileDialog::AcceptOpen);
    fd.setDefaultSuffix("hevol");
    fd.selectFile(QString::fromStdString(makeHeVolFileName(testVolumeSize)));
    if (fd.exec() == QDialog::Accepted) {
        //img.save(fd.selectedFiles().first());
		std::ifstream file(fd.selectedFiles().first().toStdString(), std::ios::in|std::ios::binary|std::ios::ate);
		if (file.is_open()) {
			const std::streampos size = file.tellg();
			uint16_t fileHeaderBuffer[5];
			file.seekg (0, std::ios::beg);
			
			// read header with size information
			file.read(reinterpret_cast<char*>(fileHeaderBuffer), sizeof(uint16_t) * 5);
			const uint16_t volumeTypeFromFile = fileHeaderBuffer[0];
			const size_t voxelSize = fileHeaderBuffer[1];
			const size_t width = fileHeaderBuffer[2];
			const size_t height = fileHeaderBuffer[3];
			const size_t depth = fileHeaderBuffer[4];
			
			if(volumeTypeFromFile != volumeType) {
				std::cout << "Volume Type does not match the current configuration (see GPU_MONTGOMERY_REDUCTION)" << std::endl;
			} else {
				if(PAILLIER_INT_STORAGE_BIT_LENGTH != voxelSize * CHAR_BIT) {
					std::cout << "Voxel storage size of file does not match PAILLIER_INT_STORAGE_BIT_LENGTH." << std::endl;
				} else {
					// read the public key
					PaillierInt modulus{0};
					file.read(reinterpret_cast<char*>(modulus.getDataUnsafe()), voxelSize);
					modulus.fixSignumAfterUnsafeOperation(false);
					if( modulus != m_secureKey->publicKey.modulus) {
						std::cout << "The Public key of the HE Volume File does not match the current secure key." << std::endl;
						// This is not an error. However, it is not posible to decrypt the rendered image with the current secury key.
					}
					if(m_encryptedVolumeKey != nullptr) {
						delete m_encryptedVolumeKey;
					}
					m_encryptedVolumeKey = new PublicKey{modulus};
					
					// reat the volume data
					if(m_encryptedVolume == nullptr) {
						m_encryptedVolume = new Volume<PaillierInt>();
					}
					m_encryptedVolume->resize(width, height, depth);
					const size_t volumeSize = m_encryptedVolume->length();
					for (size_t i=0; i < volumeSize; i++) {
						PaillierInt& voxel = m_encryptedVolume->get(i);
						file.read(reinterpret_cast<char*>(voxel.getDataUnsafe()), voxelSize);
						voxel.fixSignumAfterUnsafeOperation(false);
					}
					
					std::cout << "The entire volume from " << fd.selectedFiles().first().toStdString() << " is in memory." << std::endl;;
				}
			}
			
			file.close();
		}
	}
}

VkPhysicalDevice MainWindow::getGpuForEncryptedRendering() {
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	if(false) {
		// Use the GPU from onscreen rendering
		physicalDevice = m_vulkanWindow->physicalDevice();
	} else {
		// try to find an other GPU
		uint32_t deviceCount = 0;
		qvInstance->functions()->vkEnumeratePhysicalDevices(qvInstance->vkInstance(), &deviceCount, nullptr);
		if (deviceCount == 0) {
			throw std::runtime_error("failed to find GPUs with Vulkan support!");
		} else if (deviceCount == 1) {
			std::cout << "Only one GPU with Vulkan support found. Use the GPU from QT window rendering for encrypted rendering" << std::endl;
			physicalDevice = m_vulkanWindow->physicalDevice();
		} else {
			std::vector<VkPhysicalDevice> pDevices(deviceCount);
			qvInstance->functions()->vkEnumeratePhysicalDevices(qvInstance->vkInstance(), &deviceCount, pDevices.data());
			for (size_t i = 0; i < deviceCount; i++) {
				if(pDevices[i] != m_vulkanWindow->physicalDevice()) {
					physicalDevice = pDevices[i];
					VkPhysicalDeviceProperties pDevProps;
					qvInstance->functions()->vkGetPhysicalDeviceProperties(physicalDevice, &pDevProps);
					std::cout << "Physical device for encrypted rendering, index: '" << i << "', name: '" << pDevProps.deviceName << "'"
						<< " version "<<VK_VERSION_MAJOR(pDevProps.driverVersion)<<"."<<VK_VERSION_MINOR(pDevProps.driverVersion)<<"."<<VK_VERSION_PATCH(pDevProps.driverVersion)
						<< " API version "<<VK_VERSION_MAJOR(pDevProps.apiVersion)<<"."<<VK_VERSION_MINOR(pDevProps.apiVersion)<<"."<<VK_VERSION_PATCH(pDevProps.apiVersion)
						<< std::endl;
					break;
				}
			}
		}
	}
	return physicalDevice;
}

void MainWindow::renderEcrypted() {
	// rendering config
	QSize imageSize{512, 512};
	
	// create key
	if(m_secureKey == nullptr) {
		m_secureKey = new SecureKey{SecureKey::create(PAILLIER_MODULUS_BIT_LENGTH)};
	}
	
	SecureKey sk = *m_secureKey;
	PublicKey pk = sk.publicKey;
	std::cout << "Key: P=" << sk.p.toStringHex() << ", Q=" << sk.q.toStringHex() << ", M=" << pk.modulus.toStringHex() << ", M^2=" << pk.getModulusSquared().toStringHex() << std::endl;
	
	// create encrypted volume if it does not exist
	if(m_encryptedVolume == nullptr) {
		this->encryptVolume(m_secureKey->publicKey);
	}
	
	PaillierInt rayNormalizationDivisor = PaillierInt::fromInt64(m_encryptedVolume->depth()/2);
	
	Image<PaillierInt> encryptedImage;
	Image<uint16_t> paintextImage;
	
	// pick Physical device
	VkPhysicalDevice physicalDevice = this->getGpuForEncryptedRendering();
	
	// inizialize GPU rendering
	Camera cameraCopy = m_vulkanWindow->m_vulkanRenderer->camera();
	cameraCopy.setViewportSize(imageSize.width(), imageSize.height());
	EncryptedVulkanRenderer* encRenderer = new EncryptedVulkanRenderer(qvInstance, physicalDevice, cameraCopy);
	encRenderer->setEncryptedVolume(&pk, m_encryptedVolume);
	encRenderer->initGpuResources();
	encRenderer->initSwapChainResources(imageSize, 1);
	
	for(size_t f = 0; f < 3; f++) {
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
	
	// pick Physical device
	VkPhysicalDevice physicalDevice = this->getGpuForEncryptedRendering();
	EncryptedVulkanRenderer* encRenderer = new EncryptedVulkanRenderer(qvInstance, physicalDevice, m_vulkanWindow->m_vulkanRenderer->camera(), true);
	
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

