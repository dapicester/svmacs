#!/bin/bash
# test-svmacs.sh: script for testing the svmacs system

JACKD_OPTIONS="-r -dalsa -dhw:0 -r22050 -p1024 -n3 -s -Xseq"
JACKD_LOG="jackd.log"

SVMACS_LOG="svmacs.log"

MPLAYER_OPTIONS="-ao jack"
MPLAYER_LOG="mplayer.log"
TEST_FILE="online-5db.wav"

# 1. start jackd
echo -n " * starting jackd ... "
jackd $JACKD_OPTIONS > $JACKD_LOG 2> $JACKD_LOG &
echo "done"

sleep 5

# 2. start svmacs
echo TODO

# 3. play test file using mplayer
echo -n " * playing test file using mplayer ... "
mplayer $MPLAYER_OPTIONS $TEST_FILE > $MPLAYER_LOG 2> $MPLAYER_LOG 

# 4. manage connections
playback="system:playback_1"
mplayer="$(jack_lsp | grep -i MPlayer)"
svmacs_input="svmacs:input0"
svmacs_output="svmacs:output0"

echo -n " * connecting ... "
#jack_disconnect $mplayer $playback
jack_connect $svmacs_input $mplayer

# 5. cleanup
echo -n "stopping jackd ... "
killall $JACKD
echo "done"

