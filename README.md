#BattleCore 工程说明
###机甲帝国二期工程
By 狄学长

---

## Introduction

这是机甲帝国 战斗部分逻辑的C++核心代码，他将被编译成.so (linux) / .lib or .dll (windows)， 供其他的console wrapper 调用；

因为当时脑残使用了lua作为游戏数据的载入器，配置前需要在机器上装lua。这部分游戏数据载入完全可以不使用lua，改用手写的读取器，json之类，把读取数据的逻辑包含在代码中，简化配置。


## Setup method:

* edit makefile;
* modify the `LUA_LIB_PATH` and `LUA_INCLUDE_PATH` according to the path of lua on your machine.

Then run:

    make all
    sudo make setcopath



