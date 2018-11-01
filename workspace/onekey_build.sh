#!/bin/bash

cd ../
git pull

if [ $1x == 'debugx' ]
then        
   echo 'debug'
else
   echo 'release'
fi

cd workspace/buildc/
cmake ../../code
make