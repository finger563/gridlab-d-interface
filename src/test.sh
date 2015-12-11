#!/bin/bash

GLD=http://localhost:6267

# Show control interface testing
./gridlabd_interface ${GLD}/control/pauseat=2015-12-10
sleep 10
./gridlabd_interface ${GLD}/control/resume
sleep 10
./gridlabd_interface ${GLD}/control/pauseat=2015-12-10
sleep 10
./gridlabd_interface ${GLD}/control/resume

# Show global variable GET
./gridlabd_interface ${GLD}/execdir
sleep 1

# Show object property GET and SET
./gridlabd_interface ${GLD}/Market_1/current_price_mean_30min=50
sleep 1
./gridlabd_interface ${GLD}/Market_1/current_price_mean_30min
sleep 1
./gridlabd_interface ${GLD}/Market_1/current_price_mean_30min=40
sleep 1
./gridlabd_interface ${GLD}/Market_1/current_price_mean_30min
