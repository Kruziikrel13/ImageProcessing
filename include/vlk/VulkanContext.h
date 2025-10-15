#pragma once

#include <string>
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

    vk::raii::Context             context;
    vk::raii::Instance            instance            = nullptr;
    vk::raii::PhysicalDevice      physicalDevice      = nullptr;
    vk::raii::Device              device              = nullptr;
    vk::raii::Queue               computeQueue        = nullptr;
    vk::raii::CommandPool         commandPool         = nullptr; // Use this to create command buffers with which to operate
    vk::raii::DescriptorSetLayout descriptorSetLayout = nullptr;
    vk::raii::ShaderModule        computeShader       = nullptr;
    vk::raii::PipelineLayout      pipelineLayout      = nullptr;
    vk::raii::DescriptorPool      descriptorPool      = nullptr;
    vk::raii::CommandBuffer       commandBuffer       = nullptr;
    vk::raii::DescriptorSet       descriptorSet       = nullptr;

    vk::raii::Buffer              indexBuffer       = nullptr;
    vk::raii::DeviceMemory        indexBufferMemory = nullptr;

    uint32_t                      computeQueueFamilyIndex;
};
