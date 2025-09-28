# Program running order
    1. generateArrays.cpp this will generate random arrays of different sizes. Do not run it again after generating the random arrays. It will overwrite the previously generated arrays.
    2. sortedReverseSorted.cpp this will generate sorted and reverse sorted arrays from the random arrays. 
    3. analysis.cpp this will test the algorithms on random, sorted and reverse sorted arrays. It will run each iteration 3 times and take the average. It will generate 3 .csv file for each algorithm(random, sorted, reverse sorted). Save the generated csv files in a different folder once done. If you accidently run it again it will overwrite over all the privious data. It took 3-4 hours on my laptop. Don't make this mistake!!!(Ask me how I know)
    4. Plot the graph using .csv files.  

## Note
* Don't run insertion sort and bubble sort for large number of elements. Keep it below 20000.
* Don't run quick sort last element as pivot and first element as pivot on sorted and reverese sorted arrays for large number of elements(worst cases).
* Just go through the analysis.cpp once before running it.
* Don't use your laptop/pc when analysis.cpp is running.
* There's sample data if you want to see how the results looks. 