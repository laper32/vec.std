Build Status: [![Build Status](https://travis-ci.com/laper32/vec.std.svg?token=PB3yxB8sGmPykRb8qwqc&branch=master)](https://travis-ci.com/laper32/vec.std)
# 介绍
CSGO端标准库

最终是期望在Linux和Windows上通用

# 本地构建
- 找到一个合适的地方, 并输入以下指令:
> 我们使用的是SSH, 使用前注意是否配置好公钥私钥
```
git clone git@github.com:laper32/vec.std.git --recursive
```

- 切换到repo文件夹内, 并新建build文件夹
```
mdkir build
cd build
```

- 切换到build文件夹内

- 配置编译信息(Windows环境下指定MSVC, Linux环境下指定GCC)
> 目前暂时只示例MSVC

```
cmake -G "Visual Studio 16 2019" -A Win32 ../
```

- 开始编译
> 只编译release版本
```
cmake --build . --config Release
```

# 集成构建
这部分交由编译服务器完成, 大概率是不需要你去考虑的