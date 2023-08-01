/******************************************
 * DESCRIBE: static_filter() functionality
 ******************************************/

BEGIN;
SELECT plan(7);


/****************************************
 * BEFORE TEST: Generate mock data
 ****************************************/

-- Generate 1 table with noisy data
CREATE TABLE IF NOT EXISTS static_filter_test AS (
	SELECT
		time,
		2                    AS truth,
		normal_rand(1,2,1)   AS measurement
	FROM generate_series(1,60) AS time
);


/****************************************
 * TEST EXECUTION: Run scenarios
 ****************************************/

-- SCENARIO 1: Single Obervation
---- GIVEN: The static_filter() function is triggered
---- WHEN: The required `observation` parameter is provided
---- THEN: The function should run with provided parameters and return expected values

-- IT: Should apply variance/gain to the observation
SELECT is((
	SELECT static_filter(1) < 1
),TRUE,'Postive observation');

SELECT is((
	SELECT static_filter(-1) < 0
),TRUE,'Negative observation');

-- IT: Should return 0 for a NULL observation
SELECT is((
	SELECT static_filter(NULL)
),0::DOUBLE PRECISION,'NULL observation');


-- SCENARIO 2: Variance
---- GIVEN: The static_filter() function is triggered
---- WHEN: The optional `estimated_variance` parameter is provided
---- THEN: The function should run with provided parameters and return expected values

-- IT: Should apply the variance to the observation
SELECT is((
	SELECT static_filter(1, 0)
),1::DOUBLE PRECISION,'Variance of 0');

SELECT is((
	SELECT static_filter(1, 1)
),0.5::DOUBLE PRECISION,'Variance of 1');


-- SCENARIO 3: Multiple Observation Estimations

---- GIVEN: The static_filter() function is triggered
---- WHEN: Multiple records are used for the `observation` parameter 
---- THEN: The function should run with provided parameters and return expected values

-- IT: Should not die outright
SELECT lives_ok($$
	SELECT static_filter(measurement) FROM static_filter_test
$$,'Multiple records');

-- IT: Should return better estimations given more observations 
SELECT cmp_ok((
	/* First estimate */
	WITH errors (t, e) AS (
		SELECT time, abs(truth - static_filter(measurement))
		FROM static_filter_test
	)
	SELECT e FROM errors
	ORDER BY t LIMIT 1
),'>',(
	/* Last estimate */
	WITH errors (t, e) AS (
		SELECT time, abs(truth - static_filter(measurement))
		FROM static_filter_test
	)
	SELECT e FROM errors
	ORDER BY t DESC LIMIT 1
),'Estimations get better');


/****************************************
 * AFTER TEST: Finish and rollback
 ****************************************/

SELECT * FROM finish();
ROLLBACK;
