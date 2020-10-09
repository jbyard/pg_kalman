BEGIN;

SELECT plan(1);

SELECT isnt((
	WITH observations AS (
		SELECT generate_series(1,10) AS point
	) SELECT MAX(filter(point)) FROM observations
),NULL,'Does filter() return something, anything');

SELECT * FROM finish();
ROLLBACK;
