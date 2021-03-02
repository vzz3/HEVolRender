

#include "VulkanWindow.hpp"
#include "VulkanRenderer.hpp"
#include <QMouseEvent>
#include "../src/rendering/Camera.hpp"


using ppvr::rendering::Camera;

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

