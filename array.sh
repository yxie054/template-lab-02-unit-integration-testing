#!/bin/sh

INPUTS=("first input" "second input" "third input")

for input in "${INPUTS[@]}"
do
    echo "./c-echo ${input}"
    output=$(./c-echo ${input})
    if [ "${output}" = "${input}" ]
    then
        echo "Test passed"
    else
        echo "Test failed"
	echo "Expected: \"${input}\""
        echo "Received: \"${output}\""
    fi
done
