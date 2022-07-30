#!/bin/bash
if make ; then
    echo "Build succeded"
    ./bin/Example_Debug/Example
else
    echo "Build did not succeed"
fi
