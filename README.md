# Introduction

owebpp is a c++ 20 web framework. The project is currently in development, suggestions are welcome !
The framework has a code generator that is used to do the link between its own code and yours, see examples.

# Build

## Linux

While we use cmake to allow for cross platform build, the only platform that has been tested currently is *g++ 11.4.0 on Ubuntu 22.04.2*. The project also requires support for c++20. The following commands allow to build/deploy the library as well as the code generator. Examples require additionnal configuration.

```sh
sudo apt install cmake g++ git libpcre3-dev libpcre++-dev zlib1g-dev

# Execute this line if you plan to build the documentation
sudo apt-get install doxygen

git clone --depth 1 --branch 0.8.0 https://github.com/jbeder/yaml-cpp.git
cd yaml-cpp
cmake .
make
sudo make install
git clone https://github.com/Tahkyon/owebpp.git
cd owebpp
///# You can also use cmake . -DDISABLE_METADATA_LOG=On to disable logging of the metadata (file, function name, line and column since it might contain sensitive information.
cmake .
make
sudo make install

#Build documentation if needed.
cmake --build . --target owebpp-doc-gen
```

# Examples

## Nginx library

This example uses the nginx link function library to call your app (shared library) from nginx

```sh
# We assume that we start executing the following commands from the owebpp directory
cd ../
git clone --depth 1 --branch 3.2.4 https://github.com/Taymindis/nginx-link-function.git
cd ginx-link-function
sudo install -m 644 nginx-link-function/src/ngx_link_func_module.h /usr/local/include/
cd ..
wget 'http://nginx.org/download/nginx-1.25.2.tar.gz'
tar -xzvf nginx-1.25.2.tar.gz
cd nginx-1.25.2/
./configure --add-module=../nginx-link-function
make
sudo make install

# When building a different platform  than unix you might want to change the path src/os/unix/*.h to the appropriate value
sudo find src/core/*.h src/event/*.h src/event/modules/*.h src/event/quic/*.h src/os/unix/*.h objs/*.h src/http/*.h src/http/modules/*.h /usr/local/include -name "*.h" -exec install -m 664 {} /usr/local/include \;

cd ../owebpp/example/nginx
cmake .
make
sudo make install

# Launch nginx in the background with the configuration deployed by make install
# By default the nginx conf uses port 8888
sudo /usr/local/nginx/sbin/nginx -c /usr/local/etc/owebpp-example-lib-nginx/nginx.conf

# This command allows you to easily kill all the processes listening on the port 8888 for test purpose
sudo lsof -t -i:8888 -sTCP:LISTEN | sudo xargs kill

# In case you face problems when using the example, nginx logs can be found in /usr/local/nginx/logs/ and the library logs are in /var/log/libnginx.log
```