#include "vulkan_rhi.h"
#include "rhi.h"
#include "rhi_struct.h"
#include "vulkan_util.h"
#include "runtime/function/render/render_pipeline.h"
#include "core/base/macro.h"
#include <array>
#include <stdexcept>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <cassert>
#include <functional>

namespace SimpleEngine {
	void VulkanRHI::init(RHIInitInfo init_info) {
		//设置窗口
		m_window = init_info.windowSystem->getWindow();
		std::array<int, 2> window_size = init_info.windowSystem->getWindowSize();

		//设置视口和裁剪初始值
		m_viewport = { 0.0f,0.0f,(float)window_size[0],(float)window_size[1],0.0f,1.0f };
		m_scissor = { {0,0},{(uint32_t)window_size[0],(uint32_t)window_size[1]} };

		//根据环境判断开不开debug工具
#ifndef NDEBUG
		m_enable_debug_utils_label = true;
		m_enable_validation_layers = true;
#else
		m_enable_debug_utils_label = false;
		m_enable_validation_layers = false;
#endif // !NDEBUG

		//初始化Vulkan
		createInstance();
		setupDebugCallback();
		createSurface();
		pickPhysicalDevice();
		createLogicalDevice();
		createCommandPool();
		createCommandBuffers();
		createDescriptorPool();
		createSyncPrimitives();
		createSwapchain();
		createSwapchainImageViews();
		createDepthResource();
		createAssetAllocator();
	}

	void VulkanRHI::prepareContext()
	{
		m_current_command_buffer = m_command_buffers[m_current_frame_index];
	}


	//**********************************创建实例********************************************//

	//获取窗口扩展和校验层扩展
	std::vector<const char*> VulkanRHI::getRequiredExtensions() {
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);//获取所有需要的扩展
		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (m_enable_validation_layers || m_enable_debug_utils_label)
		{
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);//设置回调函数接受调试信息
		}

		return extensions;
	}

	void VulkanRHI::createInstance() {

		if (m_enable_validation_layers && !checkValidationLayerSupport()) {
			throw std::runtime_error("校验层请求失败！");
		}

		//应用程序信息
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "engine_renderer";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "SimpleEngine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		//创建信息：设置应用程序信息、全局扩展，校验层
		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		auto extensions = getRequiredExtensions();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();


		//启动校验层
		if (m_enable_validation_layers) {
			createInfo.enabledLayerCount = static_cast<uint32_t>(m_validation_layers.size());
			createInfo.ppEnabledLayerNames = m_validation_layers.data();

			VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
			populateDebugMessengerCreateInfo(debugCreateInfo);
			createInfo.pNext = &debugCreateInfo;
		}
		else {
			createInfo.enabledLayerCount = 0;
			createInfo.pNext = nullptr;
		}


		//创建实例
		if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS) {
			throw std::runtime_error("实例创建失败！");
		}
	}



	//**********************************设置校验层********************************************//

	//请求所有可用校验层
	bool VulkanRHI::checkValidationLayerSupport() {
		//找出所有可用的层
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
		std::vector<VkLayerProperties> avaliableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, avaliableLayers.data());

		//检查要使用的校验层列表是否都可用
		for (const char* layerName : m_validation_layers) {
			bool layerFound = false;
			for (const auto& layerProperties : avaliableLayers) {
				if (strcmp(layerName, layerProperties.layerName) == 0) {
					layerFound = true;
					break;
				}
			}
			if (!layerFound) return false;
		}
		return true;
	}

	//返回布尔值，表示API调用是否中断
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,//信息等级
		VkDebugUtilsMessageTypeFlagsEXT messageType,//信息类型
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData) {//设置回调时传递的数据
		std::cerr << "校验层：" << pCallbackData->pMessage << std::endl;
		return VK_FALSE;
	}

	//创建回调的代理函数
	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
		const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkDebugUtilsMessengerEXT* pCallback) {
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"); //加载函数，因为它是扩展函数，不会被Vulkan库加载
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pCallback);
		}
		else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void VulkanRHI::setupDebugCallback() {
		if (m_enable_validation_layers) {
			//回调信息
			VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
			populateDebugMessengerCreateInfo(createInfo);

			if (CreateDebugUtilsMessengerEXT(m_instance, &createInfo, nullptr, &m_callback) != VK_SUCCESS) {
				throw std::runtime_error("创建debug回调函数失败！");
			}
		}
		if (m_enable_debug_utils_label)
		{
			_vkCmdBeginDebugUtilsLabelEXT = (PFN_vkCmdBeginDebugUtilsLabelEXT)vkGetInstanceProcAddr(m_instance, "vkCmdBeginDebugUtilsLabelEXT");
			_vkCmdEndDebugUtilsLabelEXT = (PFN_vkCmdEndDebugUtilsLabelEXT)vkGetInstanceProcAddr(m_instance, "vkCmdEndDebugUtilsLabelEXT");
		}
	}

	void VulkanRHI::pushEvent(VkCommandBuffer& commond_buffer, const char* name, const float* color)
	{
		if (m_enable_debug_utils_label)
		{
			VkDebugUtilsLabelEXT label_info;
			label_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
			label_info.pNext = nullptr;
			label_info.pLabelName = name;
			for (int i = 0; i < 4; ++i)
				label_info.color[i] = color[i];
			_vkCmdBeginDebugUtilsLabelEXT(commond_buffer, &label_info);
		}
	}

	void VulkanRHI::popEvent(VkCommandBuffer& commond_buffer)
	{
		if (m_enable_debug_utils_label)
		{
			_vkCmdEndDebugUtilsLabelEXT(commond_buffer);
		}
	}

	//销毁回调的代理函数
	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT callback, VkAllocationCallbacks* pAllocator) {
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (func != nullptr) {
			func(instance, callback, pAllocator);
		}
	}

	//校验层创建信息
	void VulkanRHI::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
	{
		createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;//消息级别：警告，错误
		createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;//消息类型：影响Vulkan性能，违反规范
		createInfo.pfnUserCallback = debugCallback;//回调
	}

	//**********************************设置窗口表面********************************************//
	void VulkanRHI::createSurface() {
		if (glfwCreateWindowSurface(m_instance, m_window, nullptr, &m_surface) != VK_SUCCESS) {
			throw std::runtime_error("创建窗口表面失败！");
		}
	}

	//**********************************选择物理设备********************************************//
	bool VulkanRHI::isDeviceSuitable(VkPhysicalDevice device) {
		//获取设备的队列族索引列表
		QueueFamilyIndices indices = findQueueFamilies(device);

		//检查交换链是否满足需求
		bool extensionsSupported = checkDeviceExtensionSupport(device);
		bool swapChainAdequate = false;
		if (extensionsSupported) {
			SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();//至少支持一种图像格式和呈现模式
		}

		//检查是否支持各向异性过滤
		VkPhysicalDeviceFeatures support_features;//纹理压缩，64位浮点数和多视图渲染等可选功能的支持
		vkGetPhysicalDeviceFeatures(device, &support_features);

		return indices.isComplete() && extensionsSupported && swapChainAdequate && support_features.samplerAnisotropy;
	}

	int VulkanRHI::rateDeviceSuitability(VkPhysicalDevice device) {
		VkPhysicalDeviceProperties deviceProperties;//基本的设备属性
		vkGetPhysicalDeviceProperties(device, &deviceProperties);

		//根据设备属性打分
		int score = 0;
		if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {//显卡支持集合着色器
			score += 1000;
		}
		else if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) {
			score += 100;
		}
		return score;
	}

	QueueFamilyIndices VulkanRHI::findQueueFamilies(VkPhysicalDevice device) {
		QueueFamilyIndices indices;

		//获取设备支持的队列族信息
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		uint32_t i = 0;
		for (const auto& queueFamily : queueFamilies) {
			if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {//检查是否支持图形指令
				indices.graphics_family = i;
			}
			if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT) {//检查是否支持计算指令
				indices.compute_family = i;
			}

			VkBool32 presentSupport = false;//检查是否支持呈现指令
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_surface, &presentSupport);
			if (queueFamily.queueCount > 0 && presentSupport) {
				indices.present_family = i;
			}

			if (indices.isComplete()) {
				break;
			}
			i++;
		}

		return indices;
	}

	void VulkanRHI::pickPhysicalDevice() {
		//获取所有显卡设备
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);
		if (deviceCount == 0) {
			throw std::runtime_error("没有可用GPU设备！");
		}
		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());

		//设备打分
		std::multimap<int, VkPhysicalDevice> candidates;//自动排序map，默认升序
		for (const auto& device : devices) {
			int score = rateDeviceSuitability(device);
			candidates.insert(std::make_pair(score, device));
		}

		if (candidates.rbegin()->first > 0 && isDeviceSuitable(candidates.rbegin()->second)) {
			m_physical_device = candidates.rbegin()->second;
		}
		else {
			throw std::runtime_error("没有合适的GPU设备！");
		}
	}

	//**********************************创建逻辑设备********************************************//
	void VulkanRHI::createLogicalDevice() {
		m_queue_indices = findQueueFamilies(m_physical_device);//设置队列索引信息

		//设备队列创建信息*3：要使用的队列族索引、队列数、优先级
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> queueFamilies = { m_queue_indices.graphics_family.value(),m_queue_indices.present_family.value(),m_queue_indices.compute_family.value() };
		float queuePriority = 1.0f;
		for (uint32_t queueFamily : queueFamilies) {
			VkDeviceQueueCreateInfo queueCreateInfo = {};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;//影响命令缓冲区的调用
			queueCreateInfos.push_back(queueCreateInfo);
		}

		//设置物理设备特性信息
		VkPhysicalDeviceFeatures deviceFeatures = {};
		deviceFeatures.samplerAnisotropy = VK_TRUE;//启用各向异性过滤。可提高纹理质量
		deviceFeatures.fragmentStoresAndAtomics = VK_TRUE;//启用片段着色器中的原子操作和存储图像
		deviceFeatures.independentBlend = VK_TRUE;//允许使用不同的混合设置渲染不同的颜色

		if (m_enable_point_light_shadow)
		{
			deviceFeatures.geometryShader = VK_TRUE;//光源阴影需要几何着色器来计算阴影投射
		}

		//创建逻辑设备,指定队列族、使用特性、扩展
		VkDeviceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(m_device_extensions.size());
		createInfo.ppEnabledExtensionNames = m_device_extensions.data();
		createInfo.enabledLayerCount = 0;

		if (vkCreateDevice(m_physical_device, &createInfo, nullptr, &m_device) != VK_SUCCESS) {
			throw std::runtime_error("创建逻辑设备失败！");
		}

		//获取逻辑设备的队列
		vkGetDeviceQueue(m_device, m_queue_indices.graphics_family.value(), 0, &m_graphics_queue);
		vkGetDeviceQueue(m_device, m_queue_indices.present_family.value(), 0, &m_present_queue);
		vkGetDeviceQueue(m_device, m_queue_indices.compute_family.value(), 0, &m_compute_queue);
	}


	//**********************************创建交换链********************************************//

	bool VulkanRHI::checkDeviceExtensionSupport(VkPhysicalDevice device) {
		//查询设备所有可用扩展
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

		std::set<std::string> requiredExtensions(m_device_extensions.begin(), m_device_extensions.end());

		//检查需要的扩展是否包含在可用扩展中
		for (const auto& extension : availableExtensions) {
			requiredExtensions.erase(extension.extensionName);
		}
		return requiredExtensions.empty();
	}

	SwapChainSupportDetails VulkanRHI::querySwapChainSupport(VkPhysicalDevice device) {
		SwapChainSupportDetails details;
		//查询基础表面特性
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_surface, &details.capabilities);
		//查询表面支持的格式
		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, nullptr);
		if (formatCount != 0) {
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, details.formats.data());
		}
		//查询支持的呈现模式
		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, nullptr);
		if (presentModeCount != 0) {
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, details.presentModes.data());
		}

		return details;
	}

	//设置表面格式：颜色格式、颜色空间
	VkSurfaceFormatKHR VulkanRHI::chooseSwapchainSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& available_surface_formats) {
		if (available_surface_formats.size() == 1 && available_surface_formats[0].format == VK_FORMAT_UNDEFINED) {//没有默认格式
			return { VK_FORMAT_B8G8R8A8_UNORM,VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };//颜色格式：RGB，颜色空间；SRGB
		}
		for (const auto& available_surface_format : available_surface_formats) {
			if (available_surface_format.format == VK_FORMAT_B8G8R8A8_UNORM && available_surface_format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
				return available_surface_format;
			}
		}
		return available_surface_formats[0];
	}
	//设置呈现模式：图像显示到屏幕的条件
	VkPresentModeKHR VulkanRHI::chooseSwapchainPresentMode(const std::vector<VkPresentModeKHR>& available_present_modes) {
		for (const auto& available_present_mode : available_present_modes) {
			if (available_present_mode == VK_PRESENT_MODE_MAILBOX_KHR)//交换链为队列，队满时直接替换队内图像
				return available_present_mode;
		}
		return VK_PRESENT_MODE_FIFO_KHR;
	}
	//设置交换范围：图像分辨率
	VkExtent2D VulkanRHI::chooseSwapchainExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
		if (capabilities.currentExtent.width != UINT32_MAX) {//非uint_t最大值，不能自定义范围
			return capabilities.currentExtent;
		}
		else {//自定义范围：设置为帧缓冲大小
			int width, height;
			glfwGetFramebufferSize(m_window, &width, &height);
			VkExtent2D actualExtent = { static_cast<uint32_t>(width),static_cast<uint32_t>(height) };
			actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
			actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
			return actualExtent;
		}
	}

	void VulkanRHI::createSwapchain() {
		SwapChainSupportDetails swapChainSupport = querySwapChainSupport(m_physical_device);
		VkSurfaceFormatKHR surfaceFormat = chooseSwapchainSurfaceFormat(swapChainSupport.formats);
		VkPresentModeKHR presentMode = chooseSwapchainPresentMode(swapChainSupport.presentModes);
		VkExtent2D extent = chooseSwapchainExtent(swapChainSupport.capabilities);

		//设置最小图像个数=交换链最小图像个数+1，实现三重缓冲
		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {//大于0时无限制
			imageCount = swapChainSupport.capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = m_surface;
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;//图像层次，通常1，VR有更多层次
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;//对图像进行的具体操作：把图像当颜色附着

		uint32_t queueFamilyIndices[] = { m_queue_indices.graphics_family.value(),m_queue_indices.present_family.value() };
		if (m_queue_indices.graphics_family != m_queue_indices.present_family) {
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;//图像可在多队列族间使用
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;//指定共享所有权的队列族
		}
		else {
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;//一张图同时只能被一个队列族拥有
			createInfo.queueFamilyIndexCount = 0;
			createInfo.pQueueFamilyIndices = nullptr;
		}

		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;//不进行变换
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;//不用alpha混合其他窗口
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE; //忽略窗口遮挡住的像素颜色
		createInfo.oldSwapchain = VK_NULL_HANDLE;//防止运行时交换链失效

		if (vkCreateSwapchainKHR(m_device, &createInfo, nullptr, &m_swapchain) != VK_SUCCESS) {
			throw std::runtime_error("创建交换链失败！");
		}

		//获取交换链图像
		vkGetSwapchainImagesKHR(m_device, m_swapchain, &imageCount, nullptr);
		m_swapchain_images.resize(imageCount);
		vkGetSwapchainImagesKHR(m_device, m_swapchain, &imageCount, m_swapchain_images.data());

		//存储交换链格式和范围
		m_swapchain_image_format = surfaceFormat.format;
		m_swapchain_extent = extent;

		//设置裁剪矩形
		m_scissor = { {0, 0}, {m_swapchain_extent.width, m_swapchain_extent.height} };
	}

	//交换链信息：范围，图像视图，图像格式，裁剪，视口
	SwapChainDesc VulkanRHI::getSwapchainInfo() {
		SwapChainDesc desc = {};
		desc.extent = m_swapchain_extent;
		desc.imageViews = m_swapchain_imageviews;
		desc.image_format = m_swapchain_image_format;
		desc.scissor = &m_scissor;
		desc.viewport = &m_viewport;
		return desc;
	}

	//动态设置视口、裁剪
	void VulkanRHI::cmdSetViewport(uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports) {
		vkCmdSetViewport(m_current_command_buffer, firstViewport, viewportCount, pViewports);
	}
	void VulkanRHI::cmdSetScissor(uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors) {
		vkCmdSetScissor(m_current_command_buffer, firstScissor, scissorCount, pScissors);
	}
	//**********************************重建交换链********************************************//
	void VulkanRHI::recreateSwapchain() {
		//窗口最小化时，帧缓冲大小为0，等待窗口重新可见
		int width = 0;
		int height = 0;
		glfwGetFramebufferSize(m_window, &width, &height);
		while (width == 0 || height == 0)
		{
			glfwGetFramebufferSize(m_window, &width, &height);
			glfwWaitEvents();
		}

		//等待所有帧都结束，让设备处于空闲状态
		VkResult res_wait_for_fences = waitForFences(k_max_frames_in_flight, m_is_frame_in_flight_fences, VK_TRUE, UINT64_MAX);
		if (VK_SUCCESS != res_wait_for_fences)
		{
			throw std::runtime_error("等待栅栏信号失败！");
			return;
		}

		//销毁图像视图、图像、交换链
		vkDestroyImageView(m_device, m_depth_image_view, nullptr);
		vkDestroyImage(m_device, m_depth_image, nullptr);
		vkFreeMemory(m_device, m_depth_image_memory, nullptr);

		for (auto imageview : m_swapchain_imageviews)
		{
			vkDestroyImageView(m_device, imageview, nullptr);
		}
		vkDestroySwapchainKHR(m_device, m_swapchain, nullptr);

		//创建交换链、视图、帧缓冲图像和视图
		createSwapchain();
		createSwapchainImageViews();
		createDepthResource();
	}
	//**********************************创建图像视图********************************************//
	void VulkanRHI::createSwapchainImageViews() {
		m_swapchain_imageviews.resize(m_swapchain_images.size());
		for (size_t i = 0; i < m_swapchain_images.size(); i++) {
			//参数：设备，交换链图像，格式，图像为渲染目标，2D纹理，级数，层数
			m_swapchain_imageviews[i] = VulkanUtil::createImageView(m_device, m_swapchain_images[i], m_swapchain_image_format, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_VIEW_TYPE_2D, 1, 1);
			//VulkanUtil::transitionImageLayout(this, m_swapchain_images[i], VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, 1, 1, VK_IMAGE_ASPECT_COLOR_BIT);
		}
	}

	void VulkanRHI::createImageView(VkImage& image, VkFormat format, VkImageAspectFlags image_aspect_flags, VkImageViewType view_type, uint32_t layout_count, uint32_t miplevels, VkImageView& image_view) {
		image_view = VulkanUtil::createImageView(m_device, image, format, image_aspect_flags, view_type, layout_count, miplevels);
	}

	//**********************************创建图形渲染管线********************************************//

	VkShaderModule VulkanRHI::createShaderModule(const std::vector<unsigned char>& shader_code) {
		VkShaderModule shader_module = VulkanUtil::createShaderModule(m_device, shader_code);
		return shader_module;
	}
	void VulkanRHI::destroyShaderModule(VkShaderModule& shaderModule) {
		vkDestroyShaderModule(m_device, shaderModule, nullptr);
	}

	VkResult VulkanRHI::createPipelineLayout(const VkPipelineLayoutCreateInfo* pCreateInfo, VkPipelineLayout* pPipelineLayout) {
		VkResult result = vkCreatePipelineLayout(m_device, pCreateInfo, nullptr, pPipelineLayout);
		return result;
	}

	VkResult VulkanRHI::createRenderPass(VkRenderPassCreateInfo* pCreateInfo, VkRenderPass* pRenderPass) {
		VkResult result = vkCreateRenderPass(m_device, pCreateInfo, nullptr, pRenderPass);
		return result;
	}


	VkResult VulkanRHI::createGraphicsPipelines(VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfo, VkPipeline* pPipelines) {
		VkResult result = vkCreateGraphicsPipelines(m_device, pipelineCache, createInfoCount, pCreateInfo, nullptr, pPipelines);
		return result;
	}

	//**********************************创建帧缓冲********************************************//
	VkResult VulkanRHI::createFramebuffer(const VkFramebufferCreateInfo* pCreateInfo, VkFramebuffer* pFramebuffer) {
		VkResult result = vkCreateFramebuffer(m_device, pCreateInfo, nullptr, pFramebuffer);
		return result;
	}

	void VulkanRHI::destroyFramebuffer(VkFramebuffer& framebuffer)
	{
		vkDestroyFramebuffer(m_device, framebuffer, nullptr);
	}

	//**********************************创建命令池、命令缓冲********************************************//

	//指令池分配指令缓冲给队列
	void VulkanRHI::createCommandPool() {

		//创建RHI的指令池：内存传输
		VkCommandPoolCreateInfo pool_info = {};
		pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		pool_info.pNext = NULL;
		pool_info.queueFamilyIndex = m_queue_indices.graphics_family.value();
		pool_info.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;//分配的帧缓冲对象频繁用于记录新指令

		if (vkCreateCommandPool(m_device, &pool_info, nullptr, &m_rhi_command_pool) != VK_SUCCESS) {
			throw std::runtime_error("创建指令池失败！");
		}

		//创建渲染用的3个指令池
		VkCommandPoolCreateInfo command_pool_info;
		command_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		command_pool_info.pNext = NULL;
		command_pool_info.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
		command_pool_info.queueFamilyIndex = m_queue_indices.graphics_family.value();

		for (uint32_t i = 0; i < k_max_frames_in_flight; ++i)
		{
			if (vkCreateCommandPool(m_device, &command_pool_info, nullptr, &m_command_pools[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("创建指令池失败！");
			}
		}
	}

	void VulkanRHI::createCommandBuffers() {
		//一个指令池分配一个指令缓冲
		VkCommandBufferAllocateInfo alloc_info = {};
		alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;//可以提交到队列上执行，不能被其他指令缓冲调用
		alloc_info.commandBufferCount = 1U;

		for (uint32_t i = 0; i < k_max_frames_in_flight; ++i)
		{
			alloc_info.commandPool = m_command_pools[i];
			if (vkAllocateCommandBuffers(m_device, &alloc_info, &m_command_buffers[i]) != VK_SUCCESS) {
				throw std::runtime_error("分配指令缓冲失败！");
			}
		}
	}

	VkResult VulkanRHI::allocateCommandBuffers(const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers) {
		VkResult result = vkAllocateCommandBuffers(m_device, pAllocateInfo, pCommandBuffers);
		return result;
	}

	void VulkanRHI::freeCommandBuffers(VkCommandPool& commandPool, uint32_t commandBufferCount, VkCommandBuffer* pCommandBuffers) {
		vkFreeCommandBuffers(m_device, commandPool, commandBufferCount, pCommandBuffers);
	}

	VkResult VulkanRHI::queueSubmit(VkQueue& queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence) {
		VkResult result = vkQueueSubmit(queue, submitCount, pSubmits, fence);
		return result;
	}
	VkResult VulkanRHI::queueWaitIdle(VkQueue& queue) {
		VkResult result = vkQueueWaitIdle(queue);
		return result;
	}

	void VulkanRHI::resetCommandPool()
	{
		VkResult res_reset_command_pool = vkResetCommandPool(m_device, m_command_pools[m_current_frame_index], 0);
		if (VK_SUCCESS != res_reset_command_pool)
		{
			LOG_ERROR("重置命令池失败！");
		}
	}

	//**********************************创建暂存缓冲********************************************//
	VkCommandBuffer& VulkanRHI::beginSingleTimeCommands() {
		//分配命令缓冲
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = m_rhi_command_pool;
		allocInfo.commandBufferCount = 1;

		VkCommandBuffer rhi_command_buffer;
		vkAllocateCommandBuffers(m_device, &allocInfo, &rhi_command_buffer);

		//开始指令缓冲
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;//只使用一次

		beginCommandBuffer(rhi_command_buffer, &beginInfo);

		return rhi_command_buffer;
	}
	void VulkanRHI::endSingleTimeCommands(VkCommandBuffer& command_buffer) {
		//结束命令缓冲
		endCommandBuffer(command_buffer);

		//提交给队列
		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &command_buffer;

		vkQueueSubmit(m_graphics_queue, 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(m_graphics_queue);//等待传输完成

		//释放命令缓冲
		vkFreeCommandBuffers(m_device, m_rhi_command_pool, 1, &command_buffer);
	}

	void VulkanRHI::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize srcOffset, VkDeviceSize dstOffset, VkDeviceSize size){
		VulkanUtil::copyBuffer(this, srcBuffer, dstBuffer, srcOffset, dstOffset, size);
	}

	void VulkanRHI::destroyBuffer(VkBuffer& buffer) {
		vkDestroyBuffer(m_device, buffer, nullptr);
	}

	//**********************************记录指令到指令缓冲********************************************//

	VkResult VulkanRHI::beginCommandBuffer(VkCommandBuffer& commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo) {
		//指定指令缓冲使用细节
		VkResult result = vkBeginCommandBuffer(commandBuffer, pBeginInfo);
		return result;
	}

	void VulkanRHI::cmdBeginRenderPass(VkCommandBuffer& commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents) {
		vkCmdBeginRenderPass(commandBuffer, pRenderPassBegin, contents);
	}

	void VulkanRHI::cmdBindPipeline(VkCommandBuffer& commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline){
		vkCmdBindPipeline(commandBuffer, pipelineBindPoint, pipeline);
	}

	void VulkanRHI::cmdDraw(VkCommandBuffer& commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance){
		vkCmdDraw(commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
	}

	void VulkanRHI::cmdEndRenderPass(VkCommandBuffer& commandBuffer){
		vkCmdEndRenderPass(commandBuffer);
	}

	VkResult VulkanRHI::endCommandBuffer(VkCommandBuffer& commandBuffer) {
		VkResult result = vkEndCommandBuffer(commandBuffer);
		return result;
	}

	//**********************************创建信号量********************************************//

	void VulkanRHI::createSyncPrimitives()
	{
		//信号量和栅栏的创建信息
		VkSemaphoreCreateInfo semaphore_create_info{};
		semaphore_create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fence_create_info{};
		fence_create_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fence_create_info.flags = VK_FENCE_CREATE_SIGNALED_BIT; //初始化为已发出信号

		for (uint32_t i = 0; i < k_max_frames_in_flight; i++)
		{
			if (vkCreateSemaphore(m_device, &semaphore_create_info, nullptr, &m_image_available_for_render_semaphores[i]) != VK_SUCCESS ||
				vkCreateSemaphore(m_device, &semaphore_create_info, nullptr, &m_image_finished_for_presentation_semaphores[i]) != VK_SUCCESS ||
				vkCreateFence(m_device, &fence_create_info, nullptr, &m_is_frame_in_flight_fences[i]) != VK_SUCCESS){
				throw std::runtime_error("同步信号创建失败！");
			}
		}

	}

	VkResult VulkanRHI::createSemaphore(const VkSemaphoreCreateInfo* pCreateInfo, VkSemaphore* pSemaphore) {
		VkResult result = vkCreateSemaphore(m_device, pCreateInfo, nullptr, pSemaphore);
		return result;
	}

	VkResult VulkanRHI::createFence(const VkFenceCreateInfo* pCreateInfo, VkFence* pFence) {
		VkResult result = vkCreateFence(m_device, pCreateInfo, nullptr, pFence);
		return result;
	}
	VkResult VulkanRHI::resetFences(uint32_t fenceCount,const VkFence*  pFences)
	{
		VkResult result = vkResetFences(m_device, fenceCount, pFences);
		return result;
	}
	VkResult VulkanRHI::waitForFences(uint32_t fenceCount, const VkFence* pFence, VkBool32 waitAll, uint64_t timeout) {
		VkResult result = vkWaitForFences(m_device, fenceCount, pFence,waitAll,timeout);
		return result;
	}
	void VulkanRHI::waitForFences()
	{
		VkResult res_wait_for_fences = waitForFences(1, &m_is_frame_in_flight_fences[m_current_frame_index], VK_TRUE, UINT64_MAX);
		if (res_wait_for_fences != VK_SUCCESS)
		{
			throw std::runtime_error("等待栅栏信号失败");
		}
	}

	//**********************************渲染通道********************************************//

	bool VulkanRHI::prepareBeforePass(std::function<void()> passUpdateAfterRecreateSwapchain) {

		//从交换链获取图像 参数：逻辑设备，交换链，超时时间，图像可用时的通知对象（可同时指定栅栏和信号量），输出可用交换链图像索引
		VkResult acquire_image_result = vkAcquireNextImageKHR(m_device,m_swapchain,UINT64_MAX,m_image_available_for_render_semaphores[m_current_frame_index],VK_NULL_HANDLE,&m_current_swapchain_image_index);

		if (VK_ERROR_OUT_OF_DATE_KHR == acquire_image_result)//交换链不能使用，一般是窗口改变后
		{
			recreateSwapchain();
			passUpdateAfterRecreateSwapchain();
			return true;
		}
		else if (VK_SUBOPTIMAL_KHR == acquire_image_result)//交换链可以使用，但表面属性不匹配
		{
			recreateSwapchain();
			passUpdateAfterRecreateSwapchain();

			//提交空命令缓冲区以等待信号量：图像仍可用
			//给队列提交信息：等待的信号量、管线阶段，指令缓冲
			VkPipelineStageFlags wait_stages[] = { VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT };//等所有阶段完成时再执行
			VkSubmitInfo submit_info = {};
			submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submit_info.waitSemaphoreCount = 1;
			submit_info.pWaitSemaphores = &m_image_available_for_render_semaphores[m_current_frame_index];//队列执行前要等待的信号量
			submit_info.pWaitDstStageMask = wait_stages;//等待的管线阶段
			submit_info.commandBufferCount = 0;//提交的指令缓冲
			submit_info.pCommandBuffers = NULL;
			submit_info.signalSemaphoreCount = 0;
			submit_info.pSignalSemaphores = NULL;

			VkResult res_reset_fences = resetFences(1, &m_is_frame_in_flight_fences[m_current_frame_index]);
			if (VK_SUCCESS != res_reset_fences)
			{
				throw std::runtime_error("重置栅栏失败！");
			}

			VkResult res_queue_submit = vkQueueSubmit(m_graphics_queue, 1, &submit_info, m_is_frame_in_flight_fences[m_current_frame_index]);//指令缓冲执行结束时发出信号
			if (VK_SUCCESS != res_queue_submit)
			{
				throw std::runtime_error("给队列提交信息失败！");
			}
			m_current_frame_index = (m_current_frame_index + 1) % k_max_frames_in_flight;//切到下一帧
			return true;
		}
		else
		{
			if (VK_SUCCESS != acquire_image_result)
			{
				throw std::runtime_error("获取图像失败！");
			}
		}

		// 开始命令缓冲
		VkCommandBufferBeginInfo command_buffer_begin_info{};
		command_buffer_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		command_buffer_begin_info.flags = 0;
		command_buffer_begin_info.pInheritanceInfo = nullptr;

		VkResult res_begin_command_buffer = beginCommandBuffer(m_command_buffers[m_current_frame_index], &command_buffer_begin_info);

		if (VK_SUCCESS != res_begin_command_buffer)
		{
			throw std::runtime_error("开启命令缓冲失败！");
			return false;
		}
		return false;
	}
	void VulkanRHI::submitRendering(std::function<void()> passUpdateAfterRecreateSwapchain) {
		//结束命令录制
		VkResult res_end_command_buffer = endCommandBuffer(m_command_buffers[m_current_frame_index]);
		if (VK_SUCCESS != res_end_command_buffer)
		{
			throw std::runtime_error("结束命令缓冲失败！");
		}

		VkSemaphore semaphores[1] = { m_image_finished_for_presentation_semaphores[m_current_frame_index] };

		//提交命令缓冲
		VkPipelineStageFlags wait_stages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		VkSubmitInfo submit_info = {};
		submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submit_info.waitSemaphoreCount = 1;
		submit_info.pWaitSemaphores = &m_image_available_for_render_semaphores[m_current_frame_index];//图像可以渲染
		submit_info.pWaitDstStageMask = wait_stages;
		submit_info.commandBufferCount = 1;
		submit_info.pCommandBuffers = &m_command_buffers[m_current_frame_index];
		submit_info.signalSemaphoreCount = 1;//指令缓冲执行结束
		submit_info.pSignalSemaphores = semaphores;

		VkResult res_reset_fences = resetFences(1, &m_is_frame_in_flight_fences[m_current_frame_index]);
		if (VK_SUCCESS != res_reset_fences){
			throw std::runtime_error("重置栅栏失败！");
			return;
		}
		VkResult res_queue_submit = vkQueueSubmit(m_graphics_queue, 1, &submit_info, m_is_frame_in_flight_fences[m_current_frame_index]);

		if (VK_SUCCESS != res_queue_submit){
			throw std::runtime_error("给队列提交信息失败！");
			return;
		}

		//渲染的图像返回给交换链
		VkPresentInfoKHR present_info = {};
		present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		present_info.waitSemaphoreCount = 1;
		present_info.pWaitSemaphores = &m_image_finished_for_presentation_semaphores[m_current_frame_index];
		present_info.swapchainCount = 1;//用于呈现图像的交换链
		present_info.pSwapchains = &m_swapchain;
		present_info.pImageIndices = &m_current_swapchain_image_index;//要呈现图像的索引

		VkResult present_result = vkQueuePresentKHR(m_present_queue, &present_info);
		if (VK_ERROR_OUT_OF_DATE_KHR == present_result || VK_SUBOPTIMAL_KHR == present_result)//窗口大小改变/表面格式不匹配，重建交换链
		{
			recreateSwapchain();
			passUpdateAfterRecreateSwapchain();
		}
		else
		{
			if (VK_SUCCESS != present_result){
				throw std::runtime_error("呈现图像失败！");
				return;
			}
		}

		m_current_frame_index = (m_current_frame_index + 1) % k_max_frames_in_flight;
	}

	void VulkanRHI::cmdNextSubpass(VkCommandBuffer& commandBuffer, VkSubpassContents contents) {
		vkCmdNextSubpass(commandBuffer, contents);
	}

	void VulkanRHI::cmdClearAttachments(VkCommandBuffer& commandBuffer, uint32_t attachmentCount, const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* pRects) {
		vkCmdClearAttachments(commandBuffer, attachmentCount, pAttachments, rectCount, pRects);
	}
	//**********************************缓冲内存********************************************//

	void VulkanRHI::freeMemory(VkDeviceMemory& memory){
		vkFreeMemory(m_device, memory, nullptr);
	}

	VkResult VulkanRHI::mapMemory(VkDeviceMemory& memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData){
		VkResult result = vkMapMemory(m_device, memory, offset, size, flags, ppData);
		return result;
	}

	void VulkanRHI::unmapMemory(VkDeviceMemory& memory){
		vkUnmapMemory(m_device, memory);
	}

	void VulkanRHI::invalidateMappedMemoryRanges(VkDeviceMemory& memory, VkDeviceSize offset, VkDeviceSize size){
		VkMappedMemoryRange mappedRange{};
		mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		mappedRange.memory = memory;
		mappedRange.offset = offset;
		mappedRange.size = size;
		vkInvalidateMappedMemoryRanges(m_device, 1, &mappedRange);
	}

	void VulkanRHI::flushMappedMemoryRanges(VkDeviceMemory& memory, VkDeviceSize offset, VkDeviceSize size)
	{
		VkMappedMemoryRange mappedRange{};
		mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		mappedRange.memory = memory;
		mappedRange.offset = offset;
		mappedRange.size = size;
		vkFlushMappedMemoryRanges(m_device, 1, &mappedRange);
	}

	void VulkanRHI::cmdBindVertexBuffers(VkCommandBuffer& commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets) {
		vkCmdBindVertexBuffers(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets);
	}

	void VulkanRHI::cmdBindIndexBuffer(VkCommandBuffer& commandBuffer, VkBuffer& buffer, VkDeviceSize offset,VkIndexType indexType) {
		vkCmdBindIndexBuffer(commandBuffer, buffer, offset,indexType);
	}

	void VulkanRHI::cmdDrawIndexed(VkCommandBuffer& commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) {
		vkCmdDrawIndexed(commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
	}

	void VulkanRHI::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& buffer_memory) {
		VulkanUtil::createBuffer(m_physical_device, m_device, size, usage, properties, buffer, buffer_memory);
	}
	void VulkanRHI::createBufferAndInitialize(VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& buffer_memory, VkDeviceSize size, void* data, int datasize) {
		VulkanUtil::createBufferAndInitialize(m_device, m_physical_device, usage, properties, buffer, buffer_memory, size, data, datasize);
	}


	//**********************************创建描述符********************************************//

	VkResult VulkanRHI::createDescriptorSetLayout(const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayout* pSetLayout) {
		VkResult result = vkCreateDescriptorSetLayout(m_device, pCreateInfo, nullptr, pSetLayout);
		return result;
	}

	void VulkanRHI::createDescriptorPool() {
		//描述符池大小
		VkDescriptorPoolSize pool_sizes[7];
		pool_sizes[0].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
		pool_sizes[0].descriptorCount = 3 + 2 + 2 + 2 + 1 + 1 + 3 + 3;
		pool_sizes[1].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		pool_sizes[1].descriptorCount = 1 + 1 + 1 * m_max_vertex_blending_mesh_count;
		pool_sizes[2].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;//普通描述符
		pool_sizes[2].descriptorCount = 1 * m_max_material_count;
		pool_sizes[3].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;//组合图像采样器描述符
		pool_sizes[3].descriptorCount = 3 + 5 * m_max_material_count + 1 + 1; // ImGui_ImplVulkan_CreateDeviceObjects
		pool_sizes[4].type = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
		pool_sizes[4].descriptorCount = 4 + 1 + 1 + 2;
		pool_sizes[5].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;//动态描述符
		pool_sizes[5].descriptorCount = 3;
		pool_sizes[6].type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
		pool_sizes[6].descriptorCount = 1;

		//描述符池创建信息
		VkDescriptorPoolCreateInfo pool_info{};
		pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		pool_info.poolSizeCount = sizeof(pool_sizes) / sizeof(pool_sizes[0]);//独立描述符个数
		pool_info.pPoolSizes = pool_sizes;
		pool_info.maxSets = 1 + 1 + 1 + m_max_material_count + m_max_vertex_blending_mesh_count + 1 + 1; //可分配的最大描述符集个数 +skybox + axis descriptor set
		pool_info.flags = 0U;

		if (vkCreateDescriptorPool(m_device, &pool_info, nullptr, &m_descriptor_pool) != VK_SUCCESS)
		{
			throw std::runtime_error("创建描述符池失败！");
		}
	}

	VkResult VulkanRHI::allocateDescriptorSets(const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets) {
		VkResult result = vkAllocateDescriptorSets(m_device, pAllocateInfo, pDescriptorSets);
		return result;
	}

	void VulkanRHI::updateDescriptorSets(uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies) {
		vkUpdateDescriptorSets(m_device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
	}

	void VulkanRHI::cmdBindDescriptorSets(VkCommandBuffer& commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets) {
		vkCmdBindDescriptorSets(commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
	}


	//**********************************图像纹理********************************************//
	//创建图像+内存绑定
	void VulkanRHI::createImage(uint32_t image_width, uint32_t image_height, VkFormat format, VkImageTiling image_tiling, VkImageUsageFlags image_usage_flags, VkMemoryPropertyFlags memory_property_flags, VkImage& image, VkDeviceMemory& memory, VkImageCreateFlags image_create_flags, uint32_t array_layers, uint32_t mip_levels) {
		VulkanUtil::createImage(m_physical_device, m_device, image_width, image_height, format, image_tiling, image_usage_flags, memory_property_flags, image, memory, image_create_flags, array_layers, mip_levels);
	}

	VkResult VulkanRHI::createSampler(const VkSamplerCreateInfo* pCreateInfo, VkSampler* pSampler) {
		VkResult result = vkCreateSampler(m_device, pCreateInfo, nullptr, pSampler);
		return result;
	}

	void VulkanRHI::createGlobalImage(VkImage& image, VkImageView& image_view, VmaAllocation& image_allocation, uint32_t texture_image_width, uint32_t texture_image_height, void* texture_image_pixels, VkFormat texture_image_format, uint32_t miplevels) {
		VulkanUtil::createGlobalImage(this, image, image_view, image_allocation, texture_image_width, texture_image_height, texture_image_pixels, texture_image_format, miplevels);
	}
	
	void VulkanRHI::destroyImageView(VkImageView& imageView)
	{
		vkDestroyImageView(m_device, imageView, nullptr);
	}

	void VulkanRHI::destroyImage(VkImage& image)
	{
		vkDestroyImage(m_device, image, nullptr);
	}

	void VulkanRHI::createCubeMap(VkImage& image, VkImageView& image_view, VmaAllocation& image_allocation, uint32_t texture_image_width, uint32_t texture_image_height, std::array<void*, 6> texture_image_pixels, VkFormat texture_image_format, uint32_t miplevels) {
		VulkanUtil::createCubeMap(this, image, image_view, image_allocation, texture_image_width, texture_image_height, texture_image_pixels, texture_image_format, miplevels);
	}
	//**********************************采样器********************************************//

	VkSampler VulkanRHI::getOrCreateDefaultSampler(DefaultSamplerType type) {
		switch (type)
		{
		case Default_Sampler_Linear:
			if (m_linear_sampler == nullptr){
				m_linear_sampler = VulkanUtil::getOrCreateLinearSampler(m_physical_device, m_device);
			}
			return m_linear_sampler;
			break;

		case Default_Sampler_Nearest:
			if (m_nearest_sampler == nullptr){
				m_nearest_sampler = VulkanUtil::getOrCreateNearestSampler(m_physical_device, m_device);
			}
			return m_nearest_sampler;
			break;

		default:
			return nullptr;
			break;
		}
	}
	VkSampler VulkanRHI::getOrCreateMipmapSampler(uint32_t width, uint32_t height) {
		if (width == 0 || height == 0)
		{
			std::runtime_error("width == 0 || height == 0");
			return nullptr;
		}
		uint32_t  mip_levels = floor(log2(std::max(width, height))) + 1;
		auto      find_sampler = m_mipmap_sampler_map.find(mip_levels);
		if (find_sampler != m_mipmap_sampler_map.end())
		{
			return find_sampler->second;
		}
		else
		{
			VkSampler sampler = VulkanUtil::getOrCreateMipmapSampler(m_physical_device, m_device, width, height);
			m_mipmap_sampler_map.insert(std::make_pair(mip_levels, sampler));

			return sampler;
		}
	}

	//**********************************深度图********************************************//
	DepthImageDesc VulkanRHI::getDepthImageInfo()
	{
		DepthImageDesc desc;
		desc.depth_image_format = m_depth_image_format;
		desc.depth_image_view = m_depth_image_view;
		desc.depth_image = m_depth_image;
		return desc;
	}
	
	VkFormat VulkanRHI::findDepthFormat(){
		return findSupportedFormat({ VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },VK_IMAGE_TILING_OPTIMAL,VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
	}

	VkFormat VulkanRHI::findSupportedFormat(const std::vector<VkFormat>& candidates,VkImageTiling tiling,VkFormatFeatureFlags features){
		for (VkFormat format : candidates)//检查每个格式的属性是否与指定的图像平铺和格式特性兼容
		{
			VkFormatProperties props;
			vkGetPhysicalDeviceFormatProperties(m_physical_device, format, &props);//获取格式属性

			//如果图形平铺和对应特性都与要求相同，就返回格式
			if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features)
			{
				return format;
			}
			else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features)
			{
				return format;
			}
		}
		std::cout << "未发现支持格式！" << std::endl;
		return VkFormat();
	}

	void VulkanRHI::createDepthResource() {
		//找合适的深度图像格式并保存
		m_depth_image_format = findDepthFormat();
		VulkanUtil::createImage(m_physical_device,m_device,m_swapchain_extent.width,m_swapchain_extent.height,m_depth_image_format,VK_IMAGE_TILING_OPTIMAL,VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT | VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT |VK_IMAGE_USAGE_TRANSFER_SRC_BIT,VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,m_depth_image,m_depth_image_memory,0,1,1);
		m_depth_image_view = VulkanUtil::createImageView(m_device, m_depth_image, m_depth_image_format, VK_IMAGE_ASPECT_DEPTH_BIT, VK_IMAGE_VIEW_TYPE_2D, 1, 1);
		//转换成适合深度附着使用
		VulkanUtil::transitionImageLayout(this, m_depth_image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,1,1,VK_IMAGE_ASPECT_DEPTH_BIT);
	}

	//**********************************vma内存分配器********************************************//

	void VulkanRHI::createAssetAllocator()
	{
		//设置自动调取Vulkan函数
		VmaVulkanFunctions vulkanFunctions = {};
		vulkanFunctions.vkGetInstanceProcAddr = &vkGetInstanceProcAddr;
		vulkanFunctions.vkGetDeviceProcAddr = &vkGetDeviceProcAddr;

		VmaAllocatorCreateInfo allocator_createInfo = {};
		allocator_createInfo.vulkanApiVersion = VK_API_VERSION_1_0;
		allocator_createInfo.physicalDevice = m_physical_device;
		allocator_createInfo.device = m_device;
		allocator_createInfo.instance = m_instance;
		allocator_createInfo.pVulkanFunctions = &vulkanFunctions;

		vmaCreateAllocator(&allocator_createInfo, &m_assets_allocator);
	}

	VkResult VulkanRHI::createBufferVMA(VmaAllocator allocator, const VkBufferCreateInfo* pBufferCreateInfo, const VmaAllocationCreateInfo* pAllocationCreateInfo, VkBuffer* pBuffer, VmaAllocation* pAllocation, VmaAllocationInfo* pAllocationInfo) {
		VkResult result = vmaCreateBuffer(allocator,pBufferCreateInfo,pAllocationCreateInfo,pBuffer,pAllocation,pAllocationInfo);
		return result;
	}

	VkResult VulkanRHI::createBufferWithAlignmentVMA(VmaAllocator allocator, const VkBufferCreateInfo* pBufferCreateInfo, const VmaAllocationCreateInfo* pAllocationCreateInfo, VkDeviceSize minAlignment, VkBuffer* pBuffer, VmaAllocation* pAllocation, VmaAllocationInfo* pAllocationInfo) {
		VkResult result = vmaCreateBufferWithAlignment(allocator, pBufferCreateInfo, pAllocationCreateInfo, minAlignment, pBuffer, pAllocation, pAllocationInfo);
		return result;
	}

	void VulkanRHI::clear() {

		/*
		vkDestroySemaphore(device, renderFinishedSemaphore, nullptr);
		vkDestroySemaphore(device, imageAvailableSemaphore, nullptr);

		vkDestroyCommandPool(m_device, m_commandPool_rhi, nullptr);
		for (auto commandPool : m_command_pools){
			vkDestroyCommandPool(m_device, commandPool, nullptr);
		}

		for (auto imageview : m_swapchain_imageviews){
			vkDestroyImageView(m_device, imageview, nullptr);
		}
		vkDestroySwapchainKHR(m_device, m_swapchain, nullptr);

		vkDestroyDevice(m_device, nullptr);

		vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
		vkDestroyInstance(m_instance, nullptr);
		*/

		//清除校验层
		if (m_enable_validation_layers) {
			DestroyDebugUtilsMessengerEXT(m_instance, m_callback, nullptr);
		}
		
	}

	
}