#include "DataRefRoutes.h"

namespace routes
{
  void DataRefRoutes::Post(const shared_ptr<Session> session)
  {

    const auto request = session->get_request();

    int content_length = request->get_header("Content-Length", 0);

    session->fetch(content_length, [](const shared_ptr<Session> session, const Bytes &body) {
      session->close(OK, "Hello, World!", {{"Content-Length", "13"}});
    });
  }

  void DataRefRoutes::Get(const shared_ptr<Session> session)
  {
    uint64_t ref = 123456789;
    json jsonDataRefs = GetDataRefValue(ref);

    string responseData = jsonDataRefs.dump();
    const multimap<string, string> headers{
        {"Content-Length", to_string(responseData.length())},
        {"Content-Type", "application/json"},
        {"Connection", "close"}};

    session->close(OK, responseData, headers);
  }
} // namespace routes