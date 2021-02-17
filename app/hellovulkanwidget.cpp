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

#include "hellovulkanwidget.h"
#include <QVulkanFunctions>
#include <QApplication>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QLCDNumber>
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

using ppvr::rendering::PlainVulkanRenderer;
using ppvr::rendering::Camera;
using ppvr::rendering::EncryptedVulkanRenderer;
using ppvr::rendering::test::BigIntTestCase;
using ppvr::rendering::test::BigIntTestFactory;
using ppvr::rendering::data::VolumeFactory;
using ppvr::rendering::data::CryptoUtil;
using ppvr::util::DurationDisplay;

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
    m_window = new VulkanWindow;
    m_window->setVulkanInstance(qvInstance);
	
	
	m_window->setDeviceExtensions(vkDeviceExtensions);
	// QVulkanWindowPrivate::recreateSwapChain()
	
	
	MainWindow* mainWindow = this;
	VulkanWindow* vulkanWindow = m_window;
    QObject::connect(vulkanWindow, &VulkanWindow::vulkanInfoReceived, mainWindow, &MainWindow::onVulkanInfoReceived);
    QObject::connect(vulkanWindow, &VulkanWindow::frameQueued, mainWindow, &MainWindow::onFrameQueued);
	
    QWidget *wrapper = QWidget::createWindowContainer(m_window);
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
    if (!m_window->supportsGrab()) {
        QMessageBox::warning(this, tr("Cannot grab"), tr("This swapchain does not support readbacks."));
        return;
    }

    QImage img = m_window->grab();

    // Our startNextFrame() implementation is synchronous so img is ready to be
    // used right here.

    QFileDialog fd(this);
    fd.setAcceptMode(QFileDialog::AcceptSave);
    fd.setDefaultSuffix("png");
    fd.selectFile("test.png");
    if (fd.exec() == QDialog::Accepted)
        img.save(fd.selectedFiles().first());
}

void MainWindow::renderEcrypted() {
	// rendering config
	size_t volumeSize = 100;
	QSize imageSize{150, 150};
	PaillierInt rayNormalizationDivisor = PaillierInt::fromInt64(volumeSize/2);
	
	// create key
	SecureKey sk = SecureKey::create(PAILLIER_MODULUS_BIT_LENGTH);
	PublicKey pk = sk.publicKey;
	std::cout << "Key: P=" << sk.p.toStringHex() << ", Q=" << sk.q.toStringHex() << ", M=" << pk.modulus.toStringHex() << ", M^2=" << pk.getModulusSquared().toStringHex() << std::endl;
	
	// create volume
	Volume<uint16_t> plainVolume;
	PRINT_DURATION( VolumeFactory::createVolume(plainVolume, volumeSize), "create volume");
	
	// encrypt volume
	Volume<PaillierInt> encryptedVolume;
	PRINT_DURATION(CryptoUtil::encrypt(sk.publicKey, plainVolume, encryptedVolume), "encrypt volume");
	
	Image<PaillierInt> encryptedImage;
	Image<uint16_t> paintextImage;
	
	// inizialize GPU rendering
	Camera cameraCopy = m_window->m_vulkanRenderer->camera();
	cameraCopy.setViewportSize(imageSize.width(), imageSize.height());
	EncryptedVulkanRenderer* encRenderer = new EncryptedVulkanRenderer(qvInstance, m_window->physicalDevice(), cameraCopy);
	encRenderer->setEncryptedVolume(&pk, &encryptedVolume);
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
	std::string textureFormatName = "Unknown (" + std::to_string(GPU_INT_TEXTURE_FORMAT) + ")";
	switch (GPU_INT_TEXTURE_FORMAT) {
		case VK_FORMAT_R8G8B8A8_UINT: textureFormatName = "GPU_INT_TEXTURE_FORMAT"; break;
		case VK_FORMAT_R32G32B32A32_UINT: textureFormatName = "VK_FORMAT_R32G32B32A32_UINT"; break;
	}
	std::cout << "BigInt GPU info: molulusLength=" << PAILLIER_MODULUS_BIT_LENGTH << "bit"
	 	<< ", storageLength=" << PAILLIER_INT_STORAGE_BIT_LENGTH << "bit"
		<< ", calculationLength=" << PAILLIER_INT_BIT_LENGTH << "bit"
		<< ", bitPerWord=" << BIG_INT_BITS_PER_WORD << "bit"
		<< ", vulkanTextureFormat=" << textureFormatName
		<< ", vulkanWordsPerTexture=" << GPU_INT_TEXTURE_WORD_COUNT
		<< ", vulkanTextureCount=" << GPU_INT_TEXTURE_SIZE
		<< std::endl;
	
	
	EncryptedVulkanRenderer* encRenderer = new EncryptedVulkanRenderer(qvInstance, m_window->physicalDevice(), m_window->m_vulkanRenderer->camera(), true);
	
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


//VulkanWindow::VulkanWindow(): m_camera(1,1) {}

QVulkanWindowRenderer* VulkanWindow::createRenderer()
{
	m_vulkanRenderer = new VulkanRenderer(this);
    return m_vulkanRenderer;
}

void VulkanWindow::mousePressEvent(QMouseEvent *event)
{
	m_lastPos = event->pos();
}

void VulkanWindow::wheelEvent(QWheelEvent *event)
{
	Camera& camera = m_vulkanRenderer->camera();
	float zoomDelta = event->angleDelta().y() / 300.0f;
	//qDebug() << "zoomDelta" << zoomDelta;
	camera.zoom(zoomDelta);
	//update(); // TODO render new frame
}

void VulkanWindow::mouseMoveEvent(QMouseEvent *event)
{
	Camera& camera = m_vulkanRenderer->camera();

	int dx = event->x() - m_lastPos.x();
	int dy = event->y() - m_lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		camera.rotateAzimuth(dx / 100.0f);
		camera.rotatePolar(dy / 100.0f);
	}

	if (event->buttons() & Qt::RightButton) {
		camera.rotateAzimuth(dx / 100.0f);
		camera.rotatePolar(dy / 100.0f);
	}
	m_lastPos = event->pos();
	//update(); // TODO render new frame
}



VulkanRenderer::VulkanRenderer(VulkanWindow *w)
    :
    //TriangleRenderer(w)
    PlainVulkanRenderer(w)
{
}

void VulkanRenderer::initResources()
{
    //TriangleRenderer::initResources();
	PlainVulkanRenderer::initResources();

    QVulkanInstance *inst = m_window->vulkanInstance();
    //m_devFuncs = inst->deviceFunctions(m_window->device());

    QString info;
    info += QString().asprintf("Number of physical devices: %d\n", m_window->availablePhysicalDevices().count());

    QVulkanFunctions *f = inst->functions();
    VkPhysicalDeviceProperties props;
    f->vkGetPhysicalDeviceProperties(m_window->physicalDevice(), &props);
    info += QString().asprintf("Active physical device name: '%s' version %d.%d.%d\nAPI version %d.%d.%d\n",
                              props.deviceName,
                              VK_VERSION_MAJOR(props.driverVersion), VK_VERSION_MINOR(props.driverVersion),
                              VK_VERSION_PATCH(props.driverVersion),
                              VK_VERSION_MAJOR(props.apiVersion), VK_VERSION_MINOR(props.apiVersion),
                              VK_VERSION_PATCH(props.apiVersion));

    info += QStringLiteral("Supported instance layers:\n");
    for (const QVulkanLayer &layer : inst->supportedLayers())
        info += QString().asprintf("    %s v%u\n", layer.name.constData(), layer.version);
    info += QStringLiteral("Enabled instance layers:\n");
    for (const QByteArray &layer : inst->layers())
        info += QString().asprintf("    %s\n", layer.constData());

    info += QStringLiteral("Supported instance extensions:\n");
    for (const QVulkanExtension &ext : inst->supportedExtensions())
        info += QString().asprintf("    %s v%u\n", ext.name.constData(), ext.version);
    info += QStringLiteral("Enabled instance extensions:\n");
    for (const QByteArray &ext : inst->extensions())
        info += QString().asprintf("    %s\n", ext.constData());
	
	{
		info += QStringLiteral("VkPhysicalDeviceFeatures:\n");
		VkPhysicalDeviceFeatures pDeviceFeatures{};
		inst->functions()->vkGetPhysicalDeviceFeatures(m_window->physicalDevice(), &pDeviceFeatures);
		info += QString().asprintf("    fragmentStoresAndAtomics: %s\n", 		(pDeviceFeatures.fragmentStoresAndAtomics ? "YES" : "NO"));
		info += QString().asprintf("    vertexPipelineStoresAndAtomics: %s\n", 	(pDeviceFeatures.vertexPipelineStoresAndAtomics ? "YES" : "NO"));
	}
	
    info += QString().asprintf("Color format: %u\nDepth-stencil format: %u\n",
                              m_window->colorFormat(), m_window->depthStencilFormat());

    info += QStringLiteral("Supported sample counts:");
    const QVector<int> sampleCounts = m_window->supportedSampleCounts();
    for (int count : sampleCounts)
        info += QLatin1Char(' ') + QString::number(count);
    info += QLatin1Char('\n');
	
	const VkPhysicalDeviceLimits& pdevLimits = props.limits; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkPhysicalDeviceLimits.html
	info += QStringLiteral("VkPhysicalDeviceLimits:\n");
	info += QString().asprintf("    maxFragmentOutputAttachments: %u\n", props.limits.maxFragmentOutputAttachments);
	info += QString().asprintf("    maxColorAttachments: %u    (max. number of FBO color attachments)\n", props.limits.maxColorAttachments);
	info += QString().asprintf("    maxPerStageDescriptorSampledImages: %u\n", props.limits.maxPerStageDescriptorSampledImages);
	info += QString().asprintf("    maxPerStageResources: %u\n", props.limits.maxPerStageResources);
	info += QString().asprintf("    maxDescriptorSetSampledImages: %u\n", props.limits.maxDescriptorSetSampledImages);

    emit static_cast<VulkanWindow *>(m_window)->vulkanInfoReceived(info);
}

void VulkanRenderer::startNextFrame()
{
    //TriangleRenderer::startNextFrame();
    //emit static_cast<VulkanWindow *>(m_window)->frameQueued(int(m_rotation) % 360);
	
	PlainVulkanRenderer::startNextFrame();
}
