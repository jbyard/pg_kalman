BEGIN;
SELECT plan(3);


SELECT is((
	SELECT filter(1) < 1
),TRUE,'Variance/gain is applied to a single observation.');

SELECT is((
	SELECT filter(-1) < 0
),TRUE,'Observations and estimations can be negative.');

SELECT is((
	SELECT MAX(filter(x)) > avg(x)
	FROM generate_series(1,10) AS x
),FALSE,'Estimation is not above the mean.');


SELECT * FROM finish();
ROLLBACK;
