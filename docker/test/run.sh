#!/bin/sh
#
# run.sh
#
# Run pg_kalman tests

make install &&
su postgres -c "initdb $PGDATA" && \
su postgres -c "pg_ctl -D $PGDATA start" &&\
pg_prove -Upostgres t/*.sql
