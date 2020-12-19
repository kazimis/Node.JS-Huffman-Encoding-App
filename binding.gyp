{
    "targets": [{
        "target_name": "testaddon",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "cppsrc/main.cpp",
            "cppsrc/Samples/BitStream.cpp",
            "cppsrc/Samples/FrequencyTable.cpp",
            "cppsrc/Samples/HuffmanTree.cpp",
            "cppsrc/PriorityQueue.h",
            "cppsrc/Samples/Node.h",
            "cppsrc/Samples/p_qNode.h",
            "cppsrc/Samples/MyClass.cpp"
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}
