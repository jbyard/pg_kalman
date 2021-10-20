#! /bin/bash
#
# plot.sh - Plot a graph of the example SQL 

# Static System Filter
psql -c "
COPY (
	WITH noisy_data AS (
		SELECT
			t                    AS time,
			2                    AS truth,
			normal_rand(1,2,1)   AS measurement
		FROM generate_series(1,60) AS t
	)
	SELECT
		time,
		truth,
		measurement,
		static_filter(measurement,1) AS estimation
	FROM noisy_data
) TO '/tmp/static.csv' WITH (FORMAT CSV, HEADER)
"

gnuplot -p -e "\
	set terminal png size 800,300 background rgb '#FFFFFF';\
	set key textcolor rgb '#46444D';\
	set output '/var/www/html/img/static.png';\
	set datafile separator ',';\
	set key below autotitle columnhead;\
	set title 'Static System Estimation';\
	plot \
	'/tmp/static.csv' using 1:2 with line lw 3 lt rgb '#CCCCCC',\
	'/tmp/static.csv' using 1:3 with points ls 3 lt rgb '#6D9DC2',\
	'/tmp/static.csv' using 1:4 with line lw 5 lt rgb '#C175BB';"


# Dynamic System Filter
psql -c "
COPY (
	WITH noisy_data AS (
		SELECT
			t                          AS time,
			(t*0.1)                    AS truth,
			normal_rand(1,(t*0.1),1)   AS measurement
		FROM generate_series(1,60) AS t
		UNION
		SELECT
			t                                   AS time,
			(t*0.1)+(t-61)                      AS truth,
			normal_rand(1,((t*0.1)+(t-61)),1)   AS measurement
		FROM generate_series(61,120) AS t
	)
	SELECT
		time,
		truth,
		measurement,
		dynamic_filter(measurement,1) AS estimation
	FROM noisy_data
) TO '/tmp/dynamic.csv' WITH (FORMAT CSV, HEADER)
"

gnuplot -p -e "\
	set terminal png size 800,300 background rgb '#FFFFFF';\
	set key textcolor rgb '#46444D';\
	set output '/var/www/html/img/dynamic.png';\
	set datafile separator ',';\
	set key below autotitle columnhead;\
	set title 'Dynamic System Estimation';\
	plot \
	'/tmp/dynamic.csv' using 1:2 with line lw 3 lt rgb '#CCCCCC',\
	'/tmp/dynamic.csv' using 1:3 with points ls 3 lt rgb '#6D9DC2',\
	'/tmp/dynamic.csv' using 1:4 with line lw 5 lt rgb '#C175BB';"
