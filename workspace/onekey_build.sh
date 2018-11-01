#!/bin/bash

cd ../
git pull

if  [ $1x = 'debugx' ]
then        
   flag='-DCMAKE_BUILD_TYPE=Debug'
else
   flag='-DCMAKE_BUILD_TYPE=Release'
fi

cd workspace/buildc/
cmake $flag ../../code
make