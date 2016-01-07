#!/bin/bash

model=$1

GLD=http://localhost:6267

# start GLD child process in real-time server mode
#gridlabd -D run_realtime=1 Market_Controller_House_example.glm --server &
gridlabd -D run_realtime=1 $model --server &

PID=$!

# wait for GLD to start up
sleep 1

# Show control interface testing
./gridlabd_interface ${GLD}/control/pauseat=2015-12-10 12:32:59 CST
sleep 5
./gridlabd_interface ${GLD}/control/resume
sleep 5
./gridlabd_interface ${GLD}/control/pauseat=2015-12-10 15:16:17 CST
sleep 5
./gridlabd_interface ${GLD}/control/resume

# Show global variable GET
./gridlabd_interface ${GLD}/execdir
sleep 2
./gridlabd_interface ${GLD}/starttime
sleep 2
./gridlabd_interface ${GLD}/stoptime
sleep 2

# Show object property GET and SET
./gridlabd_interface ${GLD}/Market_1/current_price_mean_30min=50
sleep 2
./gridlabd_interface ${GLD}/Market_1/current_price_mean_30min
sleep 2
./gridlabd_interface ${GLD}/Market_1/current_price_mean_30min=40
sleep 2
./gridlabd_interface ${GLD}/Market_1/current_price_mean_30min

sleep 5

killall gridlabd.bin
