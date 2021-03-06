#include "lang.hpp"

nlohmann::json appJson;
std::vector<std::string> g_villagerDatabase;

void loadToVector(std::string path, std::vector<std::string> &vec) {
	char* line = NULL;
	size_t len = 0;
	vec.clear();

	FILE* in = fopen(path.c_str(), "r");
	if(in) {
		while(__getline(&line, &len, in) != -1) {
			if(line[strlen(line)-1] == '\n')	line[strlen(line)-1] = '\0';
			vec.push_back(line);
		}
		fclose(in);
	}
}

std::string Lang::get(const std::string &key) {
	if(!appJson.contains(key)) {
		return "MISSING: " + key;
	}
	return appJson.at(key).get_ref<const std::string&>();
}

const std::string langs[] = {"de", "en", "es", "fr", "it", "lt", "pt", "jp"};

void Lang::load(int lang) {
	// Load app strings
	FILE* file = fopen(("nitro:/lang/"+langs[lang]+"/app.json").c_str(), "rt");
	if(file) {
		appJson = nlohmann::json::parse(file, nullptr, false);
		fclose(file);
	}
}

void Lang::loadVillager(int lang) {
	loadToVector("nitro:/lang/"+langs[lang]+"/villager.txt", g_villagerDatabase);
}