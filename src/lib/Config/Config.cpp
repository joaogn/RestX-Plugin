#include "Config.h"

namespace configure
{
  Config::Config()
  {

    char configFile[512];

    string configPath = fs::current_path();

    configPath = configPath + "/Resources/plugins/RestXPlugin/config.json";

    ifstream configStream(configPath.c_str());

    string configStr;
    getline(configStream, configStr, (char)configStream.eof());

    if (!configStream)
    {
      config = std::make_shared<json>(json::parse("{\"port\": 1991}"));
    }
    else
    {
      config = std::make_shared<json>(json::parse(configStr.c_str()));
    }
  }

  int Config::getPort()
  {
    json conf = *config;
    return conf["port"].get<int>();
  }

} // namespace configure