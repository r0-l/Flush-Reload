# Calibration
Here you can find the source code needed to calibrate the number of cycles needed to fetch data from the cache and the main memory.

From these data, you can find the threshold under which you can tell if a data has been fetched from the cache or the main memory.

The program outputs the data as CSV to `stdout`. Additional informations such as the suggested threshold are available on `stderr`.

You can plot the data using gnuplot with the following commands:

```bash
$ ./calibration > stats.csv

$ gnuplot

gnuplot> set datafile separator ','
gnuplot> plot 'stats.csv' using 1:2 with lines title 'From cache', 'stats.csv' using 1:3 with lines title 'From main memory'
```
