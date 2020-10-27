# pg_kalman

A Kalman filter extension for PostgreSQL.

```sql
WITH noisy_data AS (
	SELECT
		to_char(day,'YYYY_MM_DD')   AS time,
		normal_rand(1,3,1)          AS raw
	FROM generate_series(
		NOW() - '30 days'::interval,
		NOW(),
		'1 day'::interval) day
)
SELECT
	time, raw, filter(raw,2)
FROM noisy_data
```
![static system example](example.png)

## Tests

Test coverage depends on these great projects: 

* [pg_tap](https://pgtap.org/)
* [pg_tmp](http://eradman.com/ephemeralpg/)

## Authors

* **Josh Byard** - *Initial work* - [jbyard](https://github.com/jbyard)
