#!/bin/bash

# A POSIX variable
OPTIND=1         # Reset in case getopts has been used previously in the shell.

# Initialize our own variables:
model="IEEE_13_Node_With_Houses.glm"
GLD="http://localhost:6267"
object="waterheater15"
property="water_demand"
unit="gpm"
short_sleep=2
long_sleep=5

show_help() {
    echo "Usage: ./test.sh -m <model file> -o <object name> -p <property name> -u <units>"
    echo "       ./test.sh -m IEEE_13_Node_With_Houses.glm -o house15 -p heating_setpoint -u degF"
}

while getopts "h?m:o:p:u:" opt; do
    case "$opt" in
    h|\?)
        show_help
        exit 0
        ;;
    m)  model=$OPTARG
        ;;
    o)  object=$OPTARG
        ;;
    p)  property=$OPTARG
        ;;
    u)  unit=$OPTARG
        ;;
    esac
done

shift $((OPTIND-1))

[ "$1" = "--" ] && shift

# start GLD child process in real-time server mode
#gridlabd -D run_realtime=1 Market_Controller_House_example.glm --server &
gridlabd -D run_realtime=1 $model --server &

PID=$!

# wait for GLD to start up
sleep ${short_sleep}

# Show control interface testing
./gridlabd_interface ${GLD}/control/pauseat=2015-12-10 12:32:59 CST
sleep ${long_sleep}
./gridlabd_interface ${GLD}/control/resume
sleep ${long_sleep}
./gridlabd_interface ${GLD}/control/pauseat=2015-12-10 15:16:17 CST
sleep ${long_sleep}
./gridlabd_interface ${GLD}/control/resume

# Show global variable GET
./gridlabd_interface ${GLD}/execdir
sleep ${short_sleep}
./gridlabd_interface ${GLD}/starttime
sleep ${short_sleep}
./gridlabd_interface ${GLD}/stoptime
sleep ${short_sleep}

# Show object property GET and SET
./gridlabd_interface ${GLD}/${object}/${property}=50${unit}
sleep ${short_sleep}
./gridlabd_interface ${GLD}/${object}/${property}
sleep ${short_sleep}
./gridlabd_interface ${GLD}/${object}/${property}=40${unit}
sleep ${short_sleep}
./gridlabd_interface ${GLD}/${object}/${property}

sleep ${short_sleep}

killall gridlabd.bin
