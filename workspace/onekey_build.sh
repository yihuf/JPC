#!/bin/bash

cd ../
git pull

cd workspace/buildc/
cmake ../../code
make