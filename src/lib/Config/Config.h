#ifndef LIBCONFIG_H
#define LIBCONFIG_H

#include "XPLM/XPLMUtilities.h"
#include <string>
#include <memory>
#include <nlohmann/json.hpp>
#include <cstdlib>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>

using namespace std;
using json = nlohmann::json;
namespace fs = std::__fs::filesystem;

namespace configure
{

  class Config
  {
  public:
    Config();
    int getPort();

  private:
    std::shared_ptr<nlohmann::json> config;
  };
} // namespace configure

#endif /* SRC_ENVIRONMENT_CONFIG_H_ */