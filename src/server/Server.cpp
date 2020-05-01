#include "Server.h"

namespace server
{

  void Server::StartServer()
  try
  {

    auto getDataRef = make_shared<Resource>();
    getDataRef->set_path("/api/datarefs");
    getDataRef->set_method_handler("GET", dataRefRoutes.Get);

    auto postDataRef = make_shared<Resource>();
    postDataRef->set_path("/api/datarefs/write");
    postDataRef->set_method_handler("POST", dataRefRoutes.Post);

    auto settings = make_shared<Settings>();
    settings->set_port(1984);
    settings->set_default_header("Access-Control-Allow-Origin", "*");
    settings->set_default_header("Connection", "close");

    service.publish(getDataRef);
    service.publish(postDataRef);
    service.start(settings);
  }
  catch (const std::exception &e)
  {
  }

  void Server::StopServer()
  {
  }
} // namespace server