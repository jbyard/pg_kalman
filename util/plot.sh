#! /bin/bash
#
# plot.sh - Plot a graph of the example SQL 

psql -c "
COPY (
	WITH noisy_data AS (
		SELECT
			time,
			2                    AS truth,
			normal_rand(1,2,1)   AS raw
		FROM generate_series(1,60) AS time
	)
	SELECT
		time,
		truth,
		raw,
		filter(raw,1) AS estimation
	FROM noisy_data
) TO '/tmp/example.csv' WITH (FORMAT CSV, HEADER)
"

gnuplot -p -e "\
	set terminal png size 800,300 background rgb '#FFFFFF';\
	set key textcolor rgb '#46444D';\
	set output '/var/www/html/img/example.png';\
	set datafile separator ',';\
	set key below autotitle columnhead;\
	plot \
	'/tmp/example.csv' using 1:2 with line lw 3 lt rgb '#CCCCCC',\
	'/tmp/example.csv' using 1:3 with points ls 3 lt rgb '#6D9DC2',\
	'/tmp/example.csv' using 1:4 with line lw 5 lt rgb '#C175BB';"
