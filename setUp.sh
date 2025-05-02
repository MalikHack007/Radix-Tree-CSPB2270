#!/bin/bash

# Check for CMake and install if not present
if ! command -v cmake &> /dev/null; then
    echo "CMake not found. Installing..."
    sudo apt-get update
    sudo apt-get install -y cmake
else
    echo "CMake is already installed."
fi

# Check for npm and install if not present
if ! command -v npm &> /dev/null; then
    echo "npm not found. Installing Node.js and npm..."
    sudo apt-get update
    sudo apt-get install -y nodejs npm
else
    echo "npm is already installed."
fi

# Check for vcpkg and install if not present
if [ ! -d "vcpkg" ]; then
    echo "Cloning vcpkg repository..."
    git clone https://github.com/microsoft/vcpkg.git
    cd vcpkg
    ./bootstrap-vcpkg.sh
    cd ..
else
    echo "vcpkg is already installed."
fi

# Install jsoncpp via vcpkg
echo "Installing jsoncpp via vcpkg..."
./vcpkg/vcpkg install jsoncpp

# Set VCPKG_ROOT environment variable
echo "Setting VCPKG_ROOT environment variable..."
echo "export VCPKG_ROOT=$(pwd)/vcpkg" >> ~/.bashrc
source ~/.bashrc


echo "Setup complete! You can now build your project."
