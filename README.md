# CSPB2270 Data Structures Final Project

## Student Information
- **Name:** `Yujie "Malik" Zhang`
- **CU ID:** `mazh8442`

## Project Overview

This project implements a **radix tree** in **C++** to store [**53,373 English words**](https://github.com/ps-kostikov/english-word-frequency/blob/master/data/frequency_list.txt), each associated with a frequency value. The primary application of this data structure is to provide **word suggestions or auto-corrections** based on user input.

### Functionality

- The radix tree supports efficient prefix searches to suggest relevant words.
- Suggestions are ranked by frequency, ensuring the most common words appear first.

### Web Integration

To demonstrate this functionality:

- The project uses the [**`httplib`**](https://github.com/yhirose/cpp-httplib) library to host a lightweight **C++ HTTP server**.
- A **simple frontend** with a search bar captures user input in real-time.
- The input is sent to the C++ backend via HTTP.
- The backend returns the **top 3 word suggestions** based on frequency.
- Suggestions are displayed in an **HTML `<select>` menu** for user interaction.

## How to Build and Run The Project

### Prerequisites:

> **Note:** All command line instructions below are for **Linux**.  
> For **Windows** or **macOS**, please refer to your platform’s method for installing the listed prerequisites.

#### Set Up for Backend (c++ program):

##### 1. CMake (Build system generator)

```bash
sudo apt-get update
sudo apt-get install -y cmake
```
##### 2. C++ Build Tools (e.g., Make, GCC)
```bash
sudo apt-get install -y build-essential
```
##### 3. Vcpkg (C++ package manager)
###### **First, install dependencies:**
```bash
sudo apt-get install -y pkg-config
sudo apt-get install -y curl
```
###### **Then, clone and bootstrap vcpkg:**
```bash
cd ~/  # or any directory you prefer
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
```
###### **Set the `VCPKG_ROOT` environment variable (persists through all future terminal sessions)**:
```bash
echo "export VCPKG_ROOT=path/to/vcpkg" >> ~/.bashrc
```
###### **Now please restart your terminal for the environment variable to be recognized by the bash shell.**

#### Set Up for frontend (built with next.js framwork):
##### 1. Remove any existing versions of Node.js and npm:
```bash
sudo apt purge nodejs npm
```
##### 2. Install node.js using nvm 
>This is to ensure we have the latest node.js version, as older node.js version may not support all syntaxes used by next.js
```bash
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.33.8/install.sh | bash
source ~/.bashrc  # or restart your terminal
nvm install node
```

### Steps to Build and Run
#### First, clone the github repository to your local machine and go to the project directory
```bash
git clone https://github.com/MalikHack007/Radix-Tree-CSPB2270.git
cd Radix-Tree-CSPB2270
```
#### To Build and Run Backend:
```bash
mkdir build
cmake --preset debug
cmake --build build/
cd build
./run_app
```
>Note that with multi-config generators like Visual Studio 17 2022, the executable will be stored under a folder named after the name of the configuration. In that case, simply go to the folder for the debug configuration and you should be able to find the .exe or binary file run_app.

#### To Run the Front End:
```bash
cd "../FRONT END/radix-tree-front-end" #go to the FRONT END/radix-tree-front-end directory
npm install
npm run dev
```
##### Now you can go to localhost:3000 (or specified in your terminal) to load the front end.

## What does it do?

The app has just one simple functionality: as you type in the input field on the front-end webpage, it continuously provides the top 3 word suggestions. It only suggests one word at a time. For example, if you've already typed "existing word" and want to continue typing more words, just separate them with a space — the app will then offer suggestions for the current word you're typing.

