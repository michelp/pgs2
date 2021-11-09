#!/bin/bash

DB_HOST="pgpgs2-test-db"
DB_NAME="postgres"
SU="postgres"
EXEC="docker exec $DB_HOST"
EXECIT="docker exec -it $DB_HOST"

echo force rm previous container
docker rm -f pgpgs2-test

set -e

echo building test image
docker build . -t pgpgs2/test

echo running test container
docker run -v $(pwd)/tests/:/tests --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -d --name "$DB_HOST" pgpgs2/test

$EXECIT pg_ctl start
# $EXEC make clean
# $EXEC make install

echo waiting for database to accept connections
until
    $EXEC \
	    psql -o /dev/null -t -q -U "$SU" \
        -c 'select pg_sleep(1)' \
	    2>/dev/null;
do sleep 1;
done


if [ $# -eq 0 ]
then
    echo running tests
    $EXEC tmux new-session -d -s pgpgs2 
    $EXECIT tmux attach-session -t pgpgs2
else
    echo running repl
    $EXEC tmux new-session -d -s pgpgs2 $*
    $EXECIT tmux attach-session -t pgpgs2
fi

echo destroying test container and image

docker rm --force "$DB_HOST"
