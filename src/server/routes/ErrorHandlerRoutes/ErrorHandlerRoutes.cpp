#include "ErrorHandlerRoutes.h"

namespace routes
{

  void ErrorHandlerRoutes::ResourceError(const int, const exception &e, const shared_ptr<Session> session)
  {
    json error;
    error["error"] = e.what();
    string responseData = error.dump();
    const multimap<string, string> headers{
        {"Content-Length", to_string(responseData.length())},
        {"Content-Type", "application/json"},
        {"Connection", "close"}};

    session->close(400, responseData, headers);
  }

  void ErrorHandlerRoutes::ServiceError(const int, const exception &e, const shared_ptr<Session> session)
  {
    json error;
    error["error"] = e.what();
    string responseData = error.dump();
    const multimap<string, string> headers{
        {"Content-Length", to_string(responseData.length())},
        {"Content-Type", "application/json"},
        {"Connection", "close"}};

    session->close(500, responseData, headers);
  }

} // namespace routes