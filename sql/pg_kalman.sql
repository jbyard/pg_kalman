CREATE FUNCTION static_filter(
	observation          DOUBLE PRECISION,
	estimated_variance   DOUBLE PRECISION DEFAULT 0.01
) RETURNS DOUBLE PRECISION AS 'pg_kalman', 'filterStaticSystem'
LANGUAGE C IMMUTABLE;

COMMENT ON FUNCTION static_filter IS
'Filter a simple static system';


CREATE FUNCTION dynamic_filter(
	measurement   DOUBLE PRECISION,
	uncertainty   DOUBLE PRECISION DEFAULT 0.01
) RETURNS DOUBLE PRECISION AS 'pg_kalman', 'filterDynamicSystem'
LANGUAGE C IMMUTABLE;

COMMENT ON FUNCTION static_filter IS
'Filter a one-dimensional, dynamic system';
