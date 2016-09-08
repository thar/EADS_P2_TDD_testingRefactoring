#!/bin/bash - 

pushd build/tests/
./AnalizadorTests --gtest_output=xml:XML_Report.xml
popd
