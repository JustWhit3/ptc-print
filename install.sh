#!/bin/bash

#====================================================
#     OS-SPECIFIC INFORMATION
#====================================================
UNAME=$(uname)
if [[ "$UNAME" == Darwin* ]] ; then
    INCL=/usr/local/include
elif [[ "$UNAME" == Linux* ]] ; then
    INCL=/usr/include
else
    read -p "Insert the system include path in which you want to install ptc::print and its dependencies headers: " word_include
        mkdir -p "${word_include}"
        INCL=${word_include}
fi

#====================================================
#     INSTALLING PREREQUISITES
#====================================================

# Installing prerequisite packages
echo "Updating and upgrading the system..."
if [[ "$UNAME" == Darwin* ]] ; then
    brew install gcc cmake
elif [[ "$UNAME" == Linux* ]] ; then
    sudo apt install build-essential g++
else
    read -p "Which package-manager do you want to use? (pacman/chocolately) " word_pkg
    if [ "$word_pkg" == "pacman" ] || [ "$word_pkg" == "Pacman" ] ; then
        pacman -S wget unzip cmake
    elif [ "$word_pkg" == "chocolately" ] || [ "$word_pkg" == "Chocolately" ] || [ "$word_pkg" == "choco" ] ; then
        choco install wget unzip cmake
    else
        echo "Inserted package-manager $word_pkg is not supported!"
        exit
    fi
fi
echo ""

# Installing optional packages
read -p "Do you want to install ptc::print optional prerequisites for developers (y/n)? " word_o
if [ "$word_o" == "y" ] || [ "$word_o" == "Y" ] ; then
    if [[ "$UNAME" == Darwin* ]] ; then
        brew install doctest cppcheck clang-format valgrind
    elif [[ "$UNAME" == Linux* ]] ; then
        sudo apt install doctest-dev valgrind cppcheck clang-format
    else
        wget https://github.com/doctest/doctest/archive/refs/heads/master.zip
        unzip master.zip
        rm master.zip
        mkdir -p "${INCL}/doctest"
        cp "doctest-master/doctest/doctest.h" "${INCL}/doctest"
        rm -rf doctest-master
    fi
fi
echo ""

#====================================================
#     SAVING FILES INTO THE SYSTEM
#====================================================
if [[ "$UNAME" == Darwin* || "$UNAME" == Linux* ]] ; then
    sudo echo "Installing ptc::print header into ${INCL} folder..."
    if ! ( sudo cp -r include/ptc "${INCL}") ; then
        echo "Cannot install the header file into ${INCL} position of the system!"
    fi
else
    echo "Installing ptc::print header files into ${INCL}..."
    if ! ( cp -r include/ptc "${INCL}" ) ; then
        echo "Cannot install the header file into ${INCL} position of the system!"
    fi
fi
echo "Installation has been completed!"