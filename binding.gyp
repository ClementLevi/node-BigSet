{
  "targets": [
    {
      "target_name": "BigSet",
      "sources": [ "src/BigSet.cpp" ],
      "include_dirs": [
        "<!@(node -e \"require('node-addon-api').include\")",
        "node_modules/node-addon-api"
      ],
      "cflags": [ "/EHsc","-fno-exceptions" ],
      "defines": [ "NAPI_CPP_EXCEPTIONS" ]
    }
  ]
}
