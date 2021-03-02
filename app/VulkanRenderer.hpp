#pragma once

#include "VulkanWindow.hpp"
#include "../src/rendering/PlainVulkanRenderer.hpp"

using ppvr::rendering::PlainVulkanRenderer;

class VulkanRenderer : public PlainVulkanRenderer //TriangleRenderer
{
public:
    VulkanRenderer(VulkanWindow *w);

    void initResources() override;
    void startNextFrame() override;
};
