ARG PG_VER=13
FROM postgres:${PG_VER}

ARG PG_VER
RUN apt update
RUN apt install -y -V build-essential make locales locales-all
RUN apt install -y -V postgresql-$PG_VER libpq-dev postgresql-server-dev-$PG_VER
