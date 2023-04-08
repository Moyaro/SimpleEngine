#include <filesystem>
#include <iostream>

#include "../../runtime/engine.h"
#include "../include/editor.h"
int main(int argc, char** argv) {
	std::filesystem::path executable_path(argv[0]);//可执行文件的路径
	std::filesystem::path config_file_path = executable_path.parent_path() / "EngineEditor.ini";//编辑器配置文件

	//启动引擎
	SimpleEngine::Engine* engine = new SimpleEngine::Engine();
	engine->startEngine(config_file_path.generic_string());

	//启动编辑器
	SimpleEngine::Editor* editor = new SimpleEngine::Editor();
	editor->init(engine);
	editor->run();

	editor->clear();
	engine->closeEngine();
	return 0;
}