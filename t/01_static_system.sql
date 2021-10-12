BEGIN;
SELECT plan(2);


SELECT is((
	SELECT filter(1) < 1
),TRUE,'Variance/gain is applied to a single observation.');

SELECT is((
	SELECT filter(-1) < 0
),TRUE,'Observations and estimations can be negative.');


SELECT * FROM finish();
ROLLBACK;
