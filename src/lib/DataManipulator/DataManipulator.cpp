// DataManipulator.cpp

#include "DataManipulator.h"

namespace manipulator
{
  uint64_t GetDataRefReference(string data_ref)
  {
    XPLMRef gDataRef = XPLMFindDataRef(data_ref.c_str());
    return (uint64_t)gDataRef;
  }

  bool GetDataRefWitrable(uint64_t ref)
  {
    return XPLMCanWriteDataRef((XPLMDataRef)ref);
  }

  bool GetDataRefGood(uint64_t ref)
  {
    return XPLMIsDataRefGood((XPLMDataRef)ref);
  }

  json GetDataRefValue(uint64_t ref)
  {
    XPLMRef gDataRef = (XPLMDataRef)ref;
    XPLMDataTypeID gDataRefType = XPLMGetDataRefTypes(gDataRef);

    json response;
    if (gDataRefType == xplmType_Int)
    {
      response["value"] = ReadDataRefInt(gDataRef);
    }
    else if (gDataRefType == xplmType_Float)
    {
      response["value"] = ReadDataRefFloat(gDataRef);
    }
    else if (gDataRefType == xplmType_Double)
    {
      response["value"] = ReadDataRefDouble(gDataRef);
    }
    else if (gDataRefType == xplmType_FloatArray)
    {
      response["value"] = ReadDataRefFloatArray(gDataRef);
    }
    else if (gDataRefType == xplmType_IntArray)
    {
      response["value"] = ReadDataRefIntArray(gDataRef);
    }
    else if (gDataRefType == xplmType_Data)
    {
      response["value"] = ReadDataRefByteArray(gDataRef);
    }
    else
    {

      int sizeFLT = XPLMGetDatavf(gDataRef, nullptr, 0, 0);
      if (sizeFLT > 0)
      {
        response["value"] = ReadDataRefFloatArray(gDataRef);
      }
      else
      {
        int sizeBTY = XPLMGetDatab(gDataRef, nullptr, 0, 0);
        if (sizeBTY > 0)
        {
          response["value"] = ReadDataRefByteArray(gDataRef);
        }
        else
        {
          response["value"] = ReadDataRefDouble(gDataRef);
        }
      }
    }
    return response;
  }

  json SetDataRefValue(uint64_t ref);

  int ReadDataRefInt(XPLMRef gDataRef)
  {
    return XPLMGetDatai(gDataRef);
  }

  float ReadDataRefFloat(XPLMRef gDataRef)
  {
    return XPLMGetDataf(gDataRef);
  }

  double ReadDataRefDouble(XPLMRef gDataRef)
  {
    return XPLMGetDatad(gDataRef);
  }

  vector<int> ReadDataRefIntArray(XPLMRef gDataRef)
  {
    int size = XPLMGetDatavi(gDataRef, nullptr, 0, 0);
    int value[size];
    XPLMGetDatavi(gDataRef, value, 0, size);
    int n = sizeof(value) / sizeof(value[0]);
    vector<int> vectorValue(value, value + n);
    return vectorValue;
  }

  vector<float> ReadDataRefFloatArray(XPLMRef gDataRef)
  {
    int size = XPLMGetDatavf(gDataRef, nullptr, 0, 0);
    float value[size];
    XPLMGetDatavf(gDataRef, value, 0, size);
    int n = sizeof(value) / sizeof(value[0]);
    std::vector<float> vectorValue(value, value + n);
    return vectorValue;
  }

  string ReadDataRefByteArray(XPLMRef gDataRef)
  {
    int size = XPLMGetDatab(gDataRef, nullptr, 0, 0);
    uint8_t value[size];
    XPLMGetDatab(gDataRef, value, 0, size);
    int n = sizeof(value) / sizeof(value[0]);
    string strValue((char *)value);
    return strValue;
  }

  void WriteDataRefInt(uint64_t ref, json newValue) {}

  void WriteDataRefFloat(uint64_t ref, json newValue) {}

  void WriteDataRefDouble(uint64_t ref, json newValue) {}

  void WriteDataRefIntArray(uint64_t ref, json newValue) {}

  void WriteDataRefFloatArray(uint64_t ref, json newValue) {}

  void WriteDataRefByteArray(uint64_t ref, json newValue) {}

} // namespace manipulator