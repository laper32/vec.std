Build Status: [![Build Status](https://travis-ci.com/laper32/vec.std.svg?token=PB3yxB8sGmPykRb8qwqc&branch=master)](https://travis-ci.com/laper32/vec.std)
# ����
CSGO�˱�׼��

������������Linux��Windows��ͨ��

# ���ع���
- �ҵ�һ�����ʵĵط�, ����������ָ��:
> ����ʹ�õ���SSH, ʹ��ǰע���Ƿ����úù�Կ˽Կ
```
git clone git@github.com:laper32/vec.std.git --recursive
```

- �л���repo�ļ�����, ���½�build�ļ���
```
mdkir build
cd build
```

- �л���build�ļ�����

- ���ñ�����Ϣ(Windows������ָ��MSVC, Linux������ָ��GCC)
> Ŀǰ��ʱֻʾ��MSVC

```
cmake -G "Visual Studio 16 2019" -A Win32 ../
```

- ��ʼ����
> ֻ����release�汾
```
cmake --build . --config Release
```

# ���ɹ���
�ⲿ�ֽ��ɱ�����������, ������ǲ���Ҫ��ȥ���ǵ�