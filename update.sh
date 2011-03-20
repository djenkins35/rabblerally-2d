#!/bin/bash

git push beagle master

FILES=b2d_racing_server.cpp io testData xml Makefile
rsync -avP -e 'ssh -oPort=2222' $FILES dummy@192.168.5.223:/home/dummy/dev/b2d.racing.server

