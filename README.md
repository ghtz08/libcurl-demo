# CURL Demo

[libcurl](https://curl.se/libcurl/c/) 的 demo。

## build

```shell
mkdir build && cd build
cmake .. && cmake --build .
```

> 在 cmake 时可通过 `-DCURL_DIR=<libcurl dir>` 来指定 libcurl 的路径。
