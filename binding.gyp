{
  "targets": [
    {
      "target_name": "bigset",
      "sources": [ "src/BigSet.cpp" ],
      "include_dirs": [
        "<!(node -e \"require('node-addon-api').include\")",
        "node_modules/node-addon-api"
      ],
      "cflags": [
        "/EHsc",                  #启用 C++ 异常处理
        "-DNAPI_CPP_EXCEPTIONS"   # 定义 NAPI_CPP_EXCEPTIONS 以启用 N-API 的 C++ 异常支持
      ],
      "cflags!": [               # 禁用默认的异常处理选项
        "-fno-exceptions"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}
