#include <filesystem>
#include <iostream>

#include "../../runtime/engine.h"
#include "../include/editor.h"
int main(int argc, char** argv) {
	std::filesystem::path executable_path(argv[0]);//��ִ���ļ���·��
	std::filesystem::path config_file_path = executable_path.parent_path() / "EngineEditor.ini";//�༭�������ļ�

	//��������
	SimpleEngine::Engine* engine = new SimpleEngine::Engine();
	engine->startEngine(config_file_path.generic_string());

	//�����༭��
	SimpleEngine::Editor* editor = new SimpleEngine::Editor();
	editor->init(engine);
	editor->run();

	editor->clear();
	engine->closeEngine();
	return 0;
}