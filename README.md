# pg_kalman

A simple [Kalman filter](https://en.wikipedia.org/wiki/Kalman_filter) extension
for PostgreSQL.  Mostly just for fun.

```sql
/* Filter some noisy data generated from a true value. */
WITH noisy_data AS (
	SELECT
		to_char(day,'YYYY_MM_DD')   AS time,
		normal_rand(1,2.13,1)       AS raw
	FROM generate_series(
		NOW() - '30 days'::interval,
		NOW(),
		'1 day'::interval) day
)
SELECT
	time             AS time,
	2.13             AS truth,
	raw              AS raw,
	filter(raw, 1)   AS filtered
FROM noisy_data
```
![static system example](example.png)

## Installing

Build and install the extension.

```bash
make; sudo make install
```

Add `pg_kalman` to your postgres server's `shared_preload_libraries`
configuration and restart the service.

Then create the extension in your postgres client.

```sql
CREATE EXTENSION pg_kalman
```

## Tests

Test coverage depends on these great projects: 

* [pg_tap](https://pgtap.org/)
* [pg_tmp](http://eradman.com/ephemeralpg/)

## Authors

* **Josh Byard** - *Initial work* - [jbyard](https://github.com/jbyard)
