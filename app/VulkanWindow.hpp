#pragma once

#include <QVulkanWindow>
//#include "VulkanRenderer.hpp"
/*
#include "ui_MainWindow.h"
#include "../src/rendering/PlainVulkanRenderer.hpp"
#include "../src/rendering/data/Volume.hpp"
#include "../src/paillier/Paillier_typeDev.h"
#include "../src/paillier/crypto/SecureKey.hpp"



QT_BEGIN_NAMESPACE
class QTabWidget;
class QPlainTextEdit;
class QLCDNumber;
QT_END_NAMESPACE

using ppvr::rendering::PlainVulkanRenderer;
using ppvr::rendering::data::Volume;
using ppvr::paillier::crypto::SecureKey;
*/

class VulkanRenderer;

class VulkanWindow : public QVulkanWindow
{
    Q_OBJECT

public:
	//VulkanWindow();
    QVulkanWindowRenderer *createRenderer() override;
	
	//const ppvr::rendering::Camera& camera() const {
	//	return m_camera;
	//}

signals:
    void vulkanInfoReceived(const QString &text);
    void frameQueued(int colorValue);
	
protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

	//void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
	//void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

	void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
	
public:
	//ppvr::rendering::Camera m_camera;
	VulkanRenderer* m_vulkanRenderer = nullptr;
private:
	QPoint m_lastPos;
};
