EXTENSION   = pg_kalman
SQL         = sql/pg_kalman.sql
VERSION     = 0.1

PG_CONFIG           :=   pg_config
PG_BIN              :=   $(shell $(PG_CONFIG) --bindir)
PG_EXTENSION        :=   $(shell $(PG_CONFIG) --sharedir)/extension
PG_INCLUDE          :=   $(shell $(PG_CONFIG) --includedir)
PG_LIB              :=   $(shell $(PG_CONFIG) --pkglibdir)
PG_SERVER_INCLUDE   :=   $(shell $(PG_CONFIG) --includedir-server)

export PATH := $(PG_BIN):$(PATH)

OBJ_DIR   = obj
SRC_DIR   = src
T_DIR     = t

SRC       := $(wildcard $(SRC_DIR)/*.c)
OBJ       := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TESTS     := $(sort $(wildcard $(T_DIR)/*.sql) )

CFLAGS += -fPIC -Wall -O3 -shared -std=gnu99
CFLAGS += -Iinclude -I$(PG_INCLUDE) -I$(PG_SERVER_INCLUDE) -I/usr/local/include

.PHONY: all build clean install test

all: $(EXTENSION).so

$(EXTENSION).so: $(OBJ)
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o$@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

build:
	docker-compose --profile build up && docker-compose down

clean:
	docker-compose down
	for f in build demo test; do docker image rm -f $(EXTENSION)_$$f; done
	docker volume rm $(EXTENSION)_data
	$(RM) $(OBJ) $(EXTENSION).so
	$(RM) -r $(OBJ_DIR)

demo: build test
	docker-compose --profile demo up && docker-compose down

install:
	chmod 755 $(EXTENSION).so
	mkdir -p $(PG_EXTENSION)
	mkdir -p $(PG_LIB)
	install -c -m 644 $(EXTENSION).control $(PG_EXTENSION)
	install -c -m 644 $(SQL) $(PG_EXTENSION)/$(EXTENSION)--$(VERSION).sql
	install -c -m 755 $(EXTENSION).so $(PG_LIB)

test: build
	docker-compose --profile test up && docker-compose down
