#pragma once

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_raii.hpp>

class CVulkanContext {
  public:
    CVulkanContext();
    std::string deviceName;

  private:
    void createInstance();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createCommandPool();
    // void                          createDescriptorSetLayout(); // Create dynamically as needed for operations / buffers
    // void                          createComputePipeline();
    // void                          createDescriptorPool();

    vk::raii::Context                   m_context;
    vk::raii::Instance                  m_instance            = nullptr;
    vk::raii::PhysicalDevice            m_physicalDevice      = nullptr;
    vk::raii::Device                    m_device              = nullptr;
    vk::raii::Queue                     m_computeQueue        = nullptr;
    vk::raii::CommandPool               m_commandPool         = nullptr; // Use this to create command buffers with which to operate
    vk::raii::DescriptorSetLayout       m_descriptorSetLayout = nullptr;
    vk::raii::ShaderModule              m_computeShader       = nullptr;
    vk::raii::PipelineLayout            m_pipelineLayout      = nullptr;
    vk::raii::DescriptorPool            m_descriptorPool      = nullptr;
    vk::raii::CommandBuffer             m_commandBuffer       = nullptr;
    vk::raii::DescriptorSet             m_descriptorSet       = nullptr;

    vk::raii::Buffer              m_indexBuffer       = nullptr;
    vk::raii::DeviceMemory        m_indexBufferMemory = nullptr;

    uint32_t                      m_computeQueueFamilyIndex;
};
