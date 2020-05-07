#include "Server.h"

namespace server
{

  void Server::StartServer()
  {
    try
    {

      auto getDataRef = make_shared<Resource>();
      getDataRef->set_path("/api/datarefs");
      getDataRef->set_method_handler("GET", dataRefRoutes.Get);
      getDataRef->set_error_handler(errorHandlerRoutes.ResourceError);

      auto postDataRef = make_shared<Resource>();
      postDataRef->set_path("/api/datarefs/write");
      postDataRef->set_method_handler("POST", dataRefRoutes.Post);
      postDataRef->set_error_handler(errorHandlerRoutes.ResourceError);

      auto settings = make_shared<Settings>();
      settings->set_port(1984);
      settings->set_worker_limit(2);
      settings->set_default_header("Access-Control-Allow-Origin", "*");
      settings->set_default_header("Connection", "close");

      service.publish(getDataRef);
      service.publish(postDataRef);
      service.set_error_handler(errorHandlerRoutes.ServiceError);
      service.start(settings);
    }
    catch (const std::exception &e)
    {
    }
  }

  void Server::StopServer()
  {
    service.stop();
  }
} // namespace server