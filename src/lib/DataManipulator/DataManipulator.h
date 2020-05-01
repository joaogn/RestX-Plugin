#include <nlohmann/json.hpp>
#include <cstdlib>

using namespace std;
using json = nlohmann::json;

namespace manipulator
{

  uint64_t GetDataRefReference(string data_ref);

  json GetDataRefValue(uint64_t ref);

  json GetDataRefWitrable(uint64_t ref);

  json GetDataRefGood(uint64_t ref);

  json SetDataRefValue(uint64_t ref);

  int ReadDataRefInt(uint64_t ref);

  float ReadDataRefFloat(uint64_t ref);

  double ReadDataRefDouble(uint64_t ref);

  vector<int> ReadDataRefIntArray(uint64_t ref);

  vector<float> ReadDataRefFloatArray(uint64_t ref);

  vector<uint8_t> ReadDataRefByteArray(uint64_t ref);

  void WriteDataRefInt(uint64_t ref, json newValue);

  void WriteDataRefFloat(uint64_t ref, json newValue);

  void WriteDataRefDouble(uint64_t ref, json newValue);

  void WriteDataRefIntArray(uint64_t ref, json newValue);

  void WriteDataRefFloatArray(uint64_t ref, json newValue);

  void WriteDataRefByteArray(uint64_t ref, json newValue);

} // namespace manipulator
