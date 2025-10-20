#include "vlk/VulkanContext.h"
#include <spdlog/spdlog.h>
#include <stdexcept>

CVulkanContext::CVulkanContext() {
    SPDLOG_DEBUG("Constructing Vulkan context.");

    createInstance();
    pickPhysicalDevice();
    createLogicalDevice();
    SPDLOG_TRACE("Vulkan successfully initialized device!");

    createCommandPool();

    SPDLOG_DEBUG("Successfully constructed Vulkan context.");
}

void CVulkanContext::createInstance() {
    SPDLOG_TRACE("Creating Vulkan instance.");

    constexpr vk::ApplicationInfo applicationInfo{.pApplicationName   = "ImageProcessing",
                                                  .applicationVersion = vk::makeVersion(1, 0, 0),
                                                  .pEngineName        = "No Engine",
                                                  .engineVersion      = vk::makeVersion(1, 0, 0),
                                                  .apiVersion         = vk::ApiVersion14};

    vk::InstanceCreateInfo        createInfo{.pApplicationInfo = &applicationInfo};

    m_instance = vk::raii::Instance{m_context, createInfo};

    SPDLOG_TRACE("Successfully created Vulkan instance.");
}

void CVulkanContext::pickPhysicalDevice() {
    SPDLOG_TRACE("Selecting physical device.");

    std::vector<vk::raii::PhysicalDevice> devices = m_instance.enumeratePhysicalDevices();
    if (devices.empty()) {
        throw std::runtime_error("Failed to find GPUs with Vulkan support!");
    }

    for (auto& device : devices) {
        vk::PhysicalDeviceProperties deviceProperties = device.getProperties();
        // vk::PhysicalDeviceFeatures   deviceFeatures   = device.getFeatures();
        SPDLOG_DEBUG("Found device: {}", deviceProperties.deviceName.data());

        ///TODO: Check if device is a discrete GPU and check is has all required features for operations
        // if (deviceProperties.deviceType != vk::PhysicalDeviceType::eDiscreteGpu
        //     && deviceFeatures.shaderInt64 && deviceFeatures.shaderInt16) {
        //
        // }

        std::vector<vk::QueueFamilyProperties> queueFamilyProperties = device.getQueueFamilyProperties();
        for (uint32_t i = 0; i < queueFamilyProperties.size(); i++) {
            if (queueFamilyProperties[i].queueFlags & vk::QueueFlagBits::eCompute) {
                m_physicalDevice          = std::move(device);
                m_computeQueueFamilyIndex = i;
                deviceName                = deviceProperties.deviceName.data();
                SPDLOG_DEBUG("Selected device with compute support: {}", deviceProperties.deviceName.data());
                return;
            }
        }
    }

    throw std::runtime_error("Failed to find a suitable GPU with compute capabilities");
}

void CVulkanContext::createLogicalDevice() {
    SPDLOG_TRACE("Creating logical device.");

    float                     queuePriority = 1.0f;
    vk::DeviceQueueCreateInfo qCreateInfo{.queueFamilyIndex = m_computeQueueFamilyIndex, .queueCount = 1, .pQueuePriorities = &queuePriority};

    // Allow use of latest SPIR-V 1.4 shader modules
    // TODO: Check valid / necessary features and extensions
    std::vector<const char*> extensionList = {vk::KHRSpirv14ExtensionName, vk::KHRBufferDeviceAddressExtensionName};

    vk::DeviceCreateInfo     createInfo{.queueCreateInfoCount    = 1,
                                        .pQueueCreateInfos       = &qCreateInfo,
                                        .enabledExtensionCount   = static_cast<uint32_t>(extensionList.size()),
                                        .ppEnabledExtensionNames = extensionList.data()};

    m_device       = vk::raii::Device(m_physicalDevice, createInfo);
    m_computeQueue = vk::raii::Queue(m_device, m_computeQueueFamilyIndex, 0);

    SPDLOG_TRACE("Successfully created logical device.");
}

void CVulkanContext::createCommandPool() {
    SPDLOG_TRACE("Creating command pool.");

    vk::CommandPoolCreateInfo poolCreateInfo{.flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer, .queueFamilyIndex = m_computeQueueFamilyIndex};

    m_commandPool = vk::raii::CommandPool(m_device, poolCreateInfo);

    SPDLOG_TRACE("Successfully created command pool.");
}
