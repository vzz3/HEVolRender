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

using ppvr::rendering::PlainVulkanRenderer;
using ppvr::rendering::Camera;

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
}

MainWindow::~MainWindow() {
	delete qvInstance;
	qvInstance = nullptr;
	delete m_Ui;
	m_Ui = nullptr;
}

void MainWindow::initVulkanWindow() {
	
    qvInstance = new QVulkanInstance{};
    qvInstance->setExtensions( QByteArrayList()
    	//<< "VK_KHR_get_physical_device_properties2" // prevent validation error from QVulkanWindowPrivate::init():2021-01-03 23:58:27.397796+0100 ppvr_vulkan[91162:3916830] vkDebug: Validation: 0: Validation Error: [ VUID-vkCreateDevice-ppEnabledExtensionNames-01387 ] Object 0: VK_NULL_HANDLE, type = VK_OBJECT_TYPE_INSTANCE; | MessageID = 0x12537a2c | Missing extension required by the device extension VK_KHR_portability_subset: VK_KHR_get_physical_device_properties2. The Vulkan spec states: All required extensions for each extension in the VkDeviceCreateInfo::ppEnabledExtensionNames list must also be present in that list (https://vulkan.lunarg.com/doc/view/1.2.162.0/mac/1.2-extensions/vkspec.html#VUID-vkCreateDevice-ppEnabledExtensionNames-01387)

    );

#ifdef NDEBUG
#else
#ifndef Q_OS_ANDROID
    qvInstance->setLayers(QByteArrayList()
    	<< "VK_LAYER_KHRONOS_validation"
    	//<< "VK_LAYER_LUNARG_api_dump"
    	<< "VK_LAYER_LUNARG_standard_validation"
	);
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

    if (!qvInstance->create()) {
        qFatal("Failed to create Vulkan instance: %d", qvInstance->errorCode());
	}
    m_window = new VulkanWindow;
    m_window->setVulkanInstance(qvInstance);
	
	
	m_window->setDeviceExtensions( QByteArrayList()
 		//<< "VK_KHR_portability_subset"  // prevent validation error from QVulkanWindowPrivate::init(): 2021-01-03 23:50:50.122671+0100 ppvr_vulkan[91036:3905482] vkDebug: Validation: 0: Validation Error: [ VUID-VkDeviceCreateInfo-pProperties-04451 ] Object 0: handle = 0x10efb65e0, type = VK_OBJECT_TYPE_PHYSICAL_DEVICE; | MessageID = 0x3a3b6ca0 | vkCreateDevice: VK_KHR_portability_subset must be enabled because physical device VkPhysicalDevice 0x10efb65e0[] supports it The Vulkan spec states: If the [VK_KHR_portability_subset] extension is included in pProperties of vkEnumerateDeviceExtensionProperties, ppEnabledExtensions must include "VK_KHR_portability_subset". (https://vulkan.lunarg.com/doc/view/1.2.162.0/mac/1.2-extensions/vkspec.html#VUID-VkDeviceCreateInfo-pProperties-04451)
	);
	// QVulkanWindowPrivate::recreateSwapChain()
	
	
	MainWindow* mainWindow = this;
	VulkanWindow* vulkanWindow = m_window;
    QObject::connect(vulkanWindow, &VulkanWindow::vulkanInfoReceived, mainWindow, &MainWindow::onVulkanInfoReceived);
    QObject::connect(vulkanWindow, &VulkanWindow::frameQueued, mainWindow, &MainWindow::onFrameQueued);
	
    QWidget *wrapper = QWidget::createWindowContainer(m_window);
	//m_glWidget = new GLWidget(this, this);
	m_Ui->vlLayout->addWidget(wrapper);
	
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
	float zoomDelta = event->delta() / 300.0f;
	qDebug() << "zoomDelta" << zoomDelta;
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
    info += QString().sprintf("Number of physical devices: %d\n", m_window->availablePhysicalDevices().count());

    QVulkanFunctions *f = inst->functions();
    VkPhysicalDeviceProperties props;
    f->vkGetPhysicalDeviceProperties(m_window->physicalDevice(), &props);
    info += QString().sprintf("Active physical device name: '%s' version %d.%d.%d\nAPI version %d.%d.%d\n",
                              props.deviceName,
                              VK_VERSION_MAJOR(props.driverVersion), VK_VERSION_MINOR(props.driverVersion),
                              VK_VERSION_PATCH(props.driverVersion),
                              VK_VERSION_MAJOR(props.apiVersion), VK_VERSION_MINOR(props.apiVersion),
                              VK_VERSION_PATCH(props.apiVersion));

    info += QStringLiteral("Supported instance layers:\n");
    for (const QVulkanLayer &layer : inst->supportedLayers())
        info += QString().sprintf("    %s v%u\n", layer.name.constData(), layer.version);
    info += QStringLiteral("Enabled instance layers:\n");
    for (const QByteArray &layer : inst->layers())
        info += QString().sprintf("    %s\n", layer.constData());

    info += QStringLiteral("Supported instance extensions:\n");
    for (const QVulkanExtension &ext : inst->supportedExtensions())
        info += QString().sprintf("    %s v%u\n", ext.name.constData(), ext.version);
    info += QStringLiteral("Enabled instance extensions:\n");
    for (const QByteArray &ext : inst->extensions())
        info += QString().sprintf("    %s\n", ext.constData());

    info += QString().sprintf("Color format: %u\nDepth-stencil format: %u\n",
                              m_window->colorFormat(), m_window->depthStencilFormat());

    info += QStringLiteral("Supported sample counts:");
    const QVector<int> sampleCounts = m_window->supportedSampleCounts();
    for (int count : sampleCounts)
        info += QLatin1Char(' ') + QString::number(count);
    info += QLatin1Char('\n');

    emit static_cast<VulkanWindow *>(m_window)->vulkanInfoReceived(info);
}

void VulkanRenderer::startNextFrame()
{
    //TriangleRenderer::startNextFrame();
    //emit static_cast<VulkanWindow *>(m_window)->frameQueued(int(m_rotation) % 360);
	
	PlainVulkanRenderer::startNextFrame();
}