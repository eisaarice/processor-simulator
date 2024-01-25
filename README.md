# processor-simulator
This is a two part C++ project where one program is desgined to create and organize a file containing 10000 random jobs and the second program will use that file as input to simulate how an prompted # of processors will schedule those jobs (up to 8 processors recommended).

Each folder, "Simulator" and "File Generator", is a separate C++ project created in Visual Studio. You should be able to open those folders separately within VS and run them.
After the first program finishes running, you will need to take the org.dat file from its solution folder and paste in in the simulator's folder.
Then,  using on the data provided within the organized file, the simulation will run as the CPU will recieve the 10000 jobs with varying arrival, response, and completion times.
A real-time text log of the jobs and their corresponding details is written up while the same information is simultaneously displayed to the console during runtime.
