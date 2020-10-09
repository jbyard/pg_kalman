# pg_kalman

A Kalman filter extension for PostgreSQL.

```sql
WITH observations AS (
	SELECT generate_series(1,10) AS point
)
SELECT point, filter(point)
FROM observations;

 point |      filter
-------+------------------
     1 |                0
     2 | 1.99009895324707
     3 | 2.99502491950989
     4 |  3.9966778755188
     5 |  4.9975061416626
     6 | 5.99800395965576
     7 | 6.99833583831787
     8 | 7.99857330322266
     9 | 8.99875164031982
    10 |  9.9988899230957
```

## Tests

Test coverage depends on these great projects: 

* [pg_tap](https://pgtap.org/)
* [pg_tmp](http://eradman.com/ephemeralpg/)

## Authors

* **Josh Byard** - *Initial work* - [jbyard](https://github.com/jbyard)
