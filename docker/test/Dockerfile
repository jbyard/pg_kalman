ARG PG_VER=13
FROM pg_kalman_build

ARG PG_VER
RUN apt install -y -V postgresql-$PG_VER-pgtap

COPY docker/test/run.sh /run.sh
CMD /run.sh
