## Table of Contents
- [Introduction](#introduction)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction
Memory Match is a fun and engaging game where players must match pairs of cards. This project is a C++ implementation of the classic game.

## Installation
To compile the game, follow these steps(On linux):

1.  Install the dependencies
```sudo apt update
    sudo apt install \
    libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libfreetype-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev
```

2. Clone the repository:
    ```sh
    git clone https://github.com/nanda-gopal-sb/memory-match.git
    ```
3. Navigate to the project directory:
    ```sh
    cd memory-match
    ```
4. Compile the project using CMake:
    ```sh
    cmake -B build
    cmake --build build
    ```

## Usage
To play the game, run the following command:
```sh
./build/memory-match
```

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.