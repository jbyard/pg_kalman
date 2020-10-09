CREATE EXTENSION pgtap;

CREATE EXTENSION pg_kalman;

SELECT plan(1);
SELECT pass('prep ran');
SELECT * FROM finish();
