#!/bin/bash
# Basic if statement
export KMC_ROOT=$PWD
if [[-z $KMC_ROOT]]; then
    echo "please define KMC"
    exit 1
fi 
dir=$(echo "$@" | tr a-z A-Z); 
# model_name_lower=$(echo "$@" | tr A-Z a-z); 
model_name_lower=$(echo "$@" | tr A-Z a-z) 
echo $dir
mkdir -p $KMC_ROOT/$dir/include $KMC_ROOT/$dir/src
touch $KMC_ROOT/$dir/Makefile
touch $KMC_ROOT/$dir/include/"$model_name_lower.hpp"
touch $KMC_ROOT/$dir/src/"$model_name_lower.cc"