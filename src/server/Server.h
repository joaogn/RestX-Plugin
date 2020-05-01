
#ifndef LIBSERVER_H
#define LIBSERVER_H

#include <nlohmann/json.hpp>
#include <cstdlib>
#include <restbed>
#include "src/server/routes/DataRefRoutes/DataRefRoutes.h"

using namespace routes;
using namespace restbed;

namespace server
{
  class Server
  {
    Service service;
    DataRefRoutes dataRefRoutes;

  public:
    void StartServer();
    void StopServer();
  };

} // namespace server

#endif