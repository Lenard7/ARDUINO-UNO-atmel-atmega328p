#!/bin/bash

echo "Removing building artifacts from the project."

# check if build folder exists, if it does, remove it
if [ -d "build" ]; then
    echo "Removing build folder."
    rm -r "./build"
    else
    echo "Build folder does not exist. Nothing to be cleaned."
fi
