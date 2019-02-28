#!/bin/bash

params=$@

for (( i=201; i <= 203 ; i = $i + 1)) ; do
    echo ============= s$i $params ============
    ssh s$i $params
done
