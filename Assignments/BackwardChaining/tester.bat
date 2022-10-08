del out-long*.txt
del out-short*.txt


for /l %%x in (1, 1, 10) do (
   a test/test%%x.txt
   ren out-long.txt out-long%%x.txt
   ren out-short.txt out-short%%x.txt
   move out-short%%x.txt output
   move out-long%%x.txt output
)
