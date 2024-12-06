The folder "INSTANCES" contains the 24 instances used to test the two proposed encodings.
To test the two proposed models on six easy instances, run "./esegui.sh" on bash shell.
This script will generate 6 instances in six different folders with names
starting with "inst" and will automatically run the solver "clingo" on these instances, 
saving the results into a file called "result.txt". To test the MiniZinc model, take the instances generated and manually run them in MiniZinc.
