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
		//���ô���
		m_window = init_info.windowSystem->getWindow();
		std::array<int, 2> window_size = init_info.windowSystem->getWindowSize();

		//�����ӿںͲü���ʼֵ
		m_viewport = { 0.0f,0.0f,(float)window_size[0],(float)window_size[1],0.0f,1.0f };
		m_scissor = { {0,0},{(uint32_t)window_size[0],(uint32_t)window_size[1]} };

		//���ݻ����жϿ�����debug����
#ifndef NDEBUG
		m_enable_debug_utils_label = true;
		m_enable_validation_layers = true;
#else
		m_enable_debug_utils_label = false;
		m_enable_validation_layers = false;
#endif // !NDEBUG

		//��ʼ��Vulkan
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


	//**********************************����ʵ��********************************************//

	//��ȡ������չ��У�����չ
	std::vector<const char*> VulkanRHI::getRequiredExtensions() {
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);//��ȡ������Ҫ����չ
		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (m_enable_validation_layers || m_enable_debug_utils_label)
		{
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);//���ûص��������ܵ�����Ϣ
		}

		return extensions;
	}

	void VulkanRHI::createInstance() {

		if (m_enable_validation_layers && !checkValidationLayerSupport()) {
			throw std::runtime_error("У�������ʧ�ܣ�");
		}

		//Ӧ�ó�����Ϣ
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "engine_renderer";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "SimpleEngine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		//������Ϣ������Ӧ�ó�����Ϣ��ȫ����չ��У���
		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		auto extensions = getRequiredExtensions();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();


		//����У���
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


		//����ʵ��
		if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS) {
			throw std::runtime_error("ʵ������ʧ�ܣ�");
		}
	}



	//**********************************����У���********************************************//

	//�������п���У���
	bool VulkanRHI::checkValidationLayerSupport() {
		//�ҳ����п��õĲ�
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
		std::vector<VkLayerProperties> avaliableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, avaliableLayers.data());

		//���Ҫʹ�õ�У����б��Ƿ񶼿���
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

	//���ز���ֵ����ʾAPI�����Ƿ��ж�
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,//��Ϣ�ȼ�
		VkDebugUtilsMessageTypeFlagsEXT messageType,//��Ϣ����
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData) {//���ûص�ʱ���ݵ�����
		std::cerr << "У��㣺" << pCallbackData->pMessage << std::endl;
		return VK_FALSE;
	}

	//�����ص��Ĵ�����
	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
		const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkDebugUtilsMessengerEXT* pCallback) {
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"); //���غ�������Ϊ������չ���������ᱻVulkan�����
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pCallback);
		}
		else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void VulkanRHI::setupDebugCallback() {
		if (m_enable_validation_layers) {
			//�ص���Ϣ
			VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
			populateDebugMessengerCreateInfo(createInfo);

			if (CreateDebugUtilsMessengerEXT(m_instance, &createInfo, nullptr, &m_callback) != VK_SUCCESS) {
				throw std::runtime_error("����debug�ص�����ʧ�ܣ�");
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

	//���ٻص��Ĵ�����
	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT callback, VkAllocationCallbacks* pAllocator) {
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (func != nullptr) {
			func(instance, callback, pAllocator);
		}
	}

	//У��㴴����Ϣ
	void VulkanRHI::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
	{
		createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;//��Ϣ���𣺾��棬����
		createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;//��Ϣ���ͣ�Ӱ��Vulkan���ܣ�Υ���淶
		createInfo.pfnUserCallback = debugCallback;//�ص�
	}

	//**********************************���ô��ڱ���********************************************//
	void VulkanRHI::createSurface() {
		if (glfwCreateWindowSurface(m_instance, m_window, nullptr, &m_surface) != VK_SUCCESS) {
			throw std::runtime_error("�������ڱ���ʧ�ܣ�");
		}
	}

	//**********************************ѡ�������豸********************************************//
	bool VulkanRHI::isDeviceSuitable(VkPhysicalDevice device) {
		//��ȡ�豸�Ķ����������б�
		QueueFamilyIndices indices = findQueueFamilies(device);

		//��齻�����Ƿ���������
		bool extensionsSupported = checkDeviceExtensionSupport(device);
		bool swapChainAdequate = false;
		if (extensionsSupported) {
			SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();//����֧��һ��ͼ���ʽ�ͳ���ģʽ
		}

		//����Ƿ�֧�ָ������Թ���
		VkPhysicalDeviceFeatures support_features;//����ѹ����64λ�������Ͷ���ͼ��Ⱦ�ȿ�ѡ���ܵ�֧��
		vkGetPhysicalDeviceFeatures(device, &support_features);

		return indices.isComplete() && extensionsSupported && swapChainAdequate && support_features.samplerAnisotropy;
	}

	int VulkanRHI::rateDeviceSuitability(VkPhysicalDevice device) {
		VkPhysicalDeviceProperties deviceProperties;//�������豸����
		vkGetPhysicalDeviceProperties(device, &deviceProperties);

		//�����豸���Դ��
		int score = 0;
		if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {//�Կ�֧�ּ�����ɫ��
			score += 1000;
		}
		else if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) {
			score += 100;
		}
		return score;
	}

	QueueFamilyIndices VulkanRHI::findQueueFamilies(VkPhysicalDevice device) {
		QueueFamilyIndices indices;

		//��ȡ�豸֧�ֵĶ�������Ϣ
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		uint32_t i = 0;
		for (const auto& queueFamily : queueFamilies) {
			if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {//����Ƿ�֧��ͼ��ָ��
				indices.graphics_family = i;
			}
			if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT) {//����Ƿ�֧�ּ���ָ��
				indices.compute_family = i;
			}

			VkBool32 presentSupport = false;//����Ƿ�֧�ֳ���ָ��
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
		//��ȡ�����Կ��豸
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);
		if (deviceCount == 0) {
			throw std::runtime_error("û�п���GPU�豸��");
		}
		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());

		//�豸���
		std::multimap<int, VkPhysicalDevice> candidates;//�Զ�����map��Ĭ������
		for (const auto& device : devices) {
			int score = rateDeviceSuitability(device);
			candidates.insert(std::make_pair(score, device));
		}

		if (candidates.rbegin()->first > 0 && isDeviceSuitable(candidates.rbegin()->second)) {
			m_physical_device = candidates.rbegin()->second;
		}
		else {
			throw std::runtime_error("û�к��ʵ�GPU�豸��");
		}
	}

	//**********************************�����߼��豸********************************************//
	void VulkanRHI::createLogicalDevice() {
		m_queue_indices = findQueueFamilies(m_physical_device);//���ö���������Ϣ

		//�豸���д�����Ϣ*3��Ҫʹ�õĶ����������������������ȼ�
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> queueFamilies = { m_queue_indices.graphics_family.value(),m_queue_indices.present_family.value(),m_queue_indices.compute_family.value() };
		float queuePriority = 1.0f;
		for (uint32_t queueFamily : queueFamilies) {
			VkDeviceQueueCreateInfo queueCreateInfo = {};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;//Ӱ����������ĵ���
			queueCreateInfos.push_back(queueCreateInfo);
		}

		//���������豸������Ϣ
		VkPhysicalDeviceFeatures deviceFeatures = {};
		deviceFeatures.samplerAnisotropy = VK_TRUE;//���ø������Թ��ˡ��������������
		deviceFeatures.fragmentStoresAndAtomics = VK_TRUE;//����Ƭ����ɫ���е�ԭ�Ӳ����ʹ洢ͼ��
		deviceFeatures.independentBlend = VK_TRUE;//����ʹ�ò�ͬ�Ļ��������Ⱦ��ͬ����ɫ

		if (m_enable_point_light_shadow)
		{
			deviceFeatures.geometryShader = VK_TRUE;//��Դ��Ӱ��Ҫ������ɫ����������ӰͶ��
		}

		//�����߼��豸,ָ�������塢ʹ�����ԡ���չ
		VkDeviceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(m_device_extensions.size());
		createInfo.ppEnabledExtensionNames = m_device_extensions.data();
		createInfo.enabledLayerCount = 0;

		if (vkCreateDevice(m_physical_device, &createInfo, nullptr, &m_device) != VK_SUCCESS) {
			throw std::runtime_error("�����߼��豸ʧ�ܣ�");
		}

		//��ȡ�߼��豸�Ķ���
		vkGetDeviceQueue(m_device, m_queue_indices.graphics_family.value(), 0, &m_graphics_queue);
		vkGetDeviceQueue(m_device, m_queue_indices.present_family.value(), 0, &m_present_queue);
		vkGetDeviceQueue(m_device, m_queue_indices.compute_family.value(), 0, &m_compute_queue);
	}


	//**********************************����������********************************************//

	bool VulkanRHI::checkDeviceExtensionSupport(VkPhysicalDevice device) {
		//��ѯ�豸���п�����չ
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

		std::set<std::string> requiredExtensions(m_device_extensions.begin(), m_device_extensions.end());

		//�����Ҫ����չ�Ƿ�����ڿ�����չ��
		for (const auto& extension : availableExtensions) {
			requiredExtensions.erase(extension.extensionName);
		}
		return requiredExtensions.empty();
	}

	SwapChainSupportDetails VulkanRHI::querySwapChainSupport(VkPhysicalDevice device) {
		SwapChainSupportDetails details;
		//��ѯ������������
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_surface, &details.capabilities);
		//��ѯ����֧�ֵĸ�ʽ
		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, nullptr);
		if (formatCount != 0) {
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, details.formats.data());
		}
		//��ѯ֧�ֵĳ���ģʽ
		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, nullptr);
		if (presentModeCount != 0) {
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, details.presentModes.data());
		}

		return details;
	}

	//���ñ����ʽ����ɫ��ʽ����ɫ�ռ�
	VkSurfaceFormatKHR VulkanRHI::chooseSwapchainSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& available_surface_formats) {
		if (available_surface_formats.size() == 1 && available_surface_formats[0].format == VK_FORMAT_UNDEFINED) {//û��Ĭ�ϸ�ʽ
			return { VK_FORMAT_B8G8R8A8_UNORM,VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };//��ɫ��ʽ��RGB����ɫ�ռ䣻SRGB
		}
		for (const auto& available_surface_format : available_surface_formats) {
			if (available_surface_format.format == VK_FORMAT_B8G8R8A8_UNORM && available_surface_format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
				return available_surface_format;
			}
		}
		return available_surface_formats[0];
	}
	//���ó���ģʽ��ͼ����ʾ����Ļ������
	VkPresentModeKHR VulkanRHI::chooseSwapchainPresentMode(const std::vector<VkPresentModeKHR>& available_present_modes) {
		for (const auto& available_present_mode : available_present_modes) {
			if (available_present_mode == VK_PRESENT_MODE_MAILBOX_KHR)//������Ϊ���У�����ʱֱ���滻����ͼ��
				return available_present_mode;
		}
		return VK_PRESENT_MODE_FIFO_KHR;
	}
	//���ý�����Χ��ͼ��ֱ���
	VkExtent2D VulkanRHI::chooseSwapchainExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
		if (capabilities.currentExtent.width != UINT32_MAX) {//��uint_t���ֵ�������Զ��巶Χ
			return capabilities.currentExtent;
		}
		else {//�Զ��巶Χ������Ϊ֡�����С
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

		//������Сͼ�����=��������Сͼ�����+1��ʵ�����ػ���
		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {//����0ʱ������
			imageCount = swapChainSupport.capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = m_surface;
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;//ͼ���Σ�ͨ��1��VR�и�����
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;//��ͼ����еľ����������ͼ����ɫ����

		uint32_t queueFamilyIndices[] = { m_queue_indices.graphics_family.value(),m_queue_indices.present_family.value() };
		if (m_queue_indices.graphics_family != m_queue_indices.present_family) {
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;//ͼ����ڶ�������ʹ��
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;//ָ����������Ȩ�Ķ�����
		}
		else {
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;//һ��ͼͬʱֻ�ܱ�һ��������ӵ��
			createInfo.queueFamilyIndexCount = 0;
			createInfo.pQueueFamilyIndices = nullptr;
		}

		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;//�����б任
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;//����alpha�����������
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE; //���Դ����ڵ�ס��������ɫ
		createInfo.oldSwapchain = VK_NULL_HANDLE;//��ֹ����ʱ������ʧЧ

		if (vkCreateSwapchainKHR(m_device, &createInfo, nullptr, &m_swapchain) != VK_SUCCESS) {
			throw std::runtime_error("����������ʧ�ܣ�");
		}

		//��ȡ������ͼ��
		vkGetSwapchainImagesKHR(m_device, m_swapchain, &imageCount, nullptr);
		m_swapchain_images.resize(imageCount);
		vkGetSwapchainImagesKHR(m_device, m_swapchain, &imageCount, m_swapchain_images.data());

		//�洢��������ʽ�ͷ�Χ
		m_swapchain_image_format = surfaceFormat.format;
		m_swapchain_extent = extent;

		//���òü�����
		m_scissor = { {0, 0}, {m_swapchain_extent.width, m_swapchain_extent.height} };
	}

	//��������Ϣ����Χ��ͼ����ͼ��ͼ���ʽ���ü����ӿ�
	SwapChainDesc VulkanRHI::getSwapchainInfo() {
		SwapChainDesc desc = {};
		desc.extent = m_swapchain_extent;
		desc.imageViews = m_swapchain_imageviews;
		desc.image_format = m_swapchain_image_format;
		desc.scissor = &m_scissor;
		desc.viewport = &m_viewport;
		return desc;
	}

	//��̬�����ӿڡ��ü�
	void VulkanRHI::cmdSetViewport(uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports) {
		vkCmdSetViewport(m_current_command_buffer, firstViewport, viewportCount, pViewports);
	}
	void VulkanRHI::cmdSetScissor(uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors) {
		vkCmdSetScissor(m_current_command_buffer, firstScissor, scissorCount, pScissors);
	}
	//**********************************�ؽ�������********************************************//
	void VulkanRHI::recreateSwapchain() {
		//������С��ʱ��֡�����СΪ0���ȴ��������¿ɼ�
		int width = 0;
		int height = 0;
		glfwGetFramebufferSize(m_window, &width, &height);
		while (width == 0 || height == 0)
		{
			glfwGetFramebufferSize(m_window, &width, &height);
			glfwWaitEvents();
		}

		//�ȴ�����֡�����������豸���ڿ���״̬
		VkResult res_wait_for_fences = waitForFences(k_max_frames_in_flight, m_is_frame_in_flight_fences, VK_TRUE, UINT64_MAX);
		if (VK_SUCCESS != res_wait_for_fences)
		{
			throw std::runtime_error("�ȴ�դ���ź�ʧ�ܣ�");
			return;
		}

		//����ͼ����ͼ��ͼ�񡢽�����
		vkDestroyImageView(m_device, m_depth_image_view, nullptr);
		vkDestroyImage(m_device, m_depth_image, nullptr);
		vkFreeMemory(m_device, m_depth_image_memory, nullptr);

		for (auto imageview : m_swapchain_imageviews)
		{
			vkDestroyImageView(m_device, imageview, nullptr);
		}
		vkDestroySwapchainKHR(m_device, m_swapchain, nullptr);

		//��������������ͼ��֡����ͼ�����ͼ
		createSwapchain();
		createSwapchainImageViews();
		createDepthResource();
	}
	//**********************************����ͼ����ͼ********************************************//
	void VulkanRHI::createSwapchainImageViews() {
		m_swapchain_imageviews.resize(m_swapchain_images.size());
		for (size_t i = 0; i < m_swapchain_images.size(); i++) {
			//�������豸��������ͼ�񣬸�ʽ��ͼ��Ϊ��ȾĿ�꣬2D��������������
			m_swapchain_imageviews[i] = VulkanUtil::createImageView(m_device, m_swapchain_images[i], m_swapchain_image_format, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_VIEW_TYPE_2D, 1, 1);
			//VulkanUtil::transitionImageLayout(this, m_swapchain_images[i], VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, 1, 1, VK_IMAGE_ASPECT_COLOR_BIT);
		}
	}

	void VulkanRHI::createImageView(VkImage& image, VkFormat format, VkImageAspectFlags image_aspect_flags, VkImageViewType view_type, uint32_t layout_count, uint32_t miplevels, VkImageView& image_view) {
		image_view = VulkanUtil::createImageView(m_device, image, format, image_aspect_flags, view_type, layout_count, miplevels);
	}

	//**********************************����ͼ����Ⱦ����********************************************//

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

	//**********************************����֡����********************************************//
	VkResult VulkanRHI::createFramebuffer(const VkFramebufferCreateInfo* pCreateInfo, VkFramebuffer* pFramebuffer) {
		VkResult result = vkCreateFramebuffer(m_device, pCreateInfo, nullptr, pFramebuffer);
		return result;
	}

	void VulkanRHI::destroyFramebuffer(VkFramebuffer& framebuffer)
	{
		vkDestroyFramebuffer(m_device, framebuffer, nullptr);
	}

	//**********************************��������ء������********************************************//

	//ָ��ط���ָ��������
	void VulkanRHI::createCommandPool() {

		//����RHI��ָ��أ��ڴ洫��
		VkCommandPoolCreateInfo pool_info = {};
		pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		pool_info.pNext = NULL;
		pool_info.queueFamilyIndex = m_queue_indices.graphics_family.value();
		pool_info.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;//�����֡�������Ƶ�����ڼ�¼��ָ��

		if (vkCreateCommandPool(m_device, &pool_info, nullptr, &m_rhi_command_pool) != VK_SUCCESS) {
			throw std::runtime_error("����ָ���ʧ�ܣ�");
		}

		//������Ⱦ�õ�3��ָ���
		VkCommandPoolCreateInfo command_pool_info;
		command_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		command_pool_info.pNext = NULL;
		command_pool_info.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
		command_pool_info.queueFamilyIndex = m_queue_indices.graphics_family.value();

		for (uint32_t i = 0; i < k_max_frames_in_flight; ++i)
		{
			if (vkCreateCommandPool(m_device, &command_pool_info, nullptr, &m_command_pools[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("����ָ���ʧ�ܣ�");
			}
		}
	}

	void VulkanRHI::createCommandBuffers() {
		//һ��ָ��ط���һ��ָ���
		VkCommandBufferAllocateInfo alloc_info = {};
		alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;//�����ύ��������ִ�У����ܱ�����ָ������
		alloc_info.commandBufferCount = 1U;

		for (uint32_t i = 0; i < k_max_frames_in_flight; ++i)
		{
			alloc_info.commandPool = m_command_pools[i];
			if (vkAllocateCommandBuffers(m_device, &alloc_info, &m_command_buffers[i]) != VK_SUCCESS) {
				throw std::runtime_error("����ָ���ʧ�ܣ�");
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
			LOG_ERROR("���������ʧ�ܣ�");
		}
	}

	//**********************************�����ݴ滺��********************************************//
	VkCommandBuffer& VulkanRHI::beginSingleTimeCommands() {
		//���������
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = m_rhi_command_pool;
		allocInfo.commandBufferCount = 1;

		VkCommandBuffer rhi_command_buffer;
		vkAllocateCommandBuffers(m_device, &allocInfo, &rhi_command_buffer);

		//��ʼָ���
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;//ֻʹ��һ��

		beginCommandBuffer(rhi_command_buffer, &beginInfo);

		return rhi_command_buffer;
	}
	void VulkanRHI::endSingleTimeCommands(VkCommandBuffer& command_buffer) {
		//���������
		endCommandBuffer(command_buffer);

		//�ύ������
		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &command_buffer;

		vkQueueSubmit(m_graphics_queue, 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(m_graphics_queue);//�ȴ��������

		//�ͷ������
		vkFreeCommandBuffers(m_device, m_rhi_command_pool, 1, &command_buffer);
	}

	void VulkanRHI::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize srcOffset, VkDeviceSize dstOffset, VkDeviceSize size){
		VulkanUtil::copyBuffer(this, srcBuffer, dstBuffer, srcOffset, dstOffset, size);
	}

	void VulkanRHI::destroyBuffer(VkBuffer& buffer) {
		vkDestroyBuffer(m_device, buffer, nullptr);
	}

	//**********************************��¼ָ�ָ���********************************************//

	VkResult VulkanRHI::beginCommandBuffer(VkCommandBuffer& commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo) {
		//ָ��ָ���ʹ��ϸ��
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

	//**********************************�����ź���********************************************//

	void VulkanRHI::createSyncPrimitives()
	{
		//�ź�����դ���Ĵ�����Ϣ
		VkSemaphoreCreateInfo semaphore_create_info{};
		semaphore_create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fence_create_info{};
		fence_create_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fence_create_info.flags = VK_FENCE_CREATE_SIGNALED_BIT; //��ʼ��Ϊ�ѷ����ź�

		for (uint32_t i = 0; i < k_max_frames_in_flight; i++)
		{
			if (vkCreateSemaphore(m_device, &semaphore_create_info, nullptr, &m_image_available_for_render_semaphores[i]) != VK_SUCCESS ||
				vkCreateSemaphore(m_device, &semaphore_create_info, nullptr, &m_image_finished_for_presentation_semaphores[i]) != VK_SUCCESS ||
				vkCreateFence(m_device, &fence_create_info, nullptr, &m_is_frame_in_flight_fences[i]) != VK_SUCCESS){
				throw std::runtime_error("ͬ���źŴ���ʧ�ܣ�");
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
			throw std::runtime_error("�ȴ�դ���ź�ʧ��");
		}
	}

	//**********************************��Ⱦͨ��********************************************//

	bool VulkanRHI::prepareBeforePass(std::function<void()> passUpdateAfterRecreateSwapchain) {

		//�ӽ�������ȡͼ�� �������߼��豸������������ʱʱ�䣬ͼ�����ʱ��֪ͨ���󣨿�ͬʱָ��դ�����ź�������������ý�����ͼ������
		VkResult acquire_image_result = vkAcquireNextImageKHR(m_device,m_swapchain,UINT64_MAX,m_image_available_for_render_semaphores[m_current_frame_index],VK_NULL_HANDLE,&m_current_swapchain_image_index);

		if (VK_ERROR_OUT_OF_DATE_KHR == acquire_image_result)//����������ʹ�ã�һ���Ǵ��ڸı��
		{
			recreateSwapchain();
			passUpdateAfterRecreateSwapchain();
			return true;
		}
		else if (VK_SUBOPTIMAL_KHR == acquire_image_result)//����������ʹ�ã����������Բ�ƥ��
		{
			recreateSwapchain();
			passUpdateAfterRecreateSwapchain();

			//�ύ����������Եȴ��ź�����ͼ���Կ���
			//�������ύ��Ϣ���ȴ����ź��������߽׶Σ�ָ���
			VkPipelineStageFlags wait_stages[] = { VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT };//�����н׶����ʱ��ִ��
			VkSubmitInfo submit_info = {};
			submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submit_info.waitSemaphoreCount = 1;
			submit_info.pWaitSemaphores = &m_image_available_for_render_semaphores[m_current_frame_index];//����ִ��ǰҪ�ȴ����ź���
			submit_info.pWaitDstStageMask = wait_stages;//�ȴ��Ĺ��߽׶�
			submit_info.commandBufferCount = 0;//�ύ��ָ���
			submit_info.pCommandBuffers = NULL;
			submit_info.signalSemaphoreCount = 0;
			submit_info.pSignalSemaphores = NULL;

			VkResult res_reset_fences = resetFences(1, &m_is_frame_in_flight_fences[m_current_frame_index]);
			if (VK_SUCCESS != res_reset_fences)
			{
				throw std::runtime_error("����դ��ʧ�ܣ�");
			}

			VkResult res_queue_submit = vkQueueSubmit(m_graphics_queue, 1, &submit_info, m_is_frame_in_flight_fences[m_current_frame_index]);//ָ���ִ�н���ʱ�����ź�
			if (VK_SUCCESS != res_queue_submit)
			{
				throw std::runtime_error("�������ύ��Ϣʧ�ܣ�");
			}
			m_current_frame_index = (m_current_frame_index + 1) % k_max_frames_in_flight;//�е���һ֡
			return true;
		}
		else
		{
			if (VK_SUCCESS != acquire_image_result)
			{
				throw std::runtime_error("��ȡͼ��ʧ�ܣ�");
			}
		}

		// ��ʼ�����
		VkCommandBufferBeginInfo command_buffer_begin_info{};
		command_buffer_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		command_buffer_begin_info.flags = 0;
		command_buffer_begin_info.pInheritanceInfo = nullptr;

		VkResult res_begin_command_buffer = beginCommandBuffer(m_command_buffers[m_current_frame_index], &command_buffer_begin_info);

		if (VK_SUCCESS != res_begin_command_buffer)
		{
			throw std::runtime_error("���������ʧ�ܣ�");
			return false;
		}
		return false;
	}
	void VulkanRHI::submitRendering(std::function<void()> passUpdateAfterRecreateSwapchain) {
		//��������¼��
		VkResult res_end_command_buffer = endCommandBuffer(m_command_buffers[m_current_frame_index]);
		if (VK_SUCCESS != res_end_command_buffer)
		{
			throw std::runtime_error("���������ʧ�ܣ�");
		}

		VkSemaphore semaphores[1] = { m_image_finished_for_presentation_semaphores[m_current_frame_index] };

		//�ύ�����
		VkPipelineStageFlags wait_stages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		VkSubmitInfo submit_info = {};
		submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submit_info.waitSemaphoreCount = 1;
		submit_info.pWaitSemaphores = &m_image_available_for_render_semaphores[m_current_frame_index];//ͼ�������Ⱦ
		submit_info.pWaitDstStageMask = wait_stages;
		submit_info.commandBufferCount = 1;
		submit_info.pCommandBuffers = &m_command_buffers[m_current_frame_index];
		submit_info.signalSemaphoreCount = 1;//ָ���ִ�н���
		submit_info.pSignalSemaphores = semaphores;

		VkResult res_reset_fences = resetFences(1, &m_is_frame_in_flight_fences[m_current_frame_index]);
		if (VK_SUCCESS != res_reset_fences){
			throw std::runtime_error("����դ��ʧ�ܣ�");
			return;
		}
		VkResult res_queue_submit = vkQueueSubmit(m_graphics_queue, 1, &submit_info, m_is_frame_in_flight_fences[m_current_frame_index]);

		if (VK_SUCCESS != res_queue_submit){
			throw std::runtime_error("�������ύ��Ϣʧ�ܣ�");
			return;
		}

		//��Ⱦ��ͼ�񷵻ظ�������
		VkPresentInfoKHR present_info = {};
		present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		present_info.waitSemaphoreCount = 1;
		present_info.pWaitSemaphores = &m_image_finished_for_presentation_semaphores[m_current_frame_index];
		present_info.swapchainCount = 1;//���ڳ���ͼ��Ľ�����
		present_info.pSwapchains = &m_swapchain;
		present_info.pImageIndices = &m_current_swapchain_image_index;//Ҫ����ͼ�������

		VkResult present_result = vkQueuePresentKHR(m_present_queue, &present_info);
		if (VK_ERROR_OUT_OF_DATE_KHR == present_result || VK_SUBOPTIMAL_KHR == present_result)//���ڴ�С�ı�/�����ʽ��ƥ�䣬�ؽ�������
		{
			recreateSwapchain();
			passUpdateAfterRecreateSwapchain();
		}
		else
		{
			if (VK_SUCCESS != present_result){
				throw std::runtime_error("����ͼ��ʧ�ܣ�");
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
	//**********************************�����ڴ�********************************************//

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


	//**********************************����������********************************************//

	VkResult VulkanRHI::createDescriptorSetLayout(const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayout* pSetLayout) {
		VkResult result = vkCreateDescriptorSetLayout(m_device, pCreateInfo, nullptr, pSetLayout);
		return result;
	}

	void VulkanRHI::createDescriptorPool() {
		//�������ش�С
		VkDescriptorPoolSize pool_sizes[7];
		pool_sizes[0].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
		pool_sizes[0].descriptorCount = 3 + 2 + 2 + 2 + 1 + 1 + 3 + 3;
		pool_sizes[1].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		pool_sizes[1].descriptorCount = 1 + 1 + 1 * m_max_vertex_blending_mesh_count;
		pool_sizes[2].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;//��ͨ������
		pool_sizes[2].descriptorCount = 1 * m_max_material_count;
		pool_sizes[3].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;//���ͼ�������������
		pool_sizes[3].descriptorCount = 3 + 5 * m_max_material_count + 1 + 1; // ImGui_ImplVulkan_CreateDeviceObjects
		pool_sizes[4].type = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
		pool_sizes[4].descriptorCount = 4 + 1 + 1 + 2;
		pool_sizes[5].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;//��̬������
		pool_sizes[5].descriptorCount = 3;
		pool_sizes[6].type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
		pool_sizes[6].descriptorCount = 1;

		//�������ش�����Ϣ
		VkDescriptorPoolCreateInfo pool_info{};
		pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		pool_info.poolSizeCount = sizeof(pool_sizes) / sizeof(pool_sizes[0]);//��������������
		pool_info.pPoolSizes = pool_sizes;
		pool_info.maxSets = 1 + 1 + 1 + m_max_material_count + m_max_vertex_blending_mesh_count + 1 + 1; //�ɷ������������������� +skybox + axis descriptor set
		pool_info.flags = 0U;

		if (vkCreateDescriptorPool(m_device, &pool_info, nullptr, &m_descriptor_pool) != VK_SUCCESS)
		{
			throw std::runtime_error("������������ʧ�ܣ�");
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


	//**********************************ͼ������********************************************//
	//����ͼ��+�ڴ��
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
	//**********************************������********************************************//

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

	//**********************************���ͼ********************************************//
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
		for (VkFormat format : candidates)//���ÿ����ʽ�������Ƿ���ָ����ͼ��ƽ�̺͸�ʽ���Լ���
		{
			VkFormatProperties props;
			vkGetPhysicalDeviceFormatProperties(m_physical_device, format, &props);//��ȡ��ʽ����

			//���ͼ��ƽ�̺Ͷ�Ӧ���Զ���Ҫ����ͬ���ͷ��ظ�ʽ
			if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features)
			{
				return format;
			}
			else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features)
			{
				return format;
			}
		}
		std::cout << "δ����֧�ָ�ʽ��" << std::endl;
		return VkFormat();
	}

	void VulkanRHI::createDepthResource() {
		//�Һ��ʵ����ͼ���ʽ������
		m_depth_image_format = findDepthFormat();
		VulkanUtil::createImage(m_physical_device,m_device,m_swapchain_extent.width,m_swapchain_extent.height,m_depth_image_format,VK_IMAGE_TILING_OPTIMAL,VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT | VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT |VK_IMAGE_USAGE_TRANSFER_SRC_BIT,VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,m_depth_image,m_depth_image_memory,0,1,1);
		m_depth_image_view = VulkanUtil::createImageView(m_device, m_depth_image, m_depth_image_format, VK_IMAGE_ASPECT_DEPTH_BIT, VK_IMAGE_VIEW_TYPE_2D, 1, 1);
		//ת�����ʺ���ȸ���ʹ��
		VulkanUtil::transitionImageLayout(this, m_depth_image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,1,1,VK_IMAGE_ASPECT_DEPTH_BIT);
	}

	//**********************************vma�ڴ������********************************************//

	void VulkanRHI::createAssetAllocator()
	{
		//�����Զ���ȡVulkan����
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

		//���У���
		if (m_enable_validation_layers) {
			DestroyDebugUtilsMessengerEXT(m_instance, m_callback, nullptr);
		}
		
	}

	
}