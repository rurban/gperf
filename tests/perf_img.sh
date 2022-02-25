#!/bin/sh
# requires plotly
basedir="$(dirname $0)"
VERSION=`${basedir}/../src/gperf --version | head -n1`
if test -z "$PNG"; then
  PNG="size gperf run"
fi

perf_graph()
{
    LOG=$1
    TITLE=$2
    python3 ${basedir}/perf_plot.py "$LOG" "$TITLE"
}

size() {
  perf_graph \
    'size.log' \
    "sizes ($VERSION)"
}

gperf() {
  perf_graph \
    'gperf.log' \
    "compile-times ($VERSION)"
}

run() {
  perf_graph \
    'run.log' \
    "run-times ($VERSION)"
}

for png in $PNG; do
    $png
    test -d ../doc && mv $png.png $png.svg ../doc/
done
